#include "OOORequire.h"

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

	if (!pModule)
	{
		unsigned char * pModuleData = OOOICall(OOOF(iRepository), get, szModuleName);
		if (pModuleData)
		{
			if (O_dl_link_code_module(pModuleData) == GOOD)
			{
				Init init = O_dl_find_function(0);
				if (init)
				{
					pModule = init();
					if (pModule)
					{
						ModuleEntry * pEntry = O_malloc(sizeof(ModuleEntry));
						pEntry->pModule = pModule;
						pEntry->pModuleData = pModuleData;
						pEntry->szModuleName = O_strdup(szModuleName);
						pEntry->uninit = O_dl_find_function(1);
						pEntry->pNext = OOOF(pModules);
						OOOF(pModules) = pEntry;
					}
				}
			}
		}
	}

	OOOICall(iRequirer, module, szModuleName, pModule);
}
OOOMethodEnd

OOOConstructor(OOOIRepository * iRepository)
{
	OOOMapMethods
		OOOMapMethod(get)
	OOOMapMethodsEnd

	OOOF(iRepository) = iRepository;
}
OOOConstructorEnd

#undef OOOClass
