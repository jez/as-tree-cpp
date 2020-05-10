load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")

# TODO(jez) BUILD formatters
# TODO(jez) C/C++ formatters

# We define our externals here instead of directly in WORKSPACE so that
# libraries can pin to our versions.
def io_jez_as_tree_register_dependencies():
    http_archive(
        name = "com_grail_bazel_toolchain",
        url = "https://github.com/grailbio/bazel-toolchain/archive/0.5.zip",
        sha256 = "33011cd77021017294d1982b48d0c3a081c777b9aad9a75f3e4eada0e10894d1",
        strip_prefix = "bazel-toolchain-0.5",
    )

    http_archive(
        name = "bazel-compilation-database",
        url = "https://github.com/grailbio/bazel-compilation-database/archive/0ae6349c52700f060c9a87c5ed2b04b75f94a26f.zip",
        sha256 = "40ad122fedbf2d8b23e70e16b5f49c1a316f02db3ed29ce1af8650dad6ccc1a9",
        build_file_content = '\npackage(default_visibility = ["//visibility:public"])\n' ,
        strip_prefix = "bazel-compilation-database-0ae6349c52700f060c9a87c5ed2b04b75f94a26f",
    )
