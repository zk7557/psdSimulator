#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#define PI 3.14159265359
#define EE 2.7182818288

#define DPF 10000
#define DUTY 0.8


double functionf(double t, double f, double a, double phi,
	double rndLvl, double rndPhi1, double rndPhi2);
double randf();
double folderf(double pt);

int main(int argc, char* argv[])
{
	//initialize
	time_t now = time(NULL);
	srand(now);

	int frequency = 4000;
	double amplitude = randf() *3 + 2;
	double initialFrame = (int) (randf() * DPF);
	double randomLevel = randf()*0.3;
	double initialPhase = randf() * 2 * PI;
	double fundamentalPhase = randf() * 2 * PI;
	double thirdHarmonicPhase = randf() * 2 * PI;
	double differentPhase = randf() * PI;

	double wavex[DPF];
	double wavey[DPF];
	int ii = 0;
	double time;

	char * path = malloc(50* sizeof(char));
	sprintf(path, "psdSimulation%ld", (long)now);
	FILE * fp = fopen(path, "w");
	printf("%s\n", path);

	for(int i = initialFrame; i < DPF; i++)
	{
		time = (double)i / DPF /20;
		wavex[ii] = functionf(time, 4000, amplitude, initialPhase,
			randomLevel, fundamentalPhase,thirdHarmonicPhase);
		fprintf(fp, "%06f\t", wavex[ii]);
		wavey[ii] = functionf(time, 4000, amplitude, initialPhase+differentPhase,
			randomLevel, fundamentalPhase,thirdHarmonicPhase);
		fprintf(fp, "%06f\n", wavey[ii]);
		++ii;

	}
	for(int i = 0; i < initialFrame; i++)
	{
		time = (double) i / DPF/ 20;
		wavex[ii] = functionf(time, 4000, amplitude, initialPhase,
			randomLevel, fundamentalPhase,thirdHarmonicPhase);
		fprintf(fp, "%06f\t", wavex[ii]);
		wavey[ii] = functionf(time, 4000, amplitude, initialPhase+ differentPhase,
			randomLevel, fundamentalPhase,thirdHarmonicPhase);
		fprintf(fp, "%06f\n", wavey[ii]);
		++ii;
	}





}

double functionf(double t, double f, double a, double phi,
	double rndLvl, double rndPhi1, double rndPhi2)
{
	double signal;
	double rndNoise;
	double fundamental;
	double thirdHarmonic;

	signal = a * sin(2*PI*f * t + phi) * folderf(t*20);
	rndNoise = a * rndLvl * 2 * (randf() - 0.5);
	fundamental = 0.08 * randf() * sin(700*t + rndPhi1);
	thirdHarmonic = 0.06 * randf() * sin(10000*t + rndPhi2);

	return signal + rndNoise + fundamental + thirdHarmonic;
}

double folderf(double pt)
{
	if(pt < DUTY)
	{
		return pt/DUTY;
	}
	else
	{
		return (1-pt)/(1-DUTY);
	}
}

double randf()
{
	return (double)rand() / (double)RAND_MAX;
}
