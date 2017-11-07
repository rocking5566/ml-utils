#ifndef SysUtil_h__
#define SysUtil_h__

#include <time.h>

#if (defined WIN32 || defined _WIN32 || defined WINCE)
#define NOMINMAX    // Fix compile for std::min and std::max
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#if (defined WIN32 || defined _WIN32 || defined WINCE)
#   ifdef ROCKING_API_EXPORTS
#       define ROCKING_API __declspec(dllexport)
#   elif defined ROCKING_API_IMPORTS
#       define ROCKING_API __declspec(dllimport)
#   else
#       define ROCKING_API
#   endif
#endif

#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define SAFE_DELETE_ARRAY(p) { if((p) != NULL) { delete[] (p);   (p)=NULL; } }
#define WRITE_LOG(...) WriteLog(__FUNCTION__, __LINE__,  __VA_ARGS__)

inline void WriteLog(const char* function, int line, const char* content, ...)
{
    FILE* file = fopen("Rocking.log", "a+");
    if (NULL == file)
        return;

    va_list args;
    va_start(args, content);
    char buf[65536];
    vsprintf(buf, content, args);
    va_end(args);

    time_t t = time(0);   // get time now
    struct tm * now = localtime(&t);
    fprintf(file, "[%04d/%02d/%02d %02d:%02d:%02d] %s(%d): %s\n",
        now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour,
        now->tm_min, now->tm_sec,
        function, line, buf);
    fflush(file);
    fclose(file);
}

inline void MSleep (int milliseconds)
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif // win32
}

#endif // SysUtil_h__
