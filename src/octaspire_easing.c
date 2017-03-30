/******************************************************************************
This work is based on Robert Penner's 'penner_easing_as1.txt'. The copyright
and license of the original work is:

Open source under the BSD License.

Copyright © 2001 Robert Penner
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  • Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  • Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  • Neither the name of the author nor the names of contributors may be used to
    endorse or promote products derived from this software without specific prior
    written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This is not the original version, but a modified one, converted from
'penner_easing_as1.txt' into C99 version by www.octaspire.com.
These modifications are released also under the BSD License:

Copyright © 2017 www.octaspire.com
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  • Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  • Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  • Neither the name of the author nor the names of contributors may be used to
    endorse or promote products derived from this software without specific prior
    written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/
#include "octaspire/maze/octaspire_easing.h"
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265359)
#endif

double const OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT = 1.70158;
double const OCTASPIRE_EASING_DEFAULT_AMPLITUDE            = 0;
double const OCTASPIRE_EASING_DEFAULT_PERIOD               = 0;

// simple linear tweening - no easing
// t: current time, b: beginning value, c: change in value, d: duration
double octaspire_easing_linear(double const t, double const b, double const c, double const d)
{
    return c*t/d + b;
}


///////////// QUADRATIC EASING: t^2 ///////////////////
// quadratic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be in frames or seconds/milliseconds
double octaspire_easing_in_quad(double t, double const b, double const c, double const d)
{
    t /= d;
    return c*t*t + b;
}

// quadratic easing out - decelerating to zero velocity
double octaspire_easing_out_quad(double t, double const b, double const c, double const d)
{
    t /= d;
    return -c*t*(t-2) + b;
}

// quadratic easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_quad(double t, double const b, double const c, double const d)
{
    t /= (d * 0.5);

    if (t < 1)
    {
        return (c / 2) * pow(t,2) + b;
    }

    return -c / 2 * ((t-1) * (t-3) - 1) + b;
}


///////////// CUBIC EASING: t^3 ///////////////////////
// cubic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds
double octaspire_easing_in_cubic(double t, double const b, double const c, double const d)
{
    t /= d;
    return c*t*t*t + b;
}

// cubic easing out - decelerating to zero velocity
double octaspire_easing_out_cubic(double t, double const b, double const c, double const d)
{
    t = (t / d) - 1;
    return c * (pow(t,3) + 1) + b;
}

// cubic easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_cubic(double t, double const b, double const c, double const d)
{
    t /= (d * 0.5);

    if (t < 1)
    {
        return c/2*t*t*t + b;
    }

    t -= 2;

    return c/2*((t*t*t) + 2) + b;
}


///////////// QUARTIC EASING: t^4 /////////////////////
// quartic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds
double octaspire_easing_in_quart(double t, double const b, double const c, double const d)
{
    t /= d;
    return c*(t*t*t*t) + b;
}

// quartic easing out - decelerating to zero velocity
double octaspire_easing_out_quart(double t, double const b, double const c, double const d)
{
    t = (t / d) - 1;
    return -c * (pow(t, 4) - 1) + b;
}

// quartic easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_quart(double t, double const b, double const c, double const d)
{
    t /= (d * 0.5);
    if (t < 1) return c/2*t*t*t*t + b;
    t -= 2;
    return -c/2 * ((t*t*t*t) - 2) + b;
}


///////////// QUINTIC EASING: t^5  ////////////////////
// quintic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds
double octaspire_easing_in_quint (double t, double const b, double const c, double const d)
{
    t /= d;
    return c * (t*t*t*t*t) + b;
}

// quintic easing out - decelerating to zero velocity
double octaspire_easing_out_quint(double t, double const b, double const c, double const d)
{
    t = (t / d) -1;
    return c*((t*t*t*t*t) + 1) + b;
}

// quintic easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_quint(double t, double const b, double const c, double const d)
{
    t /= (d * 0.5);
    if (t < 1) return c/2*t*t*t*t*t + b;
    t -= 2;
    return c/2*((t*t*t*t*t) + 2) + b;
}


///////////// SINUSOIDAL EASING: sin(t) ///////////////
// sinusoidal easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
double octaspire_easing_in_sine(double const t, double const b, double const c, double const d)
{
    return -c * cos(t/d * (M_PI/2)) + c + b;
}

// sinusoidal easing out - decelerating to zero velocity
double octaspire_easing_out_sine(double const t, double const b, double const c, double const d)
{
    return c * sin(t/d * (M_PI/2)) + b;
}

// sinusoidal easing in/out - accelerating until halfway, then decelerating
double octaspire_easing_in_out_sine(double const t, double const b, double const c, double const d)
{
    return -c/2 * (cos(M_PI*t/d) - 1) + b;
}


///////////// EXPONENTIAL EASING: 2^t /////////////////
// exponential easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
double octaspire_easing_in_expo(double const t, double const b, double const c, double const d)
{
    return (t == 0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
}

// exponential easing out - decelerating to zero velocity
double octaspire_easing_out_expo(double const t, double const b, double const c, double const d)
{
    return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
}

// exponential easing in/out - accelerating until halfway, then decelerating
double octaspire_easing_in_out_expo(double t, double const b, double const c, double const d)
{
    if (t==0) return b;
    if (t==d) return b+c;

    t /= (d * 0.5);

    if (t < 1) return c/2 * pow(2, 10 * (t - 1)) + b;

    --t;

    return c/2 * (-pow(2, -10 * t) + 2) + b;
}


/////////// CIRCULAR EASING: sqrt(1-t^2) //////////////
// circular easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
double octaspire_easing_in_circ(double t, double const b, double const c, double const d)
{
    t /= d;
    return -c * (sqrt(1 - t*t) - 1) + b;
}

// circular easing out - decelerating to zero velocity
double octaspire_easing_out_circ(double t, double const b, double const c, double const d)
{
    t = (t / d) -1;
    return c * sqrt(1 - (t*t)) + b;
}

// circular easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_circ(double t, double const b, double const c, double const d)
{
    t /= (d * 0.5);

    if (t < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
    t -= 2;
    return c/2 * (sqrt(1 - t*t) + 1) + b;
}


/////////// ELASTIC EASING: exponentially decaying sine wave  //////////////
// t: current time, b: beginning value, c: change in value, d: duration, a: amplitude (optional), p: period (optional)
// t and d can be in frames or seconds/milliseconds
double octaspire_easing_in_elastic(double t, double const b, double const c, double const d, double a, double p)
{
    double s = 0;

    if (t==0) return b;

    t /= d;

    if (t==1) return b+c;

    if (!p) p=d*0.3;


    if (a < fabs(c)) { a=c; s=p/4; }
    else s = p/(2*M_PI) * asin (c/a);

    t -= 1;
    return -(a*pow(2,10*t) * sin( (t*d-s)*(2*M_PI)/p )) + b;
}

double octaspire_easing_out_elastic(double t, double const b, double const c, double const d, double a, double p)
{
    double s = 0;

    if (t==0) return b;

    t /= d;

    if (t==1) return b+c;

    if (!p) p=d*0.3;

    if (a < fabs(c)) { a=c; s=p/4; }
    else s = p/(2*M_PI) * asin (c/a);
    return a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p ) + c + b;
}

double octaspire_easing_in_out_elastic(double t, double const b, double const c, double const d, double a, double p)
{
    double s = 0;

    if (t==0) return b;

    t /= (d * 0.5);

    if (t==2) return b+c;

    if (!p) p=d*(0.3*1.5);

    if (a < fabs(c)) { a=c; s=p/4; }
    else s = p/(2*M_PI) * asin (c/a);

    if (t < 1)
    {
        --t;
        return -.5*(a*pow(2,10*t) * sin( (t*d-s)*(2*M_PI)/p )) + b;
    }

    --t;
    return a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p )*.5 + c + b;
}


/////////// BACK EASING: overshooting cubic easing: (s+1)*t^3 - s*t^2  //////////////
// back easing in - backtracking slightly, then reversing direction and moving to target
// t: current time, b: beginning value, c: change in value, d: duration, s: overshoot amount (optional)
// t and d can be in frames or seconds/milliseconds
// s controls the amount of overshoot: higher s means greater overshoot
// s has a default value of 1.70158, which produces an overshoot of 10 percent
// s==0 produces cubic easing with no overshoot
double octaspire_easing_in_back(double t, double const b, double const c, double const d, double const s)
{
    t /= d;
    return c*t*t*((s+1)*t - s) + b;
}

// back easing out - moving towards target, overshooting it slightly, then reversing and coming back to target
double octaspire_easing_out_back(double t, double const b, double const c, double const d, double const s)
{
    t = (t / d) -1;
    return c*(t*t*((s+1)*t + s) + 1) + b;
}

// back easing in/out - backtracking slightly, then reversing direction and moving to target,
// then overshooting target, reversing, and finally coming back to target
double octaspire_easing_in_out_back(double t, double const b, double const c, double const d, double s)
{
    t /= (d * 0.5);
    s *= 1.525;

    if (t < 1)
    {
        return c/2*(t*t*((s+1)*t - s)) + b;
    }

    t -= 2;
    return c/2*(t*t*((s+1)*t + s) + 2) + b;
}


/////////// BOUNCE EASING: exponentially decaying parabolic bounce  //////////////
// bounce easing in
// t: current time, b: beginning value, c: change in position, d: duration
double octaspire_easing_in_bounce(double const t, double const b, double const c, double const d)
{
    return c - octaspire_easing_out_bounce (d-t, 0, c, d) + b;
}

// bounce easing out
double octaspire_easing_out_bounce(double t, double const b, double const c, double const d)
{
    t /= d;

    if (t < (1/2.75))
    {
        return c*(7.5625*t*t) + b;
    }
    else if (t < (2/2.75))
    {
        t-=(1.5/2.75);
        return c*(7.5625*t*t + 0.75) + b;
    }
    else if (t < (2.5/2.75))
    {
        t-=(2.25/2.75);
        return c*(7.5625*t*t + 0.9375) + b;
    }
    else
    {
        t-=(2.625/2.75);
        return c*(7.5625*t*t + 0.984375) + b;
    }
}

// bounce easing in/out
double octaspire_easing_in_out_bounce(double const t, double const b, double const c, double const d)
{
    if (t < d/2) return octaspire_easing_in_bounce (t*2, 0, c, d) * .5 + b;
    return octaspire_easing_out_bounce (t*2-d, 0, c, d) * .5 + c*.5 + b;
}

