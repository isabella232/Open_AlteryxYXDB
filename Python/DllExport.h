#pragma once

#ifdef PYTHON_SDK_IS_DLL
#define ALTERYX_PYTHON_SDK_EXPORT __declspec(dllexport)
#else
#define ALTERYX_PYTHON_SDK_EXPORT
#endif
