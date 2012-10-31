#include "OOOUnitTestDefines.h"
#include "Require.h"

OOOTest(Require)
{
	Require * pRequire = OOOConstruct(Require);

	/* Check stuff here */
	OOOCheck(pRequire != NULL);

	OOODestroy(pRequire);
}
