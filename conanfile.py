from conans import ConanFile, CMake
import os

class OpenTDFLibConan(ConanFile):
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"

    # manylinux build of boost without libiconv fails because glibc is too old.  Default settings uses prebuilt binaries and works.  
    # Disable these options until that can be resolved
    default_options = ("NOTopentdf-client:without_libiconv=True", "NOTopentdf-client:without_zlib=True")

    def requirements(self):
        self.requires("pybind11/2.6.2@")
        self.requires("opentdf-client/1.3.2@")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
            
    def imports(self):
        self.copy("*.h", dst="../opentdf-cpp/include/", src="include")
        self.copy("*.**", dst="../opentdf-cpp/lib", src="lib")
        