#include "OOORequire.h"

#define OOOClass OOORequire

typedef OOOModule * (* GetModule)(void);

OOOPrivateData
	OOOIRepository * iRepository;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, get, char * szModuleName, OOOIRequirer * iRequirer)
{
	OOOModule * pModule = NULL;
	unsigned char * pModuleData = OOOICall(OOOF(iRepository), get, szModuleName);
	if (pModuleData)
	{
		if (O_dl_link_code_module(pModuleData) == GOOD)
		{
			GetModule getModule = O_dl_find_function(0);
			if (getModule)
			{
				pModule = getModule();
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
