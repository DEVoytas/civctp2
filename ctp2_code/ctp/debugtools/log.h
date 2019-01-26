#ifndef LOG_H
#define LOG_H

#include "log_on.h"
#include "ctp2_config.h" // Figures out if _DEBUG is defined on Linux

#if defined(_DEBUG) || defined(USE_LOGGING)

#ifdef __cplusplus
extern "C" {
#endif

typedef const char *LogClass;

extern LogClass LOG_FATAL;
extern LogClass LOG_ERR;
extern LogClass LOG_WARN;
extern LogClass LOG_DIAG;

extern LogClass LOG_ASSERT;
extern LogClass LOG_EXCEPTION;
extern LogClass LOG_MEMORY_LEAK;
extern LogClass LOG_MEMORY_FAIL;

void Log_NextFile();

void Log_Open (const char *config_file, int number);

void Log_Close (void);

void Log_SetLoggingPtr(void *ptr);
void *Log_GetLoggingPtr(void);

void Log_AddLoggingClasses(void);
void Hash_Init(void);

void Log_Enable (LogClass log_class);

int Log_Enabled (LogClass log_class);

int Log_OutputEnabled (void);

void Log_Begin (const char *module_name, int module_line);
#if defined(WIN32)
void __cdecl Log_Middle (LogClass log_class, const char *format, ...);
#else
void Log_Middle(LogClass log_class, const char *format, ...);
#endif
void Log_End (void);

#ifdef __cplusplus
}
#endif
#endif // _DEBUG
#endif // LOG_H
