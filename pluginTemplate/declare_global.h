#ifndef DECLARE_GLOBAL_H
#define DECLARE_GLOBAL_H

#if defined(EX_LIBRARY)
#  define EX_EXPORT Q_DECL_EXPORT
#else
#  define EX_EXPORT Q_DECL_IMPORT
#endif

#ifndef C_CPP
#ifdef __cplusplus
#define C_CPP "C" EX_EXPORT
#else
#define C_CPP EX_EXPORT
#endif
#endif


#endif // DECLARE_GLOBAL_H
