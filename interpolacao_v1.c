////////////////
//INTERPOLAÇÃO//
//PEDRO MENDES//
////////////////

#include<math.h>
#include<stdio.h>
#include<stdlib.h>

double lagrange(double x, int n, double point[n][2]);
double neville(double x, int n, double point[n][2]);

int main()
{
	int i, n, c;
	double x, value;
	char fileread[100];
	FILE *fr;

	printf("\nDigite o nome do arquivo com os dados a interpolar: ");
	scanf("%s", fileread);

	printf("\nQuantos pontos desse arquivo deseja interpolar?: ");
	scanf("%d", &n);
	
	double point[n][2];

	fr = fopen(fileread,"r");
	for(i=0;i<n;i++)
	{
		fscanf(fr, "%lf", &(point[i][0]));
		fscanf(fr, "%lf", &(point[i][1]));
	}
	fclose(fr);

	printf("\nEscolha um x para calcular y\n\n");
	scanf("%lf", &x);

	printf("\nEscolha o método\nLagrange(1)\nNeville(1)\n\n");
	scanf("%d",&c);

	switch(c)
	{
		case 1:
			value = lagrange( x, n, point);
			printf("\nx = %lf	y = %lf\n\n", x, value ); 
		break;
		
		case 2:
			value = neville( x, n, point);
			printf("\nx = %lf		y = %lf\n\n", x, value );
		break;

		default:
			printf("\nHello World\n\n");
		break;
	
	}

	return 0;
}


double lagrange(double x, int n, double point[n][2])
{
	int i,j, countl = 0;
	double value=0, Lfactor;

	for(i=0;i<n;i++)
	{
		Lfactor = 1;
		for(j=0;j<n;j++)
		{
			if( i != j )
			{
				Lfactor = Lfactor*(x-point[j][0])/(point[i][0]-point[j][0]);
			}
			countl = countl + 1;
		}
		value = value + point[i][1]*Lfactor;
	}
	
	printf("%d \n", countl);
	
	return value;
}

double neville(double x, int n, double point[n][2])
{
	int i,j,k, countn = 0;
	double A[n][n], value=0;

	for(i=0;i<n;i++)
	{
		A[i][0] = point[i][1];
	} 
	for(j=1; j< n;j++)
	{
		for(i=0; i< n-j;i++)
		{
			k = j+i-1;
			A[i][j] =  ( (x - point[k][0])*A[i][j-1] - (x-point[i][0])*A[i+1][j-1] )/(point[i][0]-point[k][0]);
			countn = countn + 1;  
		}
	}

	printf("%d \n", countn);

	return value = A[0][n-1];
}
