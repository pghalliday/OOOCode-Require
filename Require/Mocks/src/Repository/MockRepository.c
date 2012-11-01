#include "MockRepository.h"

#define OOOClass MockRepository

unsigned char aHelloWorld_Module[] =
{
#include "HelloWorld_Module.dump"
};

OOOPrivateData
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(unsigned char *, get, char * szModuleName)
{
	unsigned char * pModule = NULL;
	if (O_strcmp(szModuleName, "HelloWorld_Module") == 0)
	{
		pModule = aHelloWorld_Module;
	}
	return pModule;
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface OOOIRepository
	OOOMapVirtuals
		OOOMapVirtual(get)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass
