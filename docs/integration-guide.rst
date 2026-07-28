Integration guide
=================

Using the built execution provider
----------------------------------

After building, integrate the execution provider with your application by
deploying its runtime dependencies and registering the provider with ONNX
Runtime.

Copy required files
~~~~~~~~~~~~~~~~~~~

Copy the following files to your application directory.

**From the build output:**

::

   build\onnxruntime_providers_nv_tensorrt_rtx.dll

On Linux, use ``build/libonnxruntime_providers_nv_tensorrt_rtx.so`` instead.

**From the ONNX Runtime SDK:**

::

   <ONNXRUNTIME_ROOT>\lib\onnxruntime.dll
   <ONNXRUNTIME_ROOT>\lib\onnxruntime_providers_shared.dll

**From the TensorRT RTX SDK:**

::

   <TRT_RTX_ROOT>\lib\tensorrt_rtx_1_5.dll
   <TRT_RTX_ROOT>\lib\tensorrt_onnxparser_rtx_1_5.dll
   (and any other required runtime DLLs)

**From the CUDA Toolkit:**

::

   <CUDA_PATH>\bin\cudart64_*.dll
   (and other required CUDA DLLs)

Load the execution provider
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following sketch shows the surrounding ONNX Runtime session setup. Register
the provider library using the provider-registration API demonstrated by this
repository before creating the session.

.. code:: cpp

   #include <onnxruntime_cxx_api.h>
   #include <iostream>

   int main() {
       try {
           Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "TensorRTRtxEP");
           Ort::SessionOptions session_options;

           // Register and append the TensorRT RTX execution provider here.

           const wchar_t* model_path = L"path/to/your/model.onnx";
           Ort::Session session(env, model_path, session_options);
           std::cout << "Session created successfully." << std::endl;
       } catch (const Ort::Exception& error) {
           std::cerr << "ONNX Runtime error: " << error.what() << std::endl;
           return 1;
       }

       return 0;
   }

Configure the runtime environment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

All runtime dependencies must be discoverable by the application.

**Application-local deployment**

Copy the dependencies alongside the application executable. This is the
simplest option and keeps deployment self-contained.

**Development PATH**

.. code:: powershell

   $env:PATH += ";C:\SDK\onnxruntime-win-x64-1.26.0\lib"
   $env:PATH += ";C:\SDK\TensorRT-RTX-1.6.1.120\lib"
   $env:PATH += ";C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.2\bin"

**Production packaging**

- Package the required runtime libraries with the application installer.
- Use the project's secure delay-load support and explicit library search paths
  where appropriate.
