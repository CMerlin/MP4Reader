#ifndef _M_UTIL_H_
#define _M_UTIL_H_

#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <unistd.h>

extern "C"
{
#define LOG_DBG (printf("[%s:%s][%s][%u][De]:", __DATE__, __TIME__, __FILE__, __LINE__), printf)
#define LOG_ERR (printf("[%s:%s][%s][%u][Er]:", __DATE__, __TIME__, __FILE__, __LINE__), printf)
}

#endif

