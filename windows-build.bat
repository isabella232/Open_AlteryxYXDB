@echo off
SETLOCAL enabledelayedexpansion

SET scriptLocation=%~dp0
cd %scriptLocation%
if not exist ".\build" mkdir .\build
if not exist ".\build\windows" mkdir .\build\windows
cd build/windows

set S_ROOT=%1
if "%1" == "" set S_ROOT=S:
set BOOST_ROOT_DIR=%S_ROOT%/3rdParty/Utility/boost_1_62_0
set PYTHON_ROOT=%S_ROOT%/3rdParty/Python/Miniconda3

CMake -G "Visual Studio 14 2015 Win64" ../.. ^
-DAYX_ROOT_DIR=%S_ROOT% ^
-DBOOST_ROOT_DIR=%BOOST_ROOT_DIR% ^
-DBOOST_INCLUDEDIR=%BOOST_ROOT_DIR% ^
-DBOOST_LIBRARYDIR=%BOOST_ROOT_DIR%/stage/lib_x64/lib ^
-DPYTHON_LIBRARY=%PYTHON_ROOT%/libs ^
-DPYTHON_INCLUDE_DIR=%PYTHON_ROOT%/include && ^
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" && ^
msbuild Open_AlteryxYXDB.sln
