// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

// P/Invoke uses stdcall by default. This can be changed, but Unity's IL2CPP
// does not understand the CallingConvention attribute and instead
// unconditionally forces stdcall. So use stdcall in the API to be compatible.
#if defined(MRS_DLL) && defined(_MRS_BUILD_DLL)
/* MRS_DLL must be defined by applications that are linking against the DLL
 * version of the MRS library.  _MRS_BUILD_DLL is defined by the MRS
 * configuration header when compiling the DLL version of the library.
 */
#error "You must not have both MRS_DLL and _MRS_BUILD_DLL defined"
#endif

/* MRS_API is used to declare public API functions for export
 * from the DLL / shared library / dynamic library.
 */
#if defined(_WIN32) && defined(_MRS_BUILD_DLL)
/* We are building MRS as a Win32 DLL */
#define MRS_API __declspec(dllexport)
#define MRS_CALL __stdcall
#elif defined(_WIN32) && defined(MRS_DLL)
/* We are calling MRS as a Win32 DLL */
#define MRS_API __declspec(dllimport)
#define MRS_CALL __stdcall
#elif defined(__GNUC__) && defined(_MRS_BUILD_DLL)
/* We are building MRS as a shared / dynamic library */
#define MRS_API __attribute__((visibility("default")))
#define MRS_CALL
#else
/* We are building or calling MRS as a static library */
#define MRS_API
#define MRS_CALL
#endif

#ifndef MRS_DEPRECATED
#if defined(__GNUC__)
#define MRS_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define MRS_DEPRECATED __declspec(deprecated)
#else
#define MRS_DEPRECATED
#endif
#endif

#if (__cplusplus >= 201703L)
#define MRS_NODISCARD [[nodiscard]]
#else
#define MRS_NODISCARD
#endif
