from conans import ConanFile, CMake

class clientPythonConan(ConanFile):
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("opentdf-client/1.1.0@")
        self.requires("pybind11/2.6.2@")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
