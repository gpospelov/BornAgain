/*
    Configuration for libtiff in BornAgain
*/

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Support CCITT Group 3 & 4 algorithms */
/* #undef CCITT_SUPPORT */

/* Pick up YCbCr subsampling info from the JPEG data stream to support files
   lacking the tag (default enabled). */
/* #undef CHECK_JPEG_YCBCR_SUBSAMPLING */

/* enable partial strip reading for large strips (experimental) */
/* #undef CHUNKY_STRIP_READ_SUPPORT */

/* Support C++ stream API (requires C++ compiler) */
#define CXX_SUPPORT 1

/* enable deferred strip/tile offset/size loading (experimental) */
/* #undef DEFER_STRILE_LOAD */

/* Define to 1 if you have the <assert.h> header file. */
#define HAVE_ASSERT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `floor' function. */
/* #undef HAVE_FLOOR */

/* Define to 1 if you have the `getopt' function. */
/* #undef HAVE_GETOPT */

/* Define to 1 if you have the <GLUT/glut.h> header file. */
/* #undef HAVE_GLUT_GLUT_H */

/* Define to 1 if you have the <GL/glut.h> header file. */
/* #undef HAVE_GL_GLUT_H */

/* Define to 1 if you have the <GL/glu.h> header file. */
/* #undef HAVE_GL_GLU_H */

/* Define to 1 if you have the <GL/gl.h> header file. */
/* #undef HAVE_GL_GL_H */

/* Define to 1 if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* Define to 1 if you have the <io.h> header file. */
/* #undef HAVE_IO_H */

/* Define to 1 if you have the `isascii' function. */
/* #undef HAVE_ISASCII */

/* Define to 1 if you have the `jbg_newlen' function. */
/* #undef HAVE_JBG_NEWLEN */

/* Define to 1 if you have the `lfind' function. */
/* #undef HAVE_LFIND */

/* Define to 1 if you have the <limits.h> header file. */
/* #undef HAVE_LIMITS_H */

/* Define to 1 if you have the <malloc.h> header file. */
/* #undef HAVE_MALLOC_H */

/* Define to 1 if you have the `memmove' function. */
/* #undef HAVE_MEMMOVE */

/* Define to 1 if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define to 1 if you have the `memset' function. */
/* #undef HAVE_MEMSET */

/* Define to 1 if you have the `mmap' function. */
/* #undef HAVE_MMAP */

/* Define to 1 if you have the <OpenGL/glu.h> header file. */
/* #undef HAVE_OPENGL_GLU_H */

/* Define to 1 if you have the <OpenGL/gl.h> header file. */
/* #undef HAVE_OPENGL_GL_H */

/* Define to 1 if you have the `pow' function. */

/* Define to 1 if you have the <search.h> header file. */
/* #undef HAVE_SEARCH_H */

/* Define to 1 if you have the `setmode' function. */
/* #undef HAVE_SETMODE */

/* Define to 1 if you have the `snprintf' function. */
/* #undef HAVE_SNPRINTF */
#ifdef _WIN32
#define HAVE_SNPRINTF
#endif

/* Define to 1 if you have the `sqrt' function. */
/* #undef HAVE_SQRT */

/* Define to 1 if you have the <stdint.h> header file. */
/* #undef HAVE_STDINT_H */

/* Define to 1 if you have the `strcasecmp' function. */
/* #undef HAVE_STRCASECMP */

/* Define to 1 if you have the `strchr' function. */
/* #undef HAVE_STRCHR */

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strrchr' function. */
/* #undef HAVE_STRRCHR */

/* Define to 1 if you have the `strstr' function. */
/* #undef HAVE_STRSTR */

/* Define to 1 if you have the `strtol' function. */
/* #undef HAVE_STRTOL */

/* Define to 1 if you have the `strtoul' function. */
/* #undef HAVE_STRTOUL */

/* Define to 1 if you have the `strtoull' function. */
/* #undef HAVE_STRTOULL */

/* Define to 1 if you have the <sys/time.h> header file. */
/* #undef HAVE_SYS_TIME_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#if !defined(_WIN32)
#define HAVE_UNISTD_H 1
#endif

#undef JPEG_SUPPORT

/* 8/12 bit libjpeg dual mode enabled */
/* #undef JPEG_DUAL_MODE_8_12 */

/* 12bit libjpeg primary include file with path */
/*#define LIBJPEG_12_PATH */

/* Support LZMA2 compression */
/* #undef LZMA_SUPPORT */

/* Name of package */
/* #define PACKAGE "" */

/* Define to the address where bug reports for this package should be sent. */
/* #define PACKAGE_BUGREPORT "" */

/* Define to the full name of this package. */
/*#define PACKAGE_NAME "" */

/* Define to the full name and version of this package. */
/* #define PACKAGE_STRING "" */

/* Define to the one symbol short name of this package. */
/* #define PACKAGE_TARNAME "" */

/* Define to the home page for this package. */
/* #define PACKAGE_URL "" */

/* Define to the version of this package. */
#define PACKAGE_VERSION "4.0.6"

/* The size of `signed int', as computed by sizeof. */
/* #define SIZEOF_SIGNED_INT */

/* The size of `signed long', as computed by sizeof. */
/* #define SIZEOF_SIGNED_LONG */

/* The size of `signed long long', as computed by sizeof. */
/* #define SIZEOF_SIGNED_LONG_LONG */

/* The size of `signed short', as computed by sizeof. */
/* #define SIZEOF_SIGNED_SHORT */

/* The size of `unsigned char *', as computed by sizeof. */
/* #define SIZEOF_UNSIGNED_CHAR_P */

/* The size of `unsigned int', as computed by sizeof. */
/* #define SIZEOF_UNSIGNED_INT */

/* The size of `unsigned long', as computed by sizeof. */
/* #define SIZEOF_UNSIGNED_LONG */

/* The size of `unsigned long long', as computed by sizeof. */
/* #define SIZEOF_UNSIGNED_LONG_LONG */

/* The size of `unsigned short', as computed by sizeof. */
/* #define SIZEOF_UNSIGNED_SHORT */

/* Default size of the strip in bytes (when strip chopping enabled) */
/* #define STRIP_SIZE_DEFAULT */

/* Signed 32-bit type formatter */
#define TIFF_INT32_FORMAT "%d"

/* Signed 64-bit type formatter */
#define TIFF_INT64_FORMAT "%ld"

/* Pointer difference type formatter */
#define TIFF_PTRDIFF_FORMAT "%ld"
#define TIFF_PTRDIFF_T ptrdiff_t


/* Signed size type formatter */
#if BA_POINTER_SIZE == 4
#define TIFF_SSIZE_FORMAT "%d"
#else
#define TIFF_SSIZE_FORMAT "%ld"
#endif

/* Unsigned 32-bit type formatter */
#define TIFF_UINT32_FORMAT "%u"

/* Unsigned 64-bit type formatter */
#define TIFF_UINT64_FORMAT "%lu"

/* Unsigned 8-bit type */
/* #define TIFF_UINT8_T */

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
/* #undef TIME_WITH_SYS_TIME */

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* define to use win32 IO system */
#ifdef _WIN32
#define USE_WIN32_FILEIO 1
#endif


/* Version number of package */
/* #define VERSION "" */

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
/*
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif
*/

#if defined(BA_OS_MAC)
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #define _FILE_OFFSET_BITS */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#if defined(BA_CC_MSVC)
#ifndef __cplusplus
# ifndef inline
#  define inline __inline
# endif
#endif
#endif

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

#ifdef _WIN32
#define TIF_PLATFORM_CONSOLE
#endif

