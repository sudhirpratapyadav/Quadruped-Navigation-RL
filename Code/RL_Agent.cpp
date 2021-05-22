#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "RL.h"
#include "Quadruped.h"


#define NUM_TRAJECTORIES 10
#define STATE_VECTOR_LENGTH 35
#define WEIGHTS_LENGTH 35

/*
void main()
{

	double *state;
	double *n_state;
	
	double *WEIGHTS;

	/*
		State (35x1): 
			body configuration (3): [1-cos(phi),1-cos(theta),1-cos(psi)]
			direction of motion (2): [x(y is forward direction),v_angle(-180:180]]
			[positions of foot  w.r.t center of body] (12),
			[joint angles] (12)
			area of supporting triangle,
			height of COM,
			leg to lift (4): [ 1 0 0 0]
	

		body dimensions: 18.95x18.95 cm
		leg link lengths: [4.8,8.3,9.5]cm
		height of COM: 9cm
		maxStepSize: 14cm

		grid resoltion: 1x1 cm
		Actions (70): grid of 14*5 from foot posititon in forward direction

		WEIGHTS: 35x1
		
		V(s) = WEIGHTS'*featues(s)
	


	state = (double *)malloc(35 * sizeof(double));
	n_state = (double *)malloc(35 * sizeof(double));

	for (int i = 0; i < STATE_VECTOR_LENGTH; i++)
	{
		state[i] = 0;
		n_state[i] = 0;
	}

	for (int num_t = 0; num_t < NUM_TRAJECTORIES; num_t++)
	{
		initializeState(state);
		double stability =  1;
		while (stability>=0)
		{
			int action = selectBestAction(state, WEIGHTS);
			double reward = evolveState(state, n_state, action);
			learnValueFunction(state, n_state, reward, WEIGHTS);
			double *temp;
			temp = state;
			state = n_state;
			n_state = temp;
			stability = getStability(n_state);
			memcpy(state, n_state, STATE_VECTOR_LENGTH * sizeof(double));
		}
	}

}
*/