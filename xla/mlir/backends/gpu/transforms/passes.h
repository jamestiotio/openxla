/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef XLA_MLIR_BACKENDS_GPU_TRANSFORMS_PASSES_H_
#define XLA_MLIR_BACKENDS_GPU_TRANSFORMS_PASSES_H_

#include <cstdint>
#include <memory>

#include "mlir/Dialect/Func/IR/FuncOps.h"  // from @llvm-project
#include "mlir/IR/BuiltinOps.h"  // from @llvm-project
#include "mlir/Pass/Pass.h"  // from @llvm-project

namespace xla {
namespace gpu {

#define GEN_PASS_DECL_ADDHLOTRACEANNOTATIONSPASS
#define GEN_PASS_DECL_CONVERTGPUTOGPURUNTIMEPASS
#define GEN_PASS_DECL_CONVERTLMHLOGPUTOGPURUNTIMEPASS
#define GEN_PASS_DECL_CONVERTLMHLOTOGPULAUNCHPASS
#define GEN_PASS_DECL_CONVERTLMHLOTOGPURUNTIMEPASS
#define GEN_PASS_DECL_CONVERTMEMREFGETGLOBALTOARGPASS
#define GEN_PASS_DECL_OUTLINEGPUGRAPHSPASS
#define GEN_PASS_DECL_ADDCONCURRENTREGIONSPASS
#define GEN_PASS_DECL_STREAMASSIGNMENTPASS
#include "xla/mlir/backends/gpu/transforms/passes.h.inc"

class ThunkSequence;  // forward declare

struct GpuPipelineOpts {
  // Enable experimental pass that outlines parts of the XLA computation into
  // CUDA Graphs, which allows us to amortize the cost of launching multiple
  // device kernels.
  int32_t gpu_graph_level = 0;
  int32_t min_graph_size = 0;
  bool enable_concurrent_region = false;
};

// Populate passes that lower MLIR modules from a combination of LMHLO and
// LMHLO_GPU dialects to the XLA Gpu runtime. This pipeline is composed from
// the passes defined below, and few builtin MLIR passes.
void populateXlaGpuRuntimePasses(mlir::OpPassManager& pm,
                                 ThunkSequence* thunk_sequence,
                                 const GpuPipelineOpts& opts = {});

//===----------------------------------------------------------------------===//
// Auxiliary passes for lowering to XLA Gpu runtime.
//===----------------------------------------------------------------------===//

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createConvertMemrefGetGlobalToArgPass();

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createConvertMemrefGetGlobalToArgPass(int64_t min_num_elements);

//===-----------------------------------------------------------------------===/
// Passes for lowering from the `gpu` dialect.
//===-----------------------------------------------------------------------===/

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createConvertGpuToGpuRuntimePass();

//===----------------------------------------------------------------------===//
// Passes for lowering from the `lmhlo` dialect.
//===----------------------------------------------------------------------===//

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createConvertLmhloToGpuLaunchPass(ThunkSequence* thunk_sequence = nullptr);

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createConvertLmhloToGpuRuntimePass();

//===----------------------------------------------------------------------===//
// Passes for lowering from the `lmhlo_gpu` dialect.
//===----------------------------------------------------------------------===//

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createConvertLmhloGpuToGpuRuntimePass();

//===----------------------------------------------------------------------===//
// XLA runtime performance tracing passes.
//===----------------------------------------------------------------------===//

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createAddHloTraceAnnotationsPass();

//===----------------------------------------------------------------------===//
// XLA runtime <-> Cuda Graphs integration.
//===----------------------------------------------------------------------===//

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createOutlineGpuGraphsPass();

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createOutlineGpuGraphsPass(
    int32_t gpu_graph_level, int32_t min_graph_size);

//===----------------------------------------------------------------------===//
// Passes for marking concurrent region in CUDA graph capture function.
//===----------------------------------------------------------------------===//

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createAddConcurrentRegionsPass();

//===----------------------------------------------------------------------===//
// Passes for assigning kernels to streams in CUDA graph capture function.
//===----------------------------------------------------------------------===//

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createStreamAssignmentPass();

//===-----------------------------------------------------------------------===/

#define GEN_PASS_REGISTRATION
#include "xla/mlir/backends/gpu/transforms/passes.h.inc"

}  // namespace gpu
}  // namespace xla

#endif  // XLA_MLIR_BACKENDS_GPU_TRANSFORMS_PASSES_H_
