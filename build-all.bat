rmdir /s /q build
mkdir build
pushd build

REM need to add this in
pip install wheel

REM Install the prerequisites
conan install .. --build=missing
set builderrorlevel=%errorlevel%
if %builderrorlevel% neq 0 goto fin

REM build python wheel
cd %CURRENT_DIR%
cd src\python-bindings\pips

py -3.10-64 -m pip install wheel pybind11 twine
py -3.10-64 setup.py bdist_wheel

exit /b %builderrorlevel%
