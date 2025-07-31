#ifndef LOG_H
#define LOG_H


#if DEBUG
    #define DEBUG_PRINT(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) // no-op
#endif

#endif // LOG_H
