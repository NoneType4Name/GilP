import os

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain
from conan.tools.files import copy


class ImGui(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("imgui/[>=1.89.4]")
        self.requires("glfw/[>=3.3.8]")
        self.requires("spdlog/[>=1.11.0]")

    def generate(self):
        tc = CMakeToolchain(self, "Ninja")
        tc.generate()
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
                                          "res", "bindings"), os.path.join(self.source_folder, "bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
                                             "res", "bindings"), os.path.join(self.source_folder, "bindings"))
