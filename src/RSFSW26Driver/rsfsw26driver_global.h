#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RSFSW26DRIVER_LIB)
#  define RSFSW26DRIVER_EXPORT Q_DECL_EXPORT
# else
#  define RSFSW26DRIVER_EXPORT Q_DECL_IMPORT
# endif
#else
# define RSFSW26DRIVER_EXPORT
#endif
