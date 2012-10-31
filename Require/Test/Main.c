#include "opentv.h"
#include "assert.h"
#include "OOODebug.h"
#include "OOODebugReporter.h"
#include "OOOUnitTestsRun.h"


void main(void)
{
	/* run the tests first */
	OOODebug * pDebug = OOOConstruct(OOODebug);
	OOODebugReporter * pReporter = OOOConstruct(OOODebugReporter, OOOCast(OOOIDebug, pDebug));
	OOOUnitTestsRun(OOOCast(OOOIReporter, pReporter));
	OOODestroy(pReporter);
	OOODestroy(pDebug);

	while (TRUE) {
		// Do nothing
	}
}
