#include "stacktracesetup.h"

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <execinfo.h>
#include <errno.h>
#include <cxxabi.h>

void abortHandler(int );

StackTraceSetup::StackTraceSetup()
{
  signal( SIGABRT, abortHandler );
  signal( SIGSEGV, abortHandler );
  signal( SIGILL,  abortHandler );
  signal( SIGFPE,  abortHandler );

}

//static inline void printStackTrace( FILE *out = stderr, unsigned int max_frames = 63 )
//{
//   fprintf(out, "stack trace:\n");

//   // storage array for stack trace address data
//   void* addrlist[max_frames+1];

//   // retrieve current stack addresses
//   int addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ));

//   if ( addrlen == 0 )
//   {
//      fprintf( out, "  \n" );
//      return;
//   }

//   // create readable strings to each frame.
//   char** symbollist = backtrace_symbols( addrlist, addrlen );

//   // print the stack trace.
//   for ( int i = 4; i < addrlen; i++ )
//      fprintf( out, "%s\n", symbollist[i]);

//   free(symbollist);
//}


#include <execinfo.h>
#include <errno.h>
#include <cxxabi.h>

static inline void printStackTrace( FILE *out = stderr, unsigned int max_frames = 63 )
{
   fprintf(out, "stack trace:\n");

   // storage array for stack trace address data
   void* addrlist[max_frames+1];

   // retrieve current stack addresses
   unsigned int addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ));

   if ( addrlen == 0 )
   {
      fprintf( out, "  \n" );
      return;
   }

   // resolve addresses into strings containing "filename(function+address)",
   // Actually it will be ## program address function + offset
   // this array must be free()-ed
   char** symbollist = backtrace_symbols( addrlist, addrlen );

   size_t funcnamesize = 1024;
   char funcname[1024];

   // iterate over the returned symbol lines. skip the first, it is the
   // address of this function.
   for ( unsigned int i = 4; i < addrlen; i++ )
   {
      char* begin_name   = nullptr;
      char* begin_offset = nullptr;
      char* end_offset   = nullptr;

      // find parentheses and +address offset surrounding the mangled name
#ifdef DARWIN
      // OSX style stack trace
      for ( char *p = symbollist[i]; *p; ++p )
      {
         if (( *p == '_' ) && ( *(p-1) == ' ' ))
            begin_name = p-1;
         else if ( *p == '+' )
            begin_offset = p-1;
      }

      if ( begin_name && begin_offset && ( begin_name < begin_offset ))
      {
         *begin_name++ = '\0';
         *begin_offset++ = '\0';

         // mangled name is now in [begin_name, begin_offset) and caller
         // offset in [begin_offset, end_offset). now apply
         // __cxa_demangle():
         int status;
         char* ret = abi::__cxa_demangle( begin_name, &funcname[0],
                                          &funcnamesize, &status );
         if ( status == 0 )
         {
            funcname = ret; // use possibly realloc()-ed string
            fprintf( out, "  %-30s %-40s %s\n",
                     symbollist[i], funcname, begin_offset );
         } else {
            // demangling failed. Output function name as a C function with
            // no arguments.
            fprintf( out, "  %-30s %-38s() %s\n",
                     symbollist[i], begin_name, begin_offset );
         }

#else // !DARWIN - but is posix
      // not OSX style
      // ./module(function+0x15c) [0x8048a6d]
      for ( char *p = symbollist[i]; *p; ++p )
      {
         if ( *p == '(' )
            begin_name = p;
         else if ( *p == '+' )
            begin_offset = p;
         else if ( *p == ')' && ( begin_offset || begin_name ))
            end_offset = p;
      }

      if ( begin_name && end_offset && ( begin_name < end_offset ))
      {
         *begin_name++   = '\0';
         *end_offset++   = '\0';
         if ( begin_offset )
            *begin_offset++ = '\0';

         // mangled name is now in [begin_name, begin_offset) and caller
         // offset in [begin_offset, end_offset). now apply
         // __cxa_demangle():

         int status = 0;
         char* ret = abi::__cxa_demangle( begin_name, funcname,
                                          &funcnamesize, &status );
         char* fname = begin_name;
         if ( status == 0 )
            fname = ret;

         if ( begin_offset )
         {
            fprintf( out, "  %-30s ( %-40s  + %-6s) %s\n",
                     symbollist[i], fname, begin_offset, end_offset );
         } else {
            fprintf( out, "  %-30s ( %-40s    %-6s) %s\n",
                     symbollist[i], fname, "", end_offset );
         }
#endif  // !DARWIN - but is posix
      } else {
         // couldn't parse the line? print the whole line.
         fprintf(out, "  %-40s\n", symbollist[i]);
      }
   }

   free(symbollist);

}

void abortHandler(int signum )
{
   // associate each signal with a signal name string.
   const char* name = nullptr;
   switch( signum )
   {
   case SIGABRT: name = "SIGABRT";  break;
   case SIGSEGV: name = "SIGSEGV";  break;
   case SIGBUS:  name = "SIGBUS";   break;
   case SIGILL:  name = "SIGILL";   break;
   case SIGFPE:  name = "SIGFPE";   break;
   }

   // Notify the user which signal was caught. We use printf, because this is the
   // most basic output function. Once you get a crash, it is possible that more
   // complex output systems like streams and the like may be corrupted. So we
   // make the most basic call possible to the lowest level, most
   // standard print function.
   if ( name )
      fprintf( stderr, "Caught signal %d (%s)\n", signum, name );
   else
      fprintf( stderr, "Caught signal %d\n", signum );

   // Dump a stack trace.
   // This is the function we will be implementing next.
   printStackTrace();

   // If you caught one of the above signals, it is likely you just
   // want to quit your program right now.
   exit( signum );
}


#include <execinfo.h>

