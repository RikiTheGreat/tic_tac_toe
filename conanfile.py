from conan import ConanFile


class TicTacToe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("catch2/3.5.2")
        self.requires("spdlog/1.13.0")
        self.requires("ccache/4.9")
