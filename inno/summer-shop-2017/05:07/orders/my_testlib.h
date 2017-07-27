/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 *
 * Created:       2012.12.10
 * Last modified: 2014.03.16
 *
 * About:
 *   This is minimalistic and fast variation of
 *   "testlib.h", v.0.7.4, Copyright (c) Mike Mirzayanov
 *   Look at http://code.google.com/p/testlib/ to get original "testlib.h"
 *   Look at http://acm.spbgu.ru/~sk1/download/my_testlib to get latest version
 *
 * Notes:
 *   1. Here there is no STL, no std::string. Only fast code, only hardcore.
 *   2. I tried to make this library maximal compatible with original "teslib.h"
 *   3. This library can be used only to create "validators" and "checkers". 
 */

#define VERSION "0.2.3"

#define MY_TESTLIB

#ifdef _MSC_VER
#  define _CRT_SECURE_NO_DEPRECATE
#  include <crtdefs.h>
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#  define ON_WINDOWS
#  include <windows.h>
#  include <io.h>
#  define I64 "%I64d"
#else
#  define I64 "%lld"
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cctype>
#include <climits>
#include <fcntl.h>

#ifndef EJUDGE // testsys, pcms2
#  define OK_EXIT_CODE 0
#  define WA_EXIT_CODE 1
#  define PE_EXIT_CODE 2
#  define FAIL_EXIT_CODE 3
#  define PC_BASE_EXIT_CODE 0
#else // ejudge
#  define OK_EXIT_CODE 0
#  define WA_EXIT_CODE 5
#  define PE_EXIT_CODE 4
#  define FAIL_EXIT_CODE 6
#  define PC_BASE_EXIT_CODE 0
#endif

#ifdef TESTSYS
#  undef PC_BASE_EXIT_CODE
#  define PC_BASE_EXIT_CODE 50
#endif

#define LF    10
#define CR    13
#define TAB   9
#define SPACE 32 
#define EOFC  26

#define byte unsigned char

enum TResult
{
  _ok, _wa, _pe, _fail, _dirt, _partially
};

#define _pc(exitCode) (TResult(_partially + (exitCode)))

int resultExitCode( TResult r )
{
  if (r == _ok)   return OK_EXIT_CODE;
  if (r == _wa)   return WA_EXIT_CODE;
  if (r == _pe)   return PE_EXIT_CODE;
  if (r == _fail) return FAIL_EXIT_CODE;
  return PC_BASE_EXIT_CODE + (r - _partially);
}

enum TColor
{
  LightGray = 0x07,
  LightRed = 0x0c,
  LightCyan = 0x0b,
  LightGreen = 0x0a,
  LightYellow = 0x0e
}; 

void textColor( unsigned short color )
{
#ifdef ON_WINDOWS
  static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, color);
#else 
  if (color == LightGray)
    printf("\e[0m");
  else
  {
    int c = 0;
    switch (color)
    {
      case LightRed: c = 31; break;
      case LightCyan: c = 36; break;
      case LightGreen: c = 32; break;
      case LightYellow: c = 33; break;
    }
    char buf[20];
    sprintf(buf, "\e[0;1;%dm", c);
    printf(buf);
  }
#endif
}

void quitscr( TColor color, const char *msg, ... )
{
  va_list list;
  va_start(list, msg);
  textColor(color);
  vprintf(msg, list);
  textColor(LightGray);
}

#define ensure(cond) do { if (!(cond)) quitf(_fail, "assertion failed, line: %d, condition: %s", __LINE__, #cond); } while (0)
#define quit quitf

void _quitf( TResult result, const char *msg, va_list list );
void quitf( TResult result, const char *msg, ... );

enum TMode
{
  _input, _output, _answer, _validator
};

FILE *resultFile;

struct InStream
{
  FILE *file;
  TMode mode;
  bool opened;

  InStream()
  {
    file = NULL;
  }

  void init( FILE *f, TMode mode, const char *fileName = 0 );
  void init( const char *fileName, TMode mode );

  void unreadChar( int c );
  int readChar( byte c );
  int readChar(); 
  int nextChar(); 
  int curChar();

  bool eof();
  bool eoln(); // chars are skipped iff eoln = TRUE
  void readEof();
  void readEoln();
  void readEoln( int i, int n ); // readSpace or readEoln
  int readSpace();
  bool seekEoln();
  bool seekEof();
  void skipBlanks();
  void skipSpaces();

  double readDouble();
  double readDouble( double l, double r );
  int readInt();
  int readInt( int l, int r );
  long long readLong();
  long long readLong( long long l, long long r );
  char *readWord();
  char *readToken()  { return readWord(); }
  char *readLine();
  char *readString() { return readLine(); }
  
  void quitf( TResult result, const char *msg, ... ) const
  {
    va_list list;
    va_start(list, msg);
    ::_quitf(mode == _output ? result : _fail, msg, list);
  }

  inline void _addToBuffer( char c ) const;
};

InStream inf;
InStream ouf;
InStream ans;

void _quitf( TResult result, const char *msg, va_list list )
{
  if (result == _ok && ouf.opened && !ouf.seekEof())
    quitf(_pe, "Extra information in the output file");
  if (result == _fail)
    quitscr(LightRed, "FAIL ");
  else if (result == _ok)
    quitscr(LightGreen, "ok ");
  else if (result == _wa)
    quitscr(LightRed, "wa ");
  else if (result == _pe)
    quitscr(LightCyan, "pe ");
  else // _pc
    quitscr(LightYellow, "partially correct (%d) ", result - _partially);
  vfprintf(resultFile ? resultFile : stdout, msg, list);
  puts("");
  exit(resultExitCode(result));
}

void quitf( TResult result, const char *msg, ... )
{
  va_list list;
  va_start(list, msg);
  _quitf(result, msg, list);
}

void InStream::init( FILE *f, TMode mode, const char *fileName )
{
  if (!f)
    quitf(_fail, "can not open file '%s'", fileName ? fileName : "unknown");
#ifdef ON_WINDOWS
#ifdef _MSC_VER
  _setmode(_fileno(f), O_BINARY);
#else
  setmode(fileno(f), O_BINARY);
#endif
#endif
  file = f;
  mode = mode;
  opened = false;
}

void InStream::init( const char *fileName, TMode mode )
{
  init(fopen(fileName, "rb"), mode, fileName);
  opened = true;
}

inline bool isEof(char c)
{
  return (c == EOF || c == EOFC);
}

inline bool isBlanks( int c )
{
  return (c == SPACE || c == LF || c == CR || c == TAB);
}

inline bool isSpaces( int c )
{
  return (c == SPACE || c == TAB);
}

inline char* outputChar( int x )
{
  char buf[8];
  if (x == -1 || x == 10 || x == 13 || x == 26 || x == 8 || x == 7 || x == 0)
    sprintf(buf, "\\%d", x);
  else
    sprintf(buf, "%c", (char)x);
  return strdup(buf);
}

inline bool isEoln( int c )
{
  return (c == LF || c == CR);
}

inline void InStream::unreadChar( int c )
{
  ungetc(c, file);
}

inline int InStream::readChar()
{
  return getc(file);
}

inline int InStream::nextChar()
{
  return readChar();
}

inline int InStream::curChar()
{
  int res = readChar();
  unreadChar(res);
  return res;
}

inline int InStream::readChar( byte c )
{
  int res = readChar();
  if (res == -1)
    quitf(_pe, "Unexpected end of file");
  else if (res != c)
    quitf(_pe, "Expected char '%c', but '%s' found", c, outputChar(res));
  return res;
}

inline int InStream::readSpace()
{
  return readChar(SPACE);
}

inline bool InStream::eoln()
{
  int c = readChar(), back = -1;
#ifdef ON_WINDOWS // CR LF
  if (c != CR) 
  {
    unreadChar(c);
    return false;
  }
  back = c, c = readChar();
#endif // else only LF
  if (c != LF)
  {
    unreadChar(c);
    if (back != -1)
      unreadChar(back);
    return false;
  }
  return true;
}

inline bool InStream::eof()
{
  return isEof(curChar());
}

inline void InStream::readEoln()
{
  if (!eoln())
    quitf(_pe, "Expected EOLN");
}

inline void InStream::readEoln( int i, int n )
{
  if (i == n - 1)
    readEoln();
  else
    readSpace();
}

inline void InStream::readEof()
{
  if (!eof())
    quitf(_pe, "Expected EOF");
}

inline void InStream::skipSpaces()
{
  int c;
  while (isSpaces(c = readChar()))
    ;
  unreadChar(c);
}

inline void InStream::skipBlanks()
{
  if (mode == _validator)
    return;
  int c;
  while (isBlanks(c = readChar()))
    ;
  unreadChar(c);
}

inline bool InStream::seekEoln()
{
  skipSpaces();
  return eoln();
}

inline bool InStream::seekEof()
{
  int c;
  while (isBlanks(c = readChar()))
    ;
  if (isEof(c))
    return true;
  unreadChar(c);
  return false;
}

long long InStream::readLong( long long l, long long r )
{
  skipBlanks();

  long long x = 0;
  int sign = 1, c = readChar();
  if (c == '-') 
    sign = -1, c = readChar();
  if (isdigit(c))
  {
    int len = 0, zeroes = 0;
    while (c == '0')
      c = readChar(), zeroes++;
    while (isdigit(c))
    {
      x = x * 10 + c - '0';
      if (++len >= 19)
      {
        long long t = LONG_LONG_MAX - x;
        if ((sign == 1 && t < 0) || (sign == -1 && t < -1))
          quitf(_pe, "64-bit signed integer overflow");
      }
      c = readChar();
    }
    if (zeroes && zeroes + len > 1)
      quitf(_pe, "Leading zeroes are not allowed [zeroes = %d, len = %d]", zeroes, len);
  }
  else
    quitf(_pe, "Expected integer, but '%s' found", outputChar(c));
  unreadChar(c);
  x *= sign;
  if (!(l <= x && x <= r))
    quitf(_pe, "parse integer: out of range ["I64".."I64"]", l, r);
  return x;
}

int InStream::readInt( int l, int r )
{
  return readLong(l, r);
}

int InStream::readInt()
{
  return readLong(INT_MIN, INT_MAX);
}

long long InStream::readLong()
{
  return readLong(LONG_LONG_MIN, LONG_LONG_MAX);
}

double InStream::readDouble()
{
  char *s = readWord(), *t = s;
  int bad = 0;
  if (*t == '-' || *t == '+')
    t++;
  bad |= !isdigit(*t);
  while (isdigit(*t))
    t++;
  if (*t == '.')
    for (t++; isdigit(*t); t++)
      ;
  if (*t == 'e' || *t == 'E')
    for (t++, bad |= !isdigit(*t); isdigit(*t); t++)
      ;
  if (bad)
    quitf(_pe, "parse double: digit expected");
  if (*t)
    quitf(_pe, "parse double: extra information");

  double x;
  if (sscanf(s, "%lf", &x) != 1)
    quitf(_fail, "parse double: sscanf can not parse string");
  return x; 
}

double InStream::readDouble( double l, double r )
{
  double x = readDouble();
  if (!(l <= x && x <= r))
    quitf(_pe, "parse double: out of range [%f to %f]", l, r);
  return x;
}

namespace __testlib
{
  const int maxMem = (int)1e7;
  char mem[maxMem], *memPos = mem;
  const char *memEnd = mem + maxMem;

  inline void resetBuffer()
  {
    memPos = mem;
  }
};

inline void InStream::_addToBuffer( char c ) const
{
  if (__testlib::memPos == __testlib::memEnd)
    quitf(_pe, "__testlib::mem overflow [ML = %d bytes]", __testlib::maxMem);
  *__testlib::memPos++ = c;
}

char *InStream::readWord()
{
  skipBlanks();
  char *res = __testlib::memPos;
  while (1)
  {
    int c = readChar();
    if (isBlanks(c) || c == -1)
    {
      unreadChar(c);
      break;
    }
    _addToBuffer(c);
  }
  _addToBuffer(0);
  return res;
}

char *InStream::readLine()
{
  char *res = __testlib::memPos;
  int c, last = -1;
  while ((c = readChar()) != -1 && c != LF)
    last = c, _addToBuffer(c);
  if (mode == _validator)
    ensure(c == LF);
  #ifdef ON_WINDOWS
  if (mode == _validator)
    ensure(last == CR);
  if (c != -1)
    __testlib::memPos--;
  #endif
  _addToBuffer(0);
  return res;
}

void registerValidation()
{
  inf.init(stdin, _validator);
}

void registerTestlibCmd( int argc, char *argv[] )
{
  if (argc < 4)
    quitf(_fail, "Usage: <input-file> <output-file> <answer-file> [report-file]");

  inf.init(argv[1], _input);
  ouf.init(argv[2], _output);
  ans.init(argv[3], _answer);

  resultFile = argc < 5 ? 0 : fopen(argv[4], "wt");
}
