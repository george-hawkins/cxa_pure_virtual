#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

extern caddr_t _sbrk( int incr ) ;

extern int _close( int file ) ;

extern int _fstat( int file, struct stat *st ) ;

extern int _isatty( int file ) ;

extern int _lseek( int file, int ptr, int dir ) ;

extern int _read(int file, char *ptr, int len) ;

extern int _write( int file, char *ptr, int len ) ;

extern void _exit( int status ) ;
extern void _kill( int pid, int sig ) ;
extern int _getpid ( void ) ;

#ifdef __cplusplus
}
#endif
