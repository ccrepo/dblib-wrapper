#ifndef _DB_WRAPPER_H
#define _DB_WRAPPER_H

#ifdef _WIN32
#define DBLIB_WRAPPER_EXPORT_FUNC __declspec(dllexport)
#else
#define DBLIB_WRAPPER_EXPORT_FUNC
#endif

#include <string>

namespace dbw {

}

#endif
