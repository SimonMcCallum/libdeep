/*
 libdeep - a library for deep learning
 Copyright (C) 2015  Bob Mottram <bob@robotics.uk.to>

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

#include "deeplearn_pooling.h"

/**
* @brief Pools the first layer into the second
* @param depth Depth of the two layers
* @param layer0_across Number of units across the first layer
* @param layer0_down Number of units down the first layer
* @param layer0 Array containing the first layer values
* @param layer1_across Number of units across the second layer
* @param layer1_down Number of units down the second layer
* @param layer1 Array containing the second layer values
* @returns zero on success
*/
int pooling_from_floats_to_floats(int depth,
                                  int layer0_across,
                                  int layer0_down,
                                  float layer0[],
                                  int layer1_across,
                                  int layer1_down,
                                  float layer1[])
{
    /* second layer must be smaller than the first */
    if (layer1_across*layer1_down >
        layer0_across*layer0_down) {
        return -1;
    }

    /* if layers are the same size then copy the array */
    if (layer1_across*layer1_down ==
        layer0_across*layer0_down) {
        memcpy((void*)layer1,(void*)layer0,
               layer1_across*layer1_down*depth*sizeof(float));
        return 0;
    }

	/*#pragma omp parallel for*/
    for (int y = 0; y < layer1_down; y++) {
        int ty = y * layer0_down / layer1_down;
        int by = (y+1) * layer0_down / layer1_down;
        for (int x = 0; x < layer1_across; x++) {
            int tx = x * layer0_across / layer1_across;
            int bx = (x+1) * layer0_across / layer1_across;
            /* for every depth */
            for (int d = 0; d < depth; d++) {
                /* average the inputs in the first layer */
                float tot = 0;
                for (int y_layer0 = ty; y_layer0 < by; y_layer0++) {
                    for (int x_layer0 = tx; x_layer0 < bx; x_layer0++) {
                        tot +=
                            layer0[(y_layer0*layer0_across + x_layer0)*
                                   depth + d];
                    }
                }
                /* set the averaged second layer value */
                layer1[(y*layer1_across + x)*depth + d] =
                    tot / ((bx-tx)*(by-ty));
            }
        }
    }
    return 0;
}

/**
* @brief Pools the first layer into the second
* @param depth Depth of the two layers
* @param layer0_across Number of units across the first layer
* @param layer0_down Number of units down the first layer
* @param layer0 Array containing the first layer values
* @param layer1_across Number of units across the second layer
* @param layer1_down Number of units down the second layer
* @param layer1 Array containing the second layer values
* @returns zero on success
*/
int pooling_from_floats_to_neurons(int depth,
                                   int layer0_across,
                                   int layer0_down,
                                   float layer0[],
                                   int layer1_across,
                                   int layer1_down,
                                   bp_neuron ** layer1)
{
    /* second layer must be smaller than the first */
    if (layer1_across*layer1_down >
        layer0_across*layer0_down) {
        return -1;
    }

    /* if layers are the same size then copy the array */
    if (layer1_across*layer1_down ==
        layer0_across*layer0_down) {
        for (int i = 0; i < layer1_across*layer1_down*depth; i++) {
            layer1[i]->value = layer0[i];
        }
        return 0;
    }

	/*#pragma omp parallel for*/
    for (int y = 0; y < layer1_down; y++) {
        int ty = y * layer0_down / layer1_down;
        int by = (y+1) * layer0_down / layer1_down;
        for (int x = 0; x < layer1_across; x++) {
            int tx = x * layer0_across / layer1_across;
            int bx = (x+1) * layer0_across / layer1_across;
            /* for every depth */
            for (int d = 0; d < depth; d++) {
                /* average the inputs in the first layer */
                float tot = 0;
                for (int y_layer0 = ty; y_layer0 < by; y_layer0++) {
                    for (int x_layer0 = tx; x_layer0 < bx; x_layer0++) {
                        tot +=
                            layer0[(y_layer0*layer0_across + x_layer0)*
                                   depth + d];
                    }
                }
                /* set the averaged second layer value */
                layer1[(y*layer1_across + x)*depth + d]->value =
                    tot / ((bx-tx)*(by-ty));
            }
        }
    }
    return 0;
}