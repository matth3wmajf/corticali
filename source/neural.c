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
#include <stdlib.h>

#include <math.h>

#include <corticali/neural.h>

/* ... */
int corticali_neural_create(corticali_neural_t *pt_neural)
{
/* ... */
	pt_neural->t_neuron_buffer_size = 0;

/* ... */
	pt_neural->pt_neuron_Vm_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_An_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_Am_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_Ah_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_Cm_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_gNa_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_gK_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_gL_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_ENa_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_EK_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_EL_buffer = NULL;

/* ... */
	pt_neural->pt_neuron_Iext_buffer = NULL;

/* ... */
	return 0;
}

/* ... */
int corticali_neural_config(corticali_neural_t *pt_neural, uintmax_t t_neuron_count)
{
/* ... */
	pt_neural->t_neuron_buffer_size = t_neuron_count;

/* ... */
	pt_neural->pt_neuron_Vm_buffer = realloc(pt_neural->pt_neuron_Vm_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_An_buffer = realloc(pt_neural->pt_neuron_An_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_Am_buffer = realloc(pt_neural->pt_neuron_Am_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_Ah_buffer = realloc(pt_neural->pt_neuron_Ah_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_Cm_buffer = realloc(pt_neural->pt_neuron_Cm_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_gNa_buffer = realloc(pt_neural->pt_neuron_gNa_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_gK_buffer = realloc(pt_neural->pt_neuron_gK_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_gL_buffer = realloc(pt_neural->pt_neuron_gL_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_ENa_buffer = realloc(pt_neural->pt_neuron_ENa_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_EK_buffer = realloc(pt_neural->pt_neuron_EK_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_EL_buffer = realloc(pt_neural->pt_neuron_EL_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_Iext_buffer = realloc(pt_neural->pt_neuron_Iext_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	return 0;
}

/* ... */
int corticali_neural_update(corticali_neural_t *pt_neural, float_t t_dt)
{
/* ... */
	for(uintmax_t l_i = 0; l_i < pt_neural->t_neuron_buffer_size; l_i++)
	{
/* Pre-compute the shifted version of the membrane potential. */
		float_t l_shifted_Vm_value = pt_neural->pt_neuron_Vm_buffer[l_i] + 65.0f;

/* Declare the rate constants for the Potassium channel. */
		float_t l_alpha_n_value, l_beta_n_value;

/* Declare the rate constants for the Sodium channel. */
		float_t l_alpha_m_value, l_beta_m_value, l_alpha_h_value, l_beta_h_value;

/* Calculate the rate constant for the opening of the Potassium channel. */
		l_alpha_n_value = (fabsf(10.0f - l_shifted_Vm_value) < 1e-6f) ? 0.1f : (0.01f * (10.0f - l_shifted_Vm_value)) / (expf(0.1f * (10.0f - l_shifted_Vm_value)) - 1.0f);

/* Calculate the rate constant for the closing of the Potassium channel. */
		l_beta_n_value = 0.125f * expf(-l_shifted_Vm_value / 80.0f);

/* Calculate the rate constant for the opening of the Sodium channel. */
		l_alpha_m_value = (fabsf(25.0f - l_shifted_Vm_value) < 1e-6f) ? 1.0f : (0.1f * (25.0f - l_shifted_Vm_value)) / (expf(0.1f * (25.0f - l_shifted_Vm_value)) - 1.0f);

/* Calculate the rate constant for the closing of the Sodium channel. */
		l_beta_m_value = 4.0f * expf(-l_shifted_Vm_value / 18.0f);

/* Calculate the rate constant for the inactivation of the Sodium channel. */
		l_alpha_h_value = 0.07f * expf(-l_shifted_Vm_value / 20.0f);

/* Calculate the rate constant for the removal of inactivation of the Sodium channel. */
		l_beta_h_value = 1.0f / (expf((30.0f - l_shifted_Vm_value) / 10.0f) + 1.0f);

/* Update the Potassium channel activation variable. */
		pt_neural->pt_neuron_An_buffer[l_i] += t_dt * (l_alpha_n_value * (1.0f - pt_neural->pt_neuron_An_buffer[l_i]) - l_beta_n_value * pt_neural->pt_neuron_An_buffer[l_i]);

/* Update the Sodium channel activation variable. */
		pt_neural->pt_neuron_Am_buffer[l_i] += t_dt * (l_alpha_m_value * (1.0f - pt_neural->pt_neuron_Am_buffer[l_i]) - l_beta_m_value * pt_neural->pt_neuron_Am_buffer[l_i]);

/* Update the Sodium channel inactivation variable. */
		pt_neural->pt_neuron_Ah_buffer[l_i] += t_dt * (l_alpha_h_value * (1.0f - pt_neural->pt_neuron_Ah_buffer[l_i]) - l_beta_h_value * pt_neural->pt_neuron_Ah_buffer[l_i]);

/* Update the membrane potential. */
		pt_neural->pt_neuron_Vm_buffer[l_i] += (t_dt / pt_neural->pt_neuron_Cm_buffer[l_i]) * (pt_neural->pt_neuron_Iext_buffer[l_i] - (pt_neural->pt_neuron_gNa_buffer[l_i] * powf(pt_neural->pt_neuron_Am_buffer[l_i], 3) * pt_neural->pt_neuron_Ah_buffer[l_i] * (pt_neural->pt_neuron_Vm_buffer[l_i] - pt_neural->pt_neuron_ENa_buffer[l_i])) - (pt_neural->pt_neuron_gK_buffer[l_i]  * powf(pt_neural->pt_neuron_An_buffer[l_i], 4) * (pt_neural->pt_neuron_Vm_buffer[l_i] - pt_neural->pt_neuron_EK_buffer[l_i])) - (pt_neural->pt_neuron_gL_buffer[l_i] * (pt_neural->pt_neuron_Vm_buffer[l_i] - pt_neural->pt_neuron_EL_buffer[l_i])));
	}

/* ... */
	return 0;
}

/* ... */
int corticali_neural_delete(corticali_neural_t *pt_neural)
{
/* ... */
	pt_neural->t_neuron_buffer_size = 0;

/* ... */
	pt_neural->pt_neuron_Vm_buffer = realloc(pt_neural->pt_neuron_Vm_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_An_buffer = realloc(pt_neural->pt_neuron_An_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_Am_buffer = realloc(pt_neural->pt_neuron_Am_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_Ah_buffer = realloc(pt_neural->pt_neuron_Ah_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_Cm_buffer = realloc(pt_neural->pt_neuron_Cm_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_gNa_buffer = realloc(pt_neural->pt_neuron_gNa_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_gK_buffer = realloc(pt_neural->pt_neuron_gK_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_gL_buffer = realloc(pt_neural->pt_neuron_gL_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_ENa_buffer = realloc(pt_neural->pt_neuron_ENa_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_EK_buffer = realloc(pt_neural->pt_neuron_EK_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_EL_buffer = realloc(pt_neural->pt_neuron_EL_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	pt_neural->pt_neuron_Iext_buffer = realloc(pt_neural->pt_neuron_Iext_buffer, pt_neural->t_neuron_buffer_size * sizeof(float_t));

/* ... */
	return 0;
}