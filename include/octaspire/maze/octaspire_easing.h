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
#ifndef OCTASPIRE_EASING_H
#define OCTASPIRE_EASING_H

#ifdef __cplusplus
extern "C" {
#endif

extern double const OCTASPIRE_EASING_DEFAULT_10_PERCENT_OVERSHOOT;
extern double const OCTASPIRE_EASING_DEFAULT_AMPLITUDE;
extern double const OCTASPIRE_EASING_DEFAULT_PERIOD;

// simple linear tweening - no easing
// t: current time, b: beginning value, c: change in value, d: duration
double octaspire_easing_linear(double const t, double const b, double const c, double const d);


///////////// QUADRATIC EASING: t^2 ///////////////////
// quadratic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be in frames or seconds/milliseconds
double octaspire_easing_in_quad(double t, double const b, double const c, double const d);
// quadratic easing out - decelerating to zero velocity
double octaspire_easing_out_quad(double t, double const b, double const c, double const d);
// quadratic easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_quad(double t, double const b, double const c, double const d);


///////////// CUBIC EASING: t^3 ///////////////////////
// cubic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds
double octaspire_easing_in_cubic(double t, double const b, double const c, double const d);
// cubic easing out - decelerating to zero velocity
double octaspire_easing_out_cubic(double t, double const b, double const c, double const d);
// cubic easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_cubic(double t, double const b, double const c, double const d);


///////////// QUARTIC EASING: t^4 /////////////////////
// quartic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds
double octaspire_easing_in_quart(double t, double const b, double const c, double const d);
// quartic easing out - decelerating to zero velocity
double octaspire_easing_out_quart(double t, double const b, double const c, double const d);
// quartic easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_quart(double t, double const b, double const c, double const d);


///////////// QUINTIC EASING: t^5  ////////////////////
// quintic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds
double octaspire_easing_in_quint (double t, double const b, double const c, double const d);
// quintic easing out - decelerating to zero velocity
double octaspire_easing_out_quint(double t, double const b, double const c, double const d);
// quintic easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_quint(double t, double const b, double const c, double const d);


///////////// SINUSOIDAL EASING: sin(t) ///////////////
// sinusoidal easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
double octaspire_easing_in_sine(double const t, double const b, double const c, double const d);
// sinusoidal easing out - decelerating to zero velocity
double octaspire_easing_out_sine(double const t, double const b, double const c, double const d);
// sinusoidal easing in/out - accelerating until halfway, then decelerating
double octaspire_easing_in_out_sine(double const t, double const b, double const c, double const d);


///////////// EXPONENTIAL EASING: 2^t /////////////////
// exponential easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
double octaspire_easing_in_expo(double const t, double const b, double const c, double const d);
// exponential easing out - decelerating to zero velocity
double octaspire_easing_out_expo(double const t, double const b, double const c, double const d);
// exponential easing in/out - accelerating until halfway, then decelerating
double octaspire_easing_in_out_expo(double t, double const b, double const c, double const d);

/////////// CIRCULAR EASING: sqrt(1-t^2) //////////////
// circular easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration
double octaspire_easing_in_circ(double t, double const b, double const c, double const d);
// circular easing out - decelerating to zero velocity
double octaspire_easing_out_circ(double t, double const b, double const c, double const d);
// circular easing in/out - acceleration until halfway, then deceleration
double octaspire_easing_in_out_circ(double t, double const b, double const c, double const d);


/////////// ELASTIC EASING: exponentially decaying sine wave  //////////////
// t: current time, b: beginning value, c: change in value, d: duration, a: amplitude (optional), p: period (optional)
// t and d can be in frames or seconds/milliseconds
double octaspire_easing_in_elastic(double t, double const b, double const c, double const d, double a, double p);
double octaspire_easing_out_elastic(double t, double const b, double const c, double const d, double a, double p);
double octaspire_easing_in_out_elastic(double t, double const b, double const c, double const d, double a, double p);


/////////// BACK EASING: overshooting cubic easing: (s+1)*t^3 - s*t^2  //////////////
// back easing in - backtracking slightly, then reversing direction and moving to target
// t: current time, b: beginning value, c: change in value, d: duration, s: overshoot amount (optional)
// t and d can be in frames or seconds/milliseconds
// s controls the amount of overshoot: higher s means greater overshoot
// s has a default value of 1.70158, which produces an overshoot of 10 percent
// s==0 produces cubic easing with no overshoot
double octaspire_easing_in_back(double t, double const b, double const c, double const d, double const s);
// back easing out - moving towards target, overshooting it slightly, then reversing and coming back to target
double octaspire_easing_out_back(double t, double const b, double const c, double const d, double const s);
// back easing in/out - backtracking slightly, then reversing direction and moving to target,
// then overshooting target, reversing, and finally coming back to target
double octaspire_easing_in_out_back(double t, double const b, double const c, double const d, double s);


/////////// BOUNCE EASING: exponentially decaying parabolic bounce  //////////////
// bounce easing in
// t: current time, b: beginning value, c: change in position, d: duration
double octaspire_easing_in_bounce(double const t, double const b, double const c, double const d);
// bounce easing out
double octaspire_easing_out_bounce(double t, double const b, double const c, double const d);
// bounce easing in/out
double octaspire_easing_in_out_bounce(double const t, double const b, double const c, double const d);

#ifdef __cplusplus
}
#endif

#endif

