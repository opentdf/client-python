from conans import ConanFile, CMake
import os

class VirtruTDF3LibConan(ConanFile):
    generators = "cmake", "CMakeToolchain"
    settings = "os", "compiler", "build_type", "arch"

    # manylinux build of boost without libiconv fails because glibc is too old.  Default settings uses prebuilt binaries and works.  
    # Disable these options until that can be resolved
    default_options = ("NOTopentdf-client:without_libiconv=True", "NOTopentdf-client:without_zlib=True")

    def requirements(self):
        self.requires("pybind11/2.10.1@")
        self.requires("opentdf-client/1.5.4@")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()