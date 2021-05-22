#include "RL.h"

#define ACTIONS 80
#define STATE_VECTOR_LENGTH 35
#define ALPHA 0.005



double getValueOfState(const double *state, const double *WEIGHTS)
{
	double val = 0;
	for (int i = 0; i < STATE_VECTOR_LENGTH; i++)
	{
		val = val + state[i] * WEIGHTS[i];
	}
	return val;
}

int selectBestAction(const double *state,const double *WEIGHTS)
{
	/*
		grid resoltion : 1x1 cm
		Actions(70) : grid of 14 * 5 from foot posititon in forward direction

		x: [-2,2] (inside to outside of body)
		y: [1,14] (forward)
	*/

	double n_state[35] = {};

	//first action
	double exp_reward = evolveState(state, n_state, 0);
	exp_reward = exp_reward + getValueOfState(n_state, WEIGHTS);
	double max_reward = exp_reward;
	int bestAction = 0;

	for (int a = 1; a < ACTIONS; a++)
	{
		exp_reward = evolveState(state, n_state, a);
		exp_reward = exp_reward + getValueOfState(n_state, WEIGHTS);
		if (exp_reward > max_reward)
		{
			max_reward = exp_reward;
			bestAction = a;
		}
	}

	return bestAction;
}
double evolveState(const double *state, double *n_state, int action)
{
	/*
		State(35x1) :
			body configuration(3) : [1 - cos(phi), 1 - cos(theta), 1 - cos(psi)], indices[0:3]
			error in direction of motion(2) : [y(y is forward direction), tan(del_theta)], indices[3:4]
			[positions of foot  w.r.t center of body](12), indices[5:16]
			[joint angles](12), indices[17:28]
			area of supporting triangle, index[29]
			height of COM, index[30]
			leg to lift(4) : [1 0 0 0] indices[31:34]
	*/

	if (state[31] == 1)
	{
		//leg one to be lifted

	}
	else if (state[32] == 1)
	{
		//leg two to be lifted

	}
	else if (state[33] == 1)
	{
		//leg three to be lifted

	}
	else
	{
		//leg four to be lifted

	}
	return 0;
}
void learnValueFunction(const double *state,const double *n_state, double reward, double *WEIGHTS)
{
	double del_weight = (ALPHA*(reward + getValueOfState(n_state, WEIGHTS) - getValueOfState(state, WEIGHTS)))/STATE_VECTOR_LENGTH;
	for (int i = 0; i < STATE_VECTOR_LENGTH; i++)
	{
		WEIGHTS[i] = WEIGHTS[i] + del_weight;
	}
}