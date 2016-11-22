#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N 40000

float *norm(float x[6], float y[6], float z[6]);
float theorical(float logM,float k,float logr);
float like(float logM,float k,float logr[8],float logv[8]);

int main()
{
  int j;
  float X[8] = {0.324190175,-0.701534590,-0.982564148,1.104185888,3.266443877,-9.218802228,19.930781147,24.323085642};
  float Y[8] = {0.090955208,-0.168809218,-0.191145980,-0.826097003,-3.888055863,1.788299816,-2.555241579,-17.606227355};
  float Z[8] = {-0.022920510,0.037947785,-0.000014724,-0.044595990,-0.057015321,0.335737817,-0.267710968,-0.197974999};
  float vX[8] = {-4.627851589,1.725066954,1.126784520,3.260215854,2.076140727,-0.496457364,0.172224285,0.664855006};
  float vY[8] = {10.390063716,-7.205747212,-6.187988860,4.524583075,1.904040630,-2.005021061,1.357933443,0.935497207};
  float vZ[8] = {1.273504997,-0.198268558,0.000330572,0.014760239,-0.054374153,0.054667082,0.002836325,-0.034716967};
  float *r;
  float *v;
  r = norm(X,Y,Z);
  v = norm(vX,vY,vZ);
  for(j=0;j<8;j++)
    {
      r[j] = log10(r[j]*149597870700);
      v[j] = log10(v[j]*149597870700/(365.25*24*3600));
    }
  float deltaM = 1;
  float deltak = 0.5;
  float UM;
  float Uk;
  float M_new;
  float k_new;
  float alpha;
  float u;
  float *M;
  float *k;
  M = malloc(N*sizeof(float));
  k = malloc(N*sizeof(float));
  M[0] = 1;
  k[0] = 0.1;
  time_t t;
  srand((unsigned) time(&t));
  for(j=1;j<N;j++)
    {
      UM = rand()/(1.0+RAND_MAX)*2*deltaM-deltaM;
      Uk = rand()/(1.0+RAND_MAX)*2*deltak-deltak;
      M_new = M[j-1] + UM;
      k_new = k[j-1] + Uk;
      if(exp(like(M_new,k_new,r,v)-like(M[j-1],k[j-1],r,v)) < 1)
	{
	  alpha = exp(like(M_new,k_new,r,v)-like(M[j-1],k[j-1],r,v));
	}
      else
	{
	  alpha = 1;
	}
      u = rand()/(1.0 +RAND_MAX);
      if(u<=alpha)
	{
	  M[j] = M_new;
	  k[j] = k_new;
	}
      else
	{
	  M[j] = M[j-1];
	  k[j] = k[j-1];
	}
    }
  for(j=0;j<N;j++)
    {
      printf("%f %f\n",M[j],k[j]*2+1);
    }
  return 0;
}

float *norm(float x[8],float y[8],float z[8])
{
  float *temp;
  temp = malloc(8*sizeof(float));
  int i;
  for(i=0;i<8;i++)
    {
      temp[i] = powf(powf(x[i],2)+powf(y[i],2)+powf(z[i],2),0.5);
    }
  return temp;
}

float theorical(float logM, float k,float logr)
{
  return 0.5*log10(6.67408e-11)+0.5*logM-k*logr;
}

float like(float logM,float k,float logr[8],float logv[8])
{
  float temp = 0;
  int l;
  for(l=0;l<8;l++)
    {
      temp -= 0.5*powf(logv[l]-theorical(logM,k,logr[l]),2);
    }
  return temp;
}
