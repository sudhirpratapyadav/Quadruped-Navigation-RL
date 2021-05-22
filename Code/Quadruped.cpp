#include <math.h>

double distanceFromLine(double px, double py, double qx, double qy, double rx, double ry, double sx, double sy)
{
	double rs = rx*sy - ry*sx;
	double qpr = (qx - px)*ry - (qy - py)*rx;
	if (rs == 0 && qpr == 0)
	{
		return 0;
	}
	else if (rs == 0 && qpr!=0)
	{
		return -1;
	}
	else if (rs!=0)
	{
		double qps = (qx - px)*sy - (qy - py)*sx;
		double u = qpr / rs;
		double t = qps / rs;
		if (u >= 0 && u <= 1 && t >= 0)
		{
			double x = px + t*rx;
			double y = py + t*ry;
			return t*sqrt(rx*rx + ry*ry);
		}
		else
		{
			return -1;
		}
	}
}

void initializeState(double *state)
{
	/*
		State(35x1) :
			body configuration(3) : [1 - cos(phi), 1 - cos(theta), 1 - cos(psi)], indices[0:3]
			error in direction of motion(2) : [y(y is forward direction), v_angle(-180:180]], indices[3:4]
			[positions of foot  w.r.t center of body](12), indices[5:16]
			[joint angles](12), indices[17:28]
			area of supporting triangle, index[29]
			height of COM, index[30]
			leg to lift(4) : [1 0 0 0] indices[31:34]

			body dimensions: 18.95x18.95 cm
			leg link lengths: [4.8,8.3,9.5]cm
			height of COM: 9cm
			maxStepSize: 14cm
	*/

	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	state[3] = 0;
	state[4] = 0;
	
	//leg foot coordinates [x1,y1,z1],[x2,y2,z2],[x3,y3,z3],[x4,y4,z4]
	state[5] = -21.48;
	state[6] = 16.15;
	state[7] = -9;
	state[8] = 21.48;
	state[9] = 7.36;
	state[10] = -9;
	state[11] = -21.48;
	state[12] = -7.19;
	state[13] = -9;
	state[14] = 21.48;
	state[15] = -15.30;
	state[16] = -9;


	state[30] = 9;
	state[31] = 0;
	state[32] = 0;
	state[33] = 0;
	state[34] = 1;

}

void getStablity(const double *state,double *stability)
{
	double x = 0;
	double y = 0;
	double x1 = 0;
	double x2 = 0;
	double x3 = 0;
	double y1 = 0;
	double y2 = 0;
	double y3 = 0;
	if (state[31] == 1)
	{
		//leg one to be lifted
		x1 = state[8];
		y1 = state[9];
		x2 = state[11];
		y2 = state[12];
		x3 = state[14];
		y3 = state[15];
	}
	else if (state[32] == 1)
	{
		//leg two to be lifted
		x1 = state[5];
		y1 = state[6];
		x2 = state[11];
		y2 = state[12];
		x3 = state[14];
		y3 = state[15];
	}
	else if (state[33] == 1)
	{
		//leg three to be lifted
		x1 = state[5];
		y1 = state[6];
		x2 = state[8];
		y2 = state[9];
		x3 = state[14];
		y3 = state[15];
	}
	else
	{
		//leg four to be lifted
		x1 = state[5];
		y1 = state[6];
		x2 = state[8];
		y2 = state[9];
		x3 = state[11];
		y3 = state[12];
	}

	double d = ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
	
	if (d!=0)
	{
		double alpha = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) /d;
		double beta = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) /d;
		double gamma = 1 - alpha - beta;
		if (alpha >= 0 && beta >= 0 && gamma >= 0)
		{
			stability[0] = abs((y2 - y1)*x - (x2 - x1)*y + x2*y1 - y2*x1) / sqrt((y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1));
			double d2 = abs((y3 - y2)*x - (x3 - x2)*y + x3*y2 - y3*x2) / sqrt((y3 - y2)*(y3 - y2) + (x3 - x2)*(x3 - x2));
			double d3 = abs((y1 - y3)*x - (x1 - x3)*y + x1*y3 - y1*x3) / sqrt((y1 - y3)*(y1 - y3) + (x1 - x3)*(x1 - x3));
			if (d2 < stability[0])
			{
				stability[0] = d2;
			}
			if (d3 < stability[0])
			{
				stability[0] = d3;
			}

			d = distanceFromLine(x, y, x1, y1, cos(state[4]), sin(state[4]), x2, y2);
			if (d != -1)
			{
				stability[1] = d;
			}
			else
			{
				d = distanceFromLine(x, y, x2, y2, cos(state[4]), sin(state[4]), x3, y3);
				if (d != -1)
				{
					stability[1] = d;
				}
				else
				{
					d = distanceFromLine(x, y, x3, y3, cos(state[4]), sin(state[4]), x1, y1);
					if (d != -1)
					{
						stability[1] = d;
					}
					else
					{
						stability[1] = -1;
					}
				}
			}

		}
		else
		{
			stability[0] = -1;
			stability[1] = -1;
		}
	}
	else
	{
		stability[0] = -1;
		stability[1] = -1;
	}
}
