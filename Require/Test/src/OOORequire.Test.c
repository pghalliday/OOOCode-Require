#include "OOOUnitTestDefines.h"
#include "OOORequire.h"

#include "MockRepository.h"

OOOTest(OOORequire)
{
	MockRepository * pMockRepository = OOOConstruct(MockRepository);
	OOORequire * pRequire = OOOConstruct(OOORequire, OOOCast(OOOIRepository, pMockRepository));

	/* Check stuff here */
	OOOCheck(pRequire != NULL);

	OOODestroy(pRequire);
	OOODestroy(pMockRepository);
}
