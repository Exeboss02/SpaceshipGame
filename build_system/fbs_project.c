// #define PROJECT_RAYLIB_SOURCE_PATH "./external/raylib"
// #define PROJECT_RAYLIB_LIB_PATH "./external/raylib/raylib"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// UTILITY
//
static void
strict_warnings(FBS_Compiler *compiler) {
    // NOTE(Patrik): MSVC
    FBS_APPEND_STR_LIT_AS_STRING(&compiler->msvc.compiler, "-WX");
    FBS_APPEND_STR_LIT_AS_STRING(&compiler->msvc.compiler, "-Wall");
    
#define E(str) FBS_APPEND_STR_LIT_AS_STRING(&compiler->msvc.compiler, str)
    
    E("-wd4189"); // local variable is initialized but not referenced
    
    E("-wd4018"); // signed/unsigned mismatch
    E("-wd4042"); // 'unnamed-parameter': has bad storage class
    E("-wd4100"); // unreferenced formal parameter
    E("-wd4127"); // conditional expression is constant
    E("-wd4191"); // 'type cast': unsafe conversion from 'foo' to 'bar'
    E("-wd4201"); // nonstandard extension used: nameless struct/union
    E("-wd4388"); // signed/unsigned mismatch
    E("-wd4459"); // declaration of 'foo' hides global declaration
    E("-wd4668"); // 'foo' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
    E("-wd4710"); //  'foo': function not inlined
    E("-wd4711"); // 'foo' selected for automatic inline expansion
    E("-wd4820"); // N bytes padding added after data member 'foo'
    E("-wd5045"); // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    E("-wd4242"); // '+=': conversion from 'A' to 'B', possible loss of data
    E("-wd4244"); // '+=': conversion from 'A' to 'B', possible loss of data
    //E("-wd"); // 
    //E("-wd"); // 
    
#undef E
    
    // NOTE(Patrik): GCC
    FBS_APPEND_STR_LIT_AS_STRING(&compiler->gcc.compiler, "-Werror");
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// BUILD
//
static
CMD_PROC(build_game) {
    FBS_Compiler compiler = {0};
    
#if defined(PROJECT_RELEASE)
    compiler.flags |= FBS_OPTIMIZATION_MAX_SPEED;
#else
    compiler.flags |= FBS_ENABLE_DEBUG_OUTPUT;
#endif
    
    FBS_APPEND_STR_LIT(&compiler.output_directory, BUILD_FOLDER_PATH);
    FBS_NULL_TERMINATE(&compiler.output_directory);
    
    FBS_APPEND_STR_LIT(&compiler.output_file_name, NAME_OF_EXECUTABLE);
    
#if defined(PROJECT_TREAT_WARNINGS_AS_ERRORS)
    strict_warnings(&compiler);
#endif
    
#if defined(PROJECT_LINK_TO_STDCPP)
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.gcc.linker, "-lstdc++");
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.msvc.compiler, "-std:c++17");
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.msvc.compiler, "-EHsc");
#endif
    
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.include_directories, SOURCE_FOLDER_PATH);
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.include_directories, LIBRARY_SOURCE_PATH);
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.include_directories, PROJECT_RAYLIB_SOURCE_PATH);
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.include_directories, HEADER_PATH);
    
    // NOTE: When compiling a static library on gcc,
    // the order of the libraries to link matters!
    // So because compilers are stupid and hate convinence,
    // you _have_ to put raylib before the other libraries that it depends on.
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.link_to_libraries, PROJECT_RAYLIB_LIB_PATH);
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.link_to_libraries, PROJECT_LUA_LIB_PATH);
    
#if (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_WINDOWS)
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.link_to_libraries, "opengl32");
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.link_to_libraries, "gdi32");
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.link_to_libraries, "winmm");
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.link_to_libraries, "user32");
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.link_to_libraries, "shell32");
#elif (FBS_PLATFORM_TARGET == FBS_PLATFORM_TARGET_LINUX)
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.link_to_libraries, "m");
#endif
    List_FBS_String files = fbs_get_directory_files(SOURCE_FOLDER_PATH);
    List_FBS_String game_files = fbs_get_directory_files(GAME_FOLDER_PATH);
    FBS_String input = {0};
    FBS_String output = {0};

    FBS_LOG(INFO, "%d\n", files.count);

    compiler.flags |= FBS_DISABLE_LINKING;

    for (int i = 0; i < game_files.count; i++)
    {
        input.length = 0;
        FBS_APPEND_STR_LIT(&input, GAME_FOLDER_PATH);
        FBS_APPEND_ARRAY(&input, game_files.data[i]);
        FBS_NULL_TERMINATE(&input);

        FBS_LOG(INFO, "%s\n", input.data);

        if(fbs_directory_exists(input.data))
        {
            continue;
        }
        else if(fbs_ends_with_ntstring(game_files.data[i], ".cpp"))
        {
            output.length = 0;
            FBS_APPEND_ARRAY(&output, game_files.data[i]);
            FBS_NULL_TERMINATE(&output);

            compiler.input_files.count = 0;
            FBS_APPEND(&compiler.input_files, input);
            if(!fbs_run_compiler(compiler)) { return COMMAND_RESULT_ERROR; }
        }
    }

    for (int i = 0; i < files.count; i++)
    {
        input.length = 0;
        FBS_APPEND_STR_LIT(&input, SOURCE_FOLDER_PATH);
        FBS_APPEND_ARRAY(&input, files.data[i]);
        FBS_NULL_TERMINATE(&input);

        FBS_LOG(INFO, "%s\n", input.data);

        if(fbs_directory_exists(input.data))
        {
            continue;
        }
        else if(fbs_ends_with_ntstring(files.data[i], ".cpp"))
        {
            output.length = 0;
            FBS_APPEND_ARRAY(&output, files.data[i]);
            FBS_NULL_TERMINATE(&output);

            compiler.input_files.count = 0;
            FBS_APPEND(&compiler.input_files, input);
            if(!fbs_run_compiler(compiler)) { return COMMAND_RESULT_ERROR; }
        }
    }

    compiler.flags &= ~FBS_DISABLE_LINKING;
    compiler.flags |= FBS_ONLY_RUN_LINKER;

    for (int i = 0; i < files.count; i++)
    {
        FBS_String input = {0};
        FBS_APPEND_STR_LIT(&input, BUILD_FOLDER_PATH);
        FBS_APPEND_ARRAY(&input, files.data[i]);

        if(fbs_directory_exists(input.data))
        {
            continue;
        }
        else if(fbs_ends_with_ntstring(files.data[i], ".cpp"))
        {
            input.length -= 4;
            FBS_NULL_TERMINATE(&input);

            FBS_APPEND(&compiler.link_to_objects, input);
        }
    }

        for (int i = 0; i < game_files.count; i++)
    {
        FBS_String input = {0};
        FBS_APPEND_STR_LIT(&input, BUILD_FOLDER_PATH);
        FBS_APPEND_ARRAY(&input, game_files.data[i]);

        if(fbs_directory_exists(input.data))
        {
            continue;
        }
        else if(fbs_ends_with_ntstring(game_files.data[i], ".cpp"))
        {
            input.length -= 4;
            FBS_NULL_TERMINATE(&input);

            FBS_APPEND(&compiler.link_to_objects, input);
        }
    }

    if(!fbs_run_compiler(compiler)) { return COMMAND_RESULT_ERROR; }
    
    return COMMAND_RESULT_EXIT;
}