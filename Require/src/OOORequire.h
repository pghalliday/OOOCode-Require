#ifndef OOORequire_H
#define OOORequire_H

#include "OOOCode.h"
#include "OOOIRepository.h"

#define OOOClass OOORequire
OOODeclare(OOOIRepository * iRepository)
	OOOImplements
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
