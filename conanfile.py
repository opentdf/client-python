from conans import ConanFile, CMake

class clientPythonConan(ConanFile):
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"

    # Should only need opentdf and pybind
    def requirements(self):
        self.requires("opentdf-client/1.1.5@")
        self.requires("pybind11/2.6.2@")

    # Skip libiconv - not needed
    def configure(self):
        self.options["libxml2"].iconv = False
        self.options["libxml2"].icu = False
        self.options["boost"].i18n_backend_iconv = "off"
        self.options["boost"].i18n_backend_icu = False
        self.options["boost"].without_locale = True

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
