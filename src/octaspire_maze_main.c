#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <octaspire/dern/octaspire_dern_vm.h>
//#include <octaspire/dern/octaspire_dern_config.h>
#include <octaspire/core/octaspire_memory.h>
#include "octaspire/maze/octaspire_sdl2_texture.h"
#include "octaspire/maze/octaspire_sdl2_animation.h"
#include "octaspire/maze/octaspire_maze_game.h"
#include "octaspire/maze/octaspire_easing.h"
#include "octaspire/maze/octaspire_maze_input.h"

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

    assert(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    assert(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs < 2)
    {
        assert(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Special 'animation-entity-define' expects at least two arguments. %zu arguments were given.",
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
            assert(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return animNameVal;
        }

        assert(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "First argument to special 'animation-entity-define' must be string value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animNameVal->typeTag));
    }

    printf("define animation \"%s\"\n", octaspire_container_utf8_string_get_c_string(animNameVal->value.string));

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
                assert(stackLength == octaspire_dern_vm_get_stack_length(vm));
                return indexVal;
            }

            assert(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "%zuth argument to special 'animation-enity-define' must be integer value. "
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

    assert(stackLength == octaspire_dern_vm_get_stack_length(vm));
    octaspire_sdl2_animation_print(animation);
    return octaspire_dern_vm_get_value_true(vm);
}


int main(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);
    //octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new_create_region(
        //OCTASPIRE_DERN_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);
        //1024*1024);

    if (!allocator)
    {
        printf("Cannot create allocator\n");
        abort();
    }

    octaspire_stdio_t *stdio = octaspire_stdio_new(allocator);

    octaspire_dern_vm_t *vm = octaspire_dern_vm_new(
        allocator,
        stdio);

    octaspire_maze_game_t *game = octaspire_maze_game_new(allocator);

    octaspire_dern_vm_set_user_data(vm, game);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL2 init failed: \"%s\"\n", SDL_GetError());
        abort();
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Cannot set hint\n");
        abort();
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
        printf("SDL2 window creation failed: \"%s\"\n", SDL_GetError());
        abort();
    }

    /*
    if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0)
    {
        // TODO log error and maybe run in windowed mode?
        abort();
    }
    */

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        printf("SDL2 renderer creation failed: \"%s\"\n", SDL_GetError());
        abort();
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("SDL2 image initialization failed: \"%s\"\n", SDL_GetError());
        abort();
    }

    octaspire_sdl2_texture_t *texture = octaspire_sdl2_texture_new_from_buffer(
        octaspire_maze_texture_entities,
        octaspire_maze_texture_entities_len,
        "test-texture",
        renderer,
        allocator);

    octaspire_sdl2_texture_print(texture);

    // TODO XXX make this builtin, there is no need for it to be special anymore!
    if (!octaspire_dern_vm_create_and_register_new_special(
        vm,
        "animation-entity-define",
        octaspire_maze_api_animation_entity_define,
        5,
        "Create new kind of animation from texture atlas with fixed sprite sizes",
        octaspire_dern_vm_get_global_environment(vm)->value.environment))
    {
        abort();
    }



    octaspire_dern_vm_read_from_buffer_and_eval_in_global_environment(
        vm,
        octaspire_maze_animations,
        octaspire_maze_animations_len);
    /*
    SDL_Rect rect;

    octaspire_sdl2_animation_t *animation = octaspire_sdl2_animation_new("unknown", allocator);

    for (size_t y = 0; y < 9; ++y)
    {
        for (size_t x = 0; x < 8; ++x)
        {
            rect.x = x * 64; rect.y = y * 64; rect.w = 64; rect.h = 64;
            octaspire_sdl2_animation_push_back_frame(animation, &rect, 0.25);
        }
    }
    */


    bool running = true;
    SDL_Event e;
#if 0
    //octaspire_sdl2_animation_t *animation = octaspire_maze_game_get_animation_copy(game, "stand");

    //char *initScriptBuffer = "(println [hi])";
    char *initScriptBuffer =
        "(define entity-new-player [entity-new-player] '(x [x-coordinate] y [y-coordinate]) (fn (x y)\n"
        "     (animation-entity-new (string-format [player-{}-{}] x y) [run] '(x y 0))\n"
        "))\n"
        "(entity-new-player 100 100)\n"
        "(entity-new-player 100 200)\n"
        "(entity-new-player 200 100)\n"
        "(define state-update [state-update] '(dt [delta time]) (fn (dt) true))";

#if 0
        //"(for i from 0 to 10 (println (to-string i)))\n"
        "(for i from 0 to 100 (animation-entity-new (to-string i) [run] '((* i 10) (* 40) 3)))\n"
        //"(animation-entity-new [animname] [run] '(100 40 3))\n"
        //"(animation-entity-new [animname2] [run] '(100 140 3))\n"
        //"(for i from 0 to 10 (println [&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&]))\n"
        "(define state-update [state-update] '(dt [delta time]) (fn (dt) true))";
#endif

    size_t const initScriptBufferLength = strlen(initScriptBuffer);
#endif

    //assert(animation);
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
        //octaspire_sdl2_animation_update(animation, deltaTime);
        //octaspire_sdl2_animation_render_at_position(animation, renderer, texture, origoX, origoY, 0, 0);
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

