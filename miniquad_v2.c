//////////////////////
////////MINIMOS///////
///////QUADRADOS//////
///COM TEMPO MEDIDO///
///////E GRAFICO//////
/////PEDRO MENDES/////
//////////////////////

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<time.h>

void RegLin(int n, double x[], double y[], double *a, double *b); 

int main()
{
	int i, N, g;
	double x[100000], y[100000], a, b, CPU_time; 

	FILE *rf, *gf;
	FILE *pipe = popen("gnuplot -persist", "w");

	char filename[100];
	clock_t ti, tf;

	ti = clock();

	printf("\n\nEscolha o nome do arquivo onde estão os dados: ");
	scanf("%s", filename);


	printf("\nInsira quantas linhas deseja usar: ");
	scanf("%d", &N);

	rf= fopen(filename, "r");

	for(i=0;i<=N;i++)
	{
		fscanf(rf,"%lf %lf", &x[i], &y[i]);
	}
	fclose(rf);

	RegLin( N, x, y, &a, &b);

	tf = clock();
	CPU_time = ( (double) (tf - ti) )/CLOCKS_PER_SEC;
	
	printf("\nA melhor reta que ajusta seus dados eh\n\n %lf*x %lf\n", a, b);
	printf("\nA CPU levou %lf segundos para calcular a reta\n\n", CPU_time);

	
	printf("\nDeseja ver o gráfico do conjunto?\nSim(0) Não(1)\n\n");
	scanf("%d", &g);

	if(g == 0)
	{
		gf = fopen("script-m.gnu", "w");

		fprintf(gf, "set title 'Regressao Linear'\n");
		fprintf(gf, "plot '%s' \n", filename);
		fprintf(gf, "replot %lf*x + %lf title 'ajuste'\n", a, b);
		fprintf(gf, "set term postscript enhanced color \n");
		fprintf(gf, "set output 'miniquad.eps'\n");
		fprintf(gf, "replot\n");
		fprintf(gf, "pause -1\n");
		
		fclose(gf);	
		
		fprintf(pipe, "load 'script-m.gnu'\n");	
	
		fclose(pipe);
	}
	
	return 0;
}

void RegLin(int n, double x[], double y[], double *a, double *b) 
{
	int i;
	double sum1=0, sum2=0, sum3=0; 
	double sum4=0, sum5=0, sum6=0; 
	double D, Da, Db;

	for(i=1;i<n;i++)
	   {
		sum1 = sum1 + i*n; //N
		sum2 = sum2 + x[i]; //X
		sum3 = sum3 + y[i]; //Y
	   }
	for(i=1;i<n;i++)
	{
		sum4 = sum4 + x[i]; //X
		sum5 = sum5 + pow(x[i],2); //x^2
		sum6 = sum6 + x[i]*y[i]; //YX
	}

	D = (sum1*sum5) - (sum2*sum4); 
	Da = (sum1*sum6) - (sum3*sum4);
	Db = (sum3*sum5) - (sum2*sum6);

	*a = Da/D;
	*b = Db/D;

	return;
}
