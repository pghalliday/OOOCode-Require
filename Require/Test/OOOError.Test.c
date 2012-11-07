#include "OOOUnitTestDefines.h"
#include "OOOError.h"

OOOTest(OOOError)
{
	OOOError * pError = OOOConstruct(OOOError, "Hello");

	/* toString should return initialisation string */
	OOOCheck(O_strcmp(OOOICall(OOOCast(OOOIError, pError), toString), "Hello") == 0);

	OOODestroy(pError);
}
