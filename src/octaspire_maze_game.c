#include <assert.h>
#include <stdbool.h>
#include "octaspire/maze/octaspire_maze_game.h"
#include "octaspire/maze/octaspire_maze_state.h"
#include <octaspire/core/octaspire_container_hash_map.h>
#include <octaspire/core/octaspire_container_vector.h>
#include <octaspire/core/octaspire_container_utf8_string.h>
#include <octaspire/core/octaspire_helpers.h>
#include "octaspire/maze/octaspire_maze_input.h"

struct octaspire_maze_game_t
{
    octaspire_memory_allocator_t   *allocator;
    octaspire_container_hash_map_t *animations;
    octaspire_container_vector_t   *states;
    octaspire_container_vector_t   *messageQueue;
};

octaspire_maze_game_t *octaspire_maze_game_new(
    octaspire_memory_allocator_t * const allocator)
{
    octaspire_maze_game_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_maze_game_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;

    self->animations = octaspire_container_hash_map_new(
        sizeof(octaspire_container_utf8_string_t*),
        true,
        sizeof(octaspire_sdl2_animation_t*),
        true,
        (octaspire_container_hash_map_key_compare_function_t)octaspire_container_utf8_string_is_equal,
        (octaspire_container_hash_map_key_hash_function_t)octaspire_container_utf8_string_get_hash,
        (octaspire_container_hash_map_element_callback_function_t)octaspire_container_utf8_string_release,
        (octaspire_container_hash_map_element_callback_function_t)octaspire_sdl2_animation_release,
        allocator);

    if (!self->animations)
    {
        octaspire_maze_game_release(self);
        self = 0;
        return self;
    }

    self->states = octaspire_container_vector_new(
        sizeof(octaspire_maze_state_t*),
        true,
        (octaspire_container_vector_element_callback_t)octaspire_maze_state_release,
        allocator);

    if (!self->states)
    {
        octaspire_maze_game_release(self);
        self = 0;
        return self;
    }

    self->messageQueue = octaspire_container_vector_new(
        sizeof(size_t),
        false,
        0,
        allocator);

    if (!self->messageQueue)
    {
        octaspire_maze_game_release(self);
        self = 0;
        return self;
    }

    return self;
}

void octaspire_maze_game_release(octaspire_maze_game_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_container_hash_map_release(self->animations);
    octaspire_container_vector_release(self->states);
    octaspire_container_vector_release(self->messageQueue);
    octaspire_memory_allocator_free(self->allocator, self);
}

bool octaspire_maze_game_add_animation(
    octaspire_maze_game_t * const self,
    char const * const name,
    octaspire_sdl2_animation_t const * const animation)
{
    octaspire_container_utf8_string_t *key = octaspire_container_utf8_string_new(name, self->allocator);

    return octaspire_container_hash_map_put(
        self->animations,
        octaspire_container_utf8_string_get_hash(key),
        &key,
        &animation);
}

void octaspire_maze_game_update(
    octaspire_maze_game_t * const self,
    double const dt,
    octaspire_maze_input_t const input,
    int const winW,
    int const winH)
{
    if (!octaspire_container_vector_is_empty(self->states))
    {
        octaspire_maze_state_t *state = octaspire_container_vector_peek_back_element(self->states);
        octaspire_maze_state_update(state, dt, input, winW, winH);

        if (octaspire_maze_state_is_done(state))
        {
            octaspire_container_vector_pop_back_element(self->states);
        }
    }
}

void octaspire_maze_game_render(
    octaspire_maze_game_t const * const self,
    SDL_Renderer * const renderer,
    octaspire_sdl2_texture_t const * const texture,
    octaspire_sdl2_texture_t const * const textureMessages,
    int const origoX,
    int const origoY)
{
    if (!octaspire_container_vector_is_empty(self->states))
    {
        octaspire_maze_state_t *state = octaspire_container_vector_peek_back_element(self->states);
        octaspire_maze_state_render(state, renderer, texture, origoX, origoY);
    }

    if (!octaspire_container_vector_is_empty(self->messageQueue))
    {

        size_t const messageIndex =
            *(size_t * const)octaspire_container_vector_peek_back_element_const(self->messageQueue);

        SDL_Rect rect;
        rect.x = (messageIndex % 4) * 512;
        rect.y = (messageIndex / 4) * 128;
        rect.w = 512;
        rect.h = 128;

        octaspire_sdl2_texture_render_at_position_clip(
            textureMessages,
            renderer,
            0,
            0,
            100,
            100,
            &rect);
    }
}

octaspire_sdl2_animation_t *octaspire_maze_game_get_animation_copy(
    octaspire_maze_game_t const * const self,
    char const * const name)
{
    octaspire_container_utf8_string_t * tmpStr =
        octaspire_container_utf8_string_new(name, self->allocator);

    octaspire_container_hash_map_element_t const * const element =
        octaspire_container_hash_map_get_const(
            self->animations,
            octaspire_container_utf8_string_get_hash(tmpStr),
            &tmpStr);

    octaspire_container_utf8_string_release(tmpStr);
    tmpStr = 0;

    if (!element)
    {
        return 0;
    }

    octaspire_sdl2_animation_t const * const animation =
        octaspire_container_hash_map_element_get_value(element);

    assert(animation);

    return octaspire_sdl2_animation_new_copy(animation, self->allocator);
}

bool octaspire_maze_game_push_back_state(
    octaspire_maze_game_t * const self,
    octaspire_maze_state_t * const state)
{
    return octaspire_container_vector_push_back_element(self->states, &state);
}

octaspire_maze_state_t *octaspire_maze_game_get_current_state(
    octaspire_maze_game_t * const self)
{
    return octaspire_container_vector_peek_back_element(self->states);
}

bool octaspire_maze_game_show_message(
    octaspire_maze_game_t * const self,
    size_t const index)
{
    return octaspire_container_vector_push_front_element(self->messageQueue, &index);
}

