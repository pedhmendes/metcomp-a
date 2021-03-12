//////////////////////
////ZEROS DA FUNCAO///
/////PEDRO MENDES/////
//////////////////////

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double funcao(double y);
double derivada(double z);

int main()
{

	double x, x0, xf, k, a, b, p;
	int N, c, i;

	printf("\nEscolha o método\nIteração Simples(1), Newton-Raphson(2), Bissecção(3): ");
	scanf("%d", &c);

	printf("\nEscolha a precisão desejada: ");
	scanf("%lf", &p);

	printf("\nQuantas raizes tem a sua função: ");
	scanf("%d", &N);

	switch (c)
	{
		case 1: //iteracao
			for(i=0;i<N;i++)
			{
				printf("\nEscolha o valor inicial\n\n");
				scanf("%lf", &x0);
	
				x = x0;
				xf = 0;
	
				while (fabs(x - xf) > p)
				{
					xf = x;
					x = x - funcao(x);
				}
			
				printf("\nA raiz é %lf\n", x);
			}
		break;
	
		case 2: //newton-raphson
 			for(i=0;i<N;i++)
			{
				printf("\nEscolha o valor inicial\n\n");
				scanf("%lf", &x0);
					
				x = x0;
				xf = 0;
				
				double h = funcao(x) / derivada(x); 
		
				while (fabs(h) >= p) 
				{ 
					h = funcao(x) / derivada(x); 
					x = x - h; 
				} 
			
				printf("\nA raiz é %lf\n", x);
			}
		break;

		case 3: //bisseccao
			for(i=1;i<=N;i++)
			{
				printf("\nEscolha o valor inicial\n\n");
				scanf("%lf", &x0);

				x = x0;
				xf = 0;
   
				printf("\nEscolha o passo\n\n");
				scanf("%lf", &k);
				a= x-k;
				b= x+k;
	
				while (fabs(a-b) > p)
				{
					xf = x;
					x= (a+b)/2;
					if(funcao(a)*funcao(x)<0)
					{
						b = x;
					}
					else
					{
						a = x;
					}
		  		}
				printf("\nA raiz é %lf\n", x);
			}
		break;

		default:
			printf("\nHello World!\n\n");
		break;
	}

	return 0;
}

double funcao(double x) 
{
	return sin(x)/(pow(x,2) + 1) + 0.2 - 0.01*pow(x,2) ;
}

double derivada(double z) 
{
	return  ( ( (pow(z,2) + 1)*cos(z) ) - 2*z*sin(z) )/( pow((pow(z,2)+1),2) ) - 0.02*z ; 
}
