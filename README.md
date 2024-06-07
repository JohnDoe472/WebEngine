# IronMaiden

## Project status

Right now available only as standalone application. Work on Emscripten migration in progress...

Used libraries:
SDL2 - for Widnow
GLM - for Math

## How To Build

Instruction for executable. Should be cross platform.

First step is to install Emscripten. https://emscripten.org/docs/getting_started/downloads.html
For Windows platform also install Ninja.

Then:
```
git clone -b dev https://gitlab.nixdev.co/cpp-internal-projects/ironmaiden.git IronMaiden
cd IronMaiden
```

### Windows:

To build with thirdparty libraries, can be skiped if library already builded
```
thirdparty\external_libs\build_dependencies.bat
```
Then:
```
emcmake cmake -Bbuild
cmake --build build
```

### MacOS:

To build with thirdparty libraries, can be skiped if library already builded
```
thirdparty/external_libs/build_dependencies.sh
```
If thirdparty libraries already builded
```
emcmake cmake -Bbuild
cmake --build build
```
## How To Launch

The project run from server. So, after installation should be created server instance with project and then launch using web browser.
The easiest solution is to open terminal and navigation to project binary location (```<ProjectFolder>/bin/Emrscripten```) and run python http instance.

### Windows:

```
python -m http.server 80
```

### MacOS:

```
python3 -m http.server 80
```

Then open page ```localhost``` in a web browser.