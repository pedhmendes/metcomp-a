///////////////////
///INTERPOLACAO////
////COM GRAFICO////
///PEDRO MENDES////
///////////////////

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double lagrange(double point[][2],double x, int N);
double neville(double x, int N, double point[N][2]);

int main()
{
	int i, cont, m, N, c, g;
	double  x, xmin, xmax, dx, fx;
	char fileprint[100], fileread[100];
	FILE *fp, *fr, *fg; 

	FILE *pipe = popen("gnuplot -persist", "w");

	printf("\nInsira o nome do arquivo com os dados:\n\n");
	scanf("%s", fileread);
	fr = fopen(fileread,"r");
	
	printf("\nInsira o nome para onde irão os dados interpolados:\n\n");
	scanf("%s", fileprint);
	fp = fopen(fileprint, "w");

	printf("\nQuantos pontos do seu arquivo deseja interpolar?\n\n");
	scanf("%d", &N);

	double point[N][2];

	for(i=0;i<N;i++)
	{
		fscanf(fr, "%lf", &(point[i][0]));
		fscanf(fr, "%lf", &(point[i][1]));
	}

	fclose(fr);

	printf("\nEscolha Xmin e Xmax\n\n");
	scanf("%lf %lf", &xmin, &xmax);

	printf("\nQuantos pontos devem ser interpolados?\n\n");
	scanf("%d", &m);

	printf("\nEscolha o modo\nLagrange (1)\nNeville (2)\n\n");
	scanf("%d",&c);

	dx = (xmax-xmin)/(m-1);
	x = xmin;

	switch(c)
	{
		case 1:
			for(cont=0;cont<m;cont++)
			{
				fx = lagrange(point, x, N);
				fprintf(fp, "%lf %lf\n", x, fx);
				x = x + dx;
			}

		break;

		case 2:
			for(cont=0;cont<m;cont++)
			{
				fx = neville(x,N,point);
				fprintf(fp, "%lf %lf\n", x, fx);
				x = x + dx;
			}

		break;
	}

	printf("\n"); //estetica
	fclose(fp);


	printf("\nDeseja ver o gráfico?\nSim(0)\nNão(1)\n\n");
	scanf("%d", &g);
	if(g==0)
	{
		fg = fopen("script.gnu", "w");
		fprintf(fg, "set title 'Interpolação Polinomial'\n");
		fprintf(fg, "plot '%s' with lines\n",fileprint);
		fprintf(fg, "set term postscript enhanced color\n");
		fprintf(fg, "set output 'grafico.eps'\n");
		fprintf(fg, "replot\n");
		fprintf(fg, "pause -1\n");
		fclose(fg);
		fprintf(pipe, "load 'script.gnu'\n");
		fclose(pipe);
	}

	return 0;
}

double lagrange(double point[][2],double x, int N)
{
	double fl, fx;
	int i, j;
	fx=0;

	for(i=0;i<N;i++)
	{
		fl = 1;
		for(j=0;j<N;j++)
		{
			if(i!=j)
			fl = fl*(x-point[j][0])/(point[i][0]-point[j][0]);
		}
		fx = fx + point[i][1]*fl;
	}
	return fx;
}

double neville(double x, int N, double point[N][2])
{
	int i,j,k;
	double a[N+1][N+1];

	for (i=1;i<=N;i++) 
	{
		a[i][1] = point[i-1][1];
	}
	for (j=2;j<=N;j++)
	{
		for(i=1;i<=N-j+1;i++)
		{
			k=j+i-1;
			a[i][j] = ((x - point[k-1][0])*a[i][j-1] - (x-point[i-1][0])*a[i+1][j-1])/(point[i-1][0]-point[k-1][0]);
		}
	}

	return a[1][N];
}


