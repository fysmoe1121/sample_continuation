
#ifndef LIBRARY_C___EXPORT_H
#define LIBRARY_C___EXPORT_H

#ifdef LIBRARY_C___STATIC_DEFINE
#  define LIBRARY_C___EXPORT
#  define LIBRARY_C___NO_EXPORT
#else
#  ifndef LIBRARY_C___EXPORT
#    ifdef Library_C___EXPORTS
        /* We are building this library */
#      define LIBRARY_C___EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LIBRARY_C___EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LIBRARY_C___NO_EXPORT
#    define LIBRARY_C___NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LIBRARY_C___DEPRECATED
#  define LIBRARY_C___DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LIBRARY_C___DEPRECATED_EXPORT
#  define LIBRARY_C___DEPRECATED_EXPORT LIBRARY_C___EXPORT LIBRARY_C___DEPRECATED
#endif

#ifndef LIBRARY_C___DEPRECATED_NO_EXPORT
#  define LIBRARY_C___DEPRECATED_NO_EXPORT LIBRARY_C___NO_EXPORT LIBRARY_C___DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIBRARY_C___NO_DEPRECATED
#    define LIBRARY_C___NO_DEPRECATED
#  endif
#endif

#endif /* LIBRARY_C___EXPORT_H */
