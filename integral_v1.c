//////////////////////
//INTEGRAL NUMERICA///
/////PEDRO MENDES/////
//////////////////////

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double F(double x); 

int main()
{
	int i, m, N;
	double x, xmin, xmax, h;
	double Int = 0., Int1 = 0., Int2 = 0.;

	printf("\nEntre com valor inicial: ");
	scanf("%lf", &xmin);

	printf("\nEntre com valor final: ");
	scanf("%lf", &xmax);

	printf("\nEntre com numero de partições (N), use N par: ");
	scanf("%d", &N);

	printf("\nEscolha o método, Trapézio(1), Simpson(2): "  );
	scanf("%d",&m);

	switch(m)
	{
		case 1: //trapézio
			h = (xmax - xmin)/N;
		
			for(i=0;i<N;i++)
			{
				x = xmin + i*h;
				Int += (F(x) + F(x+h))*h/2;
			}
		break;
		
		case 2: //simpson
			h = (xmax - xmin)/N;
			
			for(i=1;i<N;i++)
			{
				if((i%2) != 0)
				{
					Int1 += F(xmin + i*h);
				}
				else
				{
					Int2 += F(xmin + i*h);
				}
			}

			Int = (h/3.)*(F(xmin) + 4*Int1 + 2*Int2 + F(xmax));
		break;

		default:
		{
			printf("\n\nHello World!!\n\n ");
		}
		break;
	}

	printf("\nA integral eh %.14lf\n\n", Int);
	
	return 0;
}

double F(double x) 
{                            
	return sin(x); //funcao a ser integrada
}
