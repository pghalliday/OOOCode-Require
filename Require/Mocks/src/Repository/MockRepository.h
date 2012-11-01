#ifndef MockRepository_H
#define MockRepository_H

#include "OOOCode.h"
#include "OOOIRepository.h"

#define OOOClass MockRepository
OOODeclare()
	OOOImplements
		OOOImplement(OOOIRepository)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
