#ifndef OOORequireData_H
#define OOORequireData_H

#include "OOOCode.h"
#include "OOOIRepositoryData.h"
#include "OOOIRequire.h"

#define OOOClass OOORequireData
OOODeclare(char * szName, OOOIRequire * iRequire, OOOIRequirer * iRequirer)
	OOOImplements
		OOOImplement(OOOIRepositoryData)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
