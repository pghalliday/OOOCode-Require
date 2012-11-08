#include "OOORequireData.h"

#define OOOClass OOORequireData

OOOPrivateData
	char * szName;
	OOOIRequire * iRequire;
	OOOIRequirer * iRequirer;
OOOPrivateDataEnd

OOODestructor
{
	O_free(OOOF(szName));
}
OOODestructorEnd

OOOMethod(char *, getName)
{
	return OOOF(szName);
}
OOOMethodEnd

OOOMethod(void, load, OOOIError * iError, unsigned char * pData, size_t uSize)
{
	OOOICall(OOOF(iRequire), link, iError, OOOF(szName), pData, uSize, OOOF(iRequirer));
}
OOOMethodEnd

OOOConstructor(char * szName, OOOIRequire * iRequire, OOOIRequirer * iRequirer)
{
#define OOOInterface OOOIRepositoryData
	OOOMapVirtuals
		OOOMapVirtual(getName)
		OOOMapVirtual(load)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(szName) = O_strdup(szName);
	OOOF(iRequire) = iRequire;
	OOOF(iRequirer) = iRequirer;
}
OOOConstructorEnd

#undef OOOClass
