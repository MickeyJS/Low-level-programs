//Szarapanowski

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

extern char *malloc(int);
/*
void myprintf(char c[])
{
    write(1, &c, 1024);
    return;
}*/
void myprintf(char c[], ...)
{
	//int max = 0;
	int i = 0;
	char x;
	
	/*
	//Dlugosc napisu
	i=1;
	x = c[0];
	while(x != '\0')
	{
		x = c[i];
		i++;
	}
	max = i;
	*/

	//write(1, c, max-1);

	va_list vl;
	va_start(vl, c);
	
	i = 0;
	x = 'x';
	while(x != '\0')
	{
		x = c[i];

		if(x == '%')
		{
			char y = c[i+1];
			
			// Dziesietne %d
			if(y == 'd')
			{
				int I = va_arg(vl,int);
	
				if(I < 0)
				{
					x = '-';
					write(1, &x, 1);
					I = I * (-1);
				}
				
				int k = 10;
				while(I+1 > k*10)
				{
					k = k * 10;
				}
				while(k > 0)
				{
					x = (I/k) + '0';
					write(1, &x, 1);
					I = I%k;
					k = k/10;
				}

				i++;
			}
			// Napis %s
			else if(y == 's')
			{
				char *t[100];
				t[0] = va_arg(vl, char**);
				int size = (int) strlen(*t);
				
				// int i2=1; char x2 = *(t[0]; while(x2 != '\0') { x2 = *t[i2]; i2++; }

				write(1, *t, size);
				i++;
			}
			// Szesnastkowo %x
			if(y == 'x')
			{
				int I = va_arg(vl,int);
				int I2 = I;

				//Dlugosc napisu
				int length = 0;
				while(I2 > 0)
				{
					I2 = I2/16;
					length++;
				}
				char hex[length];

				int i2 = 0;
				while(I > 0)
				{
					int z = I%16;
					
					x = z + '0';

					if(z == 10)
					x = 'a';
					else if(z == 11)
					x = 'b';
					else if(z == 12)
					x = 'c';
					else if(z == 13)
					x = 'd';
					else if(z == 14)
					x = 'e';
					else if(z == 15)
					x = 'f';
					
					hex[i2] = x;

					I = I/16;
					i2++;
				}
				i2--;

				while(i2 >= 0)
				{
					x = hex[i2];
					write(1, &x, 1);
					i2--;
				}
				
				i++;
			}
			// Binarnie %b
			if(y == 'b')
			{
				int I = va_arg(vl,int);
				int I2 = I;

				//Dlugosc napisu
				int length = 0;
				while(I2 > 0)
				{
					I2 = I2/2;
					length++;
				}
				char bin[length];

				int i2 = 0;
				while(I > 0)
				{
					int z = I%2;
					
					x = z + '0';
					
					bin[i2] = x;

					I = I/2;
					i2++;
				}
				i2--;

				while(i2 >= 0)
				{
					x = bin[i2];
					write(1, &x, 1);
					i2--;
				}
				
				i++;
			}
		}
		else
		{
			write(1, &x, 1);
		}

		i++;
	}
	
	
	//write(1, c, i-1); // \0 liczy sie jako dwa znaki
	//*/
}

void myscanf(char c[], ...)
{
	int i;
	char x;
	
	va_list vl;
	va_start(vl, c);
	
	i = read(0, &x, 1);
    while(i > 0)
    {
        write(1, &x, 1);
        i = read(0, &x, 1);
    }
}


int main()
{
	myprintf("Tekst: %sLiczba: %d Hexowo: %x Binarnie: %b", "Bardzo dlugi tekst xd\n", 12345, 24032, 10);
	//char tablica[10] = "1234567890";
    //int i;
	//myscanf("%s", i);

    return 0;
}
