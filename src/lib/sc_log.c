#include "sc_log.h"

#if  !(SC_NGINX_PLATFORM) && !(SC_HTTPD_PLATFORM)

void sc_log_core(int logLevelMask, const char *fmt, va_list args)
{
    /* TODO */
}
void sc_log_error(const char *fmt, ...)
{
    /* TODO */
}
void sc_log_debug(int currentLogLevel, const char *fmt, ...)
{
    /* TODO */
}
#endif
