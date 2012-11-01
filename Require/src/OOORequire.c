#include "OOORequire.h"

#define OOOClass OOORequire

OOOPrivateData
	OOOIRepository * iRepository;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOConstructor(OOOIRepository * iRepository)
{
	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(iRepository) = iRepository;
}
OOOConstructorEnd

#undef OOOClass
