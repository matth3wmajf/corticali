#include <stdio.h>

#include <math.h>

/* ... */
int main(int argc, const char *argv[])
{
/* Declare & set the timestep. */
	float_t l_t = 0.001f;

/* Declare the structure representing a neuron. */
	struct
	{
/* The membrane potential. */
		float_t t_Vm;

/* The potassium channel activation variable. */
		float_t t_An;
		
/* The Sodium channel activation & inactivation variable. */
		float_t t_Am, t_Ah;

/* The membrane capacitance. */
		float_t t_Cm;

/* The maximum Sodium & Potassium conductance. */
		float_t t_gNa, t_gK;

/* The leak conductance. */
		float_t t_gL;

/* The Sodium & Potassium Nernst potential. */
		float_t t_ENa, t_EK;

/* The leak Nernst potential. */
		float_t t_EL;

/* The external incoming current. */
		float_t t_Iext;
	} l_n;

/* ... */
	return 0;
}