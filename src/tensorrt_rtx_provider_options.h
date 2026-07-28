// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

namespace onnxruntime
{
namespace tensorrt_rtx
{
namespace provider_option_names
{
/// @brief CUDA device index used by the execution provider.
///
/// @par Type
/// Integer
/// @par Default
/// `0`
/// @par Accepted values
/// A non-negative device index available to the process.
constexpr const char* kDeviceId = "device_id";

/// @brief Compatibility flag indicating that a user compute stream is supplied.
///
/// The provider derives the effective value from `user_compute_stream`.
///
/// @par Type
/// Boolean
/// @par Default
/// `false`
/// @par Accepted values
/// `0` or `1`.
constexpr const char* kHasUserComputeStream = "has_user_compute_stream";

/// @brief Address of a caller-owned CUDA stream used for provider work.
///
/// The caller retains ownership of the stream.
///
/// @par Type
/// Integer
/// @par Default
/// `0`
/// @par Accepted values
/// The stream pointer encoded as an unsigned decimal integer; `0` selects a provider-owned stream.
constexpr const char* kUserComputeStream = "user_compute_stream";

/// @brief Maximum GPU workspace available to TensorRT RTX when building engines.
///
/// @par Type
/// Byte count
/// @par Default
/// `0`
/// @par Accepted values
/// A non-negative number of bytes; `0` uses the TensorRT RTX default.
constexpr const char* kMaxWorkspaceSize = "nv_max_workspace_size";

/// @brief Maximum shared memory that TensorRT RTX kernels may use.
///
/// @par Type
/// Byte count
/// @par Default
/// `0`
/// @par Accepted values
/// A non-negative number of bytes; `0` uses the TensorRT RTX default.
constexpr const char* kMaxSharedMemSize = "nv_max_shared_mem_size";

/// @brief Write partitioned ONNX subgraphs to disk for debugging.
///
/// @par Type
/// Boolean
/// @par Default
/// `false`
/// @par Accepted values
/// `0` or `1`.
constexpr const char* kDumpSubgraphs = "nv_dump_subgraphs";

/// @brief Enable detailed TensorRT RTX engine-build logging.
///
/// @par Type
/// Boolean
/// @par Default
/// `false`
/// @par Accepted values
/// `0` or `1`.
constexpr const char* kDetailedBuildLog = "nv_detailed_build_log";

/// @brief Minimum input shapes used to build optimization profiles.
///
/// @par Type
/// Shape specification
/// @par Default
/// Empty
/// @par Accepted values
/// Comma-separated input-name and dimension specifications.
constexpr const char* kProfilesMinShapes = "nv_profile_min_shapes";

/// @brief Maximum input shapes used to build optimization profiles.
///
/// @par Type
/// Shape specification
/// @par Default
/// Empty
/// @par Accepted values
/// Comma-separated input-name and dimension specifications.
constexpr const char* kProfilesMaxShapes = "nv_profile_max_shapes";

/// @brief Optimal input shapes used to build optimization profiles.
///
/// @par Type
/// Shape specification
/// @par Default
/// Empty
/// @par Accepted values
/// Comma-separated input-name and dimension specifications.
constexpr const char* kProfilesOptShapes = "nv_profile_opt_shapes";

/// @brief Enable CUDA graph capture and replay.
///
/// @par Type
/// Boolean
/// @par Default
/// `true`
/// @par Accepted values
/// `0` or `1`.
constexpr const char* kCudaGraphEnable = "enable_cuda_graph";

/// @brief Build and select multiple TensorRT RTX optimization profiles.
///
/// @par Type
/// Boolean
/// @par Default
/// `false`
/// @par Accepted values
/// `0` or `1`.
constexpr const char* kMultiProfileEnable = "nv_multi_profile_enable";

/// @brief Allow model initializers stored in external data files.
///
/// @par Type
/// Boolean
/// @par Default
/// `true`
/// @par Accepted values
/// `0` or `1`.
constexpr const char* kUseExternalDataInitializer = "nv_use_external_data_initializer";

/// @brief Directory used for the TensorRT RTX runtime cache.
///
/// @par Type
/// Path
/// @par Default
/// Empty
/// @par Accepted values
/// A writable directory path.
constexpr const char* kRuntimeCacheFile = "nv_runtime_cache_path";

/// @brief Controls TensorRT RTX weight streaming and resident weight data in VRAM.
///
/// @par Type
/// Budget
/// @par Default
/// `0`
/// @par Accepted values
/// `0` disables streaming; `-1` uses the automatic budget; `1` selects minimum-VRAM mode; values
/// greater than `1` are bytes; `B`, `K`, `M`, and `G` suffixes are base-2 byte units; percentages
/// from `0%` through `100%` select the resident fraction.
constexpr const char* kWeightStreamingBudget = "nv_weight_streaming_budget";

/// @brief Operator types that TensorRT RTX must leave to other EPs during graph partitioning.
///
/// @par Type
/// String list
/// @par Default
/// Empty
/// @par Accepted values
/// A comma-separated list of ONNX operator type names.
constexpr const char* kOpTypesToExclude = "nv_op_types_to_exclude";

}  // namespace provider_option_names

namespace run_option_names
{
/// @brief Optimization profile selected for the current run when multiple profiles are enabled.
///
/// @par Type
/// Integer
/// @par Default
/// `0`
/// @par Accepted values
/// A valid zero-based profile index.
constexpr const char* kProfileIndex = "nv_profile_index";

/// @brief CUDA graph annotation used to group capture and replay state for the current run.
///
/// @par Type
/// Integer
/// @par Default
/// `0`
/// @par Accepted values
/// `-1` skips CUDA graph capture; `0` is the default annotation; positive values identify
/// independent capture groups.
constexpr const char* kCudaGraphAnnotation = "cuda_graph_annotation_id";

/// @brief Requests allocator arena shrinkage after the run for matching devices.
///
/// @par Type
/// Device list
/// @par Default
/// Empty
/// @par Accepted values
/// A semicolon-separated list such as `gpu:0` or `cpu:0;gpu:0`.
constexpr const char* kMemoryArenaShrinkage = "memory.enable_memory_arena_shrinkage";

}  // namespace run_option_names

}  // namespace tensorrt_rtx
}  // namespace onnxruntime
