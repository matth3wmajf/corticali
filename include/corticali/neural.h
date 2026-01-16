/*
 *	 .o88b.  .d88b.  d8888b. d888888b d888888b  .o88b.  .d8b.  db      d888888b
 *	d8P  Y8 .8P  Y8. 88  `8D `~~88~~'   `88'   d8P  Y8 d8' `8b 88        `88'  
 *	8P      88    88 88oobY'    88       88    8P      88ooo88 88         88   
 *	8b      88    88 88`8b      88       88    8b      88~~~88 88         88   
 *	Y8b  d8 `8b  d8' 88 `88.    88      .88.   Y8b  d8 88   88 88booo.   .88.  
 *	 `Y88P'  `Y88P'  88   YD    YP    Y888888P  `Y88P' YP   YP Y88888P Y888888P
 *
 *	Copyright (C) 2025-2026 Matthew E. Majfud-Wilinski. All Rights Reserved.
 */

#include <stdio.h>
#include <stdint.h>

#include <math.h>

#pragma once

/* ... */
typedef struct
{
/* ... */
	float_t *pt_neuron_Vm_buffer;

/* ... */
	float_t *pt_neuron_An_buffer;

/* ... */
	float_t *pt_neuron_Am_buffer;

/* ... */
	float_t *pt_neuron_Ah_buffer;

/* ... */
	float_t *pt_neuron_Cm_buffer;

/* ... */
	float_t *pt_neuron_gNa_buffer;

/* ... */
	float_t *pt_neuron_gK_buffer;

/* ... */
	float_t *pt_neuron_gL_buffer;

/* ... */
	float_t *pt_neuron_ENa_buffer;

/* ... */
	float_t *pt_neuron_EK_buffer;

/* ... */
	float_t *pt_neuron_EL_buffer;

/* ... */
	float_t *pt_neuron_Iext_buffer;

/* ... */
	uintmax_t t_neuron_buffer_size;
} corticali_neural_t;

/* ... */
int corticali_neural_create(corticali_neural_t *pt_neural);

/* ... */
int corticali_neural_config(corticali_neural_t *pt_neural, uintmax_t t_neuron_count);

/* ... */
int corticali_neural_update(corticali_neural_t *pt_neural, float_t t_dt);

/* ... */
int corticali_neural_delete(corticali_neural_t *pt_neural);