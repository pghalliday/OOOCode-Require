#include "OOOUnitTestDefines.h"
#include "OOORequireData.h"
#include "OOOInMemoryRepository.h"

static char * szTest = "This is a test";

#define KNOWN_TEST		0
#define UNKNOWN_TEST	1

#define OOOClass TestRepositoryDataListener
OOODeclare()
	OOOImplements
		OOOImplement(OOOIRequire)
		OOOImplement(OOOIRequirer)
	OOOImplementsEnd
	OOOExports
		OOOExport(void, start)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	OOORequireData * pInvalidRepositoryData;
	OOORequireData * pValidRepositoryData;
	OOOInMemoryRepository * pRepository;
	unsigned int uTest;
OOOPrivateDataEnd

OOODestructor
{
	OOODestroy(OOOF(pInvalidRepositoryData));
	OOODestroy(OOOF(pValidRepositoryData));
	OOODestroy(OOOF(pRepository));
}
OOODestructorEnd

OOOMethod(void, start)
{
	OOOF(uTest) = KNOWN_TEST;
	OOOICall(OOOCast(OOOIRepository, OOOF(pRepository)), get, OOOCast(OOOIRepositoryData, OOOF(pValidRepositoryData)));
	OOOF(uTest) = UNKNOWN_TEST;
	OOOICall(OOOCast(OOOIRepository, OOOF(pRepository)), get, OOOCast(OOOIRepositoryData, OOOF(pInvalidRepositoryData)));
}
OOOMethodEnd

OOOMethod(void, link, OOOIError * iError, char * szModuleName, unsigned char * pData, size_t uSize, OOOIRequirer * iRequirer)
{
	OOOCheck(iRequirer == OOOCast(OOOIRequirer, OOOThis));
	if (OOOF(uTest) == KNOWN_TEST)
	{
		/* Error should be NULL */
		OOOCheck(iError == NULL);

		/* Data should be the KNOWN module data */
		OOOCheck(O_strcmp((char *) pData, szTest) == 0);

		/* Size should be the KNOWN module data size */
		OOOCheck(O_strlen(szTest) + 1 == uSize);

		OOOCheck(O_strcmp(szModuleName, "KNOWN") == 0);
	}
	else if (OOOF(uTest) == UNKNOWN_TEST)
	{
		/* Error should be UNKNOWN MODULE */
		OOOCheck(O_strcmp(OOOICall(iError, toString), "UNKNOWN MODULE") == 0);

		/* Data should be NULL */
		OOOCheck(pData == NULL);

		/* Size should be 0 */
		OOOCheck(0 == uSize);

		OOOCheck(O_strcmp(szModuleName, "UNKNOWN") == 0);
	}
}
OOOMethodEnd

OOOMethod(void, module, OOOIError * iError, char * szModuleName, OOOModule * pModule)
{
	/* do nothing */
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface OOOIRequire
	OOOMapVirtuals
		OOOMapVirtual(link)
	OOOMapVirtualsEnd
	#undef OOOInterface

	#define OOOInterface OOOIRequirer
	OOOMapVirtuals
		OOOMapVirtual(module)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
		OOOMapMethod(start)
	OOOMapMethodsEnd

	OOOF(pRepository) = OOOConstruct(OOOInMemoryRepository);
	OOOCall(OOOF(pRepository), add, "KNOWN", (unsigned char *) szTest, O_strlen(szTest) + 1);
	OOOF(pValidRepositoryData) = OOOConstruct(OOORequireData, "KNOWN", OOOCast(OOOIRequire, OOOThis), OOOCast(OOOIRequirer, OOOThis));
	OOOF(pInvalidRepositoryData) = OOOConstruct(OOORequireData, "UNKNOWN", OOOCast(OOOIRequire, OOOThis), OOOCast(OOOIRequirer, OOOThis));
}
OOOConstructorEnd
#undef OOOClass

OOOTest(OOORequireData)
{
	TestRepositoryDataListener * pTestRepositoryDataListener = OOOConstruct(TestRepositoryDataListener);
	OOOCall(pTestRepositoryDataListener, start);
	OOODestroy(pTestRepositoryDataListener);
}
