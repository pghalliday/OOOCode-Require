#include "OOOUnitTestDefines.h"
#include "OOORequire.h"

#include "OOOInMemoryRepository.h"
#include "MockCache.h"
#include "OOOTestLog.h"

#include "HelloWorld.h"

unsigned char HelloWorld_Module[] =
{
#include "HelloWorld_Module.dump"
};
size_t HelloWorld_Module_uSize = sizeof(HelloWorld_Module);

OOOModuleDeclare(HelloWorld);

#define OOOClass TestRequirer
OOODeclare()
	OOOImplements
		OOOImplement(OOOIRequirer)
	OOOImplementsEnd
	OOOExports
		OOOExport(void, start)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	OOOInMemoryRepository * pRepository;
	MockCache * pMockCache;
	OOORequire * pRequire;
	OOOModule * pModule;
OOOPrivateDataEnd

OOODestructor
{
	OOODestroy(OOOF(pRequire));
	OOODestroy(OOOF(pRepository));
	OOODestroy(OOOF(pMockCache));
}
OOODestructorEnd

OOOMethod(void, start)
{
	// Require the HelloWorld_Module
	OOOCall(OOOF(pRequire), get, "HelloWorld_Module", OOOCast(OOOIRequirer, OOOThis));
}
OOOMethodEnd

OOOMethod(void, module, OOOIError * iError, char * szModuleName, OOOModule * pModule)
{
	if (!OOOF(pModule))
	{
		OOOCheck(iError == NULL);

		/* name should be correct */
		OOOCheck(O_strcmp(szModuleName, "HelloWorld_Module") == 0);

		/* Should be able to link the HelloWorld class */
		OOOModuleLink(pModule, HelloWorld);

		/* Should be able to instantiate the HelloWorld class */
		{
			OOOTestLog * pLog = OOOConstruct(OOOTestLog);
			HelloWorld * pHelloWorld = OOOConstruct(HelloWorld, OOOCast(OOOILog, pLog));

			OOOCall(pHelloWorld, sayHello);
			OOOCheck(OOOCall(pLog, check, "Hello, world!"));

			OOODestroy(pHelloWorld);
			OOODestroy(pLog);
		}

		OOOF(pModule) = pModule;

		/* now lets see what happens if we get the module again */
		OOOCall(OOOF(pRequire), get, "HelloWorld_Module", OOOCast(OOOIRequirer, OOOThis));
	}
	else
	{
		OOOCheck(iError == NULL);

		/* name should be correct */
		OOOCheck(O_strcmp(szModuleName, "HelloWorld_Module") == 0);

		/* should get the same pModule instance */
		OOOCheck(OOOF(pModule) == pModule);

		/* TODO: should get the module from the cache */
			/* TODO: reconstruct the require instance with the same cache but an empty repository */

		/* TODO: should report appropriate errors */
	}
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface OOOIRequirer
	OOOMapVirtuals
		OOOMapVirtual(module)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
		OOOMapMethod(start)
	OOOMapMethodsEnd

	OOOF(pRepository) = OOOConstruct(OOOInMemoryRepository);
	OOOCall(OOOF(pRepository), add, "HelloWorld_Module", HelloWorld_Module, HelloWorld_Module_uSize);
	OOOF(pMockCache) = OOOConstruct(MockCache);
	OOOF(pRequire) = OOOConstruct(OOORequire, OOOCast(OOOIRepository, OOOF(pRepository)), OOOCast(OOOICache, OOOF(pMockCache)));
}
OOOConstructorEnd
#undef OOOClass

OOOTest(OOORequire)
{
	TestRequirer * testRequirer = OOOConstruct(TestRequirer);
	OOOCall(testRequirer, start);
	OOODestroy(testRequirer);
}
