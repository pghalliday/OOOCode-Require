#ifndef OOOIRequireModule_H
#define OOOIRequireModule_H

#include "OOOCode.h"
#include "OOOModule.h"
#include "OOOIError.h"

#define OOOInterface OOOIRequireModule
OOOVirtuals
	OOOVirtual(char *, getName)
	OOOVirtual(void, module, OOOIError * iError, OOOModule * pModule)
OOOVirtualsEnd
#undef OOOInterface

#endif
