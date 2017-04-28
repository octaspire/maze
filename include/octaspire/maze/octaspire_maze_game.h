#ifndef OCTASPIRE_MAZE_GAME_H
#define OCTASPIRE_MAZE_GAME_H

#include <stdbool.h>
#include <octaspire/sdl2-utils/octaspire_sdl2_animation.h>
#include "octaspire/maze/octaspire_maze_state.h"
#include "octaspire/maze/octaspire_maze_input.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_maze_game_t octaspire_maze_game_t;

octaspire_maze_game_t *octaspire_maze_game_new(
    octaspire_memory_allocator_t * const allocator);

void octaspire_maze_game_release(octaspire_maze_game_t *self);

bool octaspire_maze_game_add_animation(
    octaspire_maze_game_t * const self,
    char const * const name,
    octaspire_sdl2_animation_t const * const animation);

void octaspire_maze_game_update(
    octaspire_maze_game_t * const self,
    double const dt,
    octaspire_maze_input_t const intput,
    int const winW,
    int const winH);

void octaspire_maze_game_render(
    octaspire_maze_game_t const * const self,
    SDL_Renderer * const renderer,
    octaspire_sdl2_texture_t const * const texture,
    int const origoX,
    int const origoY);

octaspire_sdl2_animation_t *octaspire_maze_game_get_animation_copy(
    octaspire_maze_game_t const * const self,
    char const * const name);

bool octaspire_maze_game_push_back_state(
    octaspire_maze_game_t * const self,
    octaspire_maze_state_t * const state);

octaspire_maze_state_t *octaspire_maze_game_get_current_state(
    octaspire_maze_game_t * const self);

bool octaspire_maze_game_show_message(
    octaspire_maze_game_t * const self,
    size_t const index);


#ifdef __cplusplus
}
#endif

#endif

