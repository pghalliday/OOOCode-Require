#include "OOOUnitTestDefines.h"
#include "OOORequire.h"

#include "MockRepository.h"
#include "OOOBufferedLog.h"

#include "HelloWorld.h"

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
	MockRepository * pMockRepository;
	OOORequire * pRequire;
OOOPrivateDataEnd

OOODestructor
{
	OOODestroy(OOOF(pRequire));
	OOODestroy(OOOF(pMockRepository));
}
OOODestructorEnd

OOOMethod(void, start)
{
	// Require the HelloWorld_Module
	OOOCall(OOOF(pRequire), get, "HelloWorld_Module", OOOCast(OOOIRequirer, OOOThis));
}
OOOMethodEnd

OOOMethod(void, module, char * szModuleName, OOOModule * pModule)
{
	/* name should be correct */
	OOOCheck(O_strcmp(szModuleName, "HelloWorld_Module") == 0);

	/* Should be able to link the HelloWorld class */
	OOOModuleLink(pModule, HelloWorld);

	/* Should be able to instantiate the HelloWorld class */
	{
		OOOBufferedLog * pLog = OOOConstruct(OOOBufferedLog);
		HelloWorld * pHelloWorld = OOOConstruct(HelloWorld, OOOCast(OOOILog, pLog));

		OOOCall(pHelloWorld, sayHello);
		OOOCheck(OOOCall(pLog, check, "Hello, world!"));

		OOODestroy(pHelloWorld);
		OOODestroy(pLog);
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

	OOOF(pMockRepository) = OOOConstruct(MockRepository);
	OOOF(pRequire) = OOOConstruct(OOORequire, OOOCast(OOOIRepository, OOOF(pMockRepository)));
}
OOOConstructorEnd
#undef OOOClass

OOOTest(OOORequire)
{
	TestRequirer * testRequirer = OOOConstruct(TestRequirer);
	OOOCall(testRequirer, start);
	OOODestroy(testRequirer);
}
