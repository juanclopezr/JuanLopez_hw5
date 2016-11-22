#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N 40000

float *theorical(float alpha,float beta,float gamma,float delta,float x0,float y0,float h);
float like(float alpha, float beta,float gamma,float delta,float x0,float y0,float ti[96],float x[96],float y[96]);

int main()
{
  int j;
  float prob;
  float Xm[96];
  float Ym[96];
  float Ti[96];
  char str1[5], str2[2], str3[2];
  int k;
  FILE * f;
  f = fopen("lotka_volterra_obs.dat","r");
  rewind(f);
  for(j=0;j<96;j++)
   {
     fscanf(f,"%s %s %s",str1,str2,str3);
     Ti[j] = atof(str1);
     Xm[j] = atof(str2);
     Ym[j] = atof(str3);
   }
  float *Alpha;
  float *Beta;
  float *Gamma;
  float *Delta;
  Alpha = malloc(N*sizeof(float));
  Beta = malloc(N*sizeof(float));
  Gamma = malloc(N*sizeof(float));
  Delta = malloc(N*sizeof(float));
  float deltaa = 0.1;
  float deltab = 0.1;
  float deltac = 0.1;
  float deltad = 0.1;
  float a_new;
  float b_new;
  float c_new;
  float d_new;
  float alpha;
  float Ua;
  float Ub;
  float Uc;
  float Ud;
  float u;
  time_t t;
  srand((unsigned) time(&t));
  for(j=1;j<N;j++)
    {
      Ua = rand()/(1.0+RAND_MAX)*2*deltaa-deltaa;
      Ub = rand()/(1.0+RAND_MAX)*2*deltab-deltab;
      Uc = rand()/(1.0+RAND_MAX)*2*deltac-deltac;
      Ud = rand()/(1.0+RAND_MAX)*2*deltad-deltad;
      a_new = Alpha[j-1] + Ua;
      b_new = Beta[j-1] + Ub;
      c_new = Gamma[j-1] + Uc;
      d_new = Delta[j-1] + Ud;
      prob = exp(like(a_new,b_new,c_new,d_new,Xm[0],Ym[0],Ti,Xm,Ym)-like(Alpha[j-1],Beta[j-1],Gamma[j-1],Delta[j-1],Xm[0],Ym[0],Ti,Xm,Ym));
      if(prob < 1)
	{
	  alpha = prob;
	}
      else
	{
	  alpha = 1;
	}
      u = rand()/(1.0 + RAND_MAX);
      if(u<=alpha)
	{
	  Alpha[j] = a_new;
	  Beta[j] = b_new;
	  Gamma[j] = c_new;
	  Delta[j] = d_new;
	}
      else
	{
	  Alpha[j] = Alpha[j-1];
	  Beta[j] = Beta[j-1];
	  Gamma[j] = Gamma[j-1];
	  Delta[j] = Delta[j-1];
	}
    }
  return 0;
}

float *theorical(float alpha,float beta,float gamma,float delta,float x0,float y0,float h)
{
  float *tup;
  tup = malloc(2*sizeof(float));
  float k1x = x0*(alpha-beta*y0);
  float k1y = -y0*(gamma-delta*x0);
  float k2x = (x0+0.5*h*k1x)*(alpha-beta*(y0+0.5*h*k1y));
  float k2y = -(y0+0.5*h*k1y)*(gamma-delta*(x0+0.5*h*k1x));
  float k3x = (x0+0.5*h*k2x)*(alpha-beta*(y0+0.5*h*k2y));
  float k3y = -(y0+0.5*h*k2y)*(gamma-delta*(x0+0.5*h*k2x));
  float k4x = (x0+h*k3x)*(alpha-beta*(y0+h*k3y));
  float k4y = -(y0+h*k3y)*(gamma-delta*(x0+h*k3x));
  tup[0] = x0 + h*(k1x+2*k2x+2*k3x+k4x)/6.0;
  tup[1] = y0 + h*(k1y+2*k2y+2*k3y+k4y)/6.0;
  return tup;
}

float like(float alpha, float beta,float gamma,float delta,float x0,float y0,float ti[96],float x[96],float y[96])
{
  float temp = 0;
  int i;
  float h;
  float *res;
  float xt = x0;
  float yt = y0;
  for(i=1;i<95;i++)
    {
      h = ti[i]-ti[i-1];
      res = theorical(alpha,beta,gamma,delta,xt,yt,h);
      xt = res[0];
      yt = res[1];
      temp -= 0.5*(powf(x[i]-xt,2)+powf(y[i]-yt,2));
    }
  return temp;
}
