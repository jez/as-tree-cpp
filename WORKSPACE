BAZEL_VERSION = "3.1.0"

workspace(name = "io_jez_as_tree_cpp")

load("//third_party:externals.bzl", "io_jez_as_tree_register_dependencies")
io_jez_as_tree_register_dependencies()

load("@com_grail_bazel_toolchain//toolchain:deps.bzl", "bazel_toolchain_dependencies")
bazel_toolchain_dependencies()

load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")
llvm_toolchain(
    name = "llvm_toolchain",
    absolute_paths = True,
    llvm_version = "9.0.0",
)

# Use llvm_toolchain by default
load("@llvm_toolchain//:toolchains.bzl", "llvm_register_toolchains")
llvm_register_toolchains()

BAZEL_INSTALLER_VERSION_darwin_SHA = "5cfa97031b43432b3c742c80e2e01c41c0acdca7ba1052fc8cf1e291271bc9cd"
BAZEL_INSTALLER_VERSION_linux_SHA = "7ba815cbac712d061fe728fef958651512ff394b2708e89f79586ec93d1185ed"
