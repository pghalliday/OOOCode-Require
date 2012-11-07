#ifndef OOOError_H
#define OOOError_H

#include "OOOCode.h"
#include "OOOIError.h"

#define OOOClass OOOError
OOODeclare(char * szMessage)
	OOOImplements
		OOOImplement(OOOIError)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
