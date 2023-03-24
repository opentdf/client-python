set CURRENT_DIR=%~dp0
rmdir /s /q build
mkdir build
pushd build

set WHEELVER=0.3.8
set PYBIND11VER=2.10.3
set TWINEVER=4.0.2

REM need to add this in
pip install wheel==%WHEELVER%

REM Install the prerequisites
conan --version
conan install .. --build=missing
set builderrorlevel=%errorlevel%
if %builderrorlevel% neq 0 goto fin

REM build python wheel
cd %CURRENT_DIR%
cd %CURRENT_DIR%\src\python-bindings\pips
py -3.8-64 -m pip install wheel==%WHEELVER% pybind11==%PYBINDVER% twine==%TWINEVER%
py -3.8-64 setup.py bdist_wheel

py -3.9-64 -m pip install wheel==%WHEELVER% pybind11==%PYBINDVER% twine==%TWINEVER%
py -3.9-64 setup.py bdist_wheel

py -3.10-64 -m pip install wheel==%WHEELVER% pybind11==%PYBINDVER% twine==%TWINEVER%
py -3.10-64 setup.py bdist_wheel

py -3.11-64 -m pip install wheel==%WHEELVER% pybind11==%PYBINDVER% twine==%TWINEVER%
py -3.11-64 setup.py bdist_wheel

:fin
REM return to where we came from
popd
exit /b %builderrorlevel%
