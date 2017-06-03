#include <assert.h>
#include <octaspire/easing/octaspire_easing.h>
#include <octaspire/core/octaspire_container_hash_map.h>
#include <octaspire/core/octaspire_helpers.h>
#include <octaspire/dern/octaspire_dern_vm.h>
#include "octaspire/maze/octaspire_maze_state.h"
#include "octaspire/maze/octaspire_maze_game.h"
#include "octaspire/maze/octaspire_maze_input.h"

typedef enum octaspire_maze_state_tween_direction_t
{
    OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_OUT,
    OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_IN,
    OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_NONE
}
octaspire_maze_state_tween_direction_t;

struct octaspire_maze_state_t
{
    octaspire_memory_allocator_t           *allocator;
    octaspire_maze_game_t                  *parent;
    octaspire_dern_vm_t                    *vm;
    bool                                    done;
    octaspire_container_hash_map_t         *animations;
    octaspire_maze_state_tween_direction_t  tweenTo;
    int                                     origoX;
    int                                     winW;
    int                                     shakeX;
    int                                     shakeCounter;
    double                                  tweenUptime;
};

octaspire_dern_value_t *octaspire_maze_api_shake(
    octaspire_dern_vm_t *vm,
    octaspire_dern_value_t *arguments,
    octaspire_dern_value_t *environment)
{
    //octaspire_dern_vm_gc(vm);

    size_t const stackLength = octaspire_dern_vm_get_stack_length(vm);

    octaspire_helpers_verify(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    octaspire_helpers_verify(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs != 0)
    {
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Builtin 'shake' expects no arguments. %zu arguments were given.",
            octaspire_dern_value_get_length(arguments));
    }

    octaspire_maze_state_t *state = (octaspire_maze_state_t*)octaspire_dern_vm_get_user_data(vm);

    state->shakeCounter = 16;

    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
    return octaspire_dern_vm_get_value_true(vm);
}


octaspire_dern_value_t *octaspire_maze_api_animation_entity_new(
    octaspire_dern_vm_t *vm,
    octaspire_dern_value_t *arguments,
    octaspire_dern_value_t *environment)
{
    size_t const stackLength = octaspire_dern_vm_get_stack_length(vm);

    octaspire_helpers_verify(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    octaspire_helpers_verify(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs != 3)
    {
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Builtin 'animation-entity-new' expects exactly three arguments. %zu arguments were given.",
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
            "First argument to builtin 'animation-entity-new' must be string value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animNameVal->typeTag));
    }



    // Type
    octaspire_dern_value_t * const animTypeVal =
        octaspire_dern_value_as_vector_get_element_at(
            arguments,
            1);

    if (animTypeVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_STRING)
    {
        octaspire_dern_vm_pop_value(vm, arguments);

        if (animTypeVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
        {
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return animTypeVal;
        }

        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Second argument to builtin 'animation-entity-new' must be string value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animTypeVal->typeTag));
    }



    // Position
    octaspire_dern_value_t * const animPosVal =
        octaspire_dern_value_as_vector_get_element_at(
            arguments,
            2);

    if (animPosVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_VECTOR)
    {
        octaspire_dern_vm_pop_value(vm, arguments);

        if (animPosVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
        {
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return animPosVal;
        }

        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Third argument to builtin 'animation-entity-new' must be vector value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animPosVal->typeTag));
    }

    if (octaspire_dern_value_as_vector_get_length(animPosVal) != 3)
    {
        octaspire_dern_vm_pop_value(vm, arguments);
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Third argument to builtin 'animation-entity-new' must be a vector with three values. "
            "Now it has %zu values.",
            octaspire_dern_value_as_vector_get_length(animPosVal));
    }

    int animPosX = 0;
    int animPosY = 0;
    int animPosZ = 0;

    octaspire_dern_value_t *animPosXVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 0);

    if (animPosXVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosXVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "X position to builtin 'animation-entity-new' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosXVal->typeTag));
        }
        else
        {
            animPosX = tmpVal->value.integer;
        }
    }
    else
    {
        animPosX = animPosXVal->value.integer;
    }

    octaspire_dern_value_t *animPosYVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 1);

    if (animPosYVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosYVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "Y position to builtin 'animation-entity-new' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosYVal->typeTag));
        }
        else
        {
            animPosY = tmpVal->value.integer;
        }
    }
    else
    {
        animPosY = animPosYVal->value.integer;
    }

    octaspire_dern_value_t *animPosZVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 2);

    if (animPosZVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosZVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "Z position to builtin 'animation-entity-new' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosZVal->typeTag));
        }
        else
        {
            animPosZ = tmpVal->value.integer;
        }
    }
    else
    {
        animPosZ = animPosZVal->value.integer;
    }

    octaspire_dern_vm_pop_value(vm, arguments);

    octaspire_maze_state_t *state = (octaspire_maze_state_t*)octaspire_dern_vm_get_user_data(vm);

    if (!octaspire_maze_state_add_named_animation_of_type_to_position(
            state,
            octaspire_container_utf8_string_get_c_string(animNameVal->value.string),
            octaspire_container_utf8_string_get_c_string(animTypeVal->value.string),
            animPosX,
            animPosY,
            animPosZ))
    {
        abort();
    }

    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
    return octaspire_dern_vm_get_value_true(vm);
}

octaspire_dern_value_t *octaspire_maze_api_animation_custom_new(
    octaspire_dern_vm_t *vm,
    octaspire_dern_value_t *arguments,
    octaspire_dern_value_t *environment)
{
    size_t const stackLength = octaspire_dern_vm_get_stack_length(vm);

    octaspire_helpers_verify(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    octaspire_helpers_verify(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs != 3)
    {
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Builtin 'animation-custom-new' expects exactly three arguments. %zu arguments were given.",
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
            "First argument to builtin 'animation-custom-new' must be string value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animNameVal->typeTag));
    }



    // Type
    octaspire_dern_value_t * const animTypeVal =
        octaspire_dern_value_as_vector_get_element_at(
            arguments,
            1);

    if (animTypeVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_STRING)
    {
        octaspire_dern_vm_pop_value(vm, arguments);

        if (animTypeVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
        {
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return animTypeVal;
        }

        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Second argument to builtin 'animation-custom-new' must be string value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animTypeVal->typeTag));
    }



    // Position
    octaspire_dern_value_t * const animPosVal =
        octaspire_dern_value_as_vector_get_element_at(
            arguments,
            2);

    if (animPosVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_VECTOR)
    {
        octaspire_dern_vm_pop_value(vm, arguments);

        if (animPosVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
        {
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return animPosVal;
        }

        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Third argument to builtin 'animation-custom-new' must be vector value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animPosVal->typeTag));
    }

    if (octaspire_dern_value_as_vector_get_length(animPosVal) != 3)
    {
        octaspire_dern_vm_pop_value(vm, arguments);
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Third argument to builtin 'animation-custom-new' must be a vector with three values. "
            "Now it has %zu values.",
            octaspire_dern_value_as_vector_get_length(animPosVal));
    }

    int animPosX = 0;
    int animPosY = 0;
    int animPosZ = 0;

    octaspire_dern_value_t *animPosXVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 0);

    if (animPosXVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosXVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "X position to builtin 'animation-custom-new' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosXVal->typeTag));
        }
        else
        {
            animPosX = tmpVal->value.integer;
        }
    }
    else
    {
        animPosX = animPosXVal->value.integer;
    }

    octaspire_dern_value_t *animPosYVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 1);

    if (animPosYVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosYVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "Y position to builtin 'animation-custom-new' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosYVal->typeTag));
        }
        else
        {
            animPosY = tmpVal->value.integer;
        }
    }
    else
    {
        animPosY = animPosYVal->value.integer;
    }

    octaspire_dern_value_t *animPosZVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 2);

    if (animPosZVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosZVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "Z position to builtin 'animation-custom-new' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosZVal->typeTag));
        }
        else
        {
            animPosZ = tmpVal->value.integer;
        }
    }
    else
    {
        animPosZ = animPosZVal->value.integer;
    }

    octaspire_dern_vm_pop_value(vm, arguments);

    octaspire_maze_state_t *state = (octaspire_maze_state_t*)octaspire_dern_vm_get_user_data(vm);

    if (!octaspire_maze_state_add_named_animation_of_type_to_position(
            state,
            octaspire_container_utf8_string_get_c_string(animNameVal->value.string),
            octaspire_container_utf8_string_get_c_string(animTypeVal->value.string),
            animPosX,
            animPosY,
            animPosZ))
    {
        abort();
    }

    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
    return octaspire_dern_vm_get_value_true(vm);
}

octaspire_dern_value_t *octaspire_maze_api_animation_entity_remove(
    octaspire_dern_vm_t *vm,
    octaspire_dern_value_t *arguments,
    octaspire_dern_value_t *environment)
{
    size_t const stackLength = octaspire_dern_vm_get_stack_length(vm);

    octaspire_helpers_verify(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    octaspire_helpers_verify(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs != 1)
    {
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Builtin 'animation-entity-remove' expects exactly one argument. %zu arguments were given.",
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
            "First argument to builtin 'animation-entity-remove' must be string value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animNameVal->typeTag));
    }

    octaspire_maze_state_t *state = (octaspire_maze_state_t*)octaspire_dern_vm_get_user_data(vm);

    if (!octaspire_maze_state_remove_named_animation(
            state,
            octaspire_container_utf8_string_get_c_string(animNameVal->value.string)))
    {
        abort();
    }

    octaspire_dern_vm_pop_value(vm, arguments);
    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
    return octaspire_dern_vm_get_value_true(vm);
}

octaspire_dern_value_t *octaspire_maze_api_tween_level_out(
    octaspire_dern_vm_t *vm,
    octaspire_dern_value_t *arguments,
    octaspire_dern_value_t *environment)
{
    //octaspire_dern_vm_gc(vm);

    size_t const stackLength = octaspire_dern_vm_get_stack_length(vm);

    octaspire_helpers_verify(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    octaspire_helpers_verify(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs != 0)
    {
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Builtin 'tween-level-out' expects exactly zero arguments. %zu arguments were given.",
            octaspire_dern_value_get_length(arguments));
    }

    octaspire_maze_state_t *state = (octaspire_maze_state_t*)octaspire_dern_vm_get_user_data(vm);

    if (!octaspire_maze_state_tween_level_out(state))
    {
        abort();
    }

    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
    return octaspire_dern_vm_get_value_true(vm);
}

octaspire_dern_value_t *octaspire_maze_api_animation_entity_remove_all(
    octaspire_dern_vm_t *vm,
    octaspire_dern_value_t *arguments,
    octaspire_dern_value_t *environment)
{
    size_t const stackLength = octaspire_dern_vm_get_stack_length(vm);

    octaspire_helpers_verify(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    octaspire_helpers_verify(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs != 0)
    {
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Builtin 'animation-entity-remove-all' expects exactly zero arguments. %zu arguments were given.",
            octaspire_dern_value_get_length(arguments));
    }

    //octaspire_dern_vm_push_value(vm, arguments);
    //octaspire_dern_vm_pop_value(vm, arguments);

    octaspire_maze_state_t *state = (octaspire_maze_state_t*)octaspire_dern_vm_get_user_data(vm);

    if (!octaspire_maze_state_remove_all_animations(state))
    {
        abort();
    }

    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
    return octaspire_dern_vm_get_value_true(vm);
}

octaspire_dern_value_t *octaspire_maze_api_animation_entity_set_position(
    octaspire_dern_vm_t *vm,
    octaspire_dern_value_t *arguments,
    octaspire_dern_value_t *environment)
{
    size_t const stackLength = octaspire_dern_vm_get_stack_length(vm);

    octaspire_helpers_verify(arguments->typeTag   == OCTASPIRE_DERN_VALUE_TAG_VECTOR);
    octaspire_helpers_verify(environment->typeTag == OCTASPIRE_DERN_VALUE_TAG_ENVIRONMENT);

    size_t const numArgs = octaspire_dern_value_get_length(arguments);

    if (numArgs != 2)
    {
        octaspire_dern_value_print(arguments, octaspire_dern_vm_get_allocator(vm));
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Builtin 'animation-entity-set-position' expects exactly two arguments. %zu arguments were given.",
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
            "First argument to builtin 'animation-entity-set-position' must be string value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animNameVal->typeTag));
    }

    // Position
    octaspire_dern_value_t * const animPosVal =
        octaspire_dern_value_as_vector_get_element_at(
            arguments,
            1);

    octaspire_helpers_verify(animPosVal);

    if (animPosVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_VECTOR)
    {
        octaspire_dern_vm_pop_value(vm, arguments);

        if (animPosVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
        {
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
            return animPosVal;
        }

        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Second argument to builtin 'animation-entity-set-position' must be vector value. "
            "Now it has type %s.",
            octaspire_dern_value_helper_get_type_as_c_string(animPosVal->typeTag));
    }

    if (octaspire_dern_value_as_vector_get_length(animPosVal) != 3)
    {
        octaspire_dern_vm_pop_value(vm, arguments);
        octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
        return octaspire_dern_vm_create_new_value_error_format(
            vm,
            "Second argument to builtin 'animation-entity-set-position' must be a vector with three values. "
            "Now it has %zu values.",
            octaspire_dern_value_as_vector_get_length(animPosVal));
    }

    int animPosX = 0;
    int animPosY = 0;
    int animPosZ = 0;

    octaspire_dern_value_t *animPosXVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 0);

    if (animPosXVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosXVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "X position to builtin 'animation-entity-set-position' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosXVal->typeTag));
        }
        else
        {
            animPosX = tmpVal->value.integer;
        }
    }
    else
    {
        animPosX = animPosXVal->value.integer;
    }

    octaspire_dern_value_t *animPosYVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 1);

    if (animPosYVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosYVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "Y position to builtin 'animation-entity-set-position' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosYVal->typeTag));
        }
        else
        {
            animPosY = tmpVal->value.integer;
        }
    }
    else
    {
        animPosY = animPosYVal->value.integer;
    }




    octaspire_dern_value_t *animPosZVal =
        octaspire_dern_value_as_vector_get_element_at(animPosVal, 2);

    if (animPosZVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
    {
        octaspire_dern_value_t *tmpVal = octaspire_dern_vm_eval(vm, animPosZVal, environment);

        octaspire_helpers_verify(tmpVal);

        if (tmpVal->typeTag != OCTASPIRE_DERN_VALUE_TAG_INTEGER)
        {
            octaspire_dern_vm_pop_value(vm, arguments);
            octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));

            if (tmpVal->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
            {
                return tmpVal;
            }

            return octaspire_dern_vm_create_new_value_error_format(
                vm,
                "Z position to builtin 'animation-entity-set-position' must be or evaluate into an integer value. "
                "Now it has type %s.",
                octaspire_dern_value_helper_get_type_as_c_string(animPosZVal->typeTag));
        }
        else
        {
            animPosZ = tmpVal->value.integer;
        }
    }
    else
    {
        animPosZ = animPosZVal->value.integer;
    }

    octaspire_dern_vm_pop_value(vm, arguments);

    octaspire_maze_state_t *state = (octaspire_maze_state_t*)octaspire_dern_vm_get_user_data(vm);

    if (!octaspire_maze_state_set_animation_position(
            state,
            octaspire_container_utf8_string_get_c_string(animNameVal->value.string),
            animPosX,
            animPosY,
            animPosZ))
    {
        abort();
    }

    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(vm));
    return octaspire_dern_vm_get_value_true(vm);
}


octaspire_maze_state_t *octaspire_maze_state_new(
    struct octaspire_maze_game_t *parent,
    char const * const scriptBuffer,
    size_t const scriptBufferLengthInOctets,
    octaspire_memory_allocator_t * const allocator,
    octaspire_stdio_t * const stdio)
{
    octaspire_maze_state_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_maze_state_t));

    if (!self)
    {
        return 0;
    }

    self->done      = false;
    self->allocator = allocator;
    self->parent    = parent;

    self->vm        = octaspire_dern_vm_new(allocator, stdio);

    if (!self->vm)
    {
        octaspire_maze_state_release(self);
        self = 0;
        return 0;
    }

    octaspire_dern_vm_set_user_data(self->vm, self);

    //octaspire_dern_vm_set_prevent_gc(self->vm, true);

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
        octaspire_maze_state_release(self);
        self = 0;
        return self;
    }

    self->tweenTo = OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_NONE;
    self->origoX  = 0;
    self->winW    = 0;
    self->shakeX  = 0;
    self->shakeCounter = 0;
    self->tweenUptime = 0;

    if (!octaspire_dern_vm_create_and_register_new_builtin(
        self->vm,
        "shake",
        octaspire_maze_api_shake,
        5,
        "Shake level",
        octaspire_dern_vm_get_global_environment(self->vm)->value.environment))
    {
        abort();
    }

    if (!octaspire_dern_vm_create_and_register_new_builtin(
        self->vm,
        "animation-entity-new",
        octaspire_maze_api_animation_entity_new,
        5,
        "Add new animation to the scene",
        octaspire_dern_vm_get_global_environment(self->vm)->value.environment))
    {
        abort();
    }

    if (!octaspire_dern_vm_create_and_register_new_builtin(
        self->vm,
        "animation-custom-new",
        octaspire_maze_api_animation_custom_new,
        5,
        "Add new animation to the scene",
        octaspire_dern_vm_get_global_environment(self->vm)->value.environment))
    {
        abort();
    }

    if (!octaspire_dern_vm_create_and_register_new_builtin(
        self->vm,
        "animation-entity-remove",
        octaspire_maze_api_animation_entity_remove,
        1,
        "Remove animation from the scene",
        octaspire_dern_vm_get_global_environment(self->vm)->value.environment))
    {
        abort();
    }

    if (!octaspire_dern_vm_create_and_register_new_builtin(
        self->vm,
        "animation-entity-remove-all",
        octaspire_maze_api_animation_entity_remove_all,
        5,
        "Remove all animations from the scene",
        octaspire_dern_vm_get_global_environment(self->vm)->value.environment))
    {
        abort();
    }



    if (!octaspire_dern_vm_create_and_register_new_builtin(
        self->vm,
        "tween-level-out",
        octaspire_maze_api_tween_level_out,
        0,
        "Tween level out",
        octaspire_dern_vm_get_global_environment(self->vm)->value.environment))
    {
        abort();
    }

    if (!octaspire_dern_vm_create_and_register_new_builtin(
        self->vm,
        "animation-entity-set-position",
        octaspire_maze_api_animation_entity_set_position,
        5,
        "Set new position for an animation on the scene",
        octaspire_dern_vm_get_global_environment(self->vm)->value.environment))
    {
        abort();
    }

    octaspire_dern_value_t * const value = octaspire_dern_vm_read_from_buffer_and_eval_in_global_environment(
        self->vm,
        scriptBuffer,
        scriptBufferLengthInOctets);

    octaspire_helpers_verify(value);

    if (value->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
    {
        octaspire_dern_value_print(value, allocator);
        abort();
    }

    return self;
}

void octaspire_maze_state_release(octaspire_maze_state_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_container_hash_map_release(self->animations);
    self->animations = 0;

    octaspire_dern_vm_release(self->vm);
    self->vm = 0;

    octaspire_memory_allocator_free(self->allocator, self);
}

void octaspire_maze_state_update(
    octaspire_maze_state_t * const self,
    double const dt,
    octaspire_maze_input_t const input,
    int const winW,
    int const winH)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(winH);

    if (self->shakeCounter > 0)
    {
        if (self->shakeCounter % 2 == 0)
        {
            self->shakeX = -4;
        }
        else
        {
            self->shakeX = 4;
        }

        --(self->shakeCounter);
    }
    else
    {
        self->shakeX = 0;
    }

    self->winW = winW;

    if (self->tweenTo == OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_OUT)
    {
        if (self->tweenUptime >= 1.25)
        {
            self->tweenTo = OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_IN;
            self->tweenUptime = 0;
            self->origoX = 0;
            octaspire_dern_vm_read_from_c_string_and_eval_in_global_environment(self->vm, "(state-on-tween-out-done)");
        }
        else
        {
            self->origoX = octaspire_easing_in_back(
                self->tweenUptime,
                0,
                winW,
                1.25,
                1);

            self->tweenUptime += dt;
        }
    }
    else if (self->tweenTo == OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_IN)
    {
        if (self->tweenUptime >= 1.25)
        {
            self->tweenTo = OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_NONE;
            self->tweenUptime = 0;

            octaspire_dern_vm_read_from_c_string_and_eval_in_global_environment(self->vm, "(state-on-tween-in-done)");
        }
        else
        {
            self->origoX = octaspire_easing_out_back(
                self->tweenUptime,
                0,
                winW,
                1.25,
                1);

            self->tweenUptime += dt;
        }
    }

    size_t const stackLength = octaspire_dern_vm_get_stack_length(self->vm);

    size_t const numAnims = octaspire_container_hash_map_get_number_of_elements(self->animations);

    for (size_t i = 0; i < numAnims; ++i)
    {
        octaspire_sdl2_animation_t * const animation =
            octaspire_container_hash_map_element_get_value(
                octaspire_container_hash_map_get_at_index(self->animations, i));

        octaspire_helpers_verify(animation);

        octaspire_sdl2_animation_update(animation, dt);
    }

    octaspire_dern_value_t *updateCallVal = octaspire_dern_vm_create_new_value_vector(self->vm);

    octaspire_dern_vm_push_value(self->vm, updateCallVal);

    octaspire_dern_value_t *tmpVal = octaspire_dern_vm_create_new_value_symbol_from_c_string(self->vm, "state-update");
    octaspire_dern_value_as_vector_push_back_element(updateCallVal, &tmpVal);
    tmpVal = octaspire_dern_vm_create_new_value_real(self->vm, dt);
    octaspire_dern_value_as_vector_push_back_element(updateCallVal, &tmpVal);

    if (input == OCTASPIRE_MAZE_INPUT_NONE)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "");
    }
    else if (input == OCTASPIRE_MAZE_INPUT_UP)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "up");
    }
    else if (input == OCTASPIRE_MAZE_INPUT_DOWN)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "down");
    }
    else if (input == OCTASPIRE_MAZE_INPUT_LEFT)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "left");
    }
    else if (input == OCTASPIRE_MAZE_INPUT_RIGHT)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "right");
    }
    else if (input == OCTASPIRE_MAZE_INPUT_RESTART)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "restart");
    }
    else if (input == OCTASPIRE_MAZE_INPUT_ACTION_1)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "action 1");
    }
    else if (input == OCTASPIRE_MAZE_INPUT_PREV_LEVEL)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "prevLevel");
    }
    else if (input == OCTASPIRE_MAZE_INPUT_NEXT_LEVEL)
    {
        tmpVal = octaspire_dern_vm_create_new_value_string_from_c_string(self->vm, "nextLevel");
    }

    octaspire_dern_value_as_vector_push_back_element(updateCallVal, &tmpVal);

    /*
    char const *buf = "(println (env-global))";
    octaspire_dern_vm_read_from_buffer_and_eval_in_global_environment(self->vm, buf, strlen(buf));
    */

    //octaspire_dern_value_print(updateCallVal, octaspire_dern_vm_get_allocator(self->vm));
    octaspire_dern_value_t *callResult = octaspire_dern_vm_eval_in_global_environment(self->vm, updateCallVal);
    octaspire_helpers_verify(callResult);

    if (callResult->typeTag == OCTASPIRE_DERN_VALUE_TAG_ERROR)
    {
        printf("----------------------- ERROR -----------------------\n");
        octaspire_dern_value_print(updateCallVal, octaspire_dern_vm_get_allocator(self->vm));
        printf("-----------------------------------------------------\n");
        octaspire_dern_value_print(callResult, octaspire_dern_vm_get_allocator(self->vm));
        abort();
    }
    else if (callResult->typeTag != OCTASPIRE_DERN_VALUE_TAG_BOOLEAN)
    {
        octaspire_dern_value_print(callResult, octaspire_dern_vm_get_allocator(self->vm));
        abort();
    }

    octaspire_dern_vm_pop_value(self->vm, updateCallVal);
    octaspire_helpers_verify(stackLength == octaspire_dern_vm_get_stack_length(self->vm));
}

bool octaspire_maze_state_tween_level_out(
    octaspire_maze_state_t * const self)
{
    if (self->tweenTo == OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_NONE)
    {
        self->tweenTo = OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_OUT;
        return true;
    }

    return false;
}

void octaspire_maze_state_private_render_layer(
    octaspire_maze_state_t const * const self,
    int const layer,
    SDL_Renderer * const renderer,
    octaspire_sdl2_texture_t const * const texture,
    int const origoX,
    int const origoY)
{
    octaspire_helpers_verify(layer < 4);

    octaspire_container_hash_map_element_iterator_t iter =
        octaspire_container_hash_map_element_iterator_init(self->animations);

    while (iter.element)
    {
        //octaspire_container_hash_map_element_t *elem  = octaspire_container_hash_map_get_at_index(self->animations, i);

        //octaspire_dern_value_print(octaspire_container_hash_map_element_get_key(elem), octaspire_dern_vm_get_allocator(self->vm));
        octaspire_sdl2_animation_t const * const animation =
            octaspire_container_hash_map_element_get_value(iter.element);

        octaspire_helpers_verify(animation);

        if (octaspire_sdl2_animation_get_z(animation) == (int)layer)
        {
            int newOrigoX = origoX;

            if (self->tweenTo == OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_OUT)
            {
                newOrigoX -= self->origoX;
            }
            else if (self->tweenTo == OCTASPIRE_MAZE_STATE_TWEEN_DIRECTION_IN)
            {
                newOrigoX += (self->winW - self->origoX);
            }

            newOrigoX += self->shakeX;

            octaspire_sdl2_animation_render(animation, renderer, texture, newOrigoX, origoY);
        }

        octaspire_container_hash_map_element_iterator_next(&iter);
    }
}

void octaspire_maze_state_render(
    octaspire_maze_state_t const * const self,
    SDL_Renderer * const renderer,
    octaspire_sdl2_texture_t const * const texture,
    int const origoX,
    int const origoY)
{
    int newOrigoX = origoX;

    for (int i = -1; i < 2; ++i)
    {
        octaspire_maze_state_private_render_layer(self, i, renderer, texture, newOrigoX, origoY);
    }
}

struct octaspire_maze_game_t *octaspire_maze_state_get_parent(
    octaspire_maze_state_t * const self)
{
    return self->parent;
}

bool octaspire_maze_state_is_done(
    octaspire_maze_state_t const * const self)
{
    return self->done;
}

bool octaspire_maze_state_add_named_animation_of_type_to_position(
    octaspire_maze_state_t * const self,
    char const * const name,
    char const * const type,
    int const x,
    int const y,
    int const z)
{
    octaspire_container_utf8_string_t * key =
        octaspire_container_utf8_string_new(name, self->allocator);

    /*
    octaspire_sdl2_animation_t *animation = octaspire_sdl2_animation_new(name, self->allocator);
    octaspire_sdl2_animation_set_position(animation, x, y, z);
    */
    octaspire_sdl2_animation_t *animation =
        octaspire_maze_game_get_animation_copy(self->parent, type);

    octaspire_helpers_verify(animation);

    octaspire_sdl2_animation_set_position(animation, x, y, z);

    return octaspire_container_hash_map_put(
        self->animations,
        octaspire_container_utf8_string_get_hash(key),
        &key,
        &animation);
}

bool octaspire_maze_state_remove_all_animations(
    octaspire_maze_state_t * const self)
{
    //return octaspire_container_hash_map_clear(self->animations);
    bool const result = octaspire_container_hash_map_clear(self->animations);
    return result;
}

bool octaspire_maze_state_set_animation_position(
    octaspire_maze_state_t * const self,
    char const * const name,
    int const x,
    int const y,
    int const z)
{
    octaspire_container_utf8_string_t * key =
        octaspire_container_utf8_string_new(name, self->allocator);

    octaspire_container_hash_map_element_t * const element =
        octaspire_container_hash_map_get(
            self->animations,
            octaspire_container_utf8_string_get_hash(key),
            &key);

    if (!element)
    {
        octaspire_container_utf8_string_release(key);
        key = 0;
        octaspire_helpers_verify(false);
        return false;
    }

    octaspire_sdl2_animation_t * const animation =
        octaspire_container_hash_map_element_get_value(element);

    octaspire_helpers_verify(animation);

    octaspire_sdl2_animation_set_position(animation, x, y, z);

    octaspire_container_utf8_string_release(key);
    key = 0;

    return true;
}

bool octaspire_maze_state_remove_named_animation(
    octaspire_maze_state_t * const self,
    char const * const name)
{
    octaspire_container_utf8_string_t * key =
        octaspire_container_utf8_string_new(name, self->allocator);

    bool const result = octaspire_container_hash_map_remove(
        self->animations,
        octaspire_container_utf8_string_get_hash(key),
        &key);

    octaspire_container_utf8_string_release(key);
    key = 0;

    return result;
}

bool octaspire_maze_state_is_named_animation_visible(
    octaspire_maze_state_t const * const self,
    char const * const name);

void octaspire_maze_state_set_named_animation_visible(
    octaspire_maze_state_t const * const self,
    char const * const name,
    bool const visible);

