from conans import ConanFile, CMake
import os

class clientPythonConan(ConanFile):
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    keep_imports = True

    def requirements(self):
        self.requires("opentdf-client/1.2.0@")
        self.requires("pybind11/2.6.2@")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.h", root_package="opentdf-client", src="include" , dst="opentdf-cpp/include")
        self.copy("*.lib", root_package="opentdf-client", src="lib" , dst="opentdf-cpp/lib")
        self.copy("*.a", root_package="opentdf-client", src="lib" , dst="opentdf-cpp/lib")