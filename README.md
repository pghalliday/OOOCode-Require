OOOCode-Require
===============

An OOOCode module for managing and dynamically linking shared shared OOOCode modules

## Features

- Watch this space

## API

```C
Require * require = OOOConstruct(Require);
```

## Roadmap

- No backlog items

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

1. I recommend creating a new workspace in the root of the project
1. In the IDE choose **File/Import...**
1. In the resulting dialog choose **General/Existing Projects Into Workspace** and press **Next**
1. Choose the **Select Root Directory:** Radio button and **Browse...** to the root of the project
1. The 4 sub projects should then be listed under **Projects**
1. Click **Select All** and then click **Finish**
1. You should then be able to build the projects by choosing **Project/Build All**

After you have built the projects at least once run the test application in the Virtual Set top box by:

1. Choosing the **OOOCodeFlow** project on the left
1. Pressing the green **Run** button at the top
1. In the resulting dialog choose **Local OpenTV Application** and press **OK**

## Release History
_(Nothing yet)_

## License
Copyright (c) 2012 Peter Halliday  
Licensed under the MIT license.