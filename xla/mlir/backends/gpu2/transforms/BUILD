load("@tsl//tsl/platform:rules_cc.bzl", "cc_library")
load("@tsl//tsl:tsl.default.bzl", "get_compatible_with_portable")
load("@llvm-project//mlir:tblgen.bzl", "gentbl_cc_library")
load("//xla/mlir/backends/gpu2:build_config.bzl", "if_gpu2", "if_not_gpu2")

package(
    # copybara:uncomment default_applicable_licenses = ["//tensorflow:license"],
    default_visibility = ["//xla:internal"],
    licenses = ["notice"],
)

# copybara:uncomment_begin(not supported in OSS build)
#
# gentbl_cc_library(
#     name = "passes_inc_gen",
#     compatible_with = get_compatible_with_portable(),
#     tbl_outs = [
#         (
#             ["-gen-pass-decls"],
#             "passes.h.inc",
#         ),
#     ],
#     tblgen = "@llvm-project//mlir:mlir-tblgen",
#     td_file = "passes.td",
#     deps = ["@llvm-project//mlir:PassBaseTdFiles"],
# )
#
# cc_library(
#     name = "passes",
#     srcs = if_gpu2([
#         "convert_to_runtime.cc",
#         "passes.cc",
#     ]),
#     hdrs = ["passes.h"],
#     # TODO(ezhulenev): Override cc_library()'s default compatibility because IREE targets are not
#     # compatible with `non_prod` constraint.
#     compatible_with = [],
#     defines = if_not_gpu2(["XLA_DISABLE_GPU2_COMPILER=1"]),
#     deps = [
#         ":passes_inc_gen",
#         "//xla/mlir/backends/gpu2/conversion:convert_compiled_ops",
#         "//xla/mlir/backends/gpu2/conversion:convert_library_ops",
#         "//xla/mlir/backends/gpu2/conversion:convert_memref_ops",
#         "//xla/mlir/backends/gpu2/conversion:convert_while_op",
#         "//xla/mlir/backends/gpu2/conversion:de_bufferization",
#         "//xla/mlir/backends/gpu2/conversion:xla_gpu_api",
#         "//xla/mlir/backends/gpu2/ir:xla_gpu",
#         "//xla/mlir_hlo:lhlo",
#         "@llvm-project//llvm:Support",
#         "@llvm-project//mlir:ArithDialect",
#         "@llvm-project//mlir:FuncDialect",
#         "@llvm-project//mlir:IR",
#         "@llvm-project//mlir:MemRefDialect",
#         "@llvm-project//mlir:Pass",
#         "@llvm-project//mlir:SCFDialect",
#         "@llvm-project//mlir:Support",
#         "@llvm-project//mlir:TensorDialect",
#         "@llvm-project//mlir:Transforms",
#     ] + if_gpu2(["//third_party/iree/llvm-external-projects/iree-dialects:IREEInputDialect"]),
# )
#
# copybara:uncomment_end_and_comment_begin
cc_library(
    name = "passes",
    hdrs = ["passes.h"],
    defines = ["XLA_DISABLE_GPU2_COMPILER=1"],
)
# copybara:comment_end
