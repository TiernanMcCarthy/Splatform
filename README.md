# Built with SFML and C++ 17 with CMAKE

# Currently being built for Linux systems & _Windows (Setup Below)_

Assets folder is duplicated on build. Replacing the map.png file with an equivalent map (colours are important) would allow for a different world.

Slowly creating a primitive engine of my own to support the project, realistically out of scope, but I've learnt a bit and can use it again later, would prefer to keep things SFML agnostic.

Windows Build

These DLLS need to placed in a folder called bin in the project root folder. CMAKE will deal with their position in builds
- libgcc_s_seh-1.dll
- libstdc++-6.dll
- libwinpthread-1.dll
- sfml-audio-d-3.dll
- sfml-graphics-d-3.dll
- sfml-system-d-3.dll
- sfml-window-d-3.dll

The first three can be found through MINGW fairly easily, CMAKE will automatically download the correct SFML files, they can found in the _deps folder.


