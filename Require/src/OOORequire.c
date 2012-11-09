#include "OOORequire.h"
#include "OOOError.h"

/*
 *
 * Declare private RepositoryData class for loading data from repositories
 *
 */
#define OOOClass RepositoryData
OOODeclare(char * szName, OOORequire * pRequire, OOOIRequireModule * iRequireModule)
	OOOImplements
		OOOImplement(OOOIRepositoryData)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

/*
 *
 * OOORequire implementation
 *
 */
#define OOOClass OOORequire
typedef OOOModule * (* Init)(void);
typedef void (* Uninit)(void);

typedef struct _ModuleEntry ModuleEntry;
struct _ModuleEntry
{
	char * szName;
	unsigned char * pData;
	OOOModule * pModule;
	Uninit uninit;
	ModuleEntry * pNext;
};

OOOPrivateData
	OOOIRepository ** aRepositories;
	size_t uRepositoriesLength;
	ModuleEntry * pModules;
OOOPrivateDataEnd

OOODestructor
{
	ModuleEntry * pEntry = OOOF(pModules);
	ModuleEntry * pLastEntry = NULL;
	while (pEntry)
	{
		pLastEntry = pEntry;
		pEntry = pEntry->pNext;

		if (pLastEntry->uninit)
		{
			pLastEntry->uninit();
		}
		else
		{
			O_debug("WARNING: Code module has no uninit method: %s\n", pLastEntry->szName);
		}

		if (O_dl_unlink_code_module(pLastEntry->pData) != GOOD)
		{
			O_debug("WARNING: Failed to unlink code module: %s\n", pLastEntry->szName);
		}

		O_free(pLastEntry->szName);
		O_free(pLastEntry);
	}
	O_free(OOOF(aRepositories));
}
OOODestructorEnd

OOOMethod(void, error, RepositoryData * pRepositoryData, OOOIRequireModule * iRequireModule, char * szError)
{
	OOOError * pError = OOOConstruct(OOOError, szError);
	OOOICall(iRequireModule, module, OOOCast(OOOIError, pError), NULL);
	OOODestroy(pError);
	OOODestroy(pRepositoryData);
}
OOOMethodEnd

OOOMethod(void, module, RepositoryData * pRepositoryData, OOOIRequireModule * iRequireModule, OOOModule * pModule)
{
	OOOICall(iRequireModule, module, NULL, pModule);
	OOODestroy(pRepositoryData);
}
OOOMethodEnd

OOOMethod(void, link, RepositoryData * pRepositoryData, OOOIError * iError, unsigned char * pData, size_t uSize, OOOIRequireModule * iRequireModule, unsigned int uCount)
{
	OOOModule * pModule = NULL;
	if (iError)
	{
		/* try the next repository if there is one */
		if (uCount < OOOF(uRepositoriesLength))
		{
			OOOICall(OOOF(aRepositories)[uCount], get, OOOCast(OOOIRepositoryData, pRepositoryData));
		}
		else
		{
			OOOC(error, pRepositoryData, iRequireModule, "NOT FOUND IN ANY REPOSITORY");
		}
	}
	else
	{
		if (O_dl_link_code_module(pData) == GOOD)
		{
			Init init = O_dl_find_function(0);
			if (init)
			{
				pModule = init();
				if (pModule)
				{
					ModuleEntry * pEntry = O_malloc(sizeof(ModuleEntry));
					pEntry->pModule = pModule;
					pEntry->pData = pData;
					pEntry->szName = O_strdup(OOOICall(iRequireModule, getName));
					pEntry->uninit = O_dl_find_function(1);
					pEntry->pNext = OOOF(pModules);
					OOOF(pModules) = pEntry;
					OOOC(module, pRepositoryData, iRequireModule, pModule);
				}
				else
				{
					OOOC(error, pRepositoryData, iRequireModule, "INIT METHOD DID NOT RETURN A MODULE");
				}
			}
			else
			{
				OOOC(error, pRepositoryData, iRequireModule, "FAILED TO FIND INIT METHOD");
			}
		}
		else
		{
			OOOC(error, pRepositoryData, iRequireModule, "FAILED TO LINK DLL");
		}
	}
}
OOOMethodEnd

OOOMethod(void, get, OOOIRequireModule * iRequireModule)
{
	OOOModule * pModule = NULL;
	ModuleEntry * pEntry = OOOF(pModules);
	char * szName = OOOICall(iRequireModule, getName);
	while (pEntry)
	{
		if (O_strcmp(pEntry->szName, szName) == 0)
		{
			pModule = pEntry->pModule;
			break;
		}
		pEntry = pEntry->pNext;
	}

	if (pModule)
	{
		OOOICall(iRequireModule, module, NULL, pModule);
	}
	else
	{
		RepositoryData * pRepositoryData = OOOConstruct(RepositoryData, szName, OOOThis, iRequireModule);
		OOOICall(OOOF(aRepositories)[0], get, OOOCast(OOOIRepositoryData, pRepositoryData));
	}
}
OOOMethodEnd

OOOConstructor(OOOIRepository ** aRepositories, size_t uRepositoriesLength)
{
	unsigned int uIndex = 0;

	OOOMapMethods
		OOOMapMethod(get)
	OOOMapMethodsEnd

	OOOF(aRepositories) = O_calloc(uRepositoriesLength, sizeof(OOOIRepository *));
	while (uIndex < uRepositoriesLength)
	{
		OOOF(aRepositories)[uIndex] = aRepositories[uIndex];
		uIndex++;
	}
	OOOF(uRepositoriesLength) = uRepositoriesLength;
}
OOOConstructorEnd
#undef OOOClass

/*
 *
 * Private RepositoryData implementation
 *
 */
#define OOOClass RepositoryData
OOOPrivateData
	char * szName;
	OOORequire * pRequire;
	OOOIRequireModule * iRequireModule;
	unsigned int uCount;
OOOPrivateDataEnd

OOODestructor
{
	O_free(OOOF(szName));
}
OOODestructorEnd

OOOMethod(char *, getName)
{
	return OOOF(szName);
}
OOOMethodEnd

OOOMethod(void, load, OOOIError * iError, unsigned char * pData, size_t uSize)
{
	/* increment the count */
	OOOF(uCount)++;

	/* call the private link method directly */
	OOOPCCall(OOORequire, OOOF(pRequire), link, OOOThis, iError, pData, uSize, OOOF(iRequireModule), OOOF(uCount));
}
OOOMethodEnd

OOOConstructor(char * szName, OOORequire * pRequire, OOOIRequireModule * iRequireModule)
{
#define OOOInterface OOOIRepositoryData
	OOOMapVirtuals
		OOOMapVirtual(getName)
		OOOMapVirtual(load)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(szName) = O_strdup(szName);
	OOOF(pRequire) = pRequire;
	OOOF(iRequireModule) = iRequireModule;
}
OOOConstructorEnd
#undef OOOClass
