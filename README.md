OOOCode-Require
===============

An OOOCode module for managing and dynamically linking shared OOOCode modules

## Features

- Should load and link modules from a passed in repository structure
- Should only load and link the module once, subsequent calls to require should provide the same instance
- Should search through a list of passed in repositories in order

## API

```C
#include "OOORequire.h"

// The repository used should implement the OOOIRepository interface
#include "Repository.h"

// Have to include the headers for required classes so that they are defined
#include "HelloWorld.h"

// Have to module declare the required classes so that they can be linked at run time
OOOModuleDeclare(HelloWorld);

#define OOOClass MyApplication
#define REPOSITORY_COUNT	1

OOODeclare()
	OOOImplements
		OOOImplement(OOOIRequireModule)
	OOOImplementsEnd
	OOOExports
		OOOExport(void, start)
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	OOOIRepository ** aRepositories[REPOSITORY_COUNT];
	OOORequire * pRequire;
OOOPrivateDataEnd

OOODestructor
{
	OOOIDestroy(OOOF(aRepositories)[0]);
	OOODestroy(OOOF(pRepository));
}
OOODestructorEnd

OOOMethod(void, start)
{
	// Require the HelloWorld_Module
	OOOCall(OOOF(pRequire), get, OOOCast(OOOIRequireModule, OOOThis));
}
OOOMethodEnd

OOOMethod(char *, getName)
{
	return "HelloWorld";
}
OOOMethodEnd

OOOMethod(void, module, OOOModule * pModule)
{
	/* name should be correct */
	if (O_strcmp(szModuleName, "HelloWorld_Module") == 0)
	{
		/* Should be able to link the HelloWorld class */
		OOOModuleLink(pModule, HelloWorld);

		/* 
		Should now be able to instantiate the HelloWorld class (in fact
		it should now be possible to call the HelloWorld constructor from any
		file that includes the HelloWorld header)
		*/
		{
			HelloWorld * pHelloWorld = OOOConstruct(HelloWorld);
			OOOCall(pHelloWorld, sayHello);
			OOODestroy(pHelloWorld);
		}	
	}
}
OOOMethodEnd

OOOConstructor()
{
	Repository * pRepository;

	#define OOOInterface OOOIRequirer
	OOOMapVirtuals
		OOOMapVirtual(getName)
		OOOMapVirtual(module)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
		OOOMapMethod(start)
	OOOMapMethodsEnd

	/* Repository class should implement the OOOIRepository interface */
	pRepository = OOOConstruct(Repository);

	/* Pass in a list of repositories in the order that they should be searched */
	OOOF(aRepositories)[0] = OOOCast(OOOIRepository, pRepository);
	OOOF(pRequire) = OOOConstruct(OOORequire, OOOF(aRepositories), REPOSITORY_COUNT);
}
OOOConstructorEnd
#undef OOOClass
```

## Roadmap

* should support asynchronous repositories

## Contributing

In lieu of a formal styleguide, take care to maintain the existing coding style. Add unit tests for any new or changed functionality.

## Prerequisites

- OpenTV SDK C2.2 from http://community.opentv.com

## Initialising

This projects references sub-modules so after cloning the repository...

```
git submodule init
git submodule update
```

Then the easiest way to work with the project in the OpenTV IDE...

1. Create a new workspace in the root of the project
1. In the IDE choose **File/Import...**
1. In the resulting dialog choose **General/Existing Projects Into Workspace** and press **Next**
1. Choose the **Select Root Directory:** Radio button and **Browse...** to the root of the project
1. A number of projects may be listed under **Projects**
1. Select the projects in the root, deselect those under the submodules folder and then click **Finish**
1. You should then be able to build the OpenTV projects by choosing **Project/Build All**

After you have built the projects at least once run the test application in the Virtual Set top box by...

1. Choosing the **RequireFlow** project on the left
1. Pressing the green **Run** button at the top
1. In the resulting dialog choose **Local OpenTV Application** and press **OK**

## Release History
_(Nothing yet)_

## License
Copyright (c) 2012 Peter Halliday  
Licensed under the MIT license.