//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// CONFIG
//
#if !defined(PROJECT_RAYLIB_PLATFORM)
#  if FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_WEB
#    define PROJECT_RAYLIB_PLATFORM "PLATFORM_WEB"
#    define PROJECT_RAYLIB_PLATFORM_IS_WEB 1
#  else
#    define PROJECT_RAYLIB_PLATFORM "PLATFORM_DESKTOP"
#    define PROJECT_RAYLIB_PLATFORM_IS_DESKTOP 1
#  endif
#endif

#if !defined(PROJECT_RAYLIB_GRAPHICS)
#  if PROJECT_RAYLIB_PLATFORM_IS_WEB
#    define PROJECT_RAYLIB_GRAPHICS "GRAPHICS_API_OPENGL_ES3"
#  elif defined(__TINYC__)
#    define PROJECT_RAYLIB_GRAPHICS "GRAPHICS_API_OPENGL_11"
#  endif
#endif

#if !defined(PROJECT_RAYLIB_ROOT_PATH)
#  if defined(PROJECT_USE_RAYLIB_VERSION)
#    define PROJECT_RAYLIB_ROOT_PATH "./lib/raylib-" PROJECT_USE_RAYLIB_VERSION "/"
#  else
#    define PROJECT_RAYLIB_ROOT_PATH "./lib/raylib/"
#  endif
#endif

#if !defined(PROJECT_RAYLIB_SOURCE_PATH)
#  define PROJECT_RAYLIB_SOURCE_PATH PROJECT_RAYLIB_ROOT_PATH "src/"
#endif

#if !defined(PROJECT_RAYLIB_BUILD_PATH)
#  define PROJECT_RAYLIB_BUILD_PATH BUILD_FOLDER_PATH "raylib/" FBS_PLATFORM_TARGET_NAME "-" FBS_COMPILER_TARGET_NAME "/"
#endif

#if !defined(PROJECT_RAYLIB_HEADER_PATH)
#  define PROJECT_RAYLIB_HEADER_PATH LIBRARY_SOURCE_PATH "raylib/"
#endif

#if defined(PROJECT_RAYLIB_SHARED)
#  if defined(PROJECT_USE_RAYLIB_VERSION)
#    define PROJECT_RAYLIB_LIB_PATH PROJECT_RAYLIB_BUILD_PATH "raylib-shared-" PROJECT_USE_RAYLIB_VERSION
#  else
#    define PROJECT_RAYLIB_LIB_PATH PROJECT_RAYLIB_BUILD_PATH "raylib-shared"
#  endif
#else
#  if defined(PROJECT_USE_RAYLIB_VERSION)
#    define PROJECT_RAYLIB_LIB_PATH PROJECT_RAYLIB_BUILD_PATH "raylib-static-" PROJECT_USE_RAYLIB_VERSION
#  else
#    define PROJECT_RAYLIB_LIB_PATH PROJECT_RAYLIB_BUILD_PATH "raylib-static"
#  endif
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// GLOBALS
//
static const char *raylib_modules[] = {
    "rcore",
    "rshapes",
    "rtext",
    "rtextures",
    "utils",
    
#if !defined(PROJECT_RAYLIB_USE_EXTERNAL_GLFW) && PROJECT_RAYLIB_PLATFORM_IS_DESKTOP
    "rglfw",
#endif
    
#if !defined(PROJECT_RAYLIB_DISABLE_MODULE_MODELS)
    "rmodels",
#endif
    
#if !defined(PROJECT_RAYLIB_DISABLE_MODULE_AUDIO)
    "raudio",
#endif
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// PROCEDURES
//
static int
should_raylib_recompile(void) {
    fbs_bool should_recompile = FBS_FALSE;
    int success = 0;
    
    {
        FBS_String directories[] = {
            FBS_String_lit(BUILD_FOLDER_PATH "raylib/"),
            FBS_String_lit(BUILD_FOLDER_PATH "raylib/" FBS_PLATFORM_TARGET_NAME"-"FBS_COMPILER_TARGET_NAME),
            FBS_String_lit(PROJECT_RAYLIB_HEADER_PATH),
        };
        
        int directory_count = FBS_ARRAY_COUNT(directories);
        for(int i = 0; i < directory_count; i += 1) {
            success = fbs_create_directory_if_new(directories[i].data);
            if(success < 0) { return -1; }
            should_recompile |= success;
        }
    }
    
    {
        struct ____ {
            const char *old_path;
            const char *new_path;
        } paths[] = {
            {PROJECT_RAYLIB_SOURCE_PATH "raylib.h", PROJECT_RAYLIB_HEADER_PATH "raylib.h"},
            {PROJECT_RAYLIB_SOURCE_PATH "raymath.h", PROJECT_RAYLIB_HEADER_PATH "raymath.h"},
            {PROJECT_RAYLIB_SOURCE_PATH "rlgl.h", PROJECT_RAYLIB_HEADER_PATH "rlgl.h"},
            {PROJECT_RAYLIB_ROOT_PATH "LICENSE", PROJECT_RAYLIB_HEADER_PATH "LICENSE"},
            //{PROJECT_RAYLIB_ROOT_PATH "futhark_changes.txt", PROJECT_RAYLIB_HEADER_PATH "futhark_changes.txt"},
        };
        
        int path_count = FBS_ARRAY_COUNT(paths);
        for(int i = 0; i < path_count; i += 1) {
            if(!fbs_file_exists(paths[i].old_path)) {
                FBS_LOG(ERROR, "The file \"%s\" does not exist!\nWas it removed by mistake?\n", paths[i].old_path);
                return -1;
            } else if(!fbs_file_exists(paths[i].new_path)) {
                fbs_copy_file(paths[i].old_path, paths[i].new_path);
                should_recompile = FBS_TRUE;
            } else if(!should_recompile) {
                if(fbs_is_file_newer(paths[i].new_path, paths[i].old_path)) {
                    fbs_copy_file(paths[i].old_path, paths[i].new_path);
                }
            }
        }
    }
    
    const char *lib_name = 0;
#if defined(PROJECT_RAYLIB_SHARED)
    lib_name = PROJECT_RAYLIB_LIB_PATH FBS_SHARED_LIBRARY_EXTENSION;
#else
    lib_name = PROJECT_RAYLIB_LIB_PATH FBS_STATIC_LIBRARY_EXTENSION;
#endif
    
    success = fbs_file_exists(lib_name);
    if(success < 0) { return -1; }
    if(!success) { should_recompile = FBS_TRUE; }
    
    // TODO(Patrik): ...
    
    return should_recompile;
}

static
CMD_PROC(build_raylib) {
    fbs_bool force_recompile = (arg_count >= 0);
    
    int should_recompile = should_raylib_recompile();
    if(should_recompile < 0) { return COMMAND_RESULT_ERROR; }
    if(!should_recompile && !force_recompile) { return COMMAND_RESULT_EXIT; }
    
    FBS_LOG(INFO, "----====>> Building Raylib...\n");
    
    FBS_String builder = {0};
    
    FBS_Compiler compiler = {0};
    //compiler.flags |= FBS_OPTIMIZATION_MAX_SPEED;
    compiler.flags |= FBS_ENABLE_DEBUG_OUTPUT;
    
    FBS_APPEND_STR_LIT(&compiler.output_directory, PROJECT_RAYLIB_BUILD_PATH);
    FBS_NULL_TERMINATE(&compiler.output_directory);
    
    FBS_APPEND(&compiler.defines, FBS_String_lit(PROJECT_RAYLIB_PLATFORM));
    
#if defined(PROJECT_RAYLIB_GRAPHICS)
    FBS_APPEND(&compiler.defines, FBS_String_lit(PROJECT_RAYLIB_GRAPHICS));
#endif
    
    FBS_String modules = {0};
    int module_count = FBS_ARRAY_COUNT(raylib_modules);
    for(int module_index = 0; module_index < module_count; module_index += 1) {
        builder.length = 0;
        FBS_APPEND_STR_LIT(&builder, PROJECT_RAYLIB_SOURCE_PATH);
        FBS_APPEND_NTSTRING(&builder, raylib_modules[module_index]);
        FBS_APPEND_STR_LIT(&builder, ".c");
        
        FBS_APPEND_ARRAY(&modules, builder);
        FBS_APPEND(&modules, 0);
    }
    compiler.input_files = fbs_string_to_list(modules);
    
    
    FBS_APPEND(&compiler.include_directories, FBS_String_lit(PROJECT_RAYLIB_SOURCE_PATH));
    FBS_APPEND(&compiler.include_directories, FBS_String_lit(PROJECT_RAYLIB_SOURCE_PATH "extras"));
    FBS_APPEND(&compiler.include_directories, FBS_String_lit(PROJECT_RAYLIB_SOURCE_PATH "external/glfw/include"));
    FBS_APPEND(&compiler.include_directories, FBS_String_lit(PROJECT_RAYLIB_SOURCE_PATH "external/glfw/deps/mingw"));
    
#if (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_WINDOWS)
    FBS_APPEND(&compiler.include_directories, FBS_String_lit(PROJECT_RAYLIB_SOURCE_PATH "external"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("gdi32"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("winmm"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("user32"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("shell32"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("opengl32"));
#elif (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_LINUX)
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("GL"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("c"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("m"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("pthread"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("dl"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("rt"));
    FBS_APPEND(&compiler.link_to_libraries, FBS_String_lit("X11"));
#  if defined(PROJECT_RAYLIB_ENABLE_WAYLAND)
    FBS_APPEND(&compiler.defines, FBS_String_lit("_GLFW_WAYLAND"));
#  else
    FBS_APPEND(&compiler.defines, FBS_String_lit("_GLFW_X11"));
#  endif
    FBS_APPEND(&compiler.gcc.compiler, FBS_String_lit("-fPIC"));
#endif
    
#if defined(PROJECT_RAYLIB_SHARED)
    compiler.flags |= FBS_OUTPUT_SHARED_LIBRARY;
    FBS_APPEND_STR_LIT(&compiler.output_file_name, "raylib-shared");
#  if defined(PROJECT_USE_RAYLIB_VERSION)
    FBS_APPEND_STR_LIT(&compiler.output_file_name, "-" PROJECT_USE_RAYLIB_VERSION);
#  endif
    
    FBS_APPEND(&compiler.defines, FBS_String_lit("BUILD_LIBTYPE_SHARED"));
#else
    compiler.flags |= FBS_OUTPUT_STATIC_LIBRARY;
    FBS_APPEND_STR_LIT(&compiler.output_file_name, "raylib-static");
#  if defined(PROJECT_USE_RAYLIB_VERSION)
    FBS_APPEND_STR_LIT(&compiler.output_file_name, "-" PROJECT_USE_RAYLIB_VERSION);
#  endif
    
#endif
    
    if(!fbs_run_compiler(compiler)) { return -1; }
    
    FBS_FREE(modules.data);
    FBS_FREE(builder.data);
    
    return COMMAND_RESULT_EXIT;
}
