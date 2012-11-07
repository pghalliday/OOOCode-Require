#include "OOOError.h"

#define OOOClass OOOError
OOOPrivateData
	char * szMessage;
OOOPrivateDataEnd

OOODestructor
{
	if (OOOF(szMessage))
	{
		O_free(OOOF(szMessage));
	}
}
OOODestructorEnd

OOOMethod(char *, toString)
{
	return OOOF(szMessage);
}
OOOMethodEnd

OOOConstructor(char * szMessage)
{
	#define OOOInterface OOOIError
	OOOMapVirtuals
		OOOMapVirtual(toString)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd

	if (szMessage)
	{
		OOOF(szMessage) = O_strdup(szMessage);
	}
}
OOOConstructorEnd
#undef OOOClass
