#ifndef MockCache_H
#define MockCache_H

#include "OOOCode.h"
#include "OOOICache.h"

#define OOOClass MockCache
OOODeclare()
	OOOImplements
		OOOImplement(OOOICache)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
