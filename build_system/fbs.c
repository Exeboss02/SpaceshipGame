//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// CONFIG
//
#define CONFIG_PATH "./build_system/config.h"
#define SOURCE_FOLDER_PATH "./src/"
#define GAME_FOLDER_PATH "./game/src/"
#define EXTERNAL_FOLDER_PATH "./external/"
#define BUILD_FOLDER_PATH "./build/"
#define FBS_HEADER_PATH "./build_system/fbs.h"
#define HEADER_PATH "./headers/"

#define LIBRARY_SOURCE_PATH SOURCE_FOLDER_PATH "external/"

#define CONFIGURED_EXECUTABLE_NAME "fbs_configured"

#define NAME_OF_EXECUTABLE "SpaceShipGame"

#define PROJECT_LUA_LIB_PATH "./lib/lua55"

#define MAX_COMMAND_ALIAS_COUNT 16


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// INCLUDES
//
#if defined(IS_CONFIGURED)
#  include "config.h"
#endif

#define FBS_IMPLEMENTATION
#include "fbs.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// TYPES
//
#define CMD_PROC(name) fbs_error name(int arg_count, char **arg_data)
typedef fbs_error Command_Proc(int arg_count, char **arg_data);

static CMD_PROC(build);
static CMD_PROC(build_raylib);
static CMD_PROC(build_game);
static CMD_PROC(run_project_executable);
static CMD_PROC(delete_build_folder);
static CMD_PROC(cmd_create_config_file);
static CMD_PROC(output_help_message);

typedef struct Command {
    Command_Proc *proc;
    const char *name;
    const char *description;
    const char *aliases[MAX_COMMAND_ALIAS_COUNT];
} Command;

enum {
    COMMAND_RESULT_ERROR = -1,
    COMMAND_RESULT_EXIT = 0,
    COMMAND_RESULT_KEEP_GOING = 1,
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// RAYLIB
//
#include "fbs_raylib.c"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// PROJECT
//
#if defined(IS_CONFIGURED)
#  include "fbs_project.c"
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// GLOBALS
//
static const char *global_files_to_check_for_recompile[] = {
    "./build_system/fbs.h",
    "./build_system/fbs.c",
    "./build_system/fbs_raylib.c",
    "./build_system/fbs_project.c",
};

FBS_String tmp_buffer = {0};

static Command global_build_commands[] = {
#if defined(IS_CONFIGURED)
#  define E(unconfigured_proc, configured_proc, ...) {configured_proc, __VA_ARGS__}
#else
#  define E(unconfigured_proc, configured_proc, ...) {unconfigured_proc, __VA_ARGS__}
#endif
    
    E(0, build, "build", "Build the project. (default)"),
    E(0, build_game, "game", "Only build the game.", "game"),
    
    E(run_project_executable, 0, "run", "Run the built executable."),
    E(delete_build_folder, 0, "delete", "Delete the build folder."),
    E(0, cmd_create_config_file, "config", "Rebuild the config file."),
    
    E(output_help_message, 0, "help", "Output this message.", "h", "-h", "-help", "--help", "?", "-?", "--?", "/?"),
    
#undef E
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// UTILITY
//
static void append_title_comment(FBS_String *buffer, FBS_String title);
static fbs_bool build_config_from_defines(FBS_String *buffer, fbs_bool config_exists);
static fbs_bool create_config_file(const char *config_path, FBS_String *buffer);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// PROCEDURES
//
static fbs_error
run_arg_command(int arg_count, char **arg_data) {
    // NOTE(Patrik): Return values:
    // If return value <  0: Error, exit the program
    // If return value == 0: No error, exit the program
    // If return value >  0: No error, keep going
    
    fbs_bool is_build = FBS_FALSE;
    
    FBS_String arg = {0};
    if(arg_count > 0) {
        arg.data = arg_data[0];
        arg.length = fbs_ntstring_length(arg.data);
        
        //is_build = fbs_string_eq_ntstring(arg, "build");
        
        arg_data += 1;
        arg_count -= 1;
    } else {
        arg = FBS_String_lit("build");
        is_build = FBS_TRUE;
    }
    
    int command_count = FBS_ARRAY_COUNT(global_build_commands);
    for(int it_index = 0; it_index < command_count; it_index += 1) {
        Command it = global_build_commands[it_index];
        
        if(!fbs_string_eq_ntstring(arg, it.name)) {
            fbs_bool found = FBS_FALSE;
            for(int alias_index = 0; alias_index < MAX_COMMAND_ALIAS_COUNT; alias_index += 1) {
                if(!it.aliases[alias_index]) { break; }
                if(!fbs_string_eq_ntstring(arg, it.aliases[alias_index])) { continue; }
                
                found = FBS_TRUE;
                break;
            }
            
            if(!found) { continue; }
        }
        
        if(!it.proc) {
#if defined(IS_CONFIGURED)
            FBS_LOG(ERROR, "No procedure for the command \"%s\"\n", it.name);
            return COMMAND_RESULT_ERROR;
#else
            return COMMAND_RESULT_KEEP_GOING;
#endif
        }
        
        fbs_error result = it.proc(arg_count, arg_data);
#if defined(PROJECT_RUN_AFTER_COMPILE)
        if(is_build && result >= 0) { result = run_project_executable(0, 0); }
#endif
        return result;
    }
    
    FBS_LOG(ERROR, "Uknown command: \"%s\"\n", arg.data);
    return -1;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// COMMANDS
//
static
CMD_PROC(build) {
    FBS_LOG(INFO, "HALLA\n");
#if !defined(IS_CONFIGURED)
    return -1;
#else    
    if(build_raylib(-1, 0) < 0) { return COMMAND_RESULT_ERROR; }
    if(build_game(-1, 0) < 0) { return COMMAND_RESULT_ERROR; }
    
    return COMMAND_RESULT_EXIT;
#endif
}

// TODO(Patrik): This is very hacky.
// It would be much more convenient to write if there was a fbs_is_executable(path);
static
CMD_PROC(run_project_executable) {
    List_FBS_String cmd = {0};
    FBS_String executable_extension = FBS_String_lit(FBS_EXECUTABLE_EXTENSION);
    
    char *executable_path = (char *)(BUILD_FOLDER_PATH NAME_OF_EXECUTABLE FBS_EXECUTABLE_EXTENSION);
    
#if !defined(PROJECT_COMPILE_STATIC_GAMES)
    fbs_error file_exists = fbs_file_exists(executable_path);
#else
    fbs_error file_exists = FBS_FALSE;
#endif
    
    if(file_exists < 0) {
        return COMMAND_RESULT_ERROR;
    } else if(file_exists) {
        tmp_buffer.length = 0;
        FBS_APPEND_NTSTRING(&tmp_buffer, executable_path);
        FBS_NULL_TERMINATE(&tmp_buffer);
    } else {
        List_FBS_String files = fbs_get_directory_files(BUILD_FOLDER_PATH);
        
        int selected = -1;
        for(int i = 0; i < files.count; i += 1) {
            FBS_String file = files.data[i];
            
            fbs_bool is_valid = fbs_begins_with_ntstring(file, NAME_OF_EXECUTABLE "_");
            if(is_valid && executable_extension.length > 0) {
                is_valid = fbs_ends_with(file, executable_extension);
            }
            
            if(is_valid) {
                selected = i;
                break;
            }
        }
        
        if(selected < 0) {
            FBS_LOG(ERROR, "No executable found!\n");
            return COMMAND_RESULT_ERROR;
        }
        
        FBS_APPEND_STR_LIT(&tmp_buffer, BUILD_FOLDER_PATH);
        FBS_APPEND_ARRAY(&tmp_buffer, files.data[selected]);
        FBS_NULL_TERMINATE(&tmp_buffer);
        
        file_exists = fbs_file_exists(tmp_buffer.data);
        if(file_exists < 0) { return COMMAND_RESULT_ERROR; }
        if(!file_exists) {
            FBS_LOG(ERROR, "The file %s does not exist!\n", tmp_buffer.data);
            return COMMAND_RESULT_ERROR;
        }
    }
    
    FBS_LOG(INFO, "--- " FBS_LOG_COLOR_BRIGHT_GREEN "RUNNING" FBS_LOG_COLOR_RESET ":\n");
    
    cmd.count = 0;
    FBS_APPEND(&cmd, tmp_buffer);
    if(!fbs_run_command_sync(cmd)) { return COMMAND_RESULT_ERROR; }
    return COMMAND_RESULT_EXIT;
}

static
CMD_PROC(cmd_create_config_file) {
    tmp_buffer.length = 0;
    if(!create_config_file(CONFIG_PATH, &tmp_buffer)) { return COMMAND_RESULT_ERROR; }
    return COMMAND_RESULT_EXIT;
}

static
CMD_PROC(delete_build_folder) {
    if(arg_count > 0) {
        FBS_String arg = fbs_ntstring_to_string(arg_data[0]);
        
        if(fbs_string_eq_ntstring(arg, "config")) {
            fbs_error delete_success = fbs_delete_file(CONFIG_PATH);
            if(delete_success < 0) { return COMMAND_RESULT_ERROR; }
            return 0;
        } else if(fbs_string_eq_ntstring(arg, "exe")) {
            fbs_bool expect_executable_extension = fbs_ntstring_length(FBS_EXECUTABLE_EXTENSION) > 0;
            
            FBS_String buffer = {0};
            
            List_FBS_String files = fbs_get_directory_files(BUILD_FOLDER_PATH);
            for(int file_index = 0; file_index < files.count; file_index += 1) {
                FBS_String file = files.data[file_index];
                
                int dot_index = fbs_last_index_of_char(file, '.');
                
                buffer.length = 0;
                if(dot_index > 0) {
                    if(fbs_ends_with_ntstring(file, FBS_SHARED_LIBRARY_EXTENSION)) {
                        FBS_APPEND_STR_LIT(&buffer, BUILD_FOLDER_PATH);
                        FBS_APPEND_ARRAY(&buffer, file);
                    } else if(expect_executable_extension) {
                        if(fbs_ends_with_ntstring(file, FBS_EXECUTABLE_EXTENSION)) {
                            FBS_APPEND_STR_LIT(&buffer, BUILD_FOLDER_PATH);
                            FBS_APPEND_ARRAY(&buffer, file);
                        }
                    }
                } else if(dot_index < 0) {
                    if(!expect_executable_extension) {
                        FBS_APPEND_STR_LIT(&buffer, BUILD_FOLDER_PATH);
                        FBS_APPEND_ARRAY(&buffer, file);
                        FBS_NULL_TERMINATE(&buffer);
                        
                        if(!fbs_file_exists(buffer.data)) { buffer.length = 0; }
                    }
                }
                
                if(buffer.length > 0) {
                    FBS_NULL_TERMINATE(&buffer);
                    fbs_error delete_success = fbs_delete_file(buffer.data);
                    if(delete_success < 0) { return COMMAND_RESULT_ERROR; }
                }
            }
            
            return 0;
        } else {
            FBS_LOG(ERROR, "Unkown subcommand for delete: %s\n", arg_data[0]);
            return -1;
        }
    }
    
    if(fbs_directory_exists(BUILD_FOLDER_PATH)) {
        if(!fbs_remove_directory_recursively(BUILD_FOLDER_PATH)) { return COMMAND_RESULT_ERROR; }
    }
    return COMMAND_RESULT_EXIT;
}

static
CMD_PROC(output_help_message) {
    FBS_LOG(ALWAYS, "Usage: %s [command] (subcommands...)\n", fbs_global_build_program_path.data);
    
    int longest_command_name_length = 0;
    int command_count = FBS_ARRAY_COUNT(global_build_commands);
    for(int command_index = 0; command_index < command_count; command_index += 1) {
        int length = fbs_ntstring_length(global_build_commands[command_index].name);
        if(length > longest_command_name_length) { longest_command_name_length = length; }
    }
    longest_command_name_length += 4;
    
    tmp_buffer.length = 0;
    for(int command_index = 0; command_index < command_count; command_index += 1) {
        Command command = global_build_commands[command_index];
        int command_name_length = fbs_ntstring_length(command.name);
        
        char spacing_char = (command_index % 2 == 0) ? '.' : ' ';
        
        tmp_buffer.length = 0;
        FBS_APPEND_STR_LIT(&tmp_buffer, "  - " FBS_LOG_COLOR_BRIGHT_CYAN);
        FBS_APPEND_NTSTRING(&tmp_buffer, command.name);
        FBS_APPEND_STR_LIT(&tmp_buffer, FBS_LOG_COLOR_GRAY " ");
        FBS_APPEND_REPEATED(&tmp_buffer, spacing_char, longest_command_name_length - command_name_length);
        FBS_APPEND_STR_LIT(&tmp_buffer, FBS_LOG_COLOR_RESET ": " FBS_LOG_COLOR_BRIGHT_YELLOW);
        
        if(command.description) { FBS_APPEND_NTSTRING(&tmp_buffer, command.description); }
        
        for(int alias_index = 0; alias_index < MAX_COMMAND_ALIAS_COUNT; alias_index += 1) {
            if(!command.aliases[alias_index]) { break; }
            
            FBS_APPEND_STR_LIT(&tmp_buffer, FBS_LOG_COLOR_RESET "\n     * " FBS_LOG_COLOR_CYAN);
            FBS_APPEND_NTSTRING(&tmp_buffer, command.aliases[alias_index]);
        }
        
        FBS_APPEND_STR_LIT(&tmp_buffer, FBS_LOG_COLOR_RESET "\n");
    }
    
    FBS_NULL_TERMINATE(&tmp_buffer);
    FBS_LOG(ALWAYS, "%s\n", tmp_buffer.data);
    return COMMAND_RESULT_EXIT;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// CONFIGURED MAIN
//
#if defined(IS_CONFIGURED)
static int
configured_main(int arg_count, char **arg_data) {
    FBS_LOG(INFO, "---- " FBS_LOG_COLOR_YELLOW "SECOND PASS" FBS_LOG_COLOR_RESET " ----\n");
    
    fbs_error result = run_arg_command(arg_count, arg_data);
    if(result < 0) { return 1; }
    return 0;
}
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// UNCONFIGURED MAIN
//
#if !defined(IS_CONFIGURED)
static int
unconfigured_main(int arg_count, char **arg_data) {
    FBS_String file = FBS_String_lit(__FILE__);
    
    fbs_bool is_rebuilt = FBS_FALSE;
    if(arg_count > 0) {
        if(fbs_ntstring_eq(arg_data[arg_count - 1], "_fbs_is_rebuilt_")) {
            is_rebuilt = FBS_TRUE;
            arg_count -= 1;
        }
    }
    
    if(!is_rebuilt) {
        List_FBS_String sources = {0};
        FBS_APPEND_STR_LIT_AS_STRING(&sources, FBS_HEADER_PATH);
        FBS_APPEND(&sources, file);
        
        int file_check_count = FBS_ARRAY_COUNT(global_files_to_check_for_recompile);
        for(int i = 0; i < file_check_count; i += 1) {
            FBS_String source = fbs_ntstring_to_string(global_files_to_check_for_recompile[i]);
            FBS_APPEND(&sources, source);
        }
        
        FBS_String moved_exe = {0};
        FBS_APPEND_ARRAY(&moved_exe, fbs_global_build_program_path);
        FBS_APPEND_STR_LIT(&moved_exe, ".old");
        FBS_NULL_TERMINATE(&moved_exe);
        
        fbs_error did_rebuild = fbs_self_rebuild(arg_count, arg_data, moved_exe.data, &sources);
        if(did_rebuild < 0) { return 1; }
        if(did_rebuild) { return 0; }
    }
    
    if(arg_count > 0) {
        fbs_error result = run_arg_command(arg_count, arg_data);
        if(result < 0) { return 1; }
        if(result == COMMAND_RESULT_EXIT) { return 0; }
    }
    
    if(is_rebuilt) {
        FBS_LOG(INFO, "---- " FBS_LOG_COLOR_YELLOW "REBUILT PASS" FBS_LOG_COLOR_RESET " ----\n");
    } else {
        FBS_LOG(INFO, "---- " FBS_LOG_COLOR_YELLOW "FIRST PASS" FBS_LOG_COLOR_RESET " ----\n");
    }
    
    fbs_error make_dir_result = fbs_create_directory_if_new(BUILD_FOLDER_PATH);
    if(make_dir_result < 0) { return 1; }
    
    fbs_bool config_created = FBS_FALSE;
    fbs_error config_exists = fbs_file_exists(CONFIG_PATH);
    if(config_exists < 0) { return 1; }
    if(!config_exists) {
        tmp_buffer.length = 0;
        if(!create_config_file(CONFIG_PATH, &tmp_buffer)) { return 1; }
        config_created = FBS_TRUE;
    }
    
    FBS_Compiler compiler = {0};
    compiler.flags |= FBS_OPTIMIZATION_MAX_SPEED;
    //compiler.flags |= FBS_ENABLE_DEBUG_OUTPUT;
    
    compiler.output_directory = FBS_String_lit(BUILD_FOLDER_PATH);
    compiler.output_file_name = FBS_String_lit(CONFIGURED_EXECUTABLE_NAME);
    FBS_APPEND_STR_LIT_AS_STRING(&compiler.defines, "-DIS_CONFIGURED");
    
    FBS_String input_file = {0};
    FBS_APPEND_STR_LIT(&input_file, __FILE__);
    if(!fbs_ends_with_ntstring(input_file, ".cpp") && !fbs_ends_with_ntstring(input_file, ".c")) {
#if defined(__cplusplus)
        FBS_APPEND_STR_LIT(&input_file, ".cpp");
#else
        FBS_APPEND_STR_LIT(&input_file, ".c");
#endif
    }
    FBS_NULL_TERMINATE(&input_file);
    FBS_APPEND(&compiler.input_files, input_file);
    
    if(!fbs_run_compiler(compiler)) { return 1; }
    
    FBS_String exe_path = {0};
    FBS_APPEND_ARRAY(&exe_path, compiler.output_directory);
    if(!fbs_ends_with_char(exe_path, '/') || !fbs_ends_with_char(exe_path, '/')) {
#if FBS_CURRENT_PLATFORM_WINDOWS
        FBS_APPEND(&exe_path, '\\');
#else
        FBS_APPEND(&exe_path, '/');
#endif
    }
    FBS_APPEND_ARRAY(&exe_path, compiler.output_file_name);
    FBS_NULL_TERMINATE(&exe_path);
    
    //
    
    List_FBS_String cmd = {0};
    FBS_APPEND(&cmd, exe_path);
    
    for(int i = 0; i < arg_count; i += 1) {
        FBS_String arg = fbs_ntstring_to_string(arg_data[i]);
        FBS_APPEND(&cmd, arg);
    }
    if(!fbs_run_command_sync(cmd)) { return 1; }
    
    FBS_LOG(INFO, "---- " FBS_LOG_COLOR_GREEN "SUCCESS" FBS_LOG_COLOR_RESET " ----\n\n");
    return 0;
}
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// MAIN
//
int
main(int arg_count, char **arg_data) {
    FBS_APPEND_STR_LIT(&fbs_global_build_source_path, __FILE__);
    FBS_NULL_TERMINATE(&fbs_global_build_source_path);
    
    FBS_APPEND_NTSTRING(&fbs_global_build_program_path, arg_data[0]);
    FBS_String executable_extension = FBS_String_lit(FBS_EXECUTABLE_EXTENSION);
    if(executable_extension.length > 0) {
        if(!fbs_ends_with(fbs_global_build_program_path, executable_extension)) {
            FBS_APPEND_ARRAY(&fbs_global_build_program_path, executable_extension);
        }
    }
    FBS_NULL_TERMINATE(&fbs_global_build_program_path);
    arg_data  += 1;
    arg_count -= 1;
    
#if defined(IS_CONFIGURED)
    return configured_main(arg_count, arg_data);
#else
    return unconfigured_main(arg_count, arg_data);
#endif
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// UTILITY
//
static void
append_title_comment(FBS_String *buffer, FBS_String title) {
    FBS_APPEND_STR_LIT(buffer, "//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FBS_APPEND_STR_LIT(buffer, "//\n");
    FBS_APPEND_STR_LIT(buffer, "//");
    if(title.data && title.length > 0) {
        FBS_APPEND(buffer, ' ');
        FBS_APPEND_ARRAY(buffer, title);
    }
    FBS_APPEND_STR_LIT(buffer, "\n//\n");
}

static fbs_bool
build_config_from_defines(FBS_String *buffer, fbs_bool config_exists) {
    append_title_comment(buffer, FBS_String_lit("GENERAL"));
    
#if !defined(PROJECT_RELEASE)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#define PROJECT_RELEASE\n");
    
#if !defined(PROJECT_RUN_AFTER_COMPILE)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#define PROJECT_RUN_AFTER_COMPILE\n");
    
#if !defined(PROJECT_TREAT_WARNINGS_AS_ERRORS)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#define PROJECT_TREAT_WARNINGS_AS_ERRORS\n");
    
#if !defined(PROJECT_LINK_TO_STDCPP)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#define PROJECT_LINK_TO_STDCPP\n");
    
#if !defined(FBS_ENABLE_CONSOLE_COLORS)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#define FBS_ENABLE_CONSOLE_COLORS\n");
    
    FBS_APPEND_STR_LIT(buffer, "\n\n");
    
    //
    
    append_title_comment(buffer, FBS_String_lit("GAME"));
    
#if !defined(PROJECT_COMPILE_STATIC_GAMES)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#define PROJECT_COMPILE_STATIC_GAME\n");
    
#if !defined(PROJECT_COMPILE_GAME)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#define PROJECT_COMPILE_GAME\n");
    
    FBS_APPEND_STR_LIT(buffer, "\n\n");
    
    //
    
    append_title_comment(buffer, FBS_String_lit("RAYLIB"));
    
#if !defined(PROJECT_USE_RAYLIB)
    if(config_exists) { FBS_APPEND_STR_LIT(buffer, "//"); }
#endif
    FBS_APPEND_STR_LIT(buffer, "#define PROJECT_USE_RAYLIB\n");
    
    FBS_APPEND_STR_LIT(buffer, "#if defined(PROJECT_USE_RAYLIB)\n");
    
#if defined(PROJECT_USE_RAYLIB_VERSION)
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_USE_RAYLIB_VERSION \"" PROJECT_USE_RAYLIB_VERSION "\"\n");
#else
    FBS_APPEND_STR_LIT(buffer, "//#  define PROJECT_USE_RAYLIB_VERSION \"5.5\"\n");
#endif
    
#if !defined(PROJECT_USE_RAYLIB_AS_PLATFORM)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_USE_RAYLIB_AS_PLATFORM\n");
    
#if !defined(PROJECT_RAYLIB_ENABLE_WAYLAND)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_RAYLIB_ENABLE_WAYLAND\n");
    
#if !defined(PROJECT_RAYLIB_SHARED)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_RAYLIB_SHARED\n");
    
#if !defined(PROJECT_RAYLIB_SHOW_FPS)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_RAYLIB_SHOW_FPS\n");
    
#if !defined(PROJECT_RAYLIB_USE_EXTERNAL_GLFW)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_RAYLIB_USE_EXTERNAL_GLFW\n");
    
#if !defined(PROJECT_RAYLIB_DISABLE_MODULE_AUDIO)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_RAYLIB_DISABLE_MODULE_AUDIO\n");
    
#if !defined(PROJECT_RAYLIB_DISABLE_MODULE_MODELS)
    FBS_APPEND_STR_LIT(buffer, "//");
#endif
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_RAYLIB_DISABLE_MODULE_MODELS\n");
    
    FBS_APPEND_STR_LIT(buffer, "#endif\n");
    FBS_APPEND_STR_LIT(buffer, "\n\n");
    
    return FBS_TRUE;
}

static fbs_bool
create_config_file(const char *config_path, FBS_String *buffer) {
    if(!config_path) { FBS_LOG(ERROR, "No config path provided!\n"); }
    
    fbs_error config_exists = fbs_file_exists(config_path);
    if(config_exists < 0) { return FBS_FALSE; }
    
    FBS_LOG(INFO, ">> Generating config buffer at: %s\n", config_path);
    
    append_title_comment(buffer, FBS_String_lit("BEGIN INCLUDE GUARD"));
    FBS_APPEND_STR_LIT(buffer, "#if !defined(PROJECT_CONFIG_H)\n");
    FBS_APPEND_STR_LIT(buffer, "#  define PROJECT_CONFIG_H\n");
    FBS_APPEND_STR_LIT(buffer, "\n\n");
    
    if(!build_config_from_defines(buffer, (fbs_bool)config_exists)) { return FBS_FALSE; }
    
    fbs_append_default_platform_and_compiler_target_config(buffer);
    append_title_comment(buffer, FBS_String_lit("END INCLUDE GUARD"));
    FBS_APPEND_STR_LIT(buffer, "#endif\n");
    
    if(!fbs_write_entire_file(config_path, (unsigned char *)buffer->data, buffer->count)) { return FBS_FALSE; }
    return FBS_TRUE;
}
