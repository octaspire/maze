#ifndef OCTASPIRE_MAZE_STATE_H
#define OCTASPIRE_MAZE_STATE_H

#include <stdbool.h>
#include <stddef.h>
#include <SDL2/SDL.h>
#include <octaspire/core/octaspire_memory.h>
#include <octaspire/core/octaspire_stdio.h>
#include "octaspire/maze/octaspire_sdl2_texture.h"
#include "octaspire/maze/octaspire_maze_input.h"

#ifdef __cplusplus
extern "C" {
#endif

struct octaspire_maze_game_t;

typedef struct octaspire_maze_state_t octaspire_maze_state_t;

octaspire_maze_state_t *octaspire_maze_state_new(
    struct octaspire_maze_game_t *parent,
    char const * const scriptBuffer,
    size_t const scriptBufferLengthInOctets,
    octaspire_memory_allocator_t * const allocator,
    octaspire_stdio_t * const stdio);

void octaspire_maze_state_release(octaspire_maze_state_t *self);

void octaspire_maze_state_update(
    octaspire_maze_state_t * const self,
    double const dt,
    octaspire_maze_input_t const input,
    int const winW,
    int const winH);

void octaspire_maze_state_render(
    octaspire_maze_state_t const * const self,
    SDL_Renderer * const renderer,
    octaspire_sdl2_texture_t const * const texture,
    int const origoX,
    int const origoY);

struct octaspire_maze_game_t *octaspire_maze_state_get_parent(
    octaspire_maze_state_t * const self);

bool octaspire_maze_state_is_done(
    octaspire_maze_state_t const * const self);

bool octaspire_maze_state_add_named_animation_of_type_to_position(
    octaspire_maze_state_t * const self,
    char const * const name,
    char const * const type,
    int const x,
    int const y,
    int const z);

bool octaspire_maze_state_remove_all_animations(
    octaspire_maze_state_t * const self);

bool octaspire_maze_state_set_animation_position(
    octaspire_maze_state_t * const self,
    char const * const name,
    int const x,
    int const y,
    int const z);

bool octaspire_maze_state_remove_named_animation(
    octaspire_maze_state_t * const self,
    char const * const name);

bool octaspire_maze_state_is_named_animation_visible(
    octaspire_maze_state_t const * const self,
    char const * const name);

void octaspire_maze_state_set_named_animation_visible(
    octaspire_maze_state_t const * const self,
    char const * const name,
    bool const visible);

bool octaspire_maze_state_tween_level_out(
    octaspire_maze_state_t * const self);


#ifdef __cplusplus
}
#endif

#endif

