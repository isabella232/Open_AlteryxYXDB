#pragma once

#ifdef DLL_EXPORT_EXPORT_FNS
#define EXPORT_EXPORT_FN PYTHON_SDK_EXPORT
#else
#define EXPORT_EXPORT_FN
#endif

// EXPORT_EXPORT_FN auto export_field() -> void;
// EXPORT_EXPORT_FN auto export_record_info() -> void;
// EXPORT_EXPORT_FN auto export_record_creator() -> void;
// EXPORT_EXPORT_FN auto export_record_ref() -> void;
// EXPORT_EXPORT_FN auto export_record_copier() -> void;
// EXPORT_EXPORT_FN auto export_engine() -> void;
// EXPORT_EXPORT_FN auto export_output_anchor() -> void;
// EXPORT_EXPORT_FN auto export_output_anchor_manager() -> void;
