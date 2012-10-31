#include "OOOUnitTestDefines.h"
#include "OOORequire.h"

OOOTest(Require)
{
	OOORequire * pRequire = OOOConstruct(OOORequire);

	/* Check stuff here */
	OOOCheck(pRequire != NULL);

	OOODestroy(pRequire);
}
