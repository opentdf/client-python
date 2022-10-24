from conans import ConanFile, CMake


class ClientPythonConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "opentdf-client/1.2.0@"
    options = {"fPIC": [True, False]}
    default_options = {"fPIC": True}

    def configure(self):
        self.options["libxml2"].iconv = False
        self.options["libxml2"].icu = False
        self.options["boost"].i18n_backend_iconv = "off"
        self.options["boost"].i18n_backend_icu = False
        self.options["boost"].without_locale = True
        self.options["boost"].without_log = True
        if str(self.settings.arch).startswith('arm'):
            self.options["openssl"].no_asm = True
            self.options["libxml2"].lzma = False
            self.options["libxml2"].zlib = False

    def config_options(self):

        if self.settings.os == "Windows":
            del self.options.fPIC
            
    def imports(self):
        self.copy("*.h", dst="../opentdf-cpp/include/", src="include")
        self.copy("*.**", dst="../opentdf-cpp/lib", src="lib")
        