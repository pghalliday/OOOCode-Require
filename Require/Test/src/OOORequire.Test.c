#include "OOOUnitTestDefines.h"
#include "OOORequire.h"

#include "repository.h"

OOOTest(OOORequire)
{
	OOORequire * pRequire = OOOConstruct(OOORequire);

	/* Check stuff here */
	OOOCheck(pRequire != NULL);

	OOODestroy(pRequire);
}
