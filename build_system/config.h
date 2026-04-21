//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// BEGIN INCLUDE GUARD
//
#if !defined(PROJECT_CONFIG_H)
#  define PROJECT_CONFIG_H


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// GENERAL
//
//#define PROJECT_RELEASE
#define PROJECT_RUN_AFTER_COMPILE
//#define PROJECT_TREAT_WARNINGS_AS_ERRORS
#define PROJECT_LINK_TO_STDCPP
#define FBS_ENABLE_CONSOLE_COLORS


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// GAME
//
//#define PROJECT_COMPILE_STATIC_GAME
//#define PROJECT_COMPILE_GAME


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// RAYLIB
//
#define PROJECT_USE_RAYLIB
#if defined(PROJECT_USE_RAYLIB)
//#  define PROJECT_USE_RAYLIB_VERSION "5.5"
//#  define PROJECT_USE_RAYLIB_AS_PLATFORM
//#  define PROJECT_RAYLIB_ENABLE_WAYLAND
//#  define PROJECT_RAYLIB_SHARED
//#  define PROJECT_RAYLIB_SHOW_FPS
//#  define PROJECT_RAYLIB_USE_EXTERNAL_GLFW
//#  define PROJECT_RAYLIB_DISABLE_MODULE_AUDIO
//#  define PROJECT_RAYLIB_DISABLE_MODULE_MODELS
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// PLATFORM TARGET
//
// NOTE: This decides which platform to build for.
// If no platform is specified, one will be assumed based on the current platform.
//
//#define FBS_PLATFORM_TARGET FBS_PLATFORM_TARGET_WINDOWS
//#define FBS_PLATFORM_TARGET FBS_PLATFORM_TARGET_WEB
//#define FBS_PLATFORM_TARGET FBS_PLATFORM_TARGET_LINUX


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// COMPILER TARGET
//
// NOTE: This decides which platform to build for.
// If no compiler is specified, one will be assumed based on the current platform.
//
//#define FBS_COMPILER_TARGET FBS_COMPILER_TARGET_MSVC
//#define FBS_COMPILER_TARGET FBS_COMPILER_TARGET_GCC
//#define FBS_COMPILER_TARGET FBS_COMPILER_TARGET_EMSCRIPTEN


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// END INCLUDE GUARD
//
#endif
