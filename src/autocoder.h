/*
 libdeep - a library for deep learning
 Copyright (C) 2013-2015  Bob Mottram <bob@robotics.uk.to>

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. Neither the name of the University nor the names of its contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.
 .
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE HOLDERS OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DEEPLEARN_AUTOCODER_H
#define DEEPLEARN_AUTOCODER_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "globals.h"
#include "deeplearn_random.h"
#include "backprop_neuron.h"

struct autocode {
    int NoOfInputs,NoOfHiddens;
    float DropoutPercent;
    float * inputs;
    float * outputs;
    float * weights;
    float * lastWeightChange;
    float * hiddens;
    float * bias;
    float * bperr;
    float lastBiasChange;
    float BPerror;
    float learningRate;
    float noise;
    float dropoutsPercent;
    unsigned int random_seed;
    unsigned int itterations;
};
typedef struct autocode ac;

int autocoder_init(ac * autocoder,
                   int no_of_inputs,
                   int no_of_hiddens,
                   unsigned int random_seed);
void autocoder_free(ac * autocoder);
void autocoder_feed_forward(ac * autocoder);
void autocoder_backprop(ac * autocoder);

#endif