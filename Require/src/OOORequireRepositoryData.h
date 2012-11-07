#ifndef OOORequireRepositoryData_H
#define OOORequireRepositoryData_H

#include "OOOCode.h"
#include "OOOIRepositoryData.h"
#include "OOOIRequire.h"

#define OOOClass OOORequireRepositoryData
OOODeclare(char * szName, OOOIRequire * iRequire, OOOIRequirer * iRequirer)
	OOOImplements
		OOOImplement(OOOIRepositoryData)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
