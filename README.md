OOOCode-Require
===============

An OOOCode module for managing and dynamically linking shared OOOCode modules

## Features

- Watch this space

## API

```C
#include "OOOCode.h"
#include "OOORequire.h"
#include "MyClass.h"
#include "YourClass.h"

Require * require = OOOConstruct(Require, repository);

OOORequireInit(require);
OOORequire(MyClass);
OOORequire(YourClass);

void onReady() {
	MyClass * myClass = OOOConstruct(MyClass);
	YourCLass * yourClass = OOOConstruct(YourClass);
}

OOOCall(require, load, onReady);
```

## Roadmap

* Should load and link modules from a passed in repository structure
- Should only load and link the module once, subsequent calls to require should provide the same instance
- Should load and link modules from the passed in server location if not found in the repository structure
- Should load and link modules from the passed in track if server cannot be reached

## Contributing

In lieu of a formal styleguide, take care to maintain the existing coding style. Add unit tests for any new or changed functionality. Lint and test your code using ``./grunt.sh`` or ``.\grunt.bat``.

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