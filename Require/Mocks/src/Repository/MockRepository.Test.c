#include "OOOUnitTestDefines.h"
#include "MockRepository.h"

unsigned char moduleTest[] =
{
#include "HelloWorld_Module.dump"
};
size_t moduleTestSize = sizeof(moduleTest);

OOOTest(MockRepository)
{
	MockRepository * pMockRepository = OOOConstruct(MockRepository);
	OOOIRepository * iRepository = OOOCast(OOOIRepository, pMockRepository);
	unsigned char * module = OOOICall(iRepository, get, "HelloWorld_Module");
	unsigned int index = 0;

	/* Should return the correct module contents */
	for (index = 0; index < moduleTestSize; index++)
	{
		OOOCheck(moduleTest[index] == module[index]);
	}

	/* Should return NULL for unknown modules */
	OOOCheck(NULL == OOOICall(iRepository, get, "SomeModule"));

	OOODestroy(pMockRepository);
}
