///////////////////////
///INTEGRAL NUMÉRICA///
////PARA DIFERENTES////
//////REPARTICOES//////
/////PEDRO MENDES//////
///////////////////////

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double F(double x); 

int main()
{
	int i, k, L, m, N; 
	double xmin, xmax, xi, h;
	double Int, Int1, Int2, Int3, Int4, Intx;
	double err;
	FILE *fp;
	
	printf("\nEntre com valor inicial: ");
	scanf("%lf", &xmin);

	printf("\nEntre com valor final: ");
	scanf("%lf", &xmax);

	printf("\nEntre com numero de partições (N), use N par: ");
	scanf("%d", &N);

	printf("\nEscolha o método, Trapézio(1), Simpson(2): ");
	scanf("%d",&m);

	fp = fopen("dados.dat", "w");
	fprintf(fp, "#N\tintegral\terro\n");

	printf("\n\nOs dados se encontram em 'dados.dat'\n\n\n");

	switch(m)
	{
		case 1: //trapézio
			for(k=2; k<=N; k++)
			{
 				h = (xmax - xmin)/k;
				
				Int1 = 0.;
				Int = 0.;
				
				for(i=0; i<k; i++)
				{
					xi = xmin + i*h;
					Int += (F(xi) + F(xi+h))*h/2;
				}
				
				L = k-2;
				h = (xmax - xmin)/L;
				
				for(i=0; i<L; i++)
				{
					xi = xmin + i*h;
					Int1 += (F(xi) + F(xi+h))*h/2;
				}
			
				err = fabs((Int - Int1))/Int;
				
				fprintf(fp, "%d\t%lf\t%lf\n", k, Int, err);
			}
		break;
	
		case 2: //simpson
			for(k=2; k<=N; k++)
			{
				h = (xmax - xmin)/k;
		
				Int = 0;
				Int1 = 0;
				Int2 = 0;
				i = 0;
		
				for(i=1; i<k; i++)
				{
					if(i%2!=0)
					{
						Int1 += F(xmin +i*h);
					}
					else
					{
						Int2 += F(xmin + i*h);
					}
				}
			
				Int = (h/3)*(F(xmin) + 4*Int1 + 2*Int2 + F(xmax));	
			
				L = k-2;
				h = (xmax - xmin)/L;
				
				Intx = 0;
				Int3 = 0;
				Int4 = 0;
				i = 0;
				
				for(i=1; i<L; i++) //for do erro
				{
					if(i%2!=0)
					{
						Int3 += F(xmin +i*h);
					}
					else
					{	
						Int4 += F(xmin + i*h);
					}
				}
		
				Intx = 4*Int3 + 2*Int3 + F(xmin) + F(xmax);
				Intx = Intx*h/3;
		
				err = fabs( (Int - Intx)/Int); 

				fprintf(fp, "%d\t%lf\t%lf\n", k, Int, err); 
		}
		break;
	
		default:
		{
			printf("\n\nHello World!!\n\n");
		}
		break;
	}

	fclose(fp);

	return 0;
}

double F(double x)
{                            
	return sin(x);		
}
