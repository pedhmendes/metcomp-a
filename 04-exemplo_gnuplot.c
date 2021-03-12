#include<stdio.h>
#include<math.h>

int main()
{
	int i, N=6;
	float X[N], Y[N];

	FILE *arquivo1, *arquivo2;
	FILE *pipe = popen("gnuplot -persist","w");

// ler os dados a partir do arquivo -> colocar em vetores x[i], y[i]

	arquivo1 = fopen ("dados.dat", "r");
	for(i=0; i<N; i++)
	{
		fscanf(arquivo1, "%f %f", &X[i], &Y[i]);
	}
	
	fclose(arquivo1);
	
	arquivo2 = fopen ("script2.gnu", "w");
	fprintf(arquivo2, "set title 'titulo'\n");
	fprintf(arquivo2, "plot 'dados.dat'\n");
	fprintf(arquivo2, "set term postscript enhanced color\n");
	fprintf(arquivo2, "set output 'grafico.eps'\n");
	fprintf(arquivo2, "replot\n");
	fprintf(arquivo2, "pause -1\n");

	fclose(arquivo2);

	fprintf(pipe, "load 'script2.gnu'\n");
	
	fclose(pipe);

	return 0;
}
