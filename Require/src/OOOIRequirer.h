#ifndef OOOIRequirer_H
#define OOOIRequirer_H

#include "OOOCode.h"
#include "OOOModule.h"

#define OOOInterface OOOIRequirer
OOOVirtuals
	OOOVirtual(void, module, char * szModuleName, OOOModule * pModule)
OOOVirtualsEnd
#undef OOOInterface

#endif