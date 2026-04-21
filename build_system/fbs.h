/*
** See end of file for license information.
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// BEGIN HEADER GUARD
//
#if !defined(FBS_H)
#  define FBS_H


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// CONFIG
//
#if !defined(FBS_ALLOC) && !defined(FBS_REALLOC) && !defined(FBS_FREE)
#  include <stdlib.h>
#  define FBS_ALLOC(size) malloc(size)
#  define FBS_REALLOC(data, size) realloc(data, size)
#  define FBS_FREE(data) free(data)
#elif !defined(FBS_ALLOC) || !defined(FBS_REALLOC) || !defined(FBS_FREE)
#  error Must define all or none of FBS_ALLOC, FBS_REALLOC, and FBS_FREE
#endif

#if !defined(FBS_PRINTF_PROC)
#  include <stdio.h>
#  define FBS_PRINTF_PROC(format, ...) do { printf((format), ##__VA_ARGS__); } while(0)
#endif

#if !defined(FBS_API)
#  define FBS_API static
#endif

#if !defined(FBS_DEFAULT_CAPACITY)
#  define FBS_DEFAULT_CAPACITY 64
#endif

#if !defined(FBS_MAX_SUBCOMMAND_ALIAS_COUNT)
#  define FBS_MAX_SUBCOMMAND_ALIAS_COUNT 8
#endif

#if !defined(FBS_EMSCRIPTEN_PATH)
#  if defined(_WIN32) || defined(_WIN64)
#    define FBS_EMSCRIPTEN_PATH "C:/emsdk/upstream/emscripten/"
#    define FBS_EMSCRIPTEN_INCLUDE_PATH FBS_EMSCRIPTEN_PATH "cache/sysroot/include/"
#  else
#    define FBS_EMSCRIPTEN_PATH ""
#    define FBS_EMSCRIPTEN_INCLUDE_PATH ""
#    define FBS_INVALID_EMSCRIPTEN_PATH
#  endif
#endif


// @compiler_info_begin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// CURRENT PLATFORM / COMPILER
//
#if defined(__EMSCRIPTEN__)
#  define FBS_CURRENT_PLATFORM_WEB 1
#  define FBS_CURRENT_COMPILER_EMSCRIPTEN 1
#elif defined(_WIN32) || defined(_WIN64)
#  define FBS_CURRENT_PLATFORM_WINDOWS 1
#elif defined(__unix)
#  define FBS_CURRENT_PLATFORM_UNIX 1
#  if defined(__linux__)
#    define FBS_CURRENT_PLATFORM_LINUX 1
#  elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#    define FBS_CURRENT_PLATFORM_FREEBSD 1
#    error FreeBSD is currently not supported.
#  else
#    error This operating system is not supported.
#  endif
#elif defined(__APPLE__)
#  if defined(__MACH__)
#    define FBS_CURRENT_PLATFORM_MACOS 1
#    error MacOS is currently not supported.
#  else
#    error This operating system is not supported.
#  endif
#else
#  error This operating system is not supported.
#endif

#if defined(_MSC_VER)
#  define FBS_CURRENT_COMPILER_MSVC 1
#  define FBS_CURRENT_CURRENT_COMPILER_EXECUTABLE "cl"
#elif defined(__GNUC__) || defined(__GNUG__)
#  define FBS_CURRENT_COMPILER_GCC 1
#  if FBS_CURRENT_PLATFORM_WINDOWS
#    define FBS_CURRENT_CURRENT_COMPILER_EXECUTABLE "gcc"
#  elif FBS_CURRENT_PLATFORM_WEB
#    define FBS_CURRENT_CURRENT_COMPILER_EXECUTABLE "emcc"
#  else
#    define FBS_CURRENT_CURRENT_COMPILER_EXECUTABLE "cc"
#  endif
#elif defined(__TINYC__)
#  error TCC is currently not supported.
#  define FBS_CURRENT_COMPILER_TCC 1
#  define FBS_CURRENT_CURRENT_COMPILER_EXECUTABLE "tcc"
#elif defined(__clang__)
#  error Clang is currently not supported.
#  define FBS_CURRENT_COMPILER_CLANG 1
#  define FBS_CURRENT_CURRENT_COMPILER_EXECUTABLE "clang"
#else
#  error This compiler is not supported.
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// PLATFORM TARGETS
//
#define FBS_PLATFORM_TARGET_DEFAULT      0
#define FBS_PLATFORM_TARGET_DEFAULT_NAME "default"
#define FBS_PLATFORM_TARGET_WINDOWS      1
#define FBS_PLATFORM_TARGET_WINDOWS_NAME "windows"
#define FBS_PLATFORM_TARGET_WEB          2
#define FBS_PLATFORM_TARGET_WEB_NAME     "web"
#define FBS_PLATFORM_TARGET_LINUX        3
#define FBS_PLATFORM_TARGET_LINUX_NAME   "linux"
#define FBS_PLATFORM_TARGET_MACOS        4
#define FBS_PLATFORM_TARGET_MACOS_NAME   "macos"

#if defined(FBS_PLATFORM_TARGET) && (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_DEFAULT)
#  undef FBS_PLATFORM_TARGET
#endif

#if !defined(FBS_PLATFORM_TARGET)
#  if defined(FBS_PLATFORM_TARGET_NAME)
#    undef FBS_PLATFORM_TARGET_NAME
#  endif
#  if FBS_CURRENT_PLATFORM_WINDOWS
#    define FBS_PLATFORM_TARGET FBS_PLATFORM_TARGET_WINDOWS
#  elif FBS_CURRENT_PLATFORM_WEB
#    define FBS_PLATFORM_TARGET FBS_PLATFORM_TARGET_WEB
#  elif FBS_CURRENT_PLATFORM_LINUX
#    define FBS_PLATFORM_TARGET FBS_PLATFORM_TARGET_LINUX
#  elif FBS_CURRENT_PLATFORM_MACOS
#    define FBS_PLATFORM_TARGET FBS_PLATFORM_TARGET_MACOS
#  else
#    error Unkown platform!
#  endif
#endif

#if !defined(FBS_PLATFORM_TARGET_NAME)
#  if (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_WINDOWS)
#    define FBS_PLATFORM_TARGET_NAME FBS_PLATFORM_TARGET_WINDOWS_NAME
#  elif (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_WEB)
#    define FBS_PLATFORM_TARGET_NAME FBS_PLATFORM_TARGET_WEB_NAME
#  elif (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_LINUX)
#    define FBS_PLATFORM_TARGET_NAME FBS_PLATFORM_TARGET_LINUX_NAME
#  elif (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_MACOS)
#    define FBS_PLATFORM_TARGET_NAME FBS_PLATFORM_TARGET_MACOS_NAME
#  else
#    error Unkown platform!
#  endif
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// COMPILER TARGETS
//
#define FBS_COMPILER_TARGET_DEFAULT         0
#define FBS_COMPILER_TARGET_DEFAULT_NAME    "default"
#define FBS_COMPILER_TARGET_MSVC            1
#define FBS_COMPILER_TARGET_MSVC_NAME       "msvc"
#define FBS_COMPILER_TARGET_GCC             2
#define FBS_COMPILER_TARGET_GCC_NAME        "gcc"
#define FBS_COMPILER_TARGET_EMSCRIPTEN      3
#define FBS_COMPILER_TARGET_EMSCRIPTEN_NAME "emscripten"

#if defined(FBS_COMPILER_TARGET) && (FBS_COMPILER_TARGET == FBS_COMPILER_TARGET_DEFAULT)
#  undef FBS_COMPILER_TARGET
#endif

#if !defined(FBS_COMPILER_TARGET)
#  if defined(FBS_COMPILER_TARGET_NAME)
#    undef FBS_COMPILER_TARGET_NAME
#  endif
#  if FBS_CURRENT_COMPILER_MSVC
#    define FBS_COMPILER_TARGET FBS_COMPILER_TARGET_MSVC
#  elif FBS_CURRENT_COMPILER_GCC
#    define FBS_COMPILER_TARGET FBS_COMPILER_TARGET_GCC
#  elif FBS_CURRENT_COMPILER_EMSCRIPTEN
#    define FBS_COMPILER_TARGET FBS_COMPILER_TARGET_EMSCRIPTEN
#  else
#    error Unkown compiler!
#  endif
#endif

#if !defined(FBS_COMPILER_TARGET_NAME)
#  if (FBS_COMPILER_TARGET == FBS_COMPILER_TARGET_MSVC)
#    define FBS_COMPILER_TARGET_NAME FBS_COMPILER_TARGET_MSVC_NAME
#  elif (FBS_COMPILER_TARGET == FBS_COMPILER_TARGET_GCC)
#    define FBS_COMPILER_TARGET_NAME FBS_COMPILER_TARGET_GCC_NAME
#  elif (FBS_COMPILER_TARGET == FBS_COMPILER_TARGET_EMSCRIPTEN)
#    define FBS_COMPILER_TARGET_NAME FBS_COMPILER_TARGET_EMSCRIPTEN_NAME
#  else
#    error Unkown compiler!
#  endif
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// COMPILER INFO
//
#if (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_WINDOWS)
#  define FBS_EXECUTABLE_EXTENSION ".exe"
#  if (FBS_COMPILER_TARGET == FBS_COMPILER_TARGET_MSVC)
#    define FBS_SHARED_LIBRARY_EXTENSION ".dll"
#    define FBS_STATIC_LIBRARY_EXTENSION ".lib"
#    define FBS_OBJECT_FILE_EXTENSION ".obj"
#  else
#    define FBS_SHARED_LIBRARY_EXTENSION ".so"
#    define FBS_STATIC_LIBRARY_EXTENSION ".a"
#    define FBS_OBJECT_FILE_EXTENSION    ""
# endif
#elif (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_WEB)
#  define FBS_EXECUTABLE_EXTENSION     ""
#  define FBS_SHARED_LIBRARY_EXTENSION ""
#  define FBS_STATIC_LIBRARY_EXTENSION ""
#  define FBS_OBJECT_FILE_EXTENSION    ""
#else
#  define FBS_EXECUTABLE_EXTENSION     ""
#  define FBS_SHARED_LIBRARY_EXTENSION ".so"
#  define FBS_STATIC_LIBRARY_EXTENSION ".a"
#  define FBS_OBJECT_FILE_EXTENSION    ""
#endif

// @compiler_info_end


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// LOG
//
enum {
    FBS_LOG_LEVEL_ALWAYS,
    
    FBS_LOG_LEVEL_INFO,
    FBS_LOG_LEVEL_WARNING,
    FBS_LOG_LEVEL_ERROR,
    FBS_LOG_LEVEL_NONE
};

static int fbs_global_log_level = FBS_LOG_LEVEL_INFO;

#define FBS_LOG(level, format, ...) do {\
if(fbs_global_log_level < FBS_LOG_LEVEL_NONE) {\
if(FBS_LOG_LEVEL_##level == FBS_LOG_LEVEL_ALWAYS) {\
FBS_PRINTF_PROC(format, ##__VA_ARGS__);\
} else if(fbs_global_log_level <= FBS_LOG_LEVEL_##level) {\
if(FBS_LOG_LEVEL_##level == FBS_LOG_LEVEL_INFO) {\
FBS_PRINTF_PROC("[" FBS_LOG_COLOR_GRAY #level FBS_LOG_COLOR_RESET "] " format, ##__VA_ARGS__);\
} else if(FBS_LOG_LEVEL_##level == FBS_LOG_LEVEL_WARNING) {\
FBS_PRINTF_PROC(FBS_FILE_AND_LINE ": [" FBS_LOG_COLOR_MAGENTA #level FBS_LOG_COLOR_RESET "] " format, ##__VA_ARGS__);\
} else if(FBS_LOG_LEVEL_##level == FBS_LOG_LEVEL_ERROR) {\
FBS_PRINTF_PROC(FBS_FILE_AND_LINE ": [" FBS_LOG_COLOR_RED #level FBS_LOG_COLOR_RESET "] " format, ##__VA_ARGS__);\
} else {\
FBS_INVALID_CODE_PATH;\
}\
}\
}\
} while(0)

#if !defined(FBS_ENABLE_CONSOLE_COLORS) && defined(FUTHARK_ENABLE_CONSOLE_COLORS)
#  define FBS_ENABLE_CONSOLE_COLORS
#endif

#define FBS_LOG_COLOR(color, string_literal) FBS_LOG_COLOR_##color string_literal FBS_LOG_COLOR_RESET

#if defined(FBS_ENABLE_CONSOLE_COLORS)
#  define FBS_LOG_COLOR_RESET          "\x1b[0m"
#  define FBS_LOG_COLOR_BLACK          "\x1b[30m"
#  define FBS_LOG_COLOR_RED            "\x1b[31m"
#  define FBS_LOG_COLOR_GREEN          "\x1b[32m"
#  define FBS_LOG_COLOR_YELLOW         "\x1b[33m"
#  define FBS_LOG_COLOR_BLUE           "\x1b[34m"
#  define FBS_LOG_COLOR_MAGENTA        "\x1b[35m"
#  define FBS_LOG_COLOR_CYAN           "\x1b[36m"
#  define FBS_LOG_COLOR_WHITE          "\x1b[37m"
#  define FBS_LOG_COLOR_GRAY           "\x1b[90m"
#  define FBS_LOG_COLOR_GREY           "\x1b[90m"
#  define FBS_LOG_COLOR_BRIGHT_BLACK   "\x1b[90m"
#  define FBS_LOG_COLOR_BRIGHT_RED     "\x1b[91m"
#  define FBS_LOG_COLOR_BRIGHT_GREEN   "\x1b[92m"
#  define FBS_LOG_COLOR_BRIGHT_YELLOW  "\x1b[93m"
#  define FBS_LOG_COLOR_BRIGHT_BLUE    "\x1b[94m"
#  define FBS_LOG_COLOR_BRIGHT_MAGENTA "\x1b[95m"
#  define FBS_LOG_COLOR_BRIGHT_CYAN    "\x1b[96m"
#  define FBS_LOG_COLOR_BRIGHT_WHITE   "\x1b[97m"
#else
#  define FBS_LOG_COLOR_RESET
#  define FBS_LOG_COLOR_BLACK
#  define FBS_LOG_COLOR_RED
#  define FBS_LOG_COLOR_GREEN
#  define FBS_LOG_COLOR_YELLOW
#  define FBS_LOG_COLOR_BLUE
#  define FBS_LOG_COLOR_MAGENTA
#  define FBS_LOG_COLOR_CYAN
#  define FBS_LOG_COLOR_WHITE
#  define FBS_LOG_COLOR_GRAY
#  define FBS_LOG_COLOR_GREY
#  define FBS_LOG_COLOR_BRIGHT_BLACK
#  define FBS_LOG_COLOR_BRIGHT_RED
#  define FBS_LOG_COLOR_BRIGHT_GREEN
#  define FBS_LOG_COLOR_BRIGHT_YELLOW
#  define FBS_LOG_COLOR_BRIGHT_BLUE
#  define FBS_LOG_COLOR_BRIGHT_MAGENTA
#  define FBS_LOG_COLOR_BRIGHT_CYAN
#  define FBS_LOG_COLOR_BRIGHT_WHITE
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// INCLUDES
//
#if FBS_CURRENT_PLATFORM_WINDOWS
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  include <shellapi.h>
#else
#  include <sys/wait.h>
#  include <sys/stat.h>
#  include <unistd.h>
#  include <dirent.h>
#  include <errno.h>
#  include <string.h>
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// ASSERT MACROS
//
#define FBS_PANIC(format, ...) do {\
FBS_PRINTF_PROC(FBS_FILE_AND_LINE ": [" FBS_LOG_COLOR_BRIGHT_RED "PANIC" FBS_LOG_COLOR_RESET "] " format, ##__VA_ARGS__);\
*(volatile int *)0 = 0;\
} while(0)

#define FBS_ASSERT(expression) do {\
if(!(expression)) {\
FBS_PRINTF_PROC(FBS_FILE_AND_LINE ": [" FBS_LOG_COLOR_BRIGHT_RED "ASSERT" FBS_LOG_COLOR_RESET "] %s\n", #expression);\
*(volatile int *)0 = 0;\
}\
} while(0)

#define FBS_NOT_IMPLEMENTED FBS_PANIC("Not implemented!\n")
#define FBS_INVALID_CODE_PATH FBS_PANIC("Invalid code path reached!\n")
#define FBS_INVALID_DEFAULT_CASE default:{ FBS_PANIC("Invalid default case reached!\n"); } break


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// MISC MACROS
//
#define FBS_FILE_AND_LINE__(A, B) A "(" #B ")"
#define FBS_FILE_AND_LINE_(A, B) FBS_FILE_AND_LINE__(A, B)
#define FBS_FILE_AND_LINE FBS_FILE_AND_LINE_(__FILE__, __LINE__)

#if !defined(____)
#  define ____
#endif

#if !defined(FBS_IS_FLAG)
#  define FBS_IS_FLAG(var, flag) (((var) & (flag)) == (flag))
#endif

#if !defined(FBS_FIELD_ALIAS)
#  define FBS_FIELD_ALIAS(T, ...) union { T __VA_ARGS__; }
#endif

#if !defined(FBS_ARRAY_COUNT)
#  define FBS_ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// ARRAY MACROS
//
#if defined(__cplusplus)
#  define FBS_DECLTYPE(var) (decltype(var))
#  define FBS_CLITERAL(T) T
#else
#  define FBS_DECLTYPE(var)
#  define FBS_CLITERAL(T) (T)
#endif

#define FBS_ARRAY_FIELDS(Index_T, Element_T) \
Element_T *data;\
FBS_FIELD_ALIAS(Index_T, count, length)

#define FBS_LIST_FIELDS(Index_T, Element_T) \
FBS_ARRAY_FIELDS(Index_T, Element_T);\
Index_T capacity

#define FBS_VA_ARRAY(T, ...) ((const T *[]){__VA_ARGS__}), (sizeof((const T *[]){__VA_ARGS__}) / sizeof(const T *))

//

#define FBS_ALLOC_ARRAY(data, capacity) do {\
(data) = FBS_DECLTYPE(data)(FBS_ALLOC((capacity) * sizeof(*(data))));\
} while(0)

#define FBS_REALLOC_ARRAY(data, capacity) do {\
(data) = FBS_DECLTYPE(data)(FBS_REALLOC((data), (capacity) * sizeof(*(data))));\
} while(0)

#define FBS_MAYBE_GROW(this, new_capacity) do {\
if((new_capacity) > 0 && (new_capacity) >= (this)->capacity) {\
if((this)->capacity <= 0) { (this)->capacity = FBS_DEFAULT_CAPACITY; }\
while((this)->capacity < (new_capacity)) { (this)->capacity *= 2; }\
if((this)->data) {\
FBS_REALLOC_ARRAY((this)->data, (this)->capacity);\
} else {\
FBS_ALLOC_ARRAY((this)->data, (this)->capacity);\
}\
}\
} while(0)

//

#define FBS_APPEND(this, it) do {\
FBS_MAYBE_GROW(this, (this)->count + 1);\
(this)->data[(this)->count] = it;\
(this)->count += 1;\
} while(0)

#define FBS_APPEND_MANY(this, it_data, it_count) do {\
if((it_count) > 0) {\
FBS_MAYBE_GROW(this, (this)->count + (it_count));\
for(int _fbs_i_ = 0; _fbs_i_ < (it_count); _fbs_i_ += 1) {\
(this)->data[((this)->count + _fbs_i_)] = (it_data)[_fbs_i_];\
}\
(this)->count += (it_count);\
}\
} while(0)

#define FBS_APPEND_REPEATED(this, it, repeats) do {\
if((repeats) > 0) {\
FBS_MAYBE_GROW(this, (this)->count + (repeats));\
for(int _fbs_i_ = 0; _fbs_i_ < (repeats); _fbs_i_ += 1) {\
(this)->data[(this)->count + _fbs_i_] = (it);\
}\
(this)->count += (repeats);\
}\
} while(0)

#define FBS_APPEND_ARRAY(this, array) FBS_APPEND_MANY(this, (array).data, (array).count)
#define FBS_APPEND_STR_LIT(this, string_literal) FBS_APPEND_MANY(this, (char *)string_literal, sizeof(string_literal) - 1)
#define FBS_APPEND_VA(this, T, ...) FBS_APPEND_MANY(this, FBS_VA_ARRAY(T, __VA_ARGS__))
#define FBS_APPEND_NTSTRING(this, ntstring) do {\
int _fbs_ntstring_length_ = fbs_ntstring_length(ntstring);\
FBS_APPEND_MANY(this, ntstring, _fbs_ntstring_length_);\
} while(0)

#define FBS_APPEND_STR_LIT_AS_STRING(this, string_literal) do {\
FBS_String _fbs_string_ = FBS_String_lit(string_literal);\
FBS_APPEND(this, _fbs_string_);\
} while(0)

#define FBS_APPEND_NTSTRING_AS_STRING(this, ntstring) do {\
FBS_String _fbs_string_ = {0}:\
_fbs_string_.data = ntstring;\
if(ntstring) {\
while(ntstring[_fbs_string_.count]) { _fbs_string_.count += 1; }\
}\
FBS_APPEND(this, _fbs_string_);\
} while(0)

//

#define FBS_DIGITS_STRING "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define FBS_APPEND_INT(this, value, base) do {\
if((base) >= 2 && (base) <= 36) {\
long long _fbs_value_ = (long long)(value);\
if(_fbs_value_ < 0) {\
FBS_APPEND(this, '-');\
_fbs_value_ = -_fbs_value_;\
}\
int _fbs_offset_ = (int)(this)->count;\
while(_fbs_value_ >= (int)(base)) {\
FBS_APPEND(this, FBS_DIGITS_STRING[_fbs_value_ % (long long)(base)]);\
_fbs_value_ /= (long long)(base);\
}\
FBS_APPEND(this, FBS_DIGITS_STRING[_fbs_value_ % (long long)(base)]);\
FBS_MAYBE_GROW(this, (this)->count + 1);\
for(int _fbs_l_ = _fbs_offset_, _fbs_r_ = (this)->count - 1;\
_fbs_l_ < _fbs_r_; _fbs_l_ += 1, _fbs_r_ -= 1)\
{\
(this)->data[(this)->count] = (this)->data[_fbs_l_];\
(this)->data[_fbs_l_] = (this)->data[_fbs_r_];\
(this)->data[_fbs_r_] = (this)->data[(this)->count];\
}\
}\
} while(0)

#define FBS_APPEND_FLOAT(this, value, precision) do {\
double _fbs_value_ = (double)(value);\
if(_fbs_value_ < 0) {\
FBS_APPEND(this, '-');\
_fbs_value_ = -_fbs_value_;\
}\
int _fbs_offset_ = (int)(this)->count;\
int _fbs_truncated_ = (int)_fbs_value_;\
double _fbs_remainder_ = _fbs_value_ - (double)_fbs_truncated_;\
while(_fbs_truncated_ >= 10) {\
FBS_APPEND(this, '0' + (_fbs_truncated_ % 10));\
_fbs_truncated_ /= 10;\
}\
FBS_APPEND(this, '0' + (_fbs_truncated_ % 10));\
FBS_MAYBE_GROW(this, (this)->count + 1);\
for(int _fbs_l_ = _fbs_offset_, _fbs_r_ = (this)->count - 1;\
_fbs_l_ < _fbs_r_; _fbs_l_ += 1, _fbs_r_ -= 1)\
{\
(this)->data[(this)->count] = (this)->data[_fbs_l_];\
(this)->data[_fbs_l_] = (this)->data[_fbs_r_];\
(this)->data[_fbs_r_] = (this)->data[(this)->count];\
}\
if(_fbs_remainder_ > 0.0f) {\
FBS_APPEND(this, '.');\
for(int _fbs_i_ = 0; _fbs_i_ < (int)(precision); _fbs_i_ += 1) {\
_fbs_remainder_ *= 10.0f;\
_fbs_truncated_ = (int)_fbs_remainder_;\
FBS_APPEND(this, '0' + (_fbs_truncated_ % 10));\
_fbs_remainder_ -= _fbs_truncated_;\
if(_fbs_remainder_ <= 0.0f) { break; }\
}\
}\
} while(0)

//

#define FBS_NULL_TERMINATE(this) do {\
FBS_MAYBE_GROW(this, (this)->count + 1);\
(this)->data[(this)->count] = 0;\
} while(0)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// BASIC TYPES
//
enum { FBS_FALSE, FBS_TRUE };

typedef int fbs_bool;
typedef int fbs_error;

typedef struct FBS_String { FBS_LIST_FIELDS(int, char); } FBS_String;
#define FBS_String(...) fbs_set_string(__VA_ARGS__)

#define FBS_String_lit(string_literal) FBS_CLITERAL(FBS_String){(string_literal), sizeof(string_literal) - 1, -1}

typedef struct List_FBS_String { FBS_LIST_FIELDS(int, FBS_String); } List_FBS_String;
#define List_FBS_String(...) fbs_set_string_list(__VA_ARGS__)

typedef struct List_FBS_NTString { FBS_LIST_FIELDS(int, char *); } List_FBS_NTString;
#define List_FBS_NTString(...) fbs_set_ntstring_list(__VA_ARGS__)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// LEXER TYPES
//
enum {
    FBS_TOKEN_END_OF_FILE = 256,
    FBS_TOKEN_PARSE_ERROR,
    FBS_TOKEN_INT_LITERAL,
    FBS_TOKEN_FLOAT_LITERAL,
    FBS_TOKEN_STRING_LITERAL,
    FBS_TOKEN_CHAR_LITERAL,
    FBS_TOKEN_IDENTIFIER,
    FBS_TOKEN_KEYWORD,
    
    FBS_TOKEN_WHITESPACE,
    FBS_TOKEN_NEWLINE,
    FBS_TOKEN_LINE_COMMENT,
    FBS_TOKEN_BLOCK_COMMENT,
    
    FBS_TOKEN_EQUAL_EQUAL,
    FBS_TOKEN_NOT_EQUAL,
    FBS_TOKEN_LESS_THAN_EQUAL,
    FBS_TOKEN_GREATER_THAN_EQUAL,
    FBS_TOKEN_AND_AND,
    FBS_TOKEN_AND_EQUAL,
    FBS_TOKEN_OR_OR,
    FBS_TOKEN_OR_EQUAL,
    FBS_TOKEN_PLUS_PLUS,
    FBS_TOKEN_PLUS_EQUAL,
    FBS_TOKEN_MINUS_MINUS,
    FBS_TOKEN_MINUS_EQUAL,
    FBS_TOKEN_MULTIPLY_EQUAL,
    FBS_TOKEN_DIVIDE_EQUAL,
    FBS_TOKEN_PERCENT_EQUAL,
    FBS_TOKEN_XOR_EQUAL,
    FBS_TOKEN_SHIFT_LEFT,
    FBS_TOKEN_SHIFT_LEFT_EQUAL,
    FBS_TOKEN_SHIFT_RIGHT,
    FBS_TOKEN_SHIFT_RIGHT_EQUAL,
    FBS_TOKEN_ARROW,
    FBS_TOKEN_THICK_ARROW,
    
    FBS_TOKEN_USER,
};

typedef struct FBS_Token {
    double    fvalue;
    long long ivalue;
    char *text;
    int   length;
    int line;
    unsigned short kind;
} FBS_Token;

typedef struct List_FBS_Token { FBS_LIST_FIELDS(int, FBS_Token); } List_FBS_Token;

typedef struct FBS_Lexer {
    FBS_String input_text;
    FBS_String token_text;
    double    fvalue;
    long long ivalue;
    int cursor, line;
    unsigned short token_kind;
} FBS_Lexer;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// COMMAND TYPES
//
typedef fbs_error FBS_Subcommand_Proc(int arg_count, char **arg_data);

typedef struct FBS_Subcommand {
    FBS_Subcommand_Proc *proc;
    const char *name;
    const char *description;
    const char *aliases[FBS_MAX_SUBCOMMAND_ALIAS_COUNT];
} FBS_Subcommand;

typedef struct List_FBS_Subcommand { FBS_LIST_FIELDS(int, FBS_Subcommand); } List_FBS_Subcommand;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// COMPILER TYPES
//
enum {
    FBS_DISABLE_OPTIMIZATION   = 1,
    FBS_OPTIMIZATION_MIN_CODE  = 2,
    FBS_OPTIMIZATION_MAX_SPEED = 3,
    
    FBS_OUTPUT_SHARED_LIBRARY = 0x04,
    FBS_OUTPUT_STATIC_LIBRARY = 0x08,
    FBS_ENABLE_DEBUG_OUTPUT   = 0x10,
    FBS_DISABLE_LINKING       = 0x20,
    FBS_ONLY_RUN_LINKER       = 0x40,
    
    // NOTE(Patrik): Used for checking
    FBS_OPTIMIZATION_MASK = FBS_DISABLE_OPTIMIZATION | FBS_OPTIMIZATION_MIN_CODE | FBS_OPTIMIZATION_MAX_SPEED,
    FBS_OUTPUT_AS_LIBRARY = FBS_OUTPUT_SHARED_LIBRARY | FBS_OUTPUT_STATIC_LIBRARY,
};


typedef struct FBS_Compiler_Linker_Args {
    List_FBS_String compiler;
    List_FBS_String linker;
} FBS_Compiler_Linker_Args;

typedef struct FBS_Compiler {
    struct ____ {
        FBS_Compiler_Linker_Args msvc;
        FBS_Compiler_Linker_Args gcc;
        FBS_Compiler_Linker_Args emscripten;
    };
    
    List_FBS_String input_files;
    FBS_String      output_directory;
    FBS_String      output_file_name;
    
    List_FBS_String defines;
    List_FBS_String include_directories;
    
    List_FBS_String link_to_objects;
    List_FBS_String link_to_libraries;
    List_FBS_String export_functions;
    FBS_String      icon_path;
    
    unsigned char optimization;
    unsigned char flags;
} FBS_Compiler;


typedef struct FBS_Async_Proc {
#if FBS_CURRENT_PLATFORM_WINDOWS
    HANDLE handle;
#else
    int handle;
#endif
    
    int error;
} FBS_Async_Proc;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// API
//
FBS_API void fbs_append_default_platform_and_compiler_target_config(FBS_String *builder);
FBS_API void fbs_append_default_config(FBS_String *builder);

//

FBS_API fbs_error fbs_run_subcommand(int arg_count, char **arg_data, List_FBS_Subcommand subcommands, int *used_subcommand_index);

//

FBS_API void           fbs_render_command(FBS_String *buffer, List_FBS_String command);
FBS_API int            fbs_wait_for_async_proc(FBS_Async_Proc proc);
FBS_API FBS_Async_Proc fbs_run_command_async(List_FBS_String command);
FBS_API int            fbs_run_command_sync(List_FBS_String command);

//

FBS_API int          fbs_self_rebuild(int arg_count, char **arg_data, const char *old_executable_path, List_FBS_String *source_paths);
FBS_API FBS_Compiler fbs_copy_compiler_settings(FBS_Compiler compiler);

FBS_API List_FBS_String fbs_compiler_to_commands(FBS_Compiler compiler);
FBS_API int fbs_run_compiler(FBS_Compiler compiler);
FBS_API int fbs_run_compiler_msvc(FBS_Compiler compiler);
FBS_API int fbs_run_compiler_gcc(FBS_Compiler compiler);
FBS_API int fbs_run_compiler_emscripten(FBS_Compiler compiler);

//

FBS_API fbs_error fbs_file_exists(const char *path);
FBS_API fbs_error fbs_delete_file(const char *path);
FBS_API fbs_error fbs_move_file(const char *from_path, const char *to_path);
FBS_API fbs_error fbs_copy_file(const char *from_path, const char *to_path);
FBS_API fbs_error fbs_read_entire_file(const char *path, FBS_String *buffer);
FBS_API fbs_error fbs_write_entire_file(const char *path, void *data, int length);
FBS_API fbs_error fbs_is_file_newer(const char *this_path, const char *other_path);

FBS_API fbs_error       fbs_directory_exists(const char *path);
FBS_API fbs_error       fbs_create_directory_if_new(const char *path);
FBS_API fbs_error       fbs_remove_directory_recursively(const char *path);
FBS_API List_FBS_String fbs_get_directory_files(const char *path);

//

FBS_API fbs_error fbs_sync_files(const char *from_directory, const char *to_directory, const char **file_names, int file_count);

//

FBS_API int               fbs_ntstring_length(const char *ntstring);
FBS_API FBS_String        fbs_set_string(const char *data, int count, int capacity);
FBS_API FBS_String        fbs_ntstring_to_string(const char *ntstring);
FBS_API List_FBS_String   fbs_string_to_list(FBS_String string);
FBS_API List_FBS_String   fbs_set_string_list(FBS_String *data, int count, int capacity);
FBS_API List_FBS_String   fbs_string_list_from_ntstring_list(List_FBS_NTString it);
FBS_API List_FBS_NTString fbs_set_ntstring_list(const char **data, int count, int capacity);
FBS_API List_FBS_NTString fbs_ntstring_list_from_string_list(List_FBS_String it);

FBS_API fbs_bool fbs_many_eq(const char *a_data, int a_length, const char *b_data, int b_length);
FBS_API fbs_bool fbs_many_eq_string(const char *a_data, int a_length, FBS_String b);
FBS_API fbs_bool fbs_many_eq_ntstring(const char *a_data, int a_length, const char *b);
FBS_API fbs_bool fbs_string_eq_many(FBS_String a, const char *b_data, int b_length);
FBS_API fbs_bool fbs_string_eq(FBS_String a, FBS_String b);
FBS_API fbs_bool fbs_string_eq_ntstring(FBS_String a, const char *b);
FBS_API fbs_bool fbs_ntstring_eq_many(const char *a, const char *b_data, int b_length);
FBS_API fbs_bool fbs_ntstring_eq_string(const char *a, FBS_String b);
FBS_API fbs_bool fbs_ntstring_eq(const char *a, const char *b);

FBS_API fbs_bool fbs_begins_with_char(FBS_String a, char b);
FBS_API fbs_bool fbs_begins_with(FBS_String a, FBS_String b);
FBS_API fbs_bool fbs_begins_with_ntstring(FBS_String a, const char *b);
FBS_API fbs_bool fbs_ends_with_char(FBS_String a, char b);
FBS_API fbs_bool fbs_ends_with(FBS_String a, FBS_String b);
FBS_API fbs_bool fbs_ends_with_ntstring(FBS_String a, const char *b);

FBS_API int fbs_index_of_char(FBS_String a, char b);
FBS_API int fbs_index_of_string(FBS_String a, FBS_String b);
FBS_API int fbs_index_of_ntstring(FBS_String a, const char *b);
FBS_API int fbs_index_of_any(FBS_String a, FBS_String b);
FBS_API int fbs_index_of_any_ntstring(FBS_String a, const char *b);
FBS_API int fbs_last_index_of_char(FBS_String a, char b);
FBS_API int fbs_last_index_of_string(FBS_String a, FBS_String b);
FBS_API int fbs_last_index_of_ntstring(FBS_String a, const char *b);
FBS_API int fbs_last_index_of_any(FBS_String a, FBS_String b);
FBS_API int fbs_last_index_of_any_ntstring(FBS_String a, const char *b);

//

FBS_API FBS_Lexer fbs_lexer_from_file(const char *path);
FBS_API char fbs_lexer_peek_char(FBS_Lexer lexer, int offset_from_cursor);
FBS_API fbs_bool fbs_parse_next_token(FBS_Lexer *lexer);
FBS_API FBS_Token fbs_get_current_token(FBS_Lexer lexer);
FBS_API List_FBS_Token fbs_parse_all_tokens(FBS_Lexer *lexer);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// ERROR CODES
//
enum {
    
    FBS_ERROR_GENERIC = -1,
    FBS_ERROR_PATH_IS_NULL = -512,
    
    FBS_ERROR_STRING_DATA_IS_NULL = -1024,
    FBS_ERROR_STRING_DATA_IS_EMPTY = -1025,
    FBS_ERROR_STRING_LENGTHS_DO_NOT_MATCH = -1026,
    FBS_ERROR_INDEX_NOT_FOUND = -2048,
    
    FBS_ERROR_NAME_DOESNT_MATCH_A_SUBCOMMAND = -4096,
    FBS_ERROR_MISSING_SUBCOMMAND = -4097,
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// END HEADER GUARD
//
#endif


//~~~~~~~~~~~~~~~~
//
// BEGIN IMPLEMENTATION GUARD
//
#if defined(FBS_IMPLEMENTATION) && !defined(FBS_IMPLEMENTATION_DONE)
#  define FBS_IMPLEMENTATION_DONE


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// GLOBALS
//
static FBS_String fbs_global_build_program_path = {0};
static FBS_String fbs_global_build_source_path = {0};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// CONFIG GENERATOR
//
FBS_API void
fbs_append_default_platform_and_compiler_target_config(FBS_String *buffer) {
    if(!buffer) { return; }
    
    struct ____ { const char *name; int value; } platform_targets[] = {
        "FBS_PLATFORM_TARGET_WINDOWS", FBS_PLATFORM_TARGET_WINDOWS,
        "FBS_PLATFORM_TARGET_WEB", FBS_PLATFORM_TARGET_WEB,
        "FBS_PLATFORM_TARGET_LINUX", FBS_PLATFORM_TARGET_LINUX,
    };
    
    struct ____ { const char *name; int value; } compiler_targets[] = {
        "FBS_COMPILER_TARGET_MSVC", FBS_COMPILER_TARGET_MSVC,
        "FBS_COMPILER_TARGET_GCC", FBS_COMPILER_TARGET_GCC,
        "FBS_COMPILER_TARGET_EMSCRIPTEN", FBS_COMPILER_TARGET_EMSCRIPTEN,
    };
    
    FBS_APPEND_STR_LIT(buffer, "//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "// PLATFORM TARGET\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "// NOTE: This decides which platform to build for.\n");
    FBS_APPEND_STR_LIT(buffer, "// If no platform is specified, one will be assumed based on the current platform.\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    for(int i = 0; i < FBS_ARRAY_COUNT(platform_targets); i += 1) {
        const char *target_name        = platform_targets[i].name;
        int         target_name_length = fbs_ntstring_length(target_name);
        
        FBS_APPEND_STR_LIT(buffer, "//#define FBS_PLATFORM_TARGET ");
        FBS_APPEND_MANY(buffer, target_name, target_name_length);
        FBS_APPEND(buffer, '\n');
    }
    FBS_APPEND_STR_LIT(buffer, "\n\n");
    
    FBS_APPEND_STR_LIT(buffer, "//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "// COMPILER TARGET\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "// NOTE: This decides which platform to build for.\n");
    FBS_APPEND_STR_LIT(buffer, "// If no compiler is specified, one will be assumed based on the current platform.\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    for(int i = 0; i < FBS_ARRAY_COUNT(compiler_targets); i += 1) {
        const char *target_name        = compiler_targets[i].name;
        int         target_name_length = fbs_ntstring_length(target_name);
        
        FBS_APPEND_STR_LIT(buffer, "//#define FBS_COMPILER_TARGET ");
        FBS_APPEND_MANY(buffer, target_name, target_name_length);
        FBS_APPEND(buffer, '\n');
    }
    FBS_APPEND_STR_LIT(buffer, "\n\n");
}

FBS_API void
fbs_append_default_config(FBS_String *buffer) {
    if(!buffer) { return; }
    
    FBS_LOG(INFO, ">> Generating config file...\n");
    
    FBS_APPEND_STR_LIT(buffer, "//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "// BEGIN INCLUDE GUARD\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "#if !defined(FBS_CONFIG_H)\n");
    FBS_APPEND_STR_LIT(buffer, "#define FBS_CONFIG_H\n\n\n");
    
    FBS_APPEND_STR_LIT(buffer, "//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "// FBS CONFIG\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "//#define FBS_ENABLE_CONSOLE_COLORS\n");
    FBS_APPEND_STR_LIT(buffer, "\n\n");
    
    fbs_append_default_platform_and_compiler_target_config(buffer);
    
    FBS_APPEND_STR_LIT(buffer, "//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "// END INCLUDE GUARD\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "#endif // FBS_CONFIG_H\n");
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// PLATFORM API
//
FBS_API int
fbs_ntstring_length(const char *ntstring) {
    if(!ntstring) { return 0; }
    int result = 0;
    while(ntstring[result]) { result += 1; }
    return result;
}

FBS_API FBS_String
fbs_set_string(const char *data, int count, int capacity) {
    FBS_String result = { (char *)data, count, capacity };
    return result;
}

FBS_API FBS_String
fbs_ntstring_to_string(const char *ntstring) {
    int length = fbs_ntstring_length(ntstring);
    FBS_String result = fbs_set_string(ntstring, length, length);
    return result;
}

FBS_API List_FBS_String
fbs_string_to_list(FBS_String string) {
    List_FBS_String result = {0};
    if(!string.data) { return result; }
    
    FBS_String it = {0};
    it.data = string.data;
    it.capacity = -1;
    for(int i = 0; i < string.length; i += 1) {
        if(string.data[i] == 0) {
            FBS_APPEND(&result, it);
            it.data = string.data + i + 1;
            it.length = 0;
        } else {
            it.length += 1;
        }
    }
    
    if(it.length > 0) { FBS_APPEND(&result, it); }
    
    return result;
}

FBS_API List_FBS_String
fbs_set_string_list(FBS_String *data, int count, int capacity) {
    List_FBS_String result = {0};
    result.data = data;
    result.count = count;
    result.capacity = capacity;
    return result;
}

FBS_API List_FBS_String
fbs_string_list_from_ntstring_list(List_FBS_NTString it) {
    List_FBS_String result = {0};
    
    if(!it.data) { return result; }
    if(it.count <= 0) { return result; }
    
    for(int i = 0; i < it.count; i += 1) {
        FBS_String s = {0};
        FBS_APPEND_NTSTRING(&s, it.data[i]);
        FBS_NULL_TERMINATE(&s);
        
        FBS_APPEND(&result, s);
    }
    
    return result;
}

FBS_API List_FBS_NTString
fbs_set_ntstring_list(const char **data, int count, int capacity) {
    List_FBS_NTString result = {0};
    result.data = (char **)data;
    result.count = count;
    result.capacity = capacity;
    return result;
}

FBS_API List_FBS_NTString
fbs_ntstring_list_from_string_list(List_FBS_String it) {
    List_FBS_NTString result = {0};
    
    if(!it.data) { return result; }
    if(it.count <= 0) { return result; }
    
    for(int i = 0; i < it.count; i += 1) {
        FBS_String s = {0};
        FBS_APPEND_ARRAY(&s, it.data[i]);
        FBS_NULL_TERMINATE(&s);
        
        FBS_APPEND(&result, s.data);
    }
    
    return result;
}

//

FBS_API fbs_bool
fbs_many_eq(const char *a_data, int a_length, const char *b_data, int b_length) {
    if(a_length != b_length) { return FBS_FALSE; }
    if(a_data == b_data) { return FBS_TRUE; }
    if(!a_data || !b_data) { return FBS_FALSE; }
    for(int i = 0; i < a_length; i += 1) {
        if(a_data[i] != b_data[i]) { return FBS_FALSE; }
    }
    return FBS_TRUE;
}

FBS_API fbs_bool
fbs_many_eq_string(const char *a_data, int a_length, FBS_String b) {
    return fbs_many_eq(a_data, a_length, b.data, b.length);
}

FBS_API fbs_bool
fbs_many_eq_ntstring(const char *a_data, int a_length, const char *b) {
    int b_length = fbs_ntstring_length(b);
    return fbs_many_eq(a_data, a_length, b, b_length);
}


FBS_API fbs_bool
fbs_string_eq_many(FBS_String a, const char *b_data, int b_length) {
    return fbs_many_eq(a.data, a.length, b_data, b_length);
}

FBS_API fbs_bool
fbs_string_eq(FBS_String a, FBS_String b) { return fbs_many_eq(a.data, a.length, b.data, b.length); }

FBS_API fbs_bool
fbs_string_eq_ntstring(FBS_String a, const char *b) { return fbs_many_eq_ntstring(a.data, a.length, b); }


FBS_API fbs_bool
fbs_ntstring_eq_many(const char *a, const char *b_data, int b_length) {
    int a_length = fbs_ntstring_length(a);
    return fbs_many_eq(a, a_length, b_data, b_length);
}

FBS_API fbs_bool
fbs_ntstring_eq_string(const char *a, FBS_String b) { return fbs_ntstring_eq_many(a, b.data, b.length); }

FBS_API fbs_bool
fbs_ntstring_eq(const char *a, const char *b) {
    int b_length = fbs_ntstring_length(b);
    return fbs_ntstring_eq_many(a, b, b_length);
}

//

FBS_API fbs_bool
fbs_begins_with_char(FBS_String a, char b) {
    if(!a.data || a.length <= 0) { return FBS_FALSE; }
    if(a.data[0] == b) { return FBS_TRUE; }
    return FBS_FALSE;
}

FBS_API fbs_bool
fbs_begins_with(FBS_String a, FBS_String b) {
    if(!a.data || a.length <= 0) { return FBS_FALSE; }
    if(!b.data || b.length <= 0) { return FBS_FALSE; }
    
    for(int i = 0; i < b.length; i += 1) {
        if(a.data[i] != b.data[i]) { return FBS_FALSE; }
    }
    return FBS_TRUE;
}

FBS_API fbs_bool
fbs_begins_with_ntstring(FBS_String a, const char *b) {
    FBS_String sb = fbs_ntstring_to_string(b);
    return fbs_begins_with(a, sb);
}

FBS_API fbs_bool
fbs_ends_with_char(FBS_String a, char b) {
    if(!a.data || a.length <= 0) { return FBS_FALSE; }
    if(a.data[a.length - 1] == b) { return FBS_TRUE; }
    return FBS_FALSE;
}

FBS_API fbs_bool
fbs_ends_with(FBS_String a, FBS_String b) {
    if(!a.data || a.length <= 0) { return FBS_FALSE; }
    if(!b.data || b.length <= 0 || b.length > a.length) { return FBS_FALSE; }
    
    int offset = a.length - b.length;
    for(int i = 0; i < b.length; i += 1) {
        if(a.data[offset + i] != b.data[i]) { return FBS_FALSE; }
    }
    return FBS_TRUE;
}

FBS_API fbs_bool
fbs_ends_with_ntstring(FBS_String a, const char *b) {
    FBS_String sb = fbs_ntstring_to_string(b);
    return fbs_ends_with(a, sb);
}

//

FBS_API int
fbs_index_of_char(FBS_String a, char b) {
    if(!a.data) { return FBS_ERROR_STRING_DATA_IS_NULL; }
    if(a.length <= 0) { return FBS_ERROR_STRING_DATA_IS_EMPTY; }
    for(int i = 0; i < a.length; i += 1) {
        if(a.data[i] == b) { return i; }
    }
    return FBS_ERROR_INDEX_NOT_FOUND;
}

FBS_API int
fbs_index_of_string(FBS_String a, FBS_String b) {
    if(!a.data) { return FBS_ERROR_STRING_DATA_IS_NULL; }
    if(a.length <= 0) { return FBS_ERROR_STRING_DATA_IS_EMPTY; }
    if(!b.data) { return FBS_ERROR_STRING_DATA_IS_NULL; }
    if(b.length > a.length) { return FBS_ERROR_STRING_LENGTHS_DO_NOT_MATCH; }
    
    for(int i = 0; i < a.length; i += 1) {
        if(a.length - i < b.length) { break; }
        
        if(a.data[i] == b.data[0]) {
            fbs_bool success = FBS_TRUE;
            for(int j = 0; j < b.length; j += 1) {
                if(a.data[i + j] != b.data[j]) {
                    success = FBS_FALSE;
                    break;
                }
            }
            if(success) { return i; }
        }
    }
    return FBS_ERROR_INDEX_NOT_FOUND;
}

FBS_API int
fbs_index_of_ntstring(FBS_String a, const char *b) {
    FBS_String it = fbs_ntstring_to_string(b);
    return fbs_index_of_string(a, it);
}

FBS_API int
fbs_index_of_any(FBS_String a, FBS_String b) {
    if(!a.data) { return FBS_ERROR_STRING_DATA_IS_NULL; }
    if(a.length <= 0) { return FBS_ERROR_STRING_DATA_IS_EMPTY; }
    if(!b.data) { return FBS_ERROR_STRING_DATA_IS_NULL; }
    if(b.length <= 0) { return FBS_ERROR_STRING_DATA_IS_EMPTY; }
    
    for(int a_index = 0; a_index < (a.length - b.length); a_index += 1) {
        for(int b_index = 0; b_index < b.length; b_index += 1) {
            if(a.data[a_index + b_index] == b.data[b_index]) { return a_index; }
        }
    }
    return FBS_ERROR_INDEX_NOT_FOUND;
}

FBS_API int
fbs_index_of_any_ntstring(FBS_String a, const char *b) {
    FBS_String sb = fbs_ntstring_to_string(b);
    return fbs_index_of_any(a, sb);
}

//

FBS_API int
fbs_last_index_of_char(FBS_String a, char b) {
    if(!a.data) { return FBS_ERROR_STRING_DATA_IS_NULL; }
    if(a.length <= 0) { return FBS_ERROR_STRING_DATA_IS_EMPTY; }
    for(int i = a.length - 1; i >= 0; i -= 1) {
        if(a.data[i] == b) { return i; }
    }
    return FBS_ERROR_INDEX_NOT_FOUND;
}

FBS_API int
fbs_last_index_of_any(FBS_String a, FBS_String b) {
    if(!a.data) { return FBS_ERROR_STRING_DATA_IS_NULL; }
    if(a.length <= 0) { return FBS_ERROR_STRING_DATA_IS_EMPTY; }
    if(!b.data) { return FBS_ERROR_STRING_DATA_IS_NULL; }
    if(b.length <= 0) { return FBS_ERROR_STRING_DATA_IS_EMPTY; }
    
    for(int a_index = (a.length - b.length) - 1; a_index >= 0; a_index -= 1) {
        for(int b_index = 0; b_index < b.length; b_index += 1) {
            if(a.data[a_index + b_index] == b.data[b_index]) { return a_index; }
        }
    }
    return FBS_ERROR_INDEX_NOT_FOUND;
}

FBS_API int
fbs_last_index_of_any_ntstring(FBS_String a, const char *b) {
    FBS_String sb = fbs_ntstring_to_string(b);
    return fbs_last_index_of_any(a, sb);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// LEXER API
//
FBS_API FBS_Lexer
fbs_lexer_from_file(const char *path) {
    FBS_Lexer result = {0};
    fbs_read_entire_file(path, &result.input_text);
    return result;
}

FBS_API char
fbs_lexer_peek_char(FBS_Lexer lexer, int offset_from_cursor) {
    int index = lexer.cursor + offset_from_cursor;
    if(index >= 0 && index < lexer.input_text.count) { return lexer.input_text.data[index]; }
    return '\0';
}

FBS_API fbs_bool
fbs_parse_next_token(FBS_Lexer *lexer) {
    if(!lexer) {
        FBS_LOG(ERROR, "Trying to parse from a null lexer!\n");
        return FBS_ERROR_GENERIC;
    } else if(!lexer->input_text.data) {
        FBS_LOG(ERROR, "Trying to parse lexer with null input text.\n");
        return FBS_ERROR_GENERIC;
    } else if(lexer->input_text.length <= 0) {
        FBS_LOG(ERROR, "Trying to parse lexer with empty input text.\n");
        return FBS_ERROR_GENERIC;
    }
    
    lexer->token_kind = FBS_TOKEN_PARSE_ERROR;
    lexer->token_text.data = lexer->input_text.data + lexer->cursor;
    lexer->token_text.length = 0;
    lexer->fvalue = 0.0;
    lexer->ivalue = 0;
    
    char c0 = fbs_lexer_peek_char(*lexer, 0);
    if(c0 == '\n' || c0 == '\r') {
        if(c0 == '\n') { lexer->line += 1; }
        
        while(c0 && (c0 == '\n' || c0 == '\r')) {
            lexer->token_text.length += 1;
            c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
            if(c0 == '\n') { lexer->line += 1; }
        }
        
        lexer->token_kind = FBS_TOKEN_NEWLINE;
        lexer->cursor += lexer->token_text.length;
        return FBS_TRUE;
    } else if(c0 == ' ' || c0 == '\t') {
        while(c0 == ' ' || c0 == '\t') {
            lexer->token_text.length += 1;
            c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
        }
        
        lexer->token_kind = FBS_TOKEN_WHITESPACE;
        lexer->cursor += lexer->token_text.length;
        return FBS_TRUE;
    } else if(c0 == '/') {
        lexer->token_text.length += 1;
        c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
        
        if(c0 == '/') {
            lexer->token_kind = FBS_TOKEN_LINE_COMMENT;
            do {
                lexer->token_text.length += 1;
                c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
            } while(!(c0 == '\n' || c0 == '\r'));
            
            lexer->cursor += lexer->token_text.length;
            return FBS_TRUE;
            
        } else if(c0 == '*') {
            lexer->token_text.length += 1;
            c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
            
            fbs_bool was_asterisk = FBS_FALSE;
            do {
                was_asterisk = (c0 == '*');
                
                lexer->token_text.length += 1;
                c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
            } while(c0 && !(was_asterisk && c0 == '/'));
            
            if(was_asterisk && c0 == '/') {
                lexer->token_kind = FBS_TOKEN_BLOCK_COMMENT;
                lexer->token_text.length += 1;
                
                for(int i = 0; i < lexer->token_text.length; i += 1) {
                    if(lexer->token_text.data[i] == '\n') { lexer->line += 1; }
                }
                
                lexer->cursor += lexer->token_text.length;
                return FBS_TRUE;
            }
            
            lexer->cursor += lexer->token_text.length;
            return FBS_FALSE;
            
        } if(c0 == '=') {
            lexer->token_kind = FBS_TOKEN_DIVIDE_EQUAL;
            lexer->token_text.length = 2;
        } else {
            lexer->token_kind = '/';
        }
        
        if(lexer->token_kind != FBS_TOKEN_PARSE_ERROR) {
            lexer->cursor += lexer->token_text.length;
            return FBS_TRUE;
        }
        return FBS_FALSE;
    } else {
        char c1 = fbs_lexer_peek_char(*lexer, 1);
        
        // NOTE: We are checking the second char first here since it is the most common character
        if(c1 == '=') {
            if(c0 == '=') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_EQUAL_EQUAL;
            } else if(c0 == '!') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_NOT_EQUAL;
            } else if(c0 == '+') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_PLUS_EQUAL;
            } else if(c0 == '-') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_MINUS_EQUAL;
            } else if(c0 == '*') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_MULTIPLY_EQUAL;
            } else if(c0 == '&') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_AND_EQUAL;
            } else if(c0 == '|') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_OR_EQUAL;
            } else if(c0 == '%') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_PERCENT_EQUAL;
            } else if(c0 == '<') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_LESS_THAN_EQUAL;
            } else if(c0 == '>') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_GREATER_THAN_EQUAL;
            } else if(c0 == '^') {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_XOR_EQUAL;
            }
            
            // NOTE: ...
        } else if(c0 == '+' && c1 == '+') {
            lexer->token_text.length = 2;
            lexer->token_kind = FBS_TOKEN_PLUS_PLUS;
        } else if(c0 == '-' && c1 == '-') {
            lexer->token_text.length = 2;
            lexer->token_kind = FBS_TOKEN_MINUS_MINUS;
        } else if(c0 == '&' && c1 == '&') {
            lexer->token_text.length = 2;
            lexer->token_kind = FBS_TOKEN_AND_AND;
        } else if(c0 == '|' && c1 == '|') {
            lexer->token_text.length = 2;
            lexer->token_kind = FBS_TOKEN_OR_OR;
        } else if(c0 == '-' && c1 == '>') {
            lexer->token_text.length = 2;
            lexer->token_kind = FBS_TOKEN_ARROW;
        } else if(c0 == '=' && c1 == '>') {
            lexer->token_text.length = 2;
            lexer->token_kind = FBS_TOKEN_THICK_ARROW;
        } else if(c0 == '<' && c1 == '<') {
            c0 = fbs_lexer_peek_char(*lexer, 2);
            if(c0 == '=') {
                lexer->token_text.length = 3;
                lexer->token_kind = FBS_TOKEN_SHIFT_LEFT_EQUAL;
            } else {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_SHIFT_LEFT;
            }
        } else if(c0 == '>' && c1 == '>') {
            c0 = fbs_lexer_peek_char(*lexer, 2);
            if(c0 == '=') {
                lexer->token_text.length = 3;
                lexer->token_kind = FBS_TOKEN_SHIFT_RIGHT_EQUAL;
            } else {
                lexer->token_text.length = 2;
                lexer->token_kind = FBS_TOKEN_SHIFT_RIGHT;
            }
        }
        
        if(lexer->token_kind != FBS_TOKEN_PARSE_ERROR) {
            lexer->cursor += lexer->token_text.length;
            return FBS_TRUE;
        }
    }
    
    switch(c0) {
        case 0: {
            lexer->token_kind = FBS_TOKEN_END_OF_FILE;
            lexer->token_text.length = 1;
            lexer->cursor += lexer->token_text.length;
            return FBS_FALSE;
        } break;
        
        default: {
            if(c0 == '_' || c0 >= 128 || (c0 >= 'A' && c0 <= 'Z') || (c0 >= 'a' && c0 <= 'z')) {
                lexer->token_text.length = 1;
                c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
                
                while(c0 == '_' || c0 >= 128 || (c0 >= 'A' && c0 <= 'Z') ||
                      (c0 >= 'a' && c0 <= 'z') || (c0 >= '0' && c0 <= '9'))
                {
                    lexer->token_text.length += 1;
                    c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
                }
                
                lexer->token_kind = FBS_TOKEN_IDENTIFIER;
                lexer->cursor += lexer->token_text.length;
                return FBS_TRUE;
            }
            
            lexer->token_kind = c0;
            lexer->token_text.length = 1;
            lexer->cursor += lexer->token_text.length;
            return FBS_TRUE;
        } break;
        
        case '"':
        case '\'': {
            char quote = c0;
            
            do {
                lexer->token_text.length += 1;
                c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
            } while(c0 && c0 != quote);
            
            if(c0 == quote) { lexer->token_text.length += 1; }
            
            if(quote == '"') {
                lexer->token_kind = FBS_TOKEN_STRING_LITERAL;
            } else if(quote == '\'') {
                lexer->token_kind = FBS_TOKEN_CHAR_LITERAL;
            }
            
            lexer->cursor += lexer->token_text.length;
            return FBS_TRUE;
        } break;
        
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            int base = 10;
            
            lexer->token_kind = FBS_TOKEN_INT_LITERAL;
            
            if(c0 == '0') {
                char base_char = fbs_lexer_peek_char(*lexer, 1);
                
                if(base_char == 'b') {
                    base = 2;
                } else if(base_char == 'o') {
                    base = 8;
                } else if(base_char == 'x') {
                    base = 16;
                }
                
                if(base != 10) {
                    lexer->token_text.length = 2;
                    c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
                }
            }
            
            if(base <= 10) {
                while(c0) {
                    if(c0 < '0' || c0 >= '0' + base) { break; }
                    
                    lexer->ivalue = (lexer->ivalue * base) + (c0 - '0');
                    lexer->token_text.length += 1;
                    c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
                }
            } else {
                while(c0) {
                    if(c0 >= '0' && c0 <= '9') {
                        lexer->ivalue = (lexer->ivalue * base) + (c0 - '0');
                    } else if(c0 >= 'A' && c0 <= 'A' + (base - 11)) {
                        lexer->ivalue = (lexer->ivalue * base) + ((c0 - 'A') + 10);
                    } else if(c0 >= 'a' && c0 <= 'a' + (base - 11)) {
                        lexer->ivalue = (lexer->ivalue * base) + ((c0 - 'a') + 10);
                    } else {
                        break;
                    }
                    
                    lexer->token_text.length += 1;
                    c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
                }
            }
            
            // NOTE: For now, we only support base-10 floats
            if(base == 10 && c0 == '.') {
                lexer->token_kind = FBS_TOKEN_FLOAT_LITERAL;
                lexer->token_text.length += 1;
                c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
                
                double power = 1.0;
                for(;; power *= base) {
                    if(c0 < '0' || c0 > '9') { break; }
                    
                    lexer->fvalue = (lexer->fvalue * base) + (c0 - '0');
                    
                    lexer->token_text.length += 1;
                    c0 = fbs_lexer_peek_char(*lexer, lexer->token_text.length);
                }
                
                lexer->fvalue = (double)lexer->ivalue + (lexer->fvalue / power);
                
                if(c0 == 'e' || c0 == 'E') {
                    // TODO(Patrik): Parse exponents
                }
            }
            
            lexer->cursor += lexer->token_text.length;
            return FBS_TRUE;
        } break;
    }
    
    //return FBS_FALSE;
}

FBS_API FBS_Token
fbs_get_current_token(FBS_Lexer lexer) {
    FBS_Token result = {0};
    result.fvalue = lexer.fvalue;
    result.ivalue = lexer.ivalue;
    result.text = lexer.token_text.data;
    result.length = lexer.token_text.length;
    result.line = lexer.line;
    result.kind = lexer.token_kind;
    return result;
}

FBS_API List_FBS_Token
fbs_parse_all_tokens(FBS_Lexer *lexer) {
    List_FBS_Token result = {0};
    
    if(!lexer) {
        FBS_LOG(ERROR, "Could not parse all tokens, lexer is null!\n");
        return result;
    } else if(!lexer->input_text.data) {
        FBS_LOG(ERROR, "Could not parse all tokens, input text is null!\n");
        return result;
    } else if(lexer->input_text.length <= 0) {
        FBS_LOG(ERROR, "Could not parse all tokens, input text is empty!\n");
        return result;
    }
    
    while(fbs_parse_next_token(lexer)) {
        FBS_Token token = fbs_get_current_token(*lexer);
        FBS_APPEND(&result, token);
    }
    
    return result;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// PLATFORM API
//
FBS_API fbs_error
fbs_file_exists(const char *path) {
    if(!path) {
        FBS_LOG(ERROR, "fbs_file_exists -> Path is null.\n");
        return FBS_ERROR_PATH_IS_NULL;
    }
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    DWORD attribute = GetFileAttributesA(path);
    if(attribute != INVALID_FILE_ATTRIBUTES) { return FBS_TRUE; }
    
    DWORD last_error = GetLastError();
    if(last_error == ERROR_FILE_NOT_FOUND || last_error == ERROR_PATH_NOT_FOUND) { return FBS_FALSE; }
    
    FBS_LOG(ERROR, "(%lu) Could not check if file %s exists.\n", last_error, path);
    return FBS_ERROR_GENERIC;
    
#else
    struct stat attribute;
    if(stat(path, &attribute) < 0) {
        if(errno == ENOENT) { return FBS_FALSE; }
        FBS_LOG(ERROR, "(%d) Could not check if file %s exists.\n", errno, path);
        return FBS_ERROR_GENERIC;
    }
    return FBS_IS_FLAG(attribute.st_mode, S_IFREG);
#endif
}

FBS_API fbs_error
fbs_delete_file(const char *path) {
#if FBS_CURRENT_PLATFORM_WINDOWS
    if(!path) { return FBS_FALSE; }
    
    if(DeleteFile(path)) { return FBS_TRUE; }
    
    DWORD last_error = GetLastError();
    if(last_error == ERROR_FILE_NOT_FOUND) { return FBS_FALSE; }
    
    FBS_LOG(ERROR, "(%lu) Could not delete the file \"%s\".\n", last_error, path);
    return FBS_ERROR_GENERIC;
    
#else
    if(!path) { return FBS_FALSE; }
    
    if(remove(path) < 0) {
        if(errno == ENOENT) { return FBS_FALSE; }
        FBS_LOG(ERROR, "(%d) Could not delete the file \"%s\".\n", errno, path);
        return FBS_ERROR_GENERIC;
    }
    return FBS_TRUE;
#endif
}

FBS_API fbs_error
fbs_move_file(const char *from_path, const char *to_path) {
#if FBS_CURRENT_PLATFORM_WINDOWS
    if(!from_path || !to_path) { return FBS_FALSE; }
    
    DWORD move_flags = (MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING);
    if(MoveFileExA(from_path, to_path, move_flags)) { return FBS_TRUE; }
    DWORD last_error = GetLastError();
    FBS_LOG(ERROR, "(%lu) Could not move \"%s\" to \"%s\".\n", last_error, from_path, to_path);
    return FBS_ERROR_GENERIC;
    
#else
    if(!from_path || !to_path) { return FBS_FALSE; }
    
    if(rename(from_path, to_path) < 0) {
        FBS_LOG(ERROR, "(%d) Could not move \"%s\" to \"%s\".\n", errno, from_path, to_path);
        return FBS_ERROR_GENERIC;
    }
    return FBS_TRUE;
#endif
}

FBS_API fbs_error
fbs_copy_file(const char *from_path, const char *to_path) {
#if FBS_CURRENT_PLATFORM_WINDOWS
    if(!from_path || !to_path) { return FBS_FALSE; }
    
    if(CopyFile(from_path, to_path, 0)) { return FBS_TRUE; }
    DWORD last_error = GetLastError();
    FBS_LOG(ERROR, "(%lu) Could not move \"%s\" to \"%s\".\n", last_error, from_path, to_path);
    return FBS_ERROR_GENERIC;
    
#else
    FBS_String buffer = {0};
    
    fbs_error success = fbs_read_entire_file(from_path, &buffer);
    if(success < 0) {
        FBS_LOG(ERROR, "Could not move \"%s\" to \"%s\".\n", from_path, to_path);
        FBS_FREE(buffer.data);
        return FBS_ERROR_GENERIC;
    } else if(!success) {
        FBS_FREE(buffer.data);
        return FBS_FALSE;
    }
    
    success = fbs_write_entire_file(to_path, buffer.data, buffer.length);
    if(success < 0) {
        FBS_LOG(ERROR, "Could not move \"%s\" to \"%s\".\n", from_path, to_path);
        FBS_FREE(buffer.data);
        return FBS_ERROR_GENERIC;
    } else if(!success) {
        FBS_FREE(buffer.data);
        return FBS_FALSE;
    }
    
    FBS_FREE(buffer.data);
    return FBS_TRUE;
#endif
}

FBS_API fbs_error
fbs_read_entire_file(const char *path, FBS_String *buffer) {
    if(!path) {
        FBS_LOG(WARNING, "fbs_read_entire_file -> path is null.\n");
        return FBS_FALSE;
    }
    
    if(!buffer) {
        FBS_LOG(WARNING, "fbs_read_entire_file -> buffer is null.\n");
        return FBS_FALSE;
    }
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    HANDLE handle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    
    LARGE_INTEGER file_size;
    if(!GetFileSizeEx(handle, &file_size)) {
        FBS_LOG(ERROR, "(%lu) Could not get the file size of: \"%s\"\n", GetLastError(), path);
        CloseHandle(handle);
        return FBS_ERROR_GENERIC;
    }
    
    FBS_MAYBE_GROW(buffer, file_size.QuadPart);
    
    DWORD bytes_read = 0;
    if(!ReadFile(handle, (buffer->data + buffer->length), (DWORD)file_size.QuadPart, &bytes_read, 0)) {
        FBS_LOG(ERROR, "(%ld) Could not read the file \"%s\"\n", GetLastError(), path);
        CloseHandle(handle);
        return FBS_ERROR_GENERIC;
    }
    
    buffer->length += bytes_read;
    CloseHandle(handle);
    return bytes_read > 0;
    
#else
    FILE *handle = fopen(path, "rb");
    if(!handle) {
        FBS_LOG(ERROR, "(%d) Could not read the file \"%s\"\n", errno, path);
        return FBS_ERROR_GENERIC;
    }
    
    if(fseek(handle, 0, SEEK_END) < 0) {
        FBS_LOG(ERROR, "(%d) Could not read the file \"%s\"\n", errno, path);
        fclose(handle);
        return FBS_ERROR_GENERIC;
    }
    
    long file_size = ftell(handle);
    if(file_size < 0) {
        FBS_LOG(ERROR, "(%d) Could not read the file \"%s\"\n", errno, path);
        fclose(handle);
        return FBS_ERROR_GENERIC;
    }
    
    if(fseek(handle, 0, SEEK_SET) < 0) {
        FBS_LOG(ERROR, "(%d) Could not read the file \"%s\"\n", errno, path);
        fclose(handle);
        return FBS_ERROR_GENERIC;
    }
    
    FBS_MAYBE_GROW(buffer, buffer->length + file_size);
    void *cursor = (void *)(buffer->data + buffer->length);
    
    int bytes_read = (int)fread(cursor, sizeof(*buffer->data), file_size, handle);
    int error = ferror(handle);
    fclose(handle);
    if(error) {
        FBS_LOG(ERROR, "(%d) Could not read the file \"%s\"\n", error, path);
        return FBS_ERROR_GENERIC;
    } else if(bytes_read > 0) {
        buffer->count += bytes_read;
        return FBS_TRUE;
    }
    return FBS_FALSE;
#endif
}

FBS_API fbs_error
fbs_write_entire_file(const char *path, void *data, int size_in_bytes) {
    if(!path) {
        FBS_LOG(WARNING, "fbs_write_entire_file -> path is null.\n");
        return FBS_FALSE;
    } else if(!data) {
        FBS_LOG(WARNING, "fbs_write_entire_file -> data is null.\n");
        return FBS_FALSE;
    } else if(size_in_bytes <= 0) {
        FBS_LOG(WARNING, "fbs_write_entire_file -> size_in_bytes is zero or less.\n");
        return FBS_FALSE;
    }
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    HANDLE handle = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if(handle == INVALID_HANDLE_VALUE) {
        // TODO(Patrik): Error...
        return FBS_ERROR_GENERIC;
    }
    
    DWORD bytes_written = 0;
    if(!WriteFile(handle, data, size_in_bytes, &bytes_written, 0)) {
        FBS_LOG(ERROR, "(%lu) Could not write to the file \"%s\"\n", GetLastError(), path);
        CloseHandle(handle);
        return FBS_ERROR_GENERIC;
    }
    
    CloseHandle(handle);
    return bytes_written > 0;
    
#else
    FILE *handle = fopen(path, "wb");
    if(handle == 0) {
        FBS_LOG(ERROR, "(%d) Could not open the file \"%s\" for writing.\n", errno, path);
        return FBS_ERROR_GENERIC;
    }
    
    int cursor = 0;
    while(cursor < size_in_bytes) {
        cursor += fwrite((unsigned char *)data + cursor, 1, size_in_bytes, handle);
        if(ferror(handle)) {
            FBS_LOG(ERROR, "(%d) Could not write to the file \"%s\"\n", errno, path);
            fclose(handle);
            return FBS_ERROR_GENERIC;
        }
    }
    
    fclose(handle);
    return FBS_TRUE;
#endif
}

FBS_API fbs_error
fbs_is_file_newer(const char *this_path, const char *other_path) {
    if(!this_path && !other_path) {
        FBS_LOG(ERROR, "this_path and other_path are both null.\n");
        return FBS_ERROR_GENERIC;
    } else if(!this_path) {
        FBS_LOG(ERROR, "this_path is null.\n");
        return FBS_ERROR_GENERIC;
    } else if(!other_path) {
        FBS_LOG(ERROR, "other_path is null.\n");
        return FBS_ERROR_GENERIC;
    }
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    HANDLE this_handle = CreateFileA(this_path, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, 0);
    if(this_handle == INVALID_HANDLE_VALUE) {
        DWORD last_error = GetLastError();
        if(last_error != ERROR_FILE_NOT_FOUND) {
            if(last_error == ERROR_SHARING_VIOLATION) {
                FBS_LOG(ERROR, "(%ld) The file \"%s\" is used by another process!\n", last_error, this_path);
                return FBS_ERROR_GENERIC;
            }
            FBS_LOG(ERROR, "(%lu) Could not view file: \"%s\"\n", last_error, this_path);
            return FBS_ERROR_GENERIC;
        }
        return FBS_FALSE;
    }
    
    FILETIME this_time = {0};
    BOOL success = GetFileTime(this_handle, 0, 0, &this_time);
    if(!success) {
        DWORD last_error = GetLastError();
        CloseHandle(this_handle);
        FBS_LOG(ERROR, "(%lu) Could not get time from file: \"%s\"\n", last_error, this_path);
        return FBS_ERROR_GENERIC;
    }
    
    HANDLE other_handle = CreateFileA(other_path, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, 0);
    if(other_handle == INVALID_HANDLE_VALUE) {
        DWORD last_error = GetLastError();
        CloseHandle(this_handle);
        if(last_error == ERROR_FILE_NOT_FOUND) { return 1; }
        if(last_error == ERROR_SHARING_VIOLATION) {
            FBS_LOG(ERROR, "(%ld) The file \"%s\" is used by another process!\n", last_error, other_path);
            return FBS_ERROR_GENERIC;
        }
        FBS_LOG(ERROR, "(%lu) Could not view file: \"%s\"\n", last_error, other_path);
        return FBS_ERROR_GENERIC;
    }
    
    FILETIME other_time = {0};
    success = GetFileTime(other_handle, 0, 0, &other_time);
    if(!success) {
        DWORD last_error = GetLastError();
        CloseHandle(this_handle);
        CloseHandle(other_handle);
        if(last_error == ERROR_FILE_NOT_FOUND) { return 1; }
        if(last_error == ERROR_SHARING_VIOLATION) {
            FBS_LOG(ERROR, "(%ld) The file \"%s\" is used by another process!\n", last_error, other_path);
            return FBS_ERROR_GENERIC;
        }
        FBS_LOG(ERROR, "(%lu) Could not get time from file: \"%s\"\n", last_error, other_path);
        return FBS_ERROR_GENERIC;
    }
    
    CloseHandle(this_handle);
    CloseHandle(other_handle);
    
    return (CompareFileTime(&this_time, &other_time) > 0);
    
#else
    struct stat this_attribute;
    if(stat(this_path, &this_attribute) < 0) {
        if(errno == ENOENT) { return FBS_TRUE; }
        FBS_LOG(ERROR, "(%d) Could not view file: \"%s\"\n", errno, this_path);
        return FBS_ERROR_GENERIC;
    }
    
    struct stat other_attribute;
    if(stat(other_path, &other_attribute) < 0) {
        FBS_LOG(ERROR, "(%d) Could not view file: \"%s\"\n", errno, this_path);
        return FBS_ERROR_GENERIC;
    }
    
    return this_attribute.st_mtime > other_attribute.st_mtime;
#endif
}

//

FBS_API fbs_error
fbs_directory_exists(const char *path) {
    if(!path) {
        FBS_LOG(ERROR, "fbs_directory_exists -> path is null.\n");
        return FBS_ERROR_GENERIC;
    }
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    WIN32_FILE_ATTRIBUTE_DATA file_information = {0};
    if(!GetFileAttributesExA(path, GetFileExInfoStandard, &file_information)) { return FBS_FALSE; }
    
    DWORD attributes = GetFileAttributesA(path);
    if(attributes & FILE_ATTRIBUTE_DIRECTORY) { return FBS_TRUE; }
    return FBS_FALSE;
    
#else
    DIR *handle = opendir(path);
    if(handle) {
        closedir(handle);
        return FBS_TRUE;
    } else if(errno == ENOENT) {
        return FBS_FALSE;
    }
    
    FBS_LOG(ERROR, "(%d) Could not check if directory \"%s\" exists.\n", errno, path);
    return FBS_ERROR_GENERIC;
#endif
}

FBS_API fbs_error
fbs_create_directory_if_new(const char *path) {
    if(!path) {
        FBS_LOG(ERROR, "fbs_create_directory_if_new -> path is null.\n");
        return FBS_ERROR_GENERIC;
    }
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    if(CreateDirectoryA(path, 0)) { return FBS_TRUE; }
    
    DWORD last_error = GetLastError();
    if(last_error == ERROR_ALREADY_EXISTS) { return FBS_FALSE; }
    
    FBS_LOG(ERROR, "(%lu) Could not create the directory \"%s\"\n", last_error, path);
    return FBS_ERROR_GENERIC;
    
#else
    if(mkdir(path, 0777) < 0) {
        if(errno == EEXIST) { return FBS_FALSE; }
        FBS_LOG(ERROR, "(%d) Could not create the directory \"%s\"\n", errno, path);
        return FBS_ERROR_GENERIC;
    }
    
    return FBS_TRUE;
#endif
}

FBS_API fbs_error
fbs_remove_directory_recursively(const char *path) {
    if(!path) {
        FBS_LOG(ERROR, "fbs_remove_directory_recursively -> path is null.\n");
        return FBS_ERROR_GENERIC;
    }
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    DWORD attributes = GetFileAttributesA(path);
    if(!FBS_IS_FLAG(attributes, FILE_ATTRIBUTE_DIRECTORY)) {
        FBS_LOG(ERROR, "The path \"%s\" is not a directory.\n", path);
        return FBS_ERROR_GENERIC;
    }
    
    FBS_String builder = {0};
    FBS_APPEND_NTSTRING(&builder, path);
    int reset_length = builder.length;
    if(builder.data[builder.length - 1] == '\\' || builder.data[builder.length - 1] == '/') {
        FBS_APPEND_STR_LIT(&builder, "*");
    } else {
        reset_length += 1;
        FBS_APPEND_STR_LIT(&builder, "\\*");
    }
    FBS_NULL_TERMINATE(&builder);
    
    WIN32_FIND_DATAA find_data = {0};
    HANDLE handle = FindFirstFileA(builder.data, &find_data);
    if(handle == INVALID_HANDLE_VALUE) {
        FBS_LOG(ERROR, "(%lu) Could not search the directory: \"%s\"\n", GetLastError(), path);
        return FBS_ERROR_GENERIC;
    }
    
    do {
        builder.length = reset_length;
        FBS_APPEND_NTSTRING(&builder, find_data.cFileName);
        FBS_NULL_TERMINATE(&builder);
        
        if(FBS_IS_FLAG(find_data.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY)) {
            if(!(fbs_ntstring_eq(find_data.cFileName, ".") || fbs_ntstring_eq(find_data.cFileName, ".."))) {
                fbs_error success = fbs_remove_directory_recursively(builder.data);
                if(success < 0) {
                    FBS_FREE(builder.data);
                    return success;
                }
            }
        } else {
            DeleteFile(builder.data);
        }
    } while(FindNextFileA(handle, &find_data));
    
    FindClose(handle);
    FBS_FREE(builder.data);
    
    if(!RemoveDirectory(path)) {
        FBS_LOG(ERROR, "(%lu) Could not remove the directory: \"%s\"\n", GetLastError(), path);
        return FBS_ERROR_GENERIC;
    }
    return FBS_TRUE;
    
#else
    struct stat attribute;
    if(stat(path, &attribute) < 0) {
        FBS_LOG(ERROR, "(%d) Could not view the path: \"%s\"\n", errno, path);
        return FBS_ERROR_GENERIC;
    } else if((attribute.st_mode & S_IFMT) != S_IFDIR) {
        FBS_LOG(ERROR, "The path \"%s\" is not a directory.\n", path);
        return FBS_ERROR_GENERIC;
    }
    
    DIR *handle = opendir(path);
    if(handle == 0) {
        FBS_LOG(ERROR, "(%d) Could not open the directory: \"%s\"\n", errno, path);
        return FBS_ERROR_GENERIC;
    }
    
    FBS_String path_str = fbs_ntstring_to_string(path);
    
    FBS_String builder = {0};
    
    struct dirent *entry = readdir(handle);
    while(entry) {
        builder.length = 0;
        
        if(!fbs_ntstring_eq(entry->d_name, ".") &&
           !fbs_ntstring_eq(entry->d_name, ".."))
        {
            FBS_APPEND_ARRAY(&builder, path_str);
            if(!fbs_ends_with_char(builder, '/')) { FBS_APPEND(&builder, '/'); }
            FBS_APPEND_NTSTRING(&builder, entry->d_name);
            FBS_NULL_TERMINATE(&builder);
            
            struct stat entry_attribute;
            if(stat(builder.data, &entry_attribute) < 0) {
                closedir(handle);
                FBS_FREE(builder.data);
                return FBS_ERROR_GENERIC;
            }
            
            if((entry_attribute.st_mode & S_IFMT) == S_IFDIR) {
                fbs_error success;
                success = fbs_remove_directory_recursively(builder.data);
                if(success < 0) {
                    closedir(handle);
                    FBS_FREE(builder.data);
                    return success;
                }
            } else if(unlink(builder.data) != 0) {
                closedir(handle);
                FBS_FREE(builder.data);
                return FBS_ERROR_GENERIC;
            }
        }
        
        entry = readdir(handle);
    }
    
    if(rmdir(path) < 0) {
        FBS_LOG(ERROR, "(%d) Could not remove the directory: \"%s\"\n", errno, path);
        closedir(handle);
        FBS_FREE(builder.data);
        return FBS_ERROR_GENERIC;
    }
    
    closedir(handle);
    FBS_FREE(builder.data);
#endif
}

FBS_API List_FBS_String
fbs_get_directory_files(const char *path) {
    List_FBS_String result = {0};
    if(!path) { return result; }
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    DWORD attributes = GetFileAttributesA(path);
    if(!FBS_IS_FLAG(attributes, FILE_ATTRIBUTE_DIRECTORY)) {
        FBS_LOG(WARNING, "The path \"%s\" is not a directory.\n", path);
        return result;
    }
    
    FBS_String find_path = {0};
    FBS_APPEND_NTSTRING(&find_path, path);
    int reset_length = find_path.length;
    if(find_path.data[find_path.length - 1] == '\\' || find_path.data[find_path.length - 1] == '/') {
        FBS_APPEND_STR_LIT(&find_path, "*");
    } else {
        reset_length += 1;
        FBS_APPEND_STR_LIT(&find_path, "\\*");
    }
    FBS_NULL_TERMINATE(&find_path);
    
    WIN32_FIND_DATAA find_data = {0};
    HANDLE handle = FindFirstFileA(find_path.data, &find_data);
    if(handle == INVALID_HANDLE_VALUE) {
        FBS_LOG(ERROR, "(%lu) Could not search the directory: \"%s\"\n", GetLastError(), path);
        FBS_FREE(find_path.data);
        return result;
    }
    FBS_FREE(find_path.data);
    
    do {
        if(fbs_ntstring_eq(find_data.cFileName, ".") || fbs_ntstring_eq(find_data.cFileName, "..")) { continue; }
        
        if(!FBS_IS_FLAG(find_data.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY)) {
            FBS_String it = {0};
            FBS_APPEND_NTSTRING(&it, find_data.cFileName);
            FBS_NULL_TERMINATE(&it);
            
            FBS_APPEND(&result, it);
        }
    } while(FindNextFileA(handle, &find_data));
    FindClose(handle);
    
    return result;
    
#else
    DIR *handle = opendir(path);
    if(!handle) {
        FBS_LOG(ERROR, "(%d) Could not open directory: \"%s\"\n", errno, path);
        return result;
    }
    
    errno = 0;
    struct dirent *entry = readdir(handle);
    while(entry) {
        if(!fbs_ntstring_eq(entry->d_name, ".") && !fbs_ntstring_eq(entry->d_name, "..")) {
            FBS_String it = {0};
            FBS_APPEND_NTSTRING(&it, entry->d_name);
            FBS_NULL_TERMINATE(&it);
            
            FBS_APPEND(&result, it);
        }
        
        entry = readdir(handle);
    }
    
    if(errno) {
        FBS_LOG(ERROR, "(%d) Could not read directory: \"%s\"\n", errno, path);
        closedir(handle);
        FBS_FREE(result.data);
        List_FBS_String empty = {0};
        return empty;
    }
    
    closedir(handle);
    return result;
#endif
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
//
FBS_API fbs_error
fbs_sync_files(const char *from_directory, const char *to_directory, const char **file_names, int file_count) {
    if(!from_directory) {
        FBS_LOG(ERROR, "from_directory is null.\n");
        return FBS_ERROR_GENERIC;
    } else if(!to_directory) {
        FBS_LOG(ERROR, "to_directory is null.\n");
        return FBS_ERROR_GENERIC;
    } else if(!file_names) {
        FBS_LOG(ERROR, "file_names is null.\n");
        return FBS_ERROR_GENERIC;
    }
    
    fbs_error error = fbs_directory_exists(from_directory);
    if(error < 0) { return error; }
    if(!error) {
        FBS_LOG(ERROR, "from_directory does not exist.\n");
    }
    
    error = fbs_directory_exists(to_directory);
    if(error < 0) { return error; }
    if(!error) {
        FBS_LOG(ERROR, "to_directory does not exist.\n");
    }
    
    FBS_String from_buffer = {0};
    FBS_String to_buffer = {0};
    
    for(int i = 0; i < file_count; i += 1) {
        from_buffer.length = 0;
        to_buffer.length = 0;
        FBS_APPEND_NTSTRING(&from_buffer, from_directory);
        FBS_APPEND_NTSTRING(&to_buffer, to_directory);
        if(from_buffer.data[from_buffer.length - 1] != '/' && from_buffer.data[from_buffer.length - 1] != '\\') {
#if defined(_WIN32) || defined(_WIN64)
            FBS_APPEND(&from_buffer, '\\');
#else
            FBS_APPEND(&from_buffer, '/');
#endif
        }
        
        if(to_buffer.data[to_buffer.length - 1] != '/' && to_buffer.data[to_buffer.length - 1] != '\\') {
#if defined(_WIN32) || defined(_WIN64)
            FBS_APPEND(&to_buffer, '\\');
#else
            FBS_APPEND(&to_buffer, '/');
#endif
        }
        
        FBS_APPEND_NTSTRING(&from_buffer, file_names[i]);
        FBS_APPEND_NTSTRING(&to_buffer, file_names[i]);
        FBS_NULL_TERMINATE(&from_buffer);
        FBS_NULL_TERMINATE(&to_buffer);
        
        error = fbs_file_exists(from_buffer.data);
        if(error < 0) { break; }
        if(error) {
            error = fbs_is_file_newer(from_buffer.data, to_buffer.data);
            if(error < 0) { break; }
        }
        
        if(error) {
            error = fbs_copy_file(from_buffer.data, to_buffer.data);
        } else {
            error = fbs_copy_file(to_buffer.data, from_buffer.data);
        }
        
        if(error < 0) { break; }
    }
    
    FBS_FREE(from_buffer.data);
    FBS_FREE(to_buffer.data);
    return error;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// SUBCOMMAND PROCEDURES
//
FBS_API fbs_error
fbs_run_subcommand(int arg_count, char **arg_data, List_FBS_Subcommand subcommands, int *used_subcommand_index) {
    // NOTE:
    // If return value <  0: Error, exit the program
    // If return value == 0: No error, exit the program
    // If return value >  0: No error, keep going
    
    FBS_String program = {0};
    if(arg_count > 0) {
        program.data = arg_data[0];
        program.length = fbs_ntstring_length(program.data);
        
        arg_data += 1;
        arg_count -= 1;
    }
    
    fbs_bool is_build = FBS_FALSE;
    
    FBS_String arg = {0};
    if(arg_count > 0) {
        arg.data = arg_data[0];
        arg.length = fbs_ntstring_length(arg.data);
        
        if(fbs_string_eq_ntstring(arg, "_fbs_is_rebuilt_")) {
            arg_data += 1;
            arg_count -= 1;
            
            arg.data = arg_data[0];
            arg.length = fbs_ntstring_length(arg.data);
        }
        
        if(fbs_string_eq_ntstring(arg, "build")) {
            is_build = FBS_TRUE;
        }
        
        arg_data += 1;
        arg_count -= 1;
    } else {
        arg = FBS_String_lit("build");
        is_build = FBS_TRUE;
    }
    
    for(int it_index = 0; it_index < subcommands.count; it_index += 1) {
        FBS_Subcommand it = subcommands.data[it_index];
        
        if(!fbs_string_eq_ntstring(arg, it.name)) {
            fbs_bool found = FBS_FALSE;
            for(int alias_index = 0; alias_index < FBS_MAX_SUBCOMMAND_ALIAS_COUNT; alias_index += 1) {
                if(!it.aliases[alias_index]) { continue; }
                if(!fbs_string_eq_ntstring(arg, it.aliases[alias_index])) { continue; }
                
                found = FBS_TRUE;
                break;
            }
            
            if(!found) { continue; }
        }
        
        //
        
        if(!it.proc) {
            if(used_subcommand_index) { *used_subcommand_index = it_index; }
            return FBS_ERROR_MISSING_SUBCOMMAND;
        }
        
        fbs_error result = it.proc(arg_count, arg_data);
        return result;
    }
    
    return FBS_ERROR_NAME_DOESNT_MATCH_A_SUBCOMMAND;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// COMMAND PROCEDURES
//
FBS_API void
fbs_render_command(FBS_String *buffer, List_FBS_String command) {
    for(int it_index = 0; it_index < command.count; it_index += 1) {
        FBS_String it = command.data[it_index];
        if(!it.data) { break; }
        
        if(it_index > 0) { FBS_APPEND(buffer, ' '); }
        
        if(fbs_index_of_char(it, ' ') >= 0) {
            FBS_APPEND(buffer, '\"');
            FBS_APPEND_ARRAY(buffer, it);
            FBS_APPEND(buffer, '\"');
        } else {
            FBS_APPEND_ARRAY(buffer, it);
        }
    }
}

FBS_API int
fbs_wait_for_async_proc(FBS_Async_Proc proc) {
#if FBS_CURRENT_PLATFORM_WINDOWS
    if(proc.handle == INVALID_HANDLE_VALUE) { return 1; }
    if(proc.error) { return 1; }
    
    DWORD result = WaitForSingleObject(proc.handle, INFINITE);
    if(result == WAIT_FAILED) {
        FBS_LOG(ERROR, "(%lu) Could not wait on child process.\n", GetLastError());
        return 0;
    }
    
    DWORD exit_status;
    if(!GetExitCodeProcess(proc.handle, &exit_status)) {
        FBS_LOG(ERROR, "(%lu) Could not get exit code for command.\n", GetLastError());
        return 0;
    }
    
    if(exit_status != 0) {
        FBS_LOG(ERROR,
                "Command exited with exit code " FBS_LOG_COLOR_BRIGHT_RED "%lu" FBS_LOG_COLOR_RESET "\n",
                exit_status);
        return 0;
    }
    
    CloseHandle(proc.handle);
    return 1;
    
#else
    if(proc.handle < 0) { return 1; }
    if(proc.error) { return 1; }
    
    fbs_bool should_loop = FBS_TRUE;
    while(should_loop) {
        int wstatus = 0;
        if(waitpid(proc.handle, &wstatus, 0) < 0) {
            FBS_LOG(ERROR, "(%d) Could not wait on child process [%d].\n", errno, proc.handle);
            return 0;
        }
        
        if(WIFEXITED(wstatus)) {
            int exit_status = WEXITSTATUS(wstatus);
            if(exit_status != 0) {
                FBS_LOG(ERROR, "Command exited with the exit code: %d\n", exit_status);
                return 0;
            }
            
            should_loop = FBS_FALSE;
        }
        
        if(WIFSIGNALED(wstatus)) {
            FBS_LOG(ERROR, "Command was terminated.\n");
            return 0;
        }
    }
    
    return 1;
#endif
}

FBS_API FBS_Async_Proc
fbs_run_command_async(List_FBS_String command) {
#if FBS_CURRENT_PLATFORM_WINDOWS
    FBS_Async_Proc result = {INVALID_HANDLE_VALUE, 1};
    
    if(command.count < 1) {
        FBS_LOG(ERROR, "Trying to run an empty command!\n");
        return result;
    }
    
    FBS_String buffer = {0};
    fbs_render_command(&buffer, command);
    FBS_NULL_TERMINATE(&buffer);
    FBS_LOG(INFO, "CMD: %s\n", buffer.data);
    
    // https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output
    STARTUPINFO start_info = {0};
    start_info.cb = sizeof(STARTUPINFO);
    // NOTE: theoretically setting 0 to std handles should not be a problem
    // https://docs.microsoft.com/en-us/windows/console/getstdhandle?redirectedfrom=MSDN#attachdetach-behavior
    // TODO: check for errors in GetStdHandle
    start_info.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    start_info.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    start_info.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    start_info.dwFlags |= STARTF_USESTDHANDLES;
    
    PROCESS_INFORMATION proc_info;
    ZeroMemory(&proc_info, sizeof(PROCESS_INFORMATION));
    
    void *environment = (void *)GetEnvironmentStrings();
    
    // TODO: use a more reliable rendering of the command instead of fbs_render_command
    // fbs_render_command is for logging primarily
    buffer.length = 0;
    fbs_render_command(&buffer, command);
    FBS_NULL_TERMINATE(&buffer);
    BOOL success = CreateProcessA(0, buffer.data, 0, 0, TRUE, 0, environment, 0, &start_info, &proc_info);
    FBS_FREE((void *)buffer.data);
    
    FreeEnvironmentStringsA((LPCH)environment);
    
    if(!success) {
        DWORD last_error = GetLastError();
        FBS_LOG(ERROR, "(%lu) Could not create child process.\n", last_error);
        return result;
    }
    
    result.error = 0;
    result.handle = proc_info.hProcess;
    CloseHandle(proc_info.hThread);
    return result;
    
#else
    FBS_Async_Proc result = {FBS_ERROR_GENERIC, 0};
    
    if(command.count < 1) {
        FBS_LOG(ERROR, "Trying to run an empty command!\n");
        result.error = 1;
        return result;
    }
    
    FBS_String buffer = {0};
    fbs_render_command(&buffer, command);
    FBS_NULL_TERMINATE(&buffer);
    FBS_LOG(INFO, "CMD: %s\n", buffer.data);
    
    pid_t cpid = fork();
    if(cpid < 0) {
        FBS_LOG(ERROR, "(%d) Could not fork child process.\n", errno);
        result.error = 1;
    } else if(cpid == 0) {
        char **args = FBS_ALLOC(sizeof(char *) * (command.count + 1));
        args[command.count] = 0;
        for(int i = 0; i < command.count; i += 1) {
            args[i] = command.data[i].data;
        }
        
        if(execvp(command.data[0].data, (char * const *)args) < 0) {
            FBS_LOG(ERROR, "Could not exec child process.\n  -> %s\n", strerror(errno));
            result.error = 1;
        } else {
            FBS_INVALID_CODE_PATH;
        }
        
        FBS_FREE(args);
    }
    
    if(result.error) { return result; }
    
    result.handle = cpid;
    return result;
#endif
}

FBS_API int
fbs_run_command_sync(List_FBS_String command) {
    FBS_Async_Proc proc = fbs_run_command_async(command);
    
#if FBS_CURRENT_PLATFORM_WINDOWS
    if(proc.handle == INVALID_HANDLE_VALUE || proc.error) { return 0; }
#else
    if(proc.handle < 0 || proc.error) { return 0; }
#endif
    
    int result = fbs_wait_for_async_proc(proc);
    return result;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// COMPILER PROCEDURES
//
FBS_API FBS_Compiler
fbs_copy_compiler_settings(FBS_Compiler compiler) {
    FBS_Compiler result = {0};
    
    result.flags = compiler.flags;
    
    FBS_APPEND_ARRAY(&result.msvc.compiler, compiler.msvc.compiler);
    FBS_APPEND_ARRAY(&result.msvc.linker, compiler.msvc.linker);
    
    FBS_APPEND_ARRAY(&result.gcc.compiler, compiler.gcc.compiler);
    FBS_APPEND_ARRAY(&result.gcc.linker, compiler.gcc.linker);
    
    FBS_APPEND_ARRAY(&result.emscripten.compiler, compiler.emscripten.compiler);
    FBS_APPEND_ARRAY(&result.emscripten.linker, compiler.emscripten.linker);
    
    FBS_APPEND_ARRAY(&result.output_directory, compiler.output_directory);
    FBS_APPEND_ARRAY(&result.output_file_name, compiler.output_file_name);
    FBS_APPEND_ARRAY(&result.icon_path, compiler.icon_path);
    
    if(compiler.input_files.count > 0) {
        FBS_String builder = {0};
        for(int i = 0; i < compiler.input_files.count; i += 1) {
            FBS_APPEND_ARRAY(&builder, compiler.input_files.data[i]);
            FBS_APPEND(&builder, '\0');
        }
        if(builder.count > 0) { result.input_files = fbs_string_to_list(builder); }
    }
    
    if(compiler.defines.count > 0) {
        FBS_String builder = {0};
        for(int i = 0; i < compiler.defines.count; i += 1) {
            FBS_APPEND_ARRAY(&builder, compiler.defines.data[i]);
            FBS_APPEND(&builder, '\0');
        }
        if(builder.count > 0) { result.defines = fbs_string_to_list(builder); }
    }
    
    if(compiler.include_directories.count > 0) {
        FBS_String builder = {0};
        for(int i = 0; i < compiler.include_directories.count; i += 1) {
            FBS_APPEND_ARRAY(&builder, compiler.include_directories.data[i]);
            FBS_APPEND(&builder, '\0');
        }
        if(builder.count > 0) { result.include_directories = fbs_string_to_list(builder); }
    }
    
    if(compiler.link_to_libraries.count > 0) {
        FBS_String builder = {0};
        for(int i = 0; i < compiler.link_to_libraries.count; i += 1) {
            FBS_APPEND_ARRAY(&builder, compiler.link_to_libraries.data[i]);
            FBS_APPEND(&builder, '\0');
        }
        if(builder.count > 0) { result.link_to_libraries = fbs_string_to_list(builder); }
    }
    
    if(compiler.export_functions.count > 0) {
        FBS_String builder = {0};
        for(int i = 0; i < compiler.export_functions.count; i += 1) {
            FBS_APPEND_ARRAY(&builder, compiler.export_functions.data[i]);
            FBS_APPEND(&builder, '\0');
        }
        if(builder.count > 0) { result.export_functions = fbs_string_to_list(builder); }
    }
    
    return result;
}

FBS_API fbs_error
fbs_self_rebuild(int arg_count, char **arg_data, const char *old_executable_path, List_FBS_String *source_paths) {
    if(!old_executable_path) {
        FBS_LOG(ERROR, "fbs_self_rebuild: old_executable_path was not set!\n");
        return FBS_ERROR_GENERIC;
    }
    
    FBS_String program_path = fbs_global_build_program_path;
    
    int needs_rebuild = 0;
    if(source_paths) {
        for(int i = 0; i < source_paths->count; i += 1) {
            FBS_String source_path = source_paths->data[i];
            
            needs_rebuild = fbs_is_file_newer(source_path.data, program_path.data);
            if(needs_rebuild < 0) { return needs_rebuild; }
            if(needs_rebuild > 0) { break; }
        }
    } else {
        needs_rebuild = 1;
    }
    
    if(!needs_rebuild) { return FBS_FALSE; }
    
    
    int move_result = fbs_move_file(program_path.data, old_executable_path);
    if(move_result < 0) { return FBS_ERROR_GENERIC; }
    
    FBS_LOG(INFO, FBS_LOG_COLOR(BRIGHT_WHITE, "Rebuilding self...\n"));
    
    FBS_Compiler compiler = {0};
    FBS_APPEND(&compiler.input_files, fbs_global_build_source_path);
    
    FBS_String executable_extension = FBS_String_lit(FBS_EXECUTABLE_EXTENSION);
    
    FBS_APPEND_ARRAY(&compiler.output_file_name, program_path);
    if(executable_extension.length > 0) {
        if(fbs_ends_with(compiler.output_file_name, executable_extension)) {
            compiler.output_file_name.length -= executable_extension.length;
        }
    }
    
#if defined(FBS_ENABLE_CONSOLE_COLORS) || defined(FUTHARK_ENABLE_CONSOLE_COLORS)
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.defines, "-DFBS_ENABLE_CONSOLE_COLORS");
#endif
    
    if(!fbs_run_compiler(compiler)) { return FBS_ERROR_GENERIC; }
    
    List_FBS_String cmd = {0};
    FBS_APPEND(&cmd, program_path);
    FBS_APPEND_STR_LIT_AS_STRING(&cmd, "_fbs_is_rebuilt_");
    for(int i = 0; i < arg_count; i += 1) {
        FBS_String it = fbs_ntstring_to_string(arg_data[i]);
        FBS_APPEND(&cmd, it);
    }
    int cmd_result = fbs_run_command_sync(cmd);
    if(cmd_result) { return FBS_ERROR_GENERIC; }
    return FBS_TRUE;
}

FBS_API void
fbs_get_compiler_output_paths(FBS_Compiler compiler,
                              FBS_String *output_directory,
                              FBS_String *output_file)
{
    if(compiler.output_directory.data) {
        FBS_APPEND_ARRAY(output_directory, compiler.output_directory);
    } else {
        int index = fbs_last_index_of_any_ntstring(compiler.output_file_name, "\\/");
        if(index >= 0) {
            FBS_APPEND_MANY(output_directory, compiler.output_file_name.data, index);
        }
    }
    
    if(output_directory->data) {
        if(!fbs_ends_with_char(*output_directory, '/') && !fbs_ends_with_char(*output_directory, '\\')) {
            FBS_APPEND(output_directory, '/');
        }
    }
    
    FBS_NULL_TERMINATE(output_directory);
    
    //
    
    if(compiler.output_file_name.data) {
        if(fbs_last_index_of_any_ntstring(compiler.output_file_name, "\\/") < 0) {
            FBS_APPEND_ARRAY(output_file, *output_directory);
        }
        
        FBS_APPEND_ARRAY(output_file, compiler.output_file_name);
        FBS_NULL_TERMINATE(output_file);
    } else if(compiler.input_files.count > 0) {
        FBS_String input_file = compiler.input_files.data[0];
        
        if(output_directory->data) {
            FBS_APPEND_ARRAY(output_file, *output_directory);
            //output_file->length -= 1;
        }
        
        int index = fbs_last_index_of_any_ntstring(input_file, "\\/");
        if(index > 0) {
            input_file.data   += index;
            input_file.length -= index;
        }
        
        int length = fbs_last_index_of_char(input_file, '.');
        if(length > 1) {
            FBS_APPEND_MANY(output_file, input_file.data, length);
        } else {
            FBS_APPEND_ARRAY(output_file, input_file);
        }
        
        FBS_NULL_TERMINATE(output_file);
    }
}

FBS_API int
fbs_run_compiler(FBS_Compiler compiler) {
    if(compiler.input_files.count < 1) {
        FBS_LOG(ERROR, "No input file(s) specified to compile!\n");
        return 0;
    }
    
    if(compiler.output_file_name.length < 1) {
        FBS_LOG(ERROR, "No output file name!\n");
        return 0;
    }
    
    int result = 0;
    
#if FBS_COMPILER_TARGET == FBS_COMPILER_TARGET_MSVC
    result = fbs_run_compiler_msvc(compiler);
#elif FBS_COMPILER_TARGET == FBS_COMPILER_TARGET_GCC
    result = fbs_run_compiler_gcc(compiler);
#elif FBS_COMPILER_TARGET == FBS_COMPILER_TARGET_EMSCRIPTEN
    result = fbs_run_compiler_emscripten(compiler);
#elif !defined(FBS_COMPILER_TARGET)
#  error FBS_COMPILER_TARGET is not defined!
#else
#  error Unimplemented compiler target!
#endif
    
    return result;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// MSVC
//
FBS_API int
fbs_run_compiler_msvc(FBS_Compiler compiler) {
    FBS_String icon_path = {0};
    
    FBS_String output_directory = {0};
    FBS_String output_file = {0};
    fbs_get_compiler_output_paths(compiler, &output_directory, &output_file);
    
#define FBS_TMP(string_literal) do {\
FBS_APPEND_STR_LIT(&builder, string_literal);\
FBS_APPEND(&builder, 0);\
} while(0)
    
    FBS_String builder = {0};
    
    // NOTE(Patrik): Compiler
    if(!FBS_IS_FLAG(compiler.flags, FBS_ONLY_RUN_LINKER)) {
        for(int input_file_index = 0; input_file_index < compiler.input_files.count; input_file_index += 1) {
            builder.length = 0;
            
            FBS_TMP("cl.exe");
            FBS_TMP("-nologo");
            FBS_TMP("-c");
            
            FBS_String input_file = compiler.input_files.data[input_file_index];
            FBS_APPEND_ARRAY(&builder, input_file);
            FBS_APPEND(&builder, 0);
            
            if(FBS_IS_FLAG(compiler.flags, FBS_ENABLE_DEBUG_OUTPUT)) { FBS_TMP("-Zi"); }
            
            if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_DISABLE_OPTIMIZATION) {
                FBS_TMP("-Od");
            } else if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_OPTIMIZATION_MIN_CODE) {
                FBS_TMP("-O1");
            } else if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_OPTIMIZATION_MAX_SPEED) {
                FBS_TMP("-O2");
            }
            
            if(output_directory.data) {
                FBS_TMP("-Fo:");
                FBS_APPEND_ARRAY(&builder, output_directory);
                //FBS_APPEND_ARRAY(&builder, compiler.output_file_name);
                FBS_APPEND(&builder, 0);
            }
            
            for(int i = 0; i < compiler.defines.count; i += 1) {
                if(!fbs_begins_with_ntstring(compiler.defines.data[i], "-D")) {
                    FBS_APPEND_STR_LIT(&builder, "-D");
                }
                FBS_APPEND_ARRAY(&builder, compiler.defines.data[i]);
                FBS_APPEND(&builder, 0);
            }
            
            for(int i = 0; i < compiler.include_directories.count; i += 1) {
                if(!fbs_begins_with_ntstring(compiler.include_directories.data[i], "-I")) {
                    FBS_APPEND_STR_LIT(&builder, "-I");
                }
                FBS_APPEND_ARRAY(&builder, compiler.include_directories.data[i]);
                FBS_APPEND(&builder, 0);
            }
            
            for(int i = 0; i < compiler.msvc.compiler.count; i += 1) {
                FBS_APPEND_ARRAY(&builder, compiler.msvc.compiler.data[i]);
                FBS_APPEND(&builder, 0);
            }
            
            List_FBS_String commands = fbs_string_to_list(builder);
            int result = fbs_run_command_sync(commands);
            if(!result) { return 0; }
            FBS_FREE(commands.data);
        }
    }
    
    if(!FBS_IS_FLAG(compiler.flags, FBS_DISABLE_LINKING)) {
        // NOTE(Patrik): Resource
        if(compiler.icon_path.data) {
            builder.length = 0;
            
            FBS_APPEND_ARRAY(&icon_path, output_file);
            FBS_APPEND_STR_LIT(&icon_path, ".res");
            
            FBS_TMP("rc.exe");
            FBS_TMP("-nologo");
            
            FBS_APPEND_STR_LIT(&builder, "-fo");
            FBS_APPEND_ARRAY(&builder, icon_path);
            FBS_APPEND(&builder, 0);
            
            FBS_APPEND_ARRAY(&builder, compiler.icon_path);
            FBS_APPEND(&builder, 0);
            
            List_FBS_String commands = fbs_string_to_list(builder);
            int result = fbs_run_command_sync(commands);
            if(!result) { return 0; }
            FBS_FREE(commands.data);
        }
        
        // NOTE(Patrik): Linker
        {
            builder.length = 0;
            
            if(FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_STATIC_LIBRARY)) {
                FBS_TMP("lib.exe");
            } else {
                FBS_TMP("link.exe");
                if(FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_SHARED_LIBRARY)) {
                    FBS_TMP("-DLL");
                }
                
                if(FBS_IS_FLAG(compiler.flags, FBS_ENABLE_DEBUG_OUTPUT)) {
                    FBS_TMP("-DEBUG");
                    
                    FBS_APPEND_STR_LIT(&builder, "-PDB:");
                    FBS_APPEND_ARRAY(&builder, output_file);
                    FBS_APPEND_STR_LIT(&builder, ".pdb");
                    FBS_APPEND(&builder, 0);
                }
            }
            
            FBS_APPEND_STR_LIT(&builder, "-out:");
            FBS_APPEND_ARRAY(&builder, output_file);
            if(FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_SHARED_LIBRARY)) {
                FBS_APPEND_STR_LIT(&builder, ".dll");
            } else if(FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_STATIC_LIBRARY)) {
                FBS_APPEND_STR_LIT(&builder, ".lib");
            } else {
                FBS_APPEND_STR_LIT(&builder, ".exe");
            }
            FBS_APPEND(&builder, 0);
            
            FBS_TMP("-nologo");
            
            for(int i = 0; i < compiler.input_files.count; i += 1) {
                FBS_String input_file = compiler.input_files.data[i];
                
                int index = fbs_last_index_of_any_ntstring(input_file, "\\/");
                if(index >= 0) {
                    input_file.data   += index + 1;
                    input_file.length -= index + 1;
                }
                
                if(input_file.length >= 0) {
                    FBS_APPEND_ARRAY(&builder, output_directory);
                    FBS_APPEND_ARRAY(&builder, input_file);
                    if(fbs_ends_with_ntstring(builder, ".cpp")) {
                        builder.length -= 4;
                    } else if(fbs_ends_with_ntstring(builder, ".c")) {
                        builder.length -= 2;
                    }
                    FBS_APPEND_STR_LIT(&builder, ".obj");
                    FBS_APPEND(&builder, 0);
                } else {
                    FBS_INVALID_CODE_PATH;
                }
            }
            
            for(int i = 0; i < compiler.link_to_objects.count; i += 1) {
                FBS_String object = compiler.link_to_objects.data[i];
                
                FBS_APPEND_ARRAY(&builder, object);
                if(!fbs_ends_with_ntstring(object, ".obj")) {
                    FBS_APPEND_STR_LIT(&builder, ".obj");
                }
                FBS_APPEND(&builder, 0);
            }
            
            for(int i = 0; i < compiler.link_to_libraries.count; i += 1) {
                FBS_String library = compiler.link_to_libraries.data[i];
                
                FBS_APPEND_ARRAY(&builder, library);
                if(!fbs_ends_with_ntstring(library, ".lib")) {
                    FBS_APPEND_STR_LIT(&builder, ".lib");
                }
                FBS_APPEND(&builder, 0);
            }
            
            if(compiler.icon_path.data) {
                FBS_APPEND_ARRAY(&builder, icon_path);
                FBS_APPEND(&builder, 0);
            }
            
            for(int i = 0; i < compiler.msvc.linker.count; i += 1) {
                FBS_APPEND_ARRAY(&builder, compiler.msvc.linker.data[i]);
                FBS_APPEND(&builder, 0);
            }
            
            List_FBS_String commands = fbs_string_to_list(builder);
            int result = fbs_run_command_sync(commands);
            if(!result) { return 0; }
            FBS_FREE(commands.data);
        }
    }
    
#undef FBS_TMP
    
    FBS_FREE(builder.data);
    return 1;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// GCC
//
FBS_API void
fbs_gcc_link_to_library(FBS_String *builder, FBS_String *temp, FBS_String it) {
    fbs_bool is_found = FBS_FALSE;
    fbs_bool is_shared = FBS_TRUE;
    fbs_bool needs_extension = FBS_TRUE;
    if(fbs_ends_with_ntstring(it, ".so")) {
        if(fbs_file_exists(it.data) > 0) {
            is_found = FBS_TRUE;
            is_shared = FBS_TRUE;
        }
    } else if(fbs_begins_with_ntstring(it, ".a")) {
        if(fbs_file_exists(it.data) > 0) {
            is_found = FBS_TRUE;
            is_shared = FBS_FALSE;
        }
    } else {
        needs_extension = FBS_TRUE;
        
        temp->length = 0;
        FBS_APPEND_ARRAY(temp, it);
        FBS_APPEND_STR_LIT(temp, ".a");
        FBS_NULL_TERMINATE(temp);
        if(fbs_file_exists(temp->data)) {
            is_found = FBS_TRUE;
            is_shared = FBS_FALSE;
        } else {
            temp->length = it.length;
            FBS_APPEND_STR_LIT(temp, ".so");
            FBS_NULL_TERMINATE(temp);
            if(fbs_file_exists(temp->data)) {
                is_found = FBS_TRUE;
                is_shared = FBS_TRUE;
            }
        }
    }
    
    if(is_found) {
        FBS_APPEND_ARRAY(builder, it);
        if(needs_extension) {
            if(is_shared) {
                FBS_APPEND_STR_LIT(builder, ".so");
            } else {
                FBS_APPEND_STR_LIT(builder, ".a");
            }
        }
        FBS_APPEND(builder, 0);
    } else {
        FBS_String name = it;
        int index = fbs_last_index_of_any_ntstring(it, "\\/");
        if(index >= 0) {
            FBS_APPEND_STR_LIT(builder, "-L");
            FBS_APPEND_MANY(builder, it.data, index + 1);
            FBS_APPEND(builder, 0);
            
            name.data   += index + 2;
            name.length -= index + 2;
        }
        
        if(is_shared) {
            FBS_APPEND_STR_LIT(builder, "-l");
            FBS_APPEND_ARRAY(builder, name);
            FBS_APPEND(builder, 0);
        } else {
            FBS_APPEND_STR_LIT(builder, "-l:");
            FBS_APPEND_ARRAY(builder, name);
            FBS_APPEND(builder, 0);
        }
    }
}

FBS_API int
fbs_run_compiler_gcc(FBS_Compiler compiler) {
    FBS_String output_directory = {0};
    FBS_String output_file = {0};
    fbs_get_compiler_output_paths(compiler, &output_directory, &output_file);
    
#define FBS_TMP(string_literal) do {\
FBS_APPEND_STR_LIT(&builder, string_literal);\
FBS_APPEND(&builder, 0);\
} while(0)
    
    FBS_String builder = {0};
    FBS_String temp = {0};
    
    for(int input_file_index = 0; input_file_index < compiler.input_files.count; input_file_index += 1) {
        builder.length = 0;
        
        FBS_TMP("gcc");
        
        FBS_String input_file = compiler.input_files.data[input_file_index];
        FBS_String input_name = input_file;
        {
            int index = fbs_last_index_of_char(input_name, '.');
            if(index >= 0) { input_name.length = index; }
            
            index = fbs_last_index_of_any_ntstring(input_name, "\\/");
            if(index >= 0) {
                input_name.data   += index + 2;
                input_name.length -= index + 2;
            }
        }
        
        for(int i = 0; i < compiler.gcc.compiler.count; i += 1) {
            FBS_APPEND_ARRAY(&builder, compiler.gcc.compiler.data[i]);
            FBS_APPEND(&builder, 0);
        }
        
        if((compiler.flags & FBS_OUTPUT_AS_LIBRARY) == 0) {
            FBS_TMP("-o");
            FBS_APPEND_ARRAY(&builder, output_file);
            if(FBS_IS_FLAG(compiler.flags, FBS_DISABLE_LINKING)) {
                FBS_APPEND_STR_LIT(&builder, ".o");
                FBS_APPEND(&builder, 0);
                FBS_TMP("-c");
            } else if(fbs_ntstring_length(FBS_EXECUTABLE_EXTENSION) > 0) {
                FBS_APPEND_STR_LIT(&builder, FBS_EXECUTABLE_EXTENSION);
                FBS_APPEND(&builder, 0);
            } else {
                FBS_APPEND(&builder, 0);
            }
        } else {
            FBS_TMP("-o");
            FBS_APPEND_ARRAY(&builder, output_directory);
            FBS_APPEND_ARRAY(&builder, input_name);
            FBS_APPEND_STR_LIT(&builder, ".o");
            FBS_APPEND(&builder, 0);
            FBS_TMP("-c");
        }
        
        FBS_APPEND_ARRAY(&builder, input_file);
        FBS_APPEND(&builder, 0);
        
        if(FBS_IS_FLAG(compiler.flags, FBS_ENABLE_DEBUG_OUTPUT)) { FBS_TMP("-g"); }
        
        if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_DISABLE_OPTIMIZATION) {
            FBS_TMP("-O0");
        } else if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_OPTIMIZATION_MIN_CODE) {
            FBS_TMP("-Os");
        } else if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_OPTIMIZATION_MAX_SPEED) {
            FBS_TMP("-O3");
        }
        
        for(int i = 0; i < compiler.defines.count; i += 1) {
            if(!fbs_begins_with_ntstring(compiler.defines.data[i], "-D")) {
                FBS_APPEND_STR_LIT(&builder, "-D");
            }
            FBS_APPEND_ARRAY(&builder, compiler.defines.data[i]);
            FBS_APPEND(&builder, 0);
        }
        
        FBS_TMP("-I.");
        for(int i = 0; i < compiler.include_directories.count; i += 1) {
            if(!fbs_begins_with_ntstring(compiler.include_directories.data[i], "-I")) {
                FBS_APPEND_STR_LIT(&builder, "-I");
            }
            FBS_APPEND_ARRAY(&builder, compiler.include_directories.data[i]);
            FBS_APPEND(&builder, 0);
        }
        
        // NOTE(Patrik): Single pass linking
        if(!FBS_IS_FLAG(compiler.flags, FBS_DISABLE_LINKING)) {
            if((compiler.flags & FBS_OUTPUT_AS_LIBRARY) == 0) {
                for(int object_index = 0; object_index < compiler.link_to_objects.count; object_index += 1) {
                    FBS_String object = compiler.link_to_objects.data[object_index];
                    
                    FBS_APPEND_ARRAY(&builder, object);
                    if(!fbs_ends_with_ntstring(object, ".o")) { FBS_APPEND_STR_LIT(&builder, ".o"); }
                    FBS_APPEND(&builder, 0);
                }
                
                if(compiler.link_to_libraries.count > 0) { FBS_TMP("-L."); }
                for(int i = 0; i < compiler.link_to_libraries.count; i += 1) {
                    FBS_String it = compiler.link_to_libraries.data[i];
                    fbs_gcc_link_to_library(&builder, &temp, it);
                }
                
                for(int i = 0; i < compiler.gcc.linker.count; i += 1) {
                    FBS_APPEND_ARRAY(&builder, compiler.gcc.linker.data[i]);
                    FBS_APPEND(&builder, 0);
                }
            }
        }
        
        List_FBS_String commands = fbs_string_to_list(builder);
        int result = fbs_run_command_sync(commands);
        if(!result) { return 0; }
        FBS_FREE(commands.data);
    }
    
    // NOTE(Patrik): Linker
    if(!FBS_IS_FLAG(compiler.flags, FBS_DISABLE_LINKING)) {
        builder.length = 0;
        
        // NOTE(Patrik): Shared library linker
        if(FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_SHARED_LIBRARY)) {
            FBS_TMP("gcc");
            
            FBS_TMP("-o");
            FBS_APPEND_ARRAY(&builder, output_file);
            FBS_APPEND_STR_LIT(&builder, ".so");
            FBS_APPEND(&builder, 0);
            FBS_TMP("-shared");
            
            for(int input_file_index = 0; input_file_index < compiler.input_files.count; input_file_index += 1) {
                FBS_String input_file = compiler.input_files.data[input_file_index];
                
                FBS_String input_name = input_file;
                {
                    int index = fbs_last_index_of_char(input_name, '.');
                    if(index >= 0) { input_name.length = index; }
                    
                    index = fbs_last_index_of_any_ntstring(input_name, "\\/");
                    if(index >= 0) {
                        input_name.data   += index + 2;
                        input_name.length -= index + 2;
                    }
                }
                
                FBS_APPEND_ARRAY(&builder, output_directory);
                FBS_APPEND_ARRAY(&builder, input_name);
                FBS_APPEND_STR_LIT(&builder, ".o");
                FBS_APPEND(&builder, 0);
            }
            
            for(int object_index = 0; object_index < compiler.link_to_objects.count; object_index += 1) {
                FBS_String object = compiler.link_to_objects.data[object_index];
                
                FBS_APPEND_ARRAY(&builder, object);
                if(!fbs_ends_with_ntstring(object, ".o")) { FBS_APPEND_STR_LIT(&builder, ".o"); }
                FBS_APPEND(&builder, 0);
            }
            
            if(compiler.link_to_libraries.count > 0) { FBS_TMP("-L."); }
            for(int i = 0; i < compiler.link_to_libraries.count; i += 1) {
                FBS_String it = compiler.link_to_libraries.data[i];
                fbs_gcc_link_to_library(&builder, &temp, it);
            }
            
            for(int i = 0; i < compiler.gcc.linker.count; i += 1) {
                FBS_APPEND_ARRAY(&builder, compiler.gcc.linker.data[i]);
                FBS_APPEND(&builder, 0);
            }
            
            List_FBS_String commands = fbs_string_to_list(builder);
            int result = fbs_run_command_sync(commands);
            if(!result) { return 0; }
            FBS_FREE(commands.data);
            
            // NOTE(Patrik): Static library linker
        } else if(FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_STATIC_LIBRARY)) {
            FBS_TMP("ar");
            FBS_TMP("rcs");
            
            FBS_TMP("-o");
            FBS_APPEND_ARRAY(&builder, output_file);
            FBS_APPEND_STR_LIT(&builder, ".a");
            FBS_APPEND(&builder, 0);
            
            for(int input_file_index = 0; input_file_index < compiler.input_files.count; input_file_index += 1) {
                FBS_String input_file = compiler.input_files.data[input_file_index];
                
                FBS_String input_name = input_file;
                {
                    int index = fbs_last_index_of_char(input_name, '.');
                    if(index >= 0) { input_name.length = index; }
                    
                    index = fbs_last_index_of_any_ntstring(input_name, "\\/");
                    if(index >= 0) {
                        input_name.data   += index + 2;
                        input_name.length -= index + 2;
                    }
                }
                
                FBS_APPEND_ARRAY(&builder, output_directory);
                FBS_APPEND_ARRAY(&builder, input_name);
                FBS_APPEND_STR_LIT(&builder, ".o");
                FBS_APPEND(&builder, 0);
            }
            
            List_FBS_String commands = fbs_string_to_list(builder);
            int result = fbs_run_command_sync(commands);
            if(!result) { return 0; }
            FBS_FREE(commands.data);
        }
    }
    
#undef FBS_TMP
    FBS_FREE(builder.data);
    return 1;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// EMSCRIPTEN
//
FBS_API int
fbs_run_compiler_emscripten(FBS_Compiler compiler) {
#if defined(FBS_INVALID_EMSCRIPTEN_PATH)
    return 0;
#endif
    
    // TODO(Patrik): Make emscripten work in a more general case.
    FBS_LOG(WARNING, "Emscripten is currently very tied to Futhark. It will probably not work outside of that project.\n");
    
    FBS_String output_directory = {0};
    FBS_String output_file = {0};
    fbs_get_compiler_output_paths(compiler, &output_directory, &output_file);
    
#define FBS_TMP(string_literal) do {\
FBS_APPEND_STR_LIT(&builder, string_literal);\
FBS_APPEND(&builder, 0);\
} while(0)
    
    FBS_String builder = {0};
    FBS_String temp = {0};
    
    for(int input_file_index = 0; input_file_index < compiler.input_files.count; input_file_index += 1) {
        builder.length = 0;
        
        FBS_TMP(FBS_EMSCRIPTEN_PATH "emcc");
        
        FBS_String input_file = compiler.input_files.data[input_file_index];
        FBS_String input_name = input_file;
        {
            int index = fbs_last_index_of_char(input_name, '.');
            if(index >= 0) { input_name.length = index; }
            
            index = fbs_last_index_of_any_ntstring(input_name, "\\/");
            if(index >= 0) {
                input_name.data   += index + 2;
                input_name.length -= index + 2;
            }
        }
        
        FBS_APPEND_ARRAY(&builder, input_file);
        FBS_APPEND(&builder, 0);
        
        // NOTE(Patrik): Executable (.html)
        if(!FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_STATIC_LIBRARY) &&
           !FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_SHARED_LIBRARY))
        {
            FBS_TMP("-o");
            FBS_APPEND_ARRAY(&builder, output_file);
            FBS_APPEND_STR_LIT(&builder, ".html");
            FBS_APPEND(&builder, 0);
            
            FBS_TMP("-s");
            FBS_TMP("USE_GLFW=3");
            FBS_TMP("-s");
            FBS_TMP("ASYNCIFY");
            FBS_TMP("-s");
            FBS_TMP("TOTAL_MEMORY=67108864");
            FBS_TMP("-s");
            FBS_TMP("FORCE_FILESYSTEM=1");
            FBS_TMP("--shell-file");
            FBS_TMP("./src/raylib_shell.html");
            FBS_TMP("--preload-file");
            FBS_TMP("./assets");
            FBS_TMP("--preload-file");
            FBS_TMP("./src");
        }
        else
        {
            FBS_TMP("-c");
            
            FBS_TMP("-o");
            FBS_APPEND_ARRAY(&builder, output_directory);
            FBS_APPEND_ARRAY(&builder, input_name);
            FBS_APPEND_STR_LIT(&builder, ".o");
            FBS_APPEND(&builder, 0);
        }
        
        if(FBS_IS_FLAG(compiler.flags, FBS_ENABLE_DEBUG_OUTPUT)) { FBS_TMP("-g"); }
        
        if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_DISABLE_OPTIMIZATION) {
            FBS_TMP("-O0");
        } else if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_OPTIMIZATION_MIN_CODE) {
            FBS_TMP("-Os");
        } else if((compiler.flags & FBS_OPTIMIZATION_MASK) == FBS_OPTIMIZATION_MAX_SPEED) {
            FBS_TMP("-O3");
        }
        
        for(int i = 0; i < compiler.defines.count; i += 1) {
            if(!fbs_begins_with_ntstring(compiler.defines.data[i], "-D")) {
                FBS_APPEND_STR_LIT(&builder, "-D");
            }
            FBS_APPEND_ARRAY(&builder, compiler.defines.data[i]);
            FBS_APPEND(&builder, 0);
        }
        
        FBS_TMP("-D_GNU_SOURCE");
        FBS_TMP("-I" FBS_EMSCRIPTEN_INCLUDE_PATH);
        
        FBS_TMP("-I.");
        for(int i = 0; i < compiler.include_directories.count; i += 1) {
            if(!fbs_begins_with_ntstring(compiler.include_directories.data[i], "-I")) {
                FBS_APPEND_STR_LIT(&builder, "-I");
            }
            FBS_APPEND_ARRAY(&builder, compiler.include_directories.data[i]);
            FBS_APPEND(&builder, 0);
        }
        
        for(int i = 0; i < compiler.emscripten.compiler.count; i += 1) {
            FBS_APPEND_ARRAY(&builder, compiler.emscripten.compiler.data[i]);
            FBS_APPEND(&builder, 0);
        }
        
        // NOTE(Patrik): Single pass linking
        if(!FBS_IS_FLAG(compiler.flags, FBS_DISABLE_LINKING)) {
            if((compiler.flags & FBS_OUTPUT_AS_LIBRARY) == 0) {
                for(int i = 0; i < compiler.link_to_objects.count; i += 1) {
                    FBS_String it = compiler.link_to_objects.data[i];
                    FBS_APPEND_ARRAY(&builder, it);
                    FBS_APPEND(&builder, 0);
                }
                
                if(compiler.link_to_libraries.count > 0) { FBS_TMP("-L."); }
                for(int i = 0; i < compiler.link_to_libraries.count; i += 1) {
                    FBS_String it = compiler.link_to_libraries.data[i];
                    fbs_gcc_link_to_library(&builder, &temp, it);
                }
                
                for(int i = 0; i < compiler.emscripten.linker.count; i += 1) {
                    FBS_APPEND_ARRAY(&builder, compiler.emscripten.linker.data[i]);
                    FBS_APPEND(&builder, 0);
                }
            }
        }
        
        
#if defined(FBS_PRINT_EMSCRIPTEN_COMMANDS)
        if(fbs_ends_with_char(builder, 0)) { builder.length -= 1; }
        FBS_NULL_TERMINATE(&builder);
        for(int i = 0; i < builder.length; i += 1) {
            if(builder.data[i] == 0) { builder.data[i] = ' '; }
        }
        FBS_LOG(ALWAYS, "%s\n", builder.data);
#else
        List_FBS_String commands = fbs_string_to_list(builder);
        int result = fbs_run_command_sync(commands);
        if(!result) { return 0; }
        FBS_FREE(commands.data);
#endif
    }
    
    if(compiler.flags & (FBS_OUTPUT_STATIC_LIBRARY | FBS_OUTPUT_SHARED_LIBRARY)) {
        compiler.flags |= FBS_DISABLE_LINKING;
    }
    
    // NOTE(Patrik): Linker
    if(!FBS_IS_FLAG(compiler.flags, FBS_DISABLE_LINKING)) {
        builder.length = 0;
        
        // NOTE(Patrik): Static library linking
        if(FBS_IS_FLAG(compiler.flags, FBS_OUTPUT_STATIC_LIBRARY)) {
            FBS_TMP(FBS_EMSCRIPTEN_PATH "emar");
            FBS_TMP("rcs");
            
            FBS_APPEND_ARRAY(&builder, output_file);
            FBS_APPEND_STR_LIT(&builder, ".a");
            FBS_APPEND(&builder, 0);
            
            for(int input_file_index = 0; input_file_index < compiler.input_files.count; input_file_index += 1) {
                FBS_String input_file = compiler.input_files.data[input_file_index];
                
                FBS_String input_name = input_file;
                {
                    int index = fbs_last_index_of_char(input_name, '.');
                    if(index >= 0) { input_name.length = index; }
                    
                    index = fbs_last_index_of_any_ntstring(input_name, "\\/");
                    if(index >= 0) {
                        input_name.data   += index + 2;
                        input_name.length -= index + 2;
                    }
                }
                
                FBS_APPEND_ARRAY(&builder, output_directory);
                FBS_APPEND_ARRAY(&builder, input_name);
                FBS_APPEND_STR_LIT(&builder, ".o");
                FBS_APPEND(&builder, 0);
            }
            
#if defined(FBS_PRINT_EMSCRIPTEN_COMMANDS)
            if(fbs_ends_with_char(builder, 0)) { builder.length -= 1; }
            FBS_NULL_TERMINATE(&builder);
            for(int i = 0; i < builder.length; i += 1) {
                if(builder.data[i] == 0) { builder.data[i] = ' '; }
            }
            FBS_LOG(ALWAYS, "%s\n", builder.data);
#else
            List_FBS_String commands = fbs_string_to_list(builder);
            int result = fbs_run_command_sync(commands);
            if(!result) { return 0; }
            FBS_FREE(commands.data);
#endif
        }
    }
    
#undef FBS_TMP
    FBS_FREE(builder.data);
    return 1;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// END IMPLEMENTATION GUARD
//
#endif


/*
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2025 Patrik Johansson
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
