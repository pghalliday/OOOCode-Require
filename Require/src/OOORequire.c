#include "OOORequire.h"
#include "OOORequireRepositoryData.h"
#include "OOOError.h"

#define OOOClass OOORequire

typedef OOOModule * (* Init)(void);
typedef void (* Uninit)(void);

typedef struct _ModuleEntry ModuleEntry;
struct _ModuleEntry
{
	char * szModuleName;
	unsigned char * pModuleData;
	OOOModule * pModule;
	Uninit uninit;
	ModuleEntry * pNext;
};

OOOPrivateData
	OOOIRepository * iRepository;
	ModuleEntry * pModules;
	OOORequireRepositoryData * pRequireRepositoryData;
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
			O_debug("WARNING: Code module has no uninit method: %s\n", pLastEntry->szModuleName);
		}

		if (O_dl_unlink_code_module(pLastEntry->pModuleData) != GOOD)
		{
			O_debug("WARNING: Failed to unlink code module: %s\n", pLastEntry->szModuleName);
		}

		O_free(pLastEntry->szModuleName);
		O_free(pLastEntry);
	}
}
OOODestructorEnd

OOOMethod(void, link, OOOIError * iError, char * szModuleName, unsigned char * pData, size_t uSize, OOOIRequirer * iRequirer)
{
	OOOModule * pModule = NULL;
	OOORequireRepositoryData * pRequireRepositoryData = OOOF(pRequireRepositoryData);
	if (iError)
	{
		OOOICall(iRequirer, module, iError, szModuleName, NULL);
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
					pEntry->pModuleData = pData;
					pEntry->szModuleName = O_strdup(szModuleName);
					pEntry->uninit = O_dl_find_function(1);
					pEntry->pNext = OOOF(pModules);
					OOOF(pModules) = pEntry;
					OOOICall(iRequirer, module, NULL, szModuleName, pModule);
				}
				else
				{
					OOOError * pError = OOOConstruct(OOOError, "INIT METHOD DID NOT RETURN A MODULE");
					OOOICall(iRequirer, module, OOOCast(OOOIError, pError), szModuleName, NULL);
					OOODestroy(pError);
				}
			}
			else
			{
				OOOError * pError = OOOConstruct(OOOError, "FAILED TO FIND INIT METHOD");
				OOOICall(iRequirer, module, OOOCast(OOOIError, pError), szModuleName, NULL);
				OOODestroy(pError);
			}
		}
		else
		{
			OOOError * pError = OOOConstruct(OOOError, "FAILED TO LINK MODULE");
			OOOICall(iRequirer, module, OOOCast(OOOIError, pError), szModuleName, NULL);
			OOODestroy(pError);
		}
	}
	OOODestroy(pRequireRepositoryData);
}
OOOMethodEnd

OOOMethod(void, get, char * szModuleName, OOOIRequirer * iRequirer)
{
	OOOModule * pModule = NULL;
	ModuleEntry * pEntry = OOOF(pModules);
	while (pEntry)
	{
		if (O_strcmp(pEntry->szModuleName, szModuleName) == 0)
		{
			pModule = pEntry->pModule;
			break;
		}
		pEntry = pEntry->pNext;
	}

	if (pModule)
	{
		OOOICall(iRequirer, module, NULL, szModuleName, pModule);
	}
	else
	{
		OOOF(pRequireRepositoryData) = OOOConstruct(OOORequireRepositoryData, szModuleName, OOOCast(OOOIRequire, OOOThis), iRequirer);
		OOOICall(OOOF(iRepository), get, OOOCast(OOOIRepositoryData, OOOF(pRequireRepositoryData)));
	}
}
OOOMethodEnd

OOOConstructor(OOOIRepository * iRepository, OOOICache * iCache)
{
#define OOOInterface OOOIRequire
	OOOMapVirtuals
		OOOMapVirtual(link)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
		OOOMapMethod(get)
	OOOMapMethodsEnd

	OOOF(iRepository) = iRepository;
}
OOOConstructorEnd

#undef OOOClass
