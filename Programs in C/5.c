//Mikolaj Szarapanowski L5/z2

#include <stdio.h>
#include <unistd.h>

#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 200

int wymiar;

int A[MAX*MAX];
int B[MAX*MAX];
int C[MAX*MAX];	//Wynik mnozenia
int U[MAX*MAX]; //Tablica zawierajaca informacje czy dana wartosc zostala obliczona

int sleepingTime = 10;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *calculate(void *arg)
{
	pthread_mutex_lock(&mutex);
	int w = wymiar;
	pthread_mutex_unlock(&mutex);

	int *numer_p = (int *) arg;
	int numer = *numer_p;
	int j = 0;
	int s = 0;
	int u;
	while(j < w*w)
	{
		pthread_mutex_lock(&mutex);
		u = U[j];
		s = s + u;
		
		if(u == 0)
		U[j] = 1; //Ustawiamy na obliczone
		pthread_mutex_unlock(&mutex);
		//... i obliczamy

		if(u == 0)
		{
			int wiersz = j/w;
			int kolumna = j%w;
			int suma = 0;
			printf("Watek %d oblicza: [%d,%d]\n", numer, wiersz, kolumna);

			for(int i=0; i<w; i++)
			{
				pthread_mutex_lock(&mutex);
				int a = A[wiersz*wymiar+i];
				int b = B[i*wymiar+kolumna];
				pthread_mutex_unlock(&mutex);
			
				//printf("%d*%d", a, b);
				suma = suma + a*b;

				//if(i < w-1)
				//printf(" + ");
			}

			//printf(" = %d\n", suma);

			pthread_mutex_lock(&mutex);
			C[j] = suma;
			pthread_mutex_unlock(&mutex);
		}

		if(j+1 == w*w) // badamy przypadek ostatniego elementu tablicy
		{
			j++;

			if(s < w*w)
			{
				s = 0;
				j = 0;
			}
		}
		else
		{
			j++;
		}
	}
	printf("Watek %d skonczyl prace...\n", numer);
}	

int main(int argc, char *argv[])
{
	srand(time(NULL));
	wymiar = strtol(argv[1], NULL, 10); // pierwszym argumentem jest wymiar macierzy
	int iloscWatkow = strtol(argv[2], NULL, 10); // Drugim jest ilość wątków na których będziemy pracować

	//Sprawdzanie poprawnosci wpisanych argumentow
	if(wymiar <= 0)
	{
		printf("Zly wymiar macierzy!\n");
		return -1;
	}
	if(wymiar > MAX)
	{
		printf("Za duza macierz!\n");
		return -1;
	}
	if(iloscWatkow <= 0)
	{
		printf("Zla ilosc watkow!\n");
		return -1;
	}

	printf("Wielkosc macierzy: %d\n", wymiar);
	printf("Ilosc watkow: %d\n", iloscWatkow);

	//Zerowanie tablic
	for(int i=0; i<MAX*MAX; i++)
	{
		A[i] = 0;
		B[i] = 0;
		C[i] = 0;
		U[i] = 0;
	}

	//Wypelnianie tablicy losowymi wartosciami
	for(int i=0; i<wymiar*wymiar; i++)
	{
		int znak;
		
		znak = rand()%2;
		if(znak == 0)
		znak = -1;
		A[i] = (rand()%100) * znak; // Wypełniliśmy pierwszą macierz wartościami losowymi

		znak = rand()%2;
		if(znak == 0)
		znak = -1;
		B[i] = (rand()%100) * znak; // Wypełniliśmy drugąmacierz wartościami losowymi
	}

	//Wypisywanie macierzy
	printf("\nMacierz A:\n");
	for(int i=0; i<wymiar; i++)
	{
		for(int j=0; j<wymiar; j++)
		{
			printf("%d ", A[wymiar*i + j]);
		}
		printf("\n");
	}
	printf("\nMacierz B:\n");
	for(int i=0; i<wymiar; i++)
	{
		for(int j=0; j<wymiar; j++)
		{
			printf("%d ", B[wymiar*i + j]);
		}
		printf("\n");
	}

	int st2 = sleepingTime/2;
	printf("\nZa %d sekundy rozpocznie sie obliczanie mnozenia macierzy A*B na %d watkach...\n",st2, iloscWatkow);
	sleep(st2);
	/*
	//Obliczanie wynikowej macierzy bez watkow
	for(int x=0; x<wymiar*wymiar; x++)
	{
		int wiersz = x/wymiar;
		int kolumna = x%wymiar;
		int suma = 0;
		printf("[%d,%d] = ", wiersz, kolumna);

		for(int i=0; i<wymiar; i++)
		{
			int a = A[wiersz*wymiar+i];
			int b = B[i*wymiar+kolumna];
			
			printf("%d*%d", a, b);
			suma = suma + a*b;

			if(i < wymiar-1)
			printf(" + ");
		}

		printf(" = %d\n", suma);
		C[x] = suma;
	}*/
	
	//Tworzenie watkow
	pthread_t th[iloscWatkow];
	int id[iloscWatkow];
	for(int i=0; i<iloscWatkow; i++)
	{
		id[i] = i;
		pthread_create(&th[i], NULL, calculate, &id[i]); //tworzymy wątki
	}
	
	for(int i=0; i<iloscWatkow; i++)
	{
		pthread_join(th[i], NULL); //oczekujemy na zakonczenie watkow
	}
	
	sleep(sleepingTime);
	//Wypisywanie macierzy wynikowej C
	printf("\nMacierz C (wynik mnozenia):\n");
	for(int i=0; i<wymiar; i++)
	{
		for(int j=0; j<wymiar; j++)
		{
			printf("%d ", C[wymiar*i + j]);
		}
		printf("\n");
	}
	
	return 0;
}
