###########################################################
# Python bindings library
###########################################################
cmake_minimum_required (VERSION 3.8)

# Set the project name
project(opentdf)

# enable verbose logging
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use the version number from the opentdf-client package
find_package(opentdf-client)
SET(PACKAGE_VERSION OPENTDF_PACKAGE_VERSION)

# add source files
set(SOURCE_FILES module/python_module.cpp)

find_package(PythonInterp 3)
find_package(PythonLibs   3)

message("Libs of conan: " ${CONAN_LIBS} )
message("Lib dirs of conan: " ${CONAN_LIB_DIRS} )
message("Include dirs of conan: " ${CONAN_INCLUDE_DIRS} )
message("Libs of python: " ${PYTHON_LIBRARIES} )
message("Include dirs of python: " ${PYTHON_INCLUDE_DIRS} )
message("python major+minor: " ${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} )

STRING(TOLOWER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME_LOWERCASE)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  SET(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
  SET(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET(CMAKE_SHARED_LIBRARY_PREFIX "")
  SET(CMAKE_SYSTEM_NAME_LOWERCASE "linux-gnu")
endif()

SET(OPENTDFMODULENAME "opentdf.cpython-${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME_LOWERCASE}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(OPENTDFMODULENAME "opentdf.cpython-${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}-${CMAKE_SYSTEM_NAME_LOWERCASE}")
  set(OSXPLATNAME "macosx_10_14_x86_64")
  message("Darwin plat name: " ${OSXPLATNAME})
endif()

message("openTDF python module name: " ${CMAKE_SHARED_LIBRARY_PREFIX}${OPENTDFMODULENAME}${CMAKE_SHARED_LIBRARY_SUFFIX} )

# Include paths
include_directories(
        ${CONAN_INCLUDE_DIRS}
        ${PYTHON_INCLUDE_DIRS}
)

link_directories(
        ${CONAN_LIB_DIRS}
        ${PYTHON_LIB_DIRS}
)

link_libraries(
        ${CONAN_LIBS}
        ${PYTHON_LIBRARIES}
)

add_library(${OPENTDFMODULENAME} SHARED ${SOURCE_FILES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
add_custom_command(TARGET ${OPENTDFMODULENAME} POST_BUILD COMMAND python3 -m pip install pybind11 twine
                                                 COMMAND mkdir build/
                                                 COMMAND mkdir build/lib
                                                 COMMAND cp  -p ../lib/*${CMAKE_SHARED_LIBRARY_SUFFIX} build/lib
                                                 COMMAND python3  ../../src/module/setup.py bdist_wheel --plat-name ${OSXPLATNAME})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_custom_command(TARGET ${OPENTDFMODULENAME} POST_BUILD COMMAND python -m pip install pybind11 twine
                                                 COMMAND mkdir build
                                                 COMMAND mkdir build\\lib
                                                 COMMAND copy ..\\bin\\*${CMAKE_SHARED_LIBRARY_SUFFIX} build\\lib
                                                 COMMAND python  ../../src/module/setup.py bdist_wheel)
else()
add_custom_command(TARGET ${OPENTDFMODULENAME} POST_BUILD COMMAND python3 -m pip install pybind11 twine
                                                 COMMAND mkdir build/
                                                 COMMAND mkdir build/lib
                                                 COMMAND cp  -p ../lib/*${CMAKE_SHARED_LIBRARY_SUFFIX} build/lib
                                                 COMMAND python3  ../../src/module/setup.py bdist_wheel)
endif()
