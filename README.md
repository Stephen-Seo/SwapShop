
# Sequence Smasher

Oh hey I submitted it (here)[http://ludumdare.com/compo/minild-59/?action=preview&uid=37473]

# Compiling

## Building with CMake

CMake gui recommended. (point CMake gui to the src directory as the source directory.)
Otherwise:

To build project, make directory "build" and cd to it. Then use the commands:
cmake ../src
make

To setup Makefile with SFML-2 in a non-standard directory:
cmake -D SFML\_ROOT=${Directory} ../src

To set install directory, use -D CMAKE\_INSTALL\_PREFIX=${Directory}

To find ResourcePacker if installed in non standard directory,
use -D CMAKE\_PREFIX\_PATH=${pathToResourcePackerRoot}

To add Eclipse project files, add the option:
-G"Eclipse CDT4 - Unix Makefiles"

