#include "octaspire/maze/octaspire_sdl2_animation.h"
#include <octaspire/core/octaspire_container_vector.h>
#include <octaspire/core/octaspire_container_utf8_string.h>

typedef struct octaspire_sdl2_animation_frame_t
{
    octaspire_memory_allocator_t *allocator;
    SDL_Rect                     *rect;
    double                        durationInSeconds;
    double                        uptimeInSeconds;
}
octaspire_sdl2_animation_frame_t;

void octaspire_sdl2_animation_frame_release(octaspire_sdl2_animation_frame_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_memory_allocator_free(self->allocator, self->rect);
    octaspire_memory_allocator_free(self->allocator, self);
}

octaspire_sdl2_animation_frame_t *octaspire_sdl2_animation_frame_new(
    SDL_Rect const * const rect,
    double const durationInSeconds,
    octaspire_memory_allocator_t * const allocator)
{
    octaspire_sdl2_animation_frame_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_sdl2_animation_frame_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;

    self->rect      = octaspire_memory_allocator_malloc(allocator, sizeof(SDL_Rect));

    if (!self->rect)
    {
        octaspire_sdl2_animation_frame_release(self);
        self = 0;
        return self;
    }

    self->rect->x = rect->x;
    self->rect->y = rect->y;
    self->rect->w = rect->w;
    self->rect->h = rect->h;

    self->durationInSeconds = durationInSeconds;
    self->uptimeInSeconds   = 0;

    return self;
}

octaspire_sdl2_animation_frame_t *octaspire_sdl2_animation_frame_new_copy(
    octaspire_sdl2_animation_frame_t const * const other,
    octaspire_memory_allocator_t * const allocator)
{
    octaspire_sdl2_animation_frame_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_sdl2_animation_frame_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;

    self->rect      = octaspire_memory_allocator_malloc(allocator, sizeof(SDL_Rect));

    if (!self->rect)
    {
        octaspire_sdl2_animation_frame_release(self);
        self = 0;
        return self;
    }

    self->rect->x = other->rect->x;
    self->rect->y = other->rect->y;
    self->rect->w = other->rect->w;
    self->rect->h = other->rect->h;

    self->durationInSeconds = other->durationInSeconds;
    self->uptimeInSeconds   = other->uptimeInSeconds;

    return self;
}



struct octaspire_sdl2_animation_t
{
    octaspire_memory_allocator_t      *allocator;
    octaspire_container_utf8_string_t *name;
    octaspire_container_vector_t      *frames;
    size_t                             frameIndex;
    int                                x;
    int                                y;
    int                                z;
    bool                               visible;
};

octaspire_sdl2_animation_t *octaspire_sdl2_animation_new(
    char const * const name,
    octaspire_memory_allocator_t * const allocator)
{
    octaspire_sdl2_animation_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_sdl2_animation_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;

    self->name      = octaspire_container_utf8_string_new(name, allocator);

    if (!self->name)
    {
        octaspire_sdl2_animation_release(self);
        self = 0;
        return self;
    }

    self->frames      = octaspire_container_vector_new(
        sizeof(octaspire_sdl2_animation_frame_t*),
        true,
        (octaspire_container_vector_element_callback_t)octaspire_sdl2_animation_frame_release,
        allocator);

    if (!self->frames)
    {
        octaspire_sdl2_animation_release(self);
        self = 0;
        return self;
    }

    self->frameIndex = 0;

    self->x = 0;
    self->y = 0;
    self->z = 0;

    self->visible = true;

    return self;
}

octaspire_sdl2_animation_t *octaspire_sdl2_animation_new_copy(
    octaspire_sdl2_animation_t const * const other,
    octaspire_memory_allocator_t * const allocator)
{
    octaspire_sdl2_animation_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_sdl2_animation_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;

    self->name      = octaspire_container_utf8_string_new_copy(other->name, allocator);

    if (!self->name)
    {
        octaspire_sdl2_animation_release(self);
        self = 0;
        return self;
    }

    self->frames      = octaspire_container_vector_new(
        sizeof(octaspire_sdl2_animation_frame_t*),
        true,
        (octaspire_container_vector_element_callback_t)octaspire_sdl2_animation_frame_release,
        allocator);

    if (!self->frames)
    {
        octaspire_sdl2_animation_release(self);
        self = 0;
        return self;
    }

    for (size_t i = 0; i < octaspire_container_vector_get_length(other->frames); ++i)
    {
        octaspire_sdl2_animation_frame_t * const frame = octaspire_sdl2_animation_frame_new_copy(
            octaspire_container_vector_get_element_at(other->frames, i),
            allocator);
        octaspire_container_vector_push_back_element(self->frames, &frame);
    }

    self->frameIndex = other->frameIndex;

    return self;
}

void octaspire_sdl2_animation_release(octaspire_sdl2_animation_t *self)
{
    if (!self)
    {
        return;;
    }

    octaspire_container_utf8_string_release(self->name);
    self->name = 0;

    octaspire_container_vector_release(self->frames);
    self->frames = 0;

    octaspire_memory_allocator_free(self->allocator, self);
}

bool octaspire_sdl2_animation_push_back_frame(
    octaspire_sdl2_animation_t * const self,
    SDL_Rect const * const rect,
    double const durationInSeconds)
{
    octaspire_sdl2_animation_frame_t *frame =
        octaspire_sdl2_animation_frame_new(
            rect,
            durationInSeconds,
            self->allocator);

    if (!frame)
    {
        return false;
    }

    return octaspire_container_vector_push_back_element(self->frames, &frame);
}

void octaspire_sdl2_animation_update(
    octaspire_sdl2_animation_t * const self,
    double const dt)
{
    octaspire_sdl2_animation_frame_t * const frame =
        octaspire_container_vector_get_element_at(self->frames, self->frameIndex);

    if (!frame)
    {
        return;
    }

    frame->uptimeInSeconds += dt;

    if (frame->uptimeInSeconds >= frame->durationInSeconds)
    {
        frame->uptimeInSeconds = 0;
        ++(self->frameIndex);

        if (self->frameIndex >= octaspire_container_vector_get_length(self->frames))
        {
            self->frameIndex = 0;
        }
    }
}

void octaspire_sdl2_animation_render(
    octaspire_sdl2_animation_t const * const self,
    SDL_Renderer * const renderer,
    octaspire_sdl2_texture_t const * const texture,
    int const origoX,
    int const origoY)
{
    octaspire_sdl2_animation_frame_t const * const frame =
        octaspire_container_vector_get_element_at(self->frames, self->frameIndex);

    if (!frame)
    {
        return;
    }

    octaspire_sdl2_texture_render_at_position_clip(
        texture,
        renderer,
        origoX,
        origoY,
        self->x,
        self->y,
        frame->rect);
}

void octaspire_sdl2_animation_print(
    octaspire_sdl2_animation_t const * const self)
{
    printf(
        "animation (%i, %i, %i) \"%s\" at frame %zu of %zu.\n",
        self->x,
        self->y,
        self->z,
        octaspire_container_utf8_string_get_c_string(self->name),
        self->frameIndex,
        octaspire_container_vector_get_length(self->frames));

    for (size_t i = 0; i < octaspire_container_vector_get_length(self->frames); ++i)
    {
        octaspire_sdl2_animation_frame_t *frame = octaspire_container_vector_get_element_at(
            self->frames,
            i);

        printf(
            "%zuth frame: duration=%g  uptime=%g rect=(%i, %i, %i, %i)\n",
            i,
            frame->durationInSeconds,
            frame->uptimeInSeconds,
            frame->rect->x,
            frame->rect->y,
            frame->rect->w,
            frame->rect->h);
    }

    printf("\n");
}

char const * octaspire_sdl2_animation_get_name(
    octaspire_sdl2_animation_t const * const self)
{
    return octaspire_container_utf8_string_get_c_string(self->name);
}

void octaspire_sdl2_animation_set_position(
    octaspire_sdl2_animation_t * const self,
    int const x,
    int const y,
    int const z)
{
    self->x = x;
    self->y = y;
    self->z = z;
}

int octaspire_sdl2_animation_get_z(
    octaspire_sdl2_animation_t const * const self)
{
    return self->z;
}

void octaspire_sdl2_animation_set_visible(
    octaspire_sdl2_animation_t * const self,
    bool const visible)
{
    self->visible = visible;
}

bool octaspire_sdl2_animation_is_visible(
    octaspire_sdl2_animation_t const * const self)
{
    return self->visible;
}

