# oophw
Repo containing my 2nd year OOP course lab projects.

### Project list
1. [GrandmaBakes](https://github.com/alexsg4/oophw/tree/OOP0)
    - needs cleanup.

2. [RamblerGarage](https://github.com/alexsg4/oophw/tree/OOP1-V2) (this)
    - Simple car workshop management app, using wxWidgets for UI and [cmake](https://cmake.org/) for build configuration.
        - Assumes [wxWidgets v3.0+](https://www.wxwidgets.org/downloads/) is present at compile time and [configured](https://wiki.wxwidgets.org/Compiling_and_getting_started) properly (unicode, no-debug).
        - VS builds may require either the Release or RelWithDebugInfo build configurations.
        - once built, project directory structure must not change, but binaries can be moved.

3. [PizzaParlor](https://github.com/alexsg4/oophw/tree/OOP2)
    - Console program for managing a small restaurant. Uses [cmake](https://cmake.org/) for build configuration.
