#include "OOOUnitTestDefines.h"
#include "OOORequire.h"

#include "OOOInMemoryRepository.h"
#include "OOOTestLog.h"

#include "HelloWorld.h"

unsigned char Test_Module[] =
{
#include "HelloWorld_Module.dump"
};
size_t Test_Module_uSize = sizeof(Test_Module);

OOOModuleDeclare(HelloWorld);

#define OOOClass TestRequireModule

typedef enum
{
	TestRequireModule_State_Test_Module0,
	TestRequireModule_State_Test_Module0_Again,
	TestRequireModule_State_Test_Module1,
	TestRequireModule_State_Test_Module1_Again
}
TestRequireModule_State;

OOODeclare()
	OOOImplements
		OOOImplement(OOOIRequireModule)
	OOOImplementsEnd
	OOOExports
		OOOExport(void, start)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	OOOIRepository * aRepositories[2];
	OOORequire * pRequire;
	OOOModule * pModule;
	char * szModuleName;
	TestRequireModule_State state;
OOOPrivateDataEnd

OOODestructor
{
	OOOIDestroy(OOOF(aRepositories)[0]);
	OOOIDestroy(OOOF(aRepositories)[1]);
	OOODestroy(OOOF(pRequire));
}
OOODestructorEnd

OOOMethod(void, start)
{
	// Require the Test_Module0 module
	OOOF(state) = TestRequireModule_State_Test_Module0;
	OOOF(szModuleName) = "Test_Module0";
	OOOCall(OOOF(pRequire), get, OOOCast(OOOIRequireModule, OOOThis));
}
OOOMethodEnd

OOOMethod(char *, getName)
{
	return OOOF(szModuleName);
}
OOOMethodEnd

OOOMethod(void, module, OOOIError * iError, OOOModule * pModule)
{
	if (OOOF(state) == TestRequireModule_State_Test_Module0)
	{
		OOOCheck(iError == NULL);

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
		OOOF(state) = TestRequireModule_State_Test_Module0_Again;
		OOOCall(OOOF(pRequire), get, OOOCast(OOOIRequireModule, OOOThis));
	}
	else if (OOOF(state) == TestRequireModule_State_Test_Module0_Again)
	{
		OOOCheck(iError == NULL);

		/* should get the same pModule instance */
		OOOCheck(OOOF(pModule) == pModule);

		// Require the Test_Module1 module
		OOOF(state) = TestRequireModule_State_Test_Module1;
		OOOF(szModuleName) = "Test_Module0";
		OOOCall(OOOF(pRequire), get, OOOCast(OOOIRequireModule, OOOThis));
	}
	else if (OOOF(state) == TestRequireModule_State_Test_Module1)
	{
		OOOCheck(iError == NULL);

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
		OOOF(state) = TestRequireModule_State_Test_Module1_Again;
		OOOCall(OOOF(pRequire), get, OOOCast(OOOIRequireModule, OOOThis));
	}
	else if (OOOF(state) == TestRequireModule_State_Test_Module1_Again)
	{
		OOOCheck(iError == NULL);

		/* should get the same pModule instance */
		OOOCheck(OOOF(pModule) == pModule);
	}

	/* TODO: should report appropriate errors */
}
OOOMethodEnd

OOOConstructor()
{
	OOOInMemoryRepository * pRepository0;
	OOOInMemoryRepository * pRepository1;

	#define OOOInterface OOOIRequireModule
	OOOMapVirtuals
		OOOMapVirtual(getName)
		OOOMapVirtual(module)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
		OOOMapMethod(start)
	OOOMapMethodsEnd

	pRepository0 = OOOConstruct(OOOInMemoryRepository);
	pRepository1 = OOOConstruct(OOOInMemoryRepository);
	OOOCall(pRepository0, add, "Test_Module0", Test_Module, Test_Module_uSize);
	OOOCall(pRepository1, add, "Test_Module1", Test_Module, Test_Module_uSize);
	OOOF(aRepositories)[0] = OOOCast(OOOIRepository, pRepository0);
	OOOF(aRepositories)[1] = OOOCast(OOOIRepository, pRepository1);
	OOOF(pRequire) = OOOConstruct(OOORequire, OOOF(aRepositories), 2);
}
OOOConstructorEnd
#undef OOOClass

OOOTest(OOORequire)
{
	TestRequireModule * testRequireModule = OOOConstruct(TestRequireModule);
	OOOCall(testRequireModule, start);
	OOODestroy(testRequireModule);
}
