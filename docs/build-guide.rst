Build guide
===========

This project uses CMake directly. The provided build scripts are convenience
wrappers and are not required.

Requirements
------------

* CMake 3.20 or newer and Git.
* A C++20 compiler:

  * Windows x64: Visual Studio 2022 with the MSVC x64 toolchain and Windows SDK,
    or Visual Studio 2026 with the equivalent components. CI uses Windows Server
    2025 and Visual Studio 2026.
  * Linux x86_64 or aarch64: a C++20-capable GCC or Clang toolchain. Ninja is
    recommended.

* Python 3. It is required while configuring the bundled ONNX dependency.
* CUDA Toolkit 12.9 or newer. CI uses CUDA 13.2 except for Windows ARM64,
  which uses CUDA 13.4. Download it from the
  `CUDA Toolkit page <https://developer.nvidia.com/cuda-downloads>`_.
* TensorRT RTX built for the installed CUDA major version. CI uses TensorRT RTX
  1.6.1.120. Obtain it from the
  `TensorRT RTX page <https://developer.nvidia.com/tensorrt/rtx>`_.
* ONNX Runtime 1.24 or newer. When ``ONNXRUNTIME_ROOT`` is not set, CMake
  downloads the version selected by ``ONNXRUNTIME_VERSION`` (1.26.0 by
  default). Prebuilt SDKs are available from the
  `ONNX Runtime releases <https://github.com/microsoft/onnxruntime/releases>`_.

The TensorRT RTX SDK can either be extracted locally and supplied through
``TRT_RTX_ROOT``, or downloaded by CMake from ``TRT_RTX_DOWNLOAD_URL``. Linux
URL downloads require support for extracting ``.tar.zst`` archives.

Configure and build
-------------------

Windows
~~~~~~~

Run CMake from a Visual Studio Developer PowerShell so that the MSVC x64
compiler and Windows SDK are available:

.. code-block:: powershell

   cmake -S . -B build -G Ninja `
     -DCMAKE_BUILD_TYPE=Release `
     -DCUDAToolkit_ROOT="C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.2" `
     -DTRT_RTX_ROOT="C:\SDK\TensorRT-RTX-1.6.1.120" `
     -DBUILD_TESTS=ON `
     -DBUILD_EXAMPLES=ON

   cmake --build build --parallel

Linux
~~~~~

.. code-block:: bash

   cmake -S . -B build -G Ninja \
     -DCMAKE_BUILD_TYPE=Release \
     -DCUDAToolkit_ROOT=/usr/local/cuda \
     -DPython3_EXECUTABLE="$(command -v python3)" \
     -DTRT_RTX_ROOT=/opt/TensorRT-RTX-1.6.1.120 \
     -DBUILD_TESTS=ON \
     -DBUILD_EXAMPLES=ON

   cmake --build build --parallel

To let CMake download TensorRT RTX, replace ``TRT_RTX_ROOT`` with the matching
archive URL:

.. code-block:: text

   -DTRT_RTX_DOWNLOAD_URL=<TensorRT-RTX archive URL>

CMake options
-------------

``CUDAToolkit_ROOT``
   CUDA Toolkit installation root.

``TRT_RTX_ROOT``
   Root of an extracted TensorRT RTX SDK.

``TRT_RTX_DOWNLOAD_URL``
   TensorRT RTX archive URL. Used when ``TRT_RTX_ROOT`` is not supplied.

``ONNXRUNTIME_ROOT``
   Root of an extracted ONNX Runtime SDK. If omitted, CMake downloads it.

``ONNXRUNTIME_VERSION``
   ONNX Runtime version to download. The default is 1.26.0.

``BUILD_TESTS``
   Build the unit tests. The default is ``ON``.

``BUILD_EXAMPLES``
   Build the C++ examples. The default is ``OFF``.

``TRT_RTX_EP_PRODUCTION_BUILD``
   Enable production-build checks and signature verification.

``TRT_RTX_EP_VERSION``
   Version embedded in production artifacts.

Run tests
---------

Most runtime tests require an NVIDIA GPU. Building the tests does not.

Windows:

.. code-block:: powershell

   .\build\tests\unittests.exe
   ctest --test-dir build --output-on-failure

Linux:

.. code-block:: bash

   ./build/tests/unittests
   ctest --test-dir build --output-on-failure

Continuous integration
----------------------

GitHub Actions builds the project and examples in these environments:

* Ubuntu 24.04 x86_64 and aarch64 in an NVIDIA CUDA 13.2 development container.
* Windows Server 2025 x64 with MSVC 2026, Ninja, and CUDA 13.2.
* Windows 11 ARM64 with MSVC 2026, Ninja, and CUDA 13.4.

Both jobs configure and build with CMake directly. Unit-test and CTest execution
is non-blocking because GitHub-hosted runners do not provide NVIDIA GPUs. Build
or configuration failures still fail the job. Compiler outputs are cached with
ccache separately for each operating system and architecture.

Build outputs
-------------

The provider library is written below ``build``:

* Windows: ``build\onnxruntime_providers_nv_tensorrt_rtx.dll`` and its import
  library.
* Linux: ``build/libonnxruntime_providers_tensorrt_rtx.so``.

Test executables are under ``build/tests`` and examples are under
``build/examples``.

Common configuration issues
---------------------------

* If CMake cannot find Python, set ``Python3_EXECUTABLE`` explicitly.
* CUDA and TensorRT RTX must target the same CUDA major version.
* A test failure caused by the absence of an NVIDIA GPU is expected on
  GitHub-hosted runners.
* After changing SDK roots or compiler generators, configure a fresh build
  directory to avoid stale cached paths.

See the :doc:`integration-guide` for provider integration and runtime usage.
