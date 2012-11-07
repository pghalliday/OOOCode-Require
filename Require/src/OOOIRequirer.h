#ifndef OOOIRequirer_H
#define OOOIRequirer_H

#include "OOOCode.h"
#include "OOOModule.h"
#include "OOOIError.h"

#define OOOInterface OOOIRequirer
OOOVirtuals
	OOOVirtual(void, module, OOOIError * iError, char * szModuleName, OOOModule * pModule)
OOOVirtualsEnd
#undef OOOInterface

#endif
