#ifndef OOORequire_H
#define OOORequire_H

#include "OOOCode.h"
#include "OOOIRepository.h"
#include "OOOIRequirer.h"
#include "OOOIRequire.h"
#include "OOOICache.h"

#define OOOClass OOORequire
OOODeclare(OOOIRepository * iRepository, OOOICache * iCache)
	OOOImplements
		OOOImplement(OOOIRequire)
	OOOImplementsEnd
	OOOExports
		OOOExport(void, get, char * szModuleName, OOOIRequirer * iRequirer)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
