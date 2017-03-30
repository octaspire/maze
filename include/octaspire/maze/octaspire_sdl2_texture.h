#ifndef OCTASPIRE_SDL2_TEXTURE_H
#define OCTASPIRE_SDL2_TEXTURE_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <octaspire/core/octaspire_memory.h>
#include <octaspire/core/octaspire_stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_sdl2_texture_t octaspire_sdl2_texture_t;

octaspire_sdl2_texture_t *octaspire_sdl2_texture_new_from_path(
    char const * const path,
    SDL_Renderer *renderer,
    octaspire_stdio_t *stdio,
    octaspire_memory_allocator_t *allocator);

octaspire_sdl2_texture_t *octaspire_sdl2_texture_new_from_buffer(
    char const * const buffer,
    size_t const bufferLengthInOctets,
    char const * const name,
    SDL_Renderer *renderer,
    octaspire_memory_allocator_t *allocator);

void octaspire_sdl2_texture_release(octaspire_sdl2_texture_t *self);

void octaspire_sdl2_texture_render_at_position_clip(
    octaspire_sdl2_texture_t const * const self,
    SDL_Renderer *renderer,
    int const origoX,
    int const origoY,
    int const x,
    int const y,
    SDL_Rect const * const src);

size_t octaspire_sdl2_texture_get_width(
    octaspire_sdl2_texture_t const * const self);

size_t octaspire_sdl2_texture_get_height(
    octaspire_sdl2_texture_t const * const self);

void octaspire_sdl2_texture_print(
    octaspire_sdl2_texture_t const * const self);

#ifdef __cplusplus
}
#endif

#endif

