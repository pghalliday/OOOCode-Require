#ifndef OOOIRequire_H
#define OOOIRequire_H

#include "OOOCode.h"
#include "OOOIRequirer.h"

#define OOOInterface OOOIRequire
OOOVirtuals
	OOOVirtual(void, link, OOOIError * iError, char * szModuleName, unsigned char * pData, size_t uSize, OOOIRequirer * iRequirer)
OOOVirtualsEnd
#undef OOOInterface

#endif
