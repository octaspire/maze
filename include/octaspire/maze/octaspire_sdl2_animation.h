#ifndef OCTASPIRE_SDL2_ANIMATION_H
#define OCTASPIRE_SDL2_ANIMATION_H

#include <stdbool.h>
#include "octaspire/maze/octaspire_sdl2_texture.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_sdl2_animation_t octaspire_sdl2_animation_t;

octaspire_sdl2_animation_t *octaspire_sdl2_animation_new(
    char const * const name,
    octaspire_memory_allocator_t * const allocator);

octaspire_sdl2_animation_t *octaspire_sdl2_animation_new_copy(
    octaspire_sdl2_animation_t const * const other,
    octaspire_memory_allocator_t * const allocator);

void octaspire_sdl2_animation_release(octaspire_sdl2_animation_t *self);

bool octaspire_sdl2_animation_push_back_frame(
    octaspire_sdl2_animation_t * const self,
    SDL_Rect const * const rect,
    double const durationInSeconds);

void octaspire_sdl2_animation_update(
    octaspire_sdl2_animation_t * const self,
    double const dt);

void octaspire_sdl2_animation_render(
    octaspire_sdl2_animation_t const * const self,
    SDL_Renderer * const renderer,
    octaspire_sdl2_texture_t const * const texture,
    int const origoX,
    int const origoY);

void octaspire_sdl2_animation_print(
    octaspire_sdl2_animation_t const * const self);

char const * octaspire_sdl2_animation_get_name(
    octaspire_sdl2_animation_t const * const self);

void octaspire_sdl2_animation_set_position(
    octaspire_sdl2_animation_t * const self,
    int const x,
    int const y,
    int const z);

int octaspire_sdl2_animation_get_z(
    octaspire_sdl2_animation_t const * const self);

void octaspire_sdl2_animation_set_visible(
    octaspire_sdl2_animation_t * const self,
    bool const visible);

bool octaspire_sdl2_animation_is_visible(
    octaspire_sdl2_animation_t const * const self);


#ifdef __cplusplus
}
#endif

#endif

