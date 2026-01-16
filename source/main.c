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

#include <math.h>

#include <corticali/endl.h>
#include <corticali/neural.h>

/* ... */
int main(int argc, const char *argv[])
{
/* Declare & set the timestep. */
	float_t l_dt = 0.001f;

/* ... */
	corticali_neural_t pt_neural;

/* ... */
	corticali_neural_create(&pt_neural);

/* ... */
	corticali_neural_config(&pt_neural, 1024);

/* Initialize the neurons with standard Hodgkin-Huxley parameters. */
	for(uintmax_t l_i = 0; l_i < pt_neural.t_neuron_buffer_size; l_i++)
	{
/* ... */
		pt_neural.pt_neuron_Vm_buffer[l_i] = -65.0f;

/* ... */
		pt_neural.pt_neuron_Cm_buffer[l_i] = 1.0f;

/* ... */
		pt_neural.pt_neuron_gNa_buffer[l_i] = 120.0f;

/* ... */
		pt_neural.pt_neuron_gK_buffer[l_i] = 36.0f;

/* ... */
		pt_neural.pt_neuron_gL_buffer[l_i] = 0.3f;

/* ... */
		pt_neural.pt_neuron_ENa_buffer[l_i] = 50.0f;

/* ... */
		pt_neural.pt_neuron_EK_buffer[l_i] = -77.0f;

/* ... */
		pt_neural.pt_neuron_EL_buffer[l_i] = -54.387f;

/* ... */
		pt_neural.pt_neuron_Iext_buffer[l_i] = 0.0f;

/* ... */
		pt_neural.pt_neuron_An_buffer[l_i] = 0.317f;

/* ... */
		pt_neural.pt_neuron_Am_buffer[l_i] = 0.052f;

/* ... */
		pt_neural.pt_neuron_Ah_buffer[l_i] = 0.596f;
	}

/* Perform one second worth of iterations. */
	for(float_t l_i = 0.0f; l_i < 1000.0f; l_i += l_dt)
	{
/* ... */
		corticali_neural_update(&pt_neural, l_dt);

/* ... */
		fprintf(stderr, "debug: Performed iteration %f." ENDL, l_i);
	}

/* ... */
	corticali_neural_delete(&pt_neural);

/* Return with success. */
	return 0;
}