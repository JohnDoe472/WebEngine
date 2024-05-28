@echo off
echo "============================================================================"
echo "Creating directories"
echo "============================================================================"
echo:

set ScriptDir=%~dp0

if exist %ScriptDir%\..\bins powershell "Remove-Item -LiteralPath %ScriptDir%\..\bins -Force -Recurse"
if exist %ScriptDir%\..\include powershell "Remove-Item -LiteralPath %ScriptDir%\..\include -Force -Recurse"
if exist %ScriptDir%\..\libs powershell "Remove-Item -LiteralPath %ScriptDir%\..\libs -Force -Recurse"
if exist %ScriptDir%\..\bootstrap powershell "Remove-Item -LiteralPath %ScriptDir%\..\bootstrap -Force -Recurse"
if exist %ScriptDir%\..\bootstrap powershell "Remove-Item -LiteralPath %ScriptDir%\temp -Force -Recurse"

mkdir %ScriptDir%\..\bins
mkdir %ScriptDir%\..\include
mkdir %ScriptDir%\..\include\stb
mkdir %ScriptDir%\..\libs
mkdir %ScriptDir%\..\bootstrap

echo:
echo "============================================================================"
echo "Start Building Assimp"
echo "============================================================================"
echo:

powershell Expand-Archive "%ScriptDir%\assimp-5.3.1.zip" -Force -DestinationPath "%ScriptDir%\temp"

call emcmake cmake %ScriptDir%\temp\assimp-5.3.1 -GNinja -B"%ScriptDir%\temp\assimp-5.3.1\build" ^
   -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=OFF ^
   -DASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT=OFF ^
   -DASSIMP_BUILD_ASSIMP_TOOLS=OFF ^
   -DASSIMP_BUILD_TESTS=OFF ^
   -DASSIMP_BUILD_FBX_IMPORTER=ON ^
   -DASSIMP_BUILD_OBJ_IMPORTER=ON ^
   -DASSIMP_BUILD_ZLIB=ON ^
   -DASSIMP_LIBRARY_SUFFIX="" ^
   -DASSIMP_INJECT_DEBUG_POSTFIX=OFF ^
   -DBUILD_SHARED_LIBS=ON ^
   -DCMAKE_DEBUG_POSTFIX=""

call cmake --build "%ScriptDir%\temp\assimp-5.3.1\build"

powershell "Copy-Item -Path %ScriptDir%\temp\assimp-5.3.1\include\* -Recurse -Destination %ScriptDir%\..\include -Container -Force"
powershell "Copy-Item -Path %ScriptDir%\temp\assimp-5.3.1\build\include\* -Recurse -Destination %ScriptDir%\..\include -Container -Force"
powershell "Get-ChildItem -Path %ScriptDir%\temp\assimp-5.3.1\build\* -Include *.lib,*.so -Recurse | Copy-Item -Destination %ScriptDir%\..\libs\ -Force"
powershell "Get-ChildItem -Path %ScriptDir%\temp\assimp-5.3.1\build\* -Include *.pdb,*.dll,*.a -Recurse | Copy-Item -Destination %ScriptDir%\..\bins\ -Force"

echo:
echo "============================================================================"
echo "Finish Building Assimp"
echo "============================================================================"
echo:

echo:
echo "============================================================================"
echo "Start Building SDL2"
echo "============================================================================"
echo:

powershell Expand-Archive "%ScriptDir%\SDL2-2.28.5.zip" -Force -DestinationPath "%ScriptDir%\temp"

call emcmake cmake %ScriptDir%\temp\SDL2-2.28.5 -GNinja -B"%ScriptDir%\temp\SDL2-2.28.5\build" ^
    -DSDL2_DISABLE_INSTALL=ON ^
    -DSDL2_DISABLE_UNINSTALL=ON ^
    -DSDL_TEST=OFF ^
    -DSDL_SHARED=ON ^
    -DSDL_STATIC=OFF

call cmake --build "%ScriptDir%\temp\SDL2-2.28.5\build"

powershell "Copy-Item -Path %ScriptDir%\temp\SDL2-2.28.5\build\include\* -Recurse -Destination %ScriptDir%\..\include -Container -Force"
powershell "Copy-Item -Path %ScriptDir%\temp\SDL2-2.28.5\build\include-config-\* -Recurse -Destination %ScriptDir%\..\include -Container -Force"
powershell "Get-ChildItem -Path %ScriptDir%\temp\SDL2-2.28.5\build\* -Include *.lib,*.so -Recurse | Copy-Item -Destination %ScriptDir%\..\libs\ -Force"
powershell "Get-ChildItem -Path %ScriptDir%\temp\SDL2-2.28.5\build\* -Include *.pdb,*.dll,*.a -Recurse | Copy-Item -Destination %ScriptDir%\..\bins\ -Force"

echo:
echo "============================================================================"
echo "Finish Building SDL2"
echo "============================================================================"
echo:

echo:
echo "============================================================================"
echo "Unpacking GLM"
echo "============================================================================"
echo:

powershell Expand-Archive "%ScriptDir%\glm-0.9.9.8.zip" -Force -DestinationPath "%ScriptDir%\temp"
powershell Copy-Item -Path "%ScriptDir%\temp\glm\glm" -Recurse -Destination "%ScriptDir%\..\include" -Container -Force

echo:
echo "============================================================================"
echo "Unpacking STB"
echo "============================================================================"
echo:

powershell Expand-Archive "%ScriptDir%\stb.zip" -Force -DestinationPath "%ScriptDir%\temp"
powershell Copy-Item -Path "%ScriptDir%\temp\stb\*" -Filter *.h -Destination "%ScriptDir%\..\include\stb" -Force

echo:
echo "============================================================================"
echo "Unpacking Bootstrap"
echo "============================================================================"
echo:

powershell Expand-Archive "%ScriptDir%\bootstrap-5.3.3.zip" -Force -DestinationPath "%ScriptDir%\temp"
powershell Copy-Item -Path "%ScriptDir%\temp\bootstrap-5.3.3-dist\*" -Recurse -Destination "%ScriptDir%\..\bootstrap" -Force

echo:
echo "============================================================================"
echo "Finished"
echo "============================================================================"