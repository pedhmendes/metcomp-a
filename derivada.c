////////////////
////DERIVADA////
//PEDRO MENDES//
////////////////

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

long double F(long double xx);

int main()
{
	long double dd, dc, x;
	long double h, i;
	FILE *file;

	file = fopen("derivada.dat", "w" );
	x = 6;

	for(i = -5 ; i <= 1; i+=0.2 ) 
	{
		h = pow(10, i); //precisao da derivada
		dd = ( F(x+h) - F(x) )/ h; // derivada a direita
		dc = ( F(x+h) - F(x-h))/(2*h);//derivada centrada
		fprintf(file, "%1.15Lf %Lf %Lf \n", h, dd, dc);	
	}

	fclose(file);

	return 0;
}

long double F(long double xx)
{
	return ( sin(xx) * pow(xx, 3) ); //funcao que quero derivar
}
