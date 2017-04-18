#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <octaspire/dern/octaspire_dern_vm.h>
#include <octaspire/dern/octaspire_dern_config.h>
#include <octaspire/core/octaspire_memory.h>
#include <octaspire/core/octaspire_region.h>
#include <octaspire/core/octaspire_helpers.h>
#include "octaspire/maze/octaspire_sdl2_texture.h"
#include "octaspire/maze/octaspire_sdl2_animation.h"
#include "octaspire/maze/octaspire_maze_game.h"
#include "octaspire/maze/octaspire_easing.h"
#include "octaspire/maze/octaspire_maze_input.h"
#include "octaspire/maze/octaspire_maze_config.h"
#include "external/octaspire_maze_banner_color.h"
#include "external/octaspire_maze_banner_white.h"

extern char   const octaspire_maze_ini[];
extern size_t const octaspire_maze_ini_len;

extern char   const octaspire_maze_animations[];
extern size_t const octaspire_maze_animations_len;

extern char   const octaspire_maze_texture_entities[];
extern size_t const octaspire_maze_texture_entities_len;


octaspire_dern_value_t *octaspire_maze_api_animation_entity_define(
    octaspire_dern_vm_t *vm,
    octaspire_dern_value_t *arguments,
    octaspire_dern_value_t *environment)
{
    size_t const stackLength = octaspire_dern_vm_get_stack_length(vm);

    octaspire_helpers_verify(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    octaspire_helpers_verify(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs < 2)
    {
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Builtin 'animation-entity-define' expects at least two arguments. %zu arguments were given.",
            octaspire_dern_value_get_length(arguments));
    }

    octaspire_dern_vm_push_value(vm, arguments);

    // Name
    octaspire_dern_value_t * const animNameVal =
        octaspire_dern_value_as_vector_get_element_at(
            arguments,
            0);

    if (animNameVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_STRING)
    {
        octaspire_dern_vm_pop_value(vm, arguments);

        if (animNameVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
        {
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return animNameVal;
        }

        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "First argument to builtin 'animation-entity-define' must be string value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animNameVal->typeTag));
    }

    octaspire_sdl2_animation_t *animation = octaspire_sdl2_animation_new(
        octaspire_container_utf8_string_get_c_string(animNameVal->value.string),
        octaspire_dern_vm_get_allocator(vm));

    // Frame indices
    for (size_t i = 1; i < numArgs; ++i)
    {
        // Index
        octaspire_dern_value_t * const indexVal =
            octaspire_dern_value_as_vector_get_element_at(
                arguments,
                i);

        if (indexVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            size_t const index = indexVal->value.integer;
            SDL_Rect rect;
            rect.x = (index % 32) * 16;
            rect.y = (index / 32) * 16;
            rect.w = 16;
            rect.h = 16;
            if (!octaspire_sdl2_animation_push_back_frame(animation, &rect, 0.125))
            {
                abort();
            }
        }
        else
        {
            octaspire_dern_vm_pop_value(vm, arguments);

            if (indexVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
                return indexVal;
            }

            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "%zuth argument to builtin 'animation-enity-define' must be integer value. "
                "Now it has type %s.",
                i + 1,
                octaspire_dern_value_helper_get_type_as_c_string(indexVal->typeTag));
        }
    }

    octaspire_dern_vm_pop_value(vm, arguments);

    octaspire_maze_game_t *game = (octaspire_maze_game_t*)octaspire_dern_vm_get_user_data(vm);

    if (!octaspire_maze_game_add_animation(
            game,
            octaspire_sdl2_animation_get_name(animation),
            animation))
    {
        abort();
    }

    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
    return octaspire_dern_vm_get_value_true(vm);
}

#define ANSI_COLOR_RED    "\x1B[31m"
#define ANSI_COLOR_GREEN  "\x1B[32m"
#define ANSI_COLOR_YELLOW "\x1B[33m"
#define ANSI_COLOR_WHITE  "\x1B[37m"
#define ANSI_COLOR_DGRAY  "\x1B[1;30m"
#define ANSI_COLOR_RESET  "\x1B[0m"

typedef enum
{
    OCTASPIRE_MAZE_MESSAGE_INFO,
    OCTASPIRE_MAZE_MESSAGE_OUTPUT,
    OCTASPIRE_MAZE_MESSAGE_ERROR,
    OCTASPIRE_MAZE_MESSAGE_FATAL
}
octaspire_maze_message_t;

void octaspire_maze_print_message_c_str(
    char const * const message,
    octaspire_maze_message_t const messageType,
    bool const useColors)
{
    if (useColors)
    {
        switch (messageType)
        {
            case OCTASPIRE_MAZE_MESSAGE_INFO:
            {
                printf(ANSI_COLOR_DGRAY);
            }
            break;

            case OCTASPIRE_MAZE_MESSAGE_OUTPUT:
            {
                printf(ANSI_COLOR_GREEN);
            }
            break;

            case OCTASPIRE_MAZE_MESSAGE_ERROR:
            {
                printf(ANSI_COLOR_RED);
            }
            break;

            case OCTASPIRE_MAZE_MESSAGE_FATAL:
            {
                printf(ANSI_COLOR_YELLOW);
            }
            break;
        }
    }

    printf("%s", message);

    if (useColors)
    {
        printf(ANSI_COLOR_RESET);
    }

    printf("\n");
}

void octaspire_maze_print_message(
    octaspire_container_utf8_string_t const * const message,
    octaspire_maze_message_t const messageType,
    bool const useColors)
{
    octaspire_maze_print_message_c_str(
        octaspire_container_utf8_string_get_c_string(message),
        messageType,
        useColors);
}

void octaspire_maze_print_version(bool const useColors)
{
    octaspire_maze_print_message_c_str(
        OCTASPIRE_MAZE_CONFIG_VERSION_STR,
        OCTASPIRE_MAZE_MESSAGE_INFO,
        useColors);
}

void octaspire_maze_print_banner(bool const useColors)
{
    if (useColors)
    {
        for (size_t i = 0; i < octaspire_maze_banner_color_len; ++i)
        {
            putchar(octaspire_maze_banner_color[i]);
        }
    }
    else
    {
        for (size_t i = 0; i < octaspire_maze_banner_white_len; ++i)
        {
            putchar(octaspire_maze_banner_white[i]);
        }
    }

    octaspire_maze_print_message_c_str(
        "Licensed under the Apache License, Version 2.0\n"
        "Distributed on an \"AS IS\" BASIS, WITHOUT WARRANTIES\n"
        "OR CONDITIONS OF ANY KIND.\n",
        OCTASPIRE_MAZE_MESSAGE_INFO, useColors);

}

void octaspire_maze_print_usage(char const * const binaryName, bool const useColors)
{
    octaspire_maze_print_banner(useColors);
    octaspire_maze_print_version(useColors);
    printf("\nusage: %s [option] ...\n", binaryName);
    printf("\nwhere [option] is one of the values listen below\n\n");
    printf("-u  --use-region-allocator : use region allocator insteead regular malloc/free\n");
    printf("-f  --fullscreen           : start in fullscreen mode\n");
    printf("-c  --color-diagnostics    : use colors on unix like systems\n");
    printf("-v  --version              : print version information and exit\n");
    printf("-h  --help                 : print this help message and exit\n");
}

int main(int argc, char *argv[])
{
    bool useColors             = false;
    bool useRegionAllocator    = false;
    bool startInFullscreenMode = false;

    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--use-region-allocator") == 0)
            {
                useRegionAllocator = true;
            }
            else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--color-diagnostics") == 0)
            {
                useColors = true;
            }
            else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fullscreen") == 0)
            {
                startInFullscreenMode = true;
            }
            else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
            {
                octaspire_maze_print_version(useColors);
                return EXIT_SUCCESS;
            }
            else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            {
                octaspire_maze_print_usage(argv[0], useColors);
                return EXIT_SUCCESS;
            }
            else
            {
                printf("Unknown argument %s\n\n", argv[i]);
                octaspire_maze_print_usage(argv[0], useColors);
                return EXIT_FAILURE;
            }
        }
    }

    octaspire_memory_allocator_t *allocator = 0;

    if (useRegionAllocator)
    {
        octaspire_region_t *region = octaspire_region_new(
            OCTASPIRE_DERN_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

        if (!region)
        {
            octaspire_maze_print_message_c_str(
                "Allocation failure",
                OCTASPIRE_MAZE_MESSAGE_FATAL,
                useColors);

            exit(EXIT_FAILURE);
        }

        allocator = octaspire_memory_allocator_new(region);
    }
    else
    {
        allocator = octaspire_memory_allocator_new(0);
    }

    if (!allocator)
    {
        octaspire_maze_print_message_c_str(
            "Allocation failure",
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        exit(EXIT_FAILURE);
    }

    octaspire_stdio_t *stdio = octaspire_stdio_new(allocator);

    octaspire_dern_vm_t *vm = octaspire_dern_vm_new(
        allocator,
        stdio);

    octaspire_maze_game_t *game = octaspire_maze_game_new(allocator);

    octaspire_dern_vm_set_user_data(vm, game);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        octaspire_maze_print_message_c_str(
            "SDL2 init failed:",
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        octaspire_maze_print_message_c_str(
            SDL_GetError(),
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        exit(EXIT_FAILURE);
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        octaspire_maze_print_message_c_str(
            "Cannot set hint",
            OCTASPIRE_MAZE_MESSAGE_INFO,
            useColors);
    }

    SDL_Window *window = SDL_CreateWindow(
        "Octaspire Maze",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN);

    SDL_SetWindowSize(window, 800, 600);

    if (!window)
    {
        octaspire_maze_print_message_c_str(
            "SDL2 window creation failed:",
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        octaspire_maze_print_message_c_str(
            SDL_GetError(),
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        exit(EXIT_FAILURE);
    }

    if (startInFullscreenMode)
    {
        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0)
        {
            octaspire_maze_print_message_c_str(
                "Entering fullscreen failed",
                OCTASPIRE_MAZE_MESSAGE_FATAL,
                useColors);

            // TODO log error and maybe run in windowed mode?
            exit(EXIT_FAILURE);
        }
    }

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        octaspire_maze_print_message_c_str(
            "SDL2 renderer creation failed:",
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        octaspire_maze_print_message_c_str(
            SDL_GetError(),
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        octaspire_maze_print_message_c_str(
            "SDL2 image initialization failed:",
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        octaspire_maze_print_message_c_str(
            SDL_GetError(),
            OCTASPIRE_MAZE_MESSAGE_FATAL,
            useColors);

        exit(EXIT_FAILURE);
    }

    octaspire_sdl2_texture_t *texture = octaspire_sdl2_texture_new_from_buffer(
        octaspire_maze_texture_entities,
        octaspire_maze_texture_entities_len,
        "test-texture",
        renderer,
        allocator);

    if (!octaspire_dern_vm_create_and_register_new_builtin(
        vm,
        "animation-entity-define",
        octaspire_maze_api_animation_entity_define,
        5,
        "Create new kind of animation from texture atlas with fixed sprite sizes",
        octaspire_dern_vm_get_global_environment(vm)->value.environment))
    {
        abort();
    }

    octaspire_dern_value_t *resultVal =
        octaspire_dern_vm_read_from_buffer_and_eval_in_global_environment(
            vm,
            octaspire_maze_animations,
            octaspire_maze_animations_len);

    if (resultVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
    {
        octaspire_dern_value_print(resultVal, octaspire_dern_vm_get_allocator(vm));
        abort();
    }

    bool running = true;
    SDL_Event e;

    octaspire_maze_game_push_back_state(
        game,
        octaspire_maze_state_new(game, octaspire_maze_ini, octaspire_maze_ini_len, allocator, stdio));

    Uint64 timeNow   = SDL_GetPerformanceCounter();
    Uint64 timeLast  = 0;
    double deltaTime = 0;

    double origoX = 0;
    double origoY = 0;

    while (running)
    {
        timeLast = timeNow;
        timeNow = SDL_GetPerformanceCounter();

        deltaTime = (((timeNow - timeLast) * 1000 / (double)SDL_GetPerformanceFrequency())) * 0.001;

        octaspire_maze_input_t input = OCTASPIRE_MAZE_INPUT_NONE;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_r)
                {
                    input = OCTASPIRE_MAZE_INPUT_RESTART;
                }
                else if (e.key.keysym.sym == SDLK_q)
                {
                    running = false;
                }
                else if (e.key.keysym.sym == SDLK_a)
                {
                    input = OCTASPIRE_MAZE_INPUT_ACTION_1;
                }
                else if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_k)
                {
                    input = OCTASPIRE_MAZE_INPUT_UP;
                }
                else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_j)
                {
                    input = OCTASPIRE_MAZE_INPUT_DOWN;
                }
                else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_h)
                {
                    input = OCTASPIRE_MAZE_INPUT_LEFT;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_l)
                {
                    input = OCTASPIRE_MAZE_INPUT_RIGHT;
                }
                else if (e.key.keysym.sym == SDLK_f)
                {
                    if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN)
                    {
                        if (SDL_SetWindowFullscreen(window, 0) < 0)
                        {
                            // TODO log error and maybe run in windowed mode?
                            abort();
                        }

                        SDL_ShowCursor(true);
                    }
                    else
                    {
                        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0)
                        {
                            // TODO log error and maybe run in windowed mode?
                            abort();
                        }

                        SDL_ShowCursor(false);
                    }

                }
            }
        }

        //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        int winW = 0;
        int winH = 0;

        SDL_GetWindowSize(window, &winW, &winH);

        origoX = winW * 0.5;
        origoY = winH * 0.5;

        octaspire_maze_game_update(game, deltaTime, input, winW, winH);
        octaspire_maze_game_render(game, renderer, texture, origoX, origoY);
        SDL_RenderPresent(renderer);
    }

    octaspire_sdl2_texture_release(texture);
    texture = 0;

    SDL_DestroyRenderer(renderer);
    renderer = 0;

    SDL_DestroyWindow(window);
    window = 0;

    IMG_Quit();
    SDL_Quit();

    // TODO XXX release (these) all in early exits from main
    octaspire_dern_vm_release(vm);
    vm = 0;

    octaspire_stdio_release(stdio);
    stdio = 0;

    octaspire_maze_game_release(game);
    game = 0;

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    return 0;
}

