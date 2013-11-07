#ifndef WINDLLMACROS_H
#define WINDLLMACROS_H

#ifdef _WIN32

#ifdef BA_CORE_BUILD_DLL

#define BA_CORE_API_ __declspec(dllexport)
#else
#define BA_CORE_API_ __declspec(dllimport)
#endif  // BA_CORE_BUILD_DLL

#endif  // _WIN32

#ifndef BA_CORE_API_
#define BA_CORE_API_
#endif

#endif // WINDLLMACROS_H
