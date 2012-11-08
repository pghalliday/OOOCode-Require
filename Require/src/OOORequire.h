#ifndef OOORequire_H
#define OOORequire_H

#include "OOOCode.h"
#include "OOOIRepository.h"
#include "OOOIRequireModule.h"
#include "OOOICache.h"

#define OOOClass OOORequire
OOODeclare(OOOIRepository * iRepository, OOOICache * iCache)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, get, OOOIRequireModule * iRequireModule)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
