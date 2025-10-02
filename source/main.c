/*
 *	 .o88b.  .d88b.  d8888b. d888888b d888888b  .o88b.  .d8b.  db      d888888b
 *	d8P  Y8 .8P  Y8. 88  `8D `~~88~~'   `88'   d8P  Y8 d8' `8b 88        `88'  
 *	8P      88    88 88oobY'    88       88    8P      88ooo88 88         88   
 *	8b      88    88 88`8b      88       88    8b      88~~~88 88         88   
 *	Y8b  d8 `8b  d8' 88 `88.    88      .88.   Y8b  d8 88   88 88booo.   .88.  
 *	 `Y88P'  `Y88P'  88   YD    YP    Y888888P  `Y88P' YP   YP Y88888P Y888888P
 *
 *	Copyright (C) 2025 Matthew E. Majfud-Wilinski. All Rights Reserved.
 */

#include <stdio.h>

#include <math.h>

/* ... */
int main(int argc, const char *argv[])
{
/* Declare & set the timestep. */
	float_t l_dt = 0.001f;

/* The membrane potential. */
	float_t l_Vm = -65.0f;

/* The potassium channel activation variable. */
	float_t l_An = 0.317f;
	
/* The Sodium channel activation & inactivation variable. */
	float_t l_Am = 0.05f, l_Ah = 0.6f;

/* The membrane capacitance. */
	float_t l_Cm = 1.0f;

/* The maximum Sodium & Potassium conductance. */
	float_t l_gNa = 120.0f, l_gK = 36.0f;

/* The leak conductance. */
	float_t l_gL = 0.3f;

/* The Sodium & Potassium reversal potential. */
	float_t l_ENa = 50.0f, l_EK = -77.0f;

/* The leak reversal potential. */
	float_t l_EL = -54.387f;

/* The external incoming current. */
	float_t l_Iext = 0.0f;

/* Perform one second worth of iterations. */
	for(float_t l_i = 0.0f; l_i < 1000.0f; l_i += l_dt)
	{
/* Pre-compute the shifted version of the membrane potential. */
		float_t l_Vm_shifted = l_Vm + 65.0f;

/* Declare the rate constants for the Potassium channel. */
		float_t l_alpha_n, l_beta_n;

/* Declare the rate constants for the Sodium channel. */
		float_t l_alpha_m, l_beta_m, l_alpha_h, l_beta_h;

/* Calculate the rate constant for the opening of the Potassium channel. */
		l_alpha_n = (fabsf(10.0f - l_Vm_shifted) < 1e-6f) ? 0.1f : (0.01f * (10.0f - l_Vm_shifted)) / (expf(0.1f * (10.0f - l_Vm_shifted)) - 1.0f);

/* Calculate the rate constant for the closing of the Potassium channel. */
		l_beta_n = 0.125f * expf(-l_Vm_shifted / 80.0f);

/* Calculate the rate constant for the opening of the Sodium channel. */
		l_alpha_m = (fabsf(25.0f - l_Vm_shifted) < 1e-6f) ? 1.0f : (0.1f * (25.0f - l_Vm_shifted)) / (expf(0.1f * (25.0f - l_Vm_shifted)) - 1.0f);

/* Calculate the rate constant for the closing of the Sodium channel. */
		l_beta_m = 4.0f * expf(-l_Vm_shifted / 18.0f);

/* Calculate the rate constant for the inactivation of the Sodium channel. */
		l_alpha_h = 0.07f * expf(-l_Vm_shifted / 20.0f);

/* Calculate the rate constant for the removal of inactivation of the Sodium channel. */
		l_beta_h = 1.0f / (expf((30.0f - l_Vm_shifted) / 10.0f) + 1.0f);

/* Update the Potassium channel activation variable. */
		l_An += l_dt * (l_alpha_n * (1.0f - l_An) - l_beta_n * l_An);

/* Update the Sodium channel activation variable. */
		l_Am += l_dt * (l_alpha_m * (1.0f - l_Am) - l_beta_m * l_Am);

/* Update the Sodium channel inactivation variable. */
		l_Ah += l_dt * (l_alpha_h * (1.0f - l_Ah) - l_beta_h * l_Ah);

/* Update the membrane potential. */
		l_Vm += (l_dt / l_Cm) * (l_Iext - (l_gNa * powf(l_Am, 3) * l_Ah * (l_Vm - l_ENa)) - (l_gK  * powf(l_An, 4) * (l_Vm - l_EK)) - (l_gL * (l_Vm - l_EL)));
	}

/* Return with success. */
	return 0;
}