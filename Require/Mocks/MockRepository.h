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
		OOOExport(void, add, char * szName, unsigned char * pData, size_t uSize)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
