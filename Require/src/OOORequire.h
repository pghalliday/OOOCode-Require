#ifndef OOORequire_H
#define OOORequire_H

#include "OOOCode.h"
#include "OOOIRepository.h"
#include "OOOIRequirer.h"

#define OOOClass OOORequire
OOODeclare(OOOIRepository * iRepository)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, get, char * szModuleName, OOOIRequirer * iRequirer)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
