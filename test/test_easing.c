#include "../src/octaspire_easing.c"
#include "external/greatest.h"

static double OCTASPIRE_EASING_SUITE_EPSILON = 0.0001;

TEST octaspire_easing_linear_0_0_1000_with_d_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,    octaspire_easing_linear(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(250,  octaspire_easing_linear(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,  octaspire_easing_linear(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(750,  octaspire_easing_linear(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000, octaspire_easing_linear(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_quad_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,     octaspire_easing_in_quad(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(62.5,  octaspire_easing_in_quad(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(250,   octaspire_easing_in_quad(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(562.5, octaspire_easing_in_quad(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,  octaspire_easing_in_quad(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_quad_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,     octaspire_easing_out_quad(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(437.5, octaspire_easing_out_quad(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(750,   octaspire_easing_out_quad(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(937.5, octaspire_easing_out_quad(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,  octaspire_easing_out_quad(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_quad_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,   octaspire_easing_in_out_quad(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(125, octaspire_easing_in_out_quad(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500, octaspire_easing_in_out_quad(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(875, octaspire_easing_in_out_quad(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,octaspire_easing_in_out_quad(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_cubic_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,       octaspire_easing_in_cubic(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(15.625,  octaspire_easing_in_cubic(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(125,     octaspire_easing_in_cubic(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(421.875, octaspire_easing_in_cubic(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,    octaspire_easing_in_cubic(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_cubic_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,       octaspire_easing_out_cubic(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(578.125, octaspire_easing_out_cubic(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(875,     octaspire_easing_out_cubic(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(984.375, octaspire_easing_out_cubic(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,    octaspire_easing_out_cubic(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_cubic_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,     octaspire_easing_in_out_cubic(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(62.5,  octaspire_easing_in_out_cubic(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,   octaspire_easing_in_out_cubic(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(937.5, octaspire_easing_in_out_cubic(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,  octaspire_easing_in_out_cubic(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_quart_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,         octaspire_easing_in_quart(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(3.90625,   octaspire_easing_in_quart(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(62.5,      octaspire_easing_in_quart(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(316.40625, octaspire_easing_in_quart(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,      octaspire_easing_in_quart(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_quart_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,         octaspire_easing_out_quart(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(683.59375, octaspire_easing_out_quart(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(937.5,     octaspire_easing_out_quart(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(996.09375, octaspire_easing_out_quart(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,      octaspire_easing_out_quart(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_quart_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,      octaspire_easing_in_out_quart(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(31.25,  octaspire_easing_in_out_quart(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,    octaspire_easing_in_out_quart(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(968.75, octaspire_easing_in_out_quart(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,   octaspire_easing_in_out_quart(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_quint_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,           octaspire_easing_in_quint(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(0.9765625,   octaspire_easing_in_quint(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(31.25,       octaspire_easing_in_quint(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(237.3046875, octaspire_easing_in_quint(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,        octaspire_easing_in_quint(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_quint_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,           octaspire_easing_out_quint(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(762.6953125, octaspire_easing_out_quint(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(968.75,      octaspire_easing_out_quint(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(999.0234375, octaspire_easing_out_quint(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,        octaspire_easing_out_quint(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_quint_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,       octaspire_easing_in_out_quint(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(15.625,  octaspire_easing_in_out_quint(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,     octaspire_easing_in_out_quint(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(984.375, octaspire_easing_in_out_quint(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,    octaspire_easing_in_out_quint(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_sine_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,               octaspire_easing_in_sine(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(76.120467488713, octaspire_easing_in_sine(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(292.89321881345, octaspire_easing_in_sine(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(617.31656763491, octaspire_easing_in_sine(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,            octaspire_easing_in_sine(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_sine_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,               octaspire_easing_out_sine(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(382.68343236509, octaspire_easing_out_sine(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(707.10678118655, octaspire_easing_out_sine(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(923.87953251129, octaspire_easing_out_sine(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,            octaspire_easing_out_sine(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_sine_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,               octaspire_easing_in_out_sine(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(146.44660940673, octaspire_easing_in_out_sine(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,             octaspire_easing_in_out_sine(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(853.55339059327, octaspire_easing_in_out_sine(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,            octaspire_easing_in_out_sine(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_expo_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,          octaspire_easing_in_expo(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(5.524272,   octaspire_easing_in_expo(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(31.25,      octaspire_easing_in_expo(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(176.776703, octaspire_easing_in_expo(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,        octaspire_easing_in_expo(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_expo_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,          octaspire_easing_out_expo(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(823.223328, octaspire_easing_out_expo(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(968.750000, octaspire_easing_out_expo(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(994.475708, octaspire_easing_out_expo(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,       octaspire_easing_out_expo(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_expo_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,       octaspire_easing_in_out_expo(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(15.625,  octaspire_easing_in_out_expo(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,     octaspire_easing_in_out_expo(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(984.375, octaspire_easing_in_out_expo(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,    octaspire_easing_in_out_expo(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_circ_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,               octaspire_easing_in_circ(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(31.754163448146, octaspire_easing_in_circ(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(133.97459621556, octaspire_easing_in_circ(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(338.56217223385, octaspire_easing_in_circ(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,            octaspire_easing_in_circ(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_circ_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,               octaspire_easing_out_circ(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(661.43782776615, octaspire_easing_out_circ(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(866.02540378444, octaspire_easing_out_circ(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(968.24583655185, octaspire_easing_out_circ(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,            octaspire_easing_out_circ(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_circ_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,               octaspire_easing_in_out_circ(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(66.987298107781, octaspire_easing_in_out_circ(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,             octaspire_easing_in_out_circ(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(933.01270189222, octaspire_easing_in_out_circ(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,            octaspire_easing_in_out_circ(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_elastic_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,                octaspire_easing_in_elastic(d * 0,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(-5.5242717280199, octaspire_easing_in_elastic(d * 0.25, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(-15.625,          octaspire_easing_in_elastic(d * 0.5,  0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(88.388347648318,  octaspire_easing_in_elastic(d * 0.75, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,             octaspire_easing_in_elastic(d * 1,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_elastic_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,                octaspire_easing_out_elastic(d * 0,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(911.61165235168, octaspire_easing_out_elastic(d * 0.25, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1015.625,          octaspire_easing_out_elastic(d * 0.5,  0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1005.524271728,  octaspire_easing_out_elastic(d * 0.75, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,             octaspire_easing_out_elastic(d * 1,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_elastic_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,               octaspire_easing_in_out_elastic(d * 0,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(11.969444423734, octaspire_easing_in_out_elastic(d * 0.25, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,             octaspire_easing_in_out_elastic(d * 0.5,  0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(988.03055557627, octaspire_easing_in_out_elastic(d * 0.75, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,            octaspire_easing_in_out_elastic(d * 1,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_AMPLITUDE, OCTASPIRE_EASING_DEFAULT_PERIOD), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_back_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,           octaspire_easing_in_back(d * 0,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(-64.1365625, octaspire_easing_in_back(d * 0.25, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(-87.6975,    octaspire_easing_in_back(d * 0.5,  0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(182.5903125, octaspire_easing_in_back(d * 0.75, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,        octaspire_easing_in_back(d * 1,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_back_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,           octaspire_easing_out_back(d * 0,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(817.4096875, octaspire_easing_out_back(d * 0.25, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1087.6975,    octaspire_easing_out_back(d * 0.5,  0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1064.1365625, octaspire_easing_out_back(d * 0.75, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,        octaspire_easing_out_back(d * 1,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_back_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,            octaspire_easing_in_out_back(d * 0,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(-99.68184375,  octaspire_easing_in_out_back(d * 0.25, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,    octaspire_easing_in_out_back(d * 0.5,  0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1099.68184375, octaspire_easing_in_out_back(d * 0.75, 0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,         octaspire_easing_in_out_back(d * 1,    0, 1000, d, OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_bounce_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,         octaspire_easing_in_bounce(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(27.34375,  octaspire_easing_in_bounce(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(234.375,   octaspire_easing_in_bounce(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(527.34375, octaspire_easing_in_bounce(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,      octaspire_easing_in_bounce(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_out_bounce_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,         octaspire_easing_out_bounce(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(472.65625, octaspire_easing_out_bounce(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(765.625,   octaspire_easing_out_bounce(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(972.65625, octaspire_easing_out_bounce(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,      octaspire_easing_out_bounce(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

TEST octaspire_easing_in_out_bounce_0_0_1000_from_0_1_to_10_test(void)
{
    for (double d = 0.1; d <= 10; d += 0.1)
    {
        ASSERT_IN_RANGE(0,         octaspire_easing_in_out_bounce(d * 0,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(117.1875, octaspire_easing_in_out_bounce(d * 0.25, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(500,   octaspire_easing_in_out_bounce(d * 0.5,  0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(882.8125, octaspire_easing_in_out_bounce(d * 0.75, 0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
        ASSERT_IN_RANGE(1000,      octaspire_easing_in_out_bounce(d * 1,    0, 1000, d), OCTASPIRE_EASING_SUITE_EPSILON);
    }

    PASS();
}

GREATEST_SUITE(octaspire_easing_suite)
{
    RUN_TEST(octaspire_easing_linear_0_0_1000_with_d_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_quad_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_quad_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_quad_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_cubic_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_cubic_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_cubic_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_quart_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_quart_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_quart_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_quint_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_quint_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_quint_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_sine_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_sine_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_sine_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_expo_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_expo_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_expo_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_circ_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_circ_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_circ_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_elastic_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_elastic_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_elastic_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_back_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_back_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_back_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_bounce_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_out_bounce_0_0_1000_from_0_1_to_10_test);
    RUN_TEST(octaspire_easing_in_out_bounce_0_0_1000_from_0_1_to_10_test);
}
