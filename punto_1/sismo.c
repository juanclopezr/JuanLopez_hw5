#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N 40000

float theorical(float x0, float y0,float x,float y);
float like(float x0, float y0, float x[6], float y[6], float t[6]);

int main()
{
  int j;
  float deltaX0 = 0.1;
  float deltaY0 = 0.1;
  float UX0;
  float UY0;
  float X0_new;
  float Y0_new;
  float alpha;
  float u;
  float *X0;
  float *Y0;
  X0 = malloc(N*sizeof(float));
  Y0 = malloc(N*sizeof(float));
  X0[0] = 0;
  Y0[0] = 0;
  float X[6] = {3,4,5,3,4,5};
  float Y[6] = {15,15,15,16,16,16};
  float Ti[6] = {3.12,2.98,2.84,3.26,3.12,2.98};
  time_t t;
  srand((unsigned) time(&t));
  for(j=1;j<N;j++)
    {
      UX0 = rand()/(1.0 + RAND_MAX)*2*deltaX0-deltaX0;
      UY0 = rand()/(1.0 + RAND_MAX)*2*deltaY0-deltaY0;
      X0_new = X0[j-1] + UX0;
      Y0_new = Y0[j-1] + UY0;
      if(exp(like(X0_new,Y0_new,X,Y,Ti)-like(X0[j-1],Y0[j-1],X,Y,Ti)) < 1)
	{
	  alpha = exp(like(X0_new,Y0_new,X,Y,Ti)-like(X0[j-1],Y0[j-1],X,Y,Ti));
	}
      else
	{
	  alpha = 1;
	}
      u = rand()/(1.0 + RAND_MAX);
      if(u<=alpha)
	{
	  X0[j] = X0_new;
	  Y0[j] = Y0_new;
	}
      else
	{
	  X0[j] = X0[j-1];
	  Y0[j] = Y0[j-1];
	}
    }
  for(j=0;j<N;j++)
    {
      printf("%f %f\n",X0[j],Y0[j]);
    }
  return 0;
}

float theorical(float x0, float y0,float x,float y)
{
  return powf(powf(x-x0,2)+powf(y-y0,2),0.5);
}

float like(float x0, float y0, float x[6], float y[6], float ti[6])
{
  float temp = 0;
  int i;
  for(i=0;i<6;i++)
    {
      temp -= 0.5*powf(ti[i]-theorical(x0,y0,x[i],y[i]),2);
    }
  return temp;
}
