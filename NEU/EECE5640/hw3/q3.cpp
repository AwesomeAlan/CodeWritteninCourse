#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#define NO_PHILO 5
#define NO_CHOPS 5

omp_lock_t writelock[NO_CHOPS];

void think(int i)
{
	printf("philosopher %d is thinking...\n", i);
	sleep(1 + (rand() % NO_PHILO));
}

void eat(int i)
{
	printf("philosopher %d is hungry...\n", i);

	if (i == NO_PHILO - 1)
	{
		omp_set_lock(&writelock[i]);
			printf("----philosopher %d took left fork...\n", i);
			omp_set_lock(&writelock[0]);
				printf("----philosopher %d took right fork...\n", i);
				printf("----philosopher %d is eating...\n", i);
				sleep(2);
				printf("----philosopher %d finished eating -> releases forks \n", i);
			omp_unset_lock(&writelock[0]);
		omp_unset_lock(&writelock[i]);
	}
	else 
	{
		omp_set_lock(&writelock[i]);
			printf("----philosopher %d took left fork...\n", i);
			omp_set_lock(&writelock[i + 1]);
				printf("----philosopher %d took left fork...\n", i);
				printf("----philosopher %d is eating...\n", i);
				sleep(2);
				printf("----philosopher %d finished eating -> releases forks \n", i);
			omp_unset_lock(&writelock[i + 1]);
		omp_unset_lock(&writelock[i]);
	}
}

void philosophize(int i)
{
	while (true)
	{
		think(i);
		eat(i);
	}
}

int  main()
{
	omp_set_num_threads(NO_PHILO);

	int i;

	for (i = 0; i < NO_PHILO; i++)
	{
		omp_init_lock(&writelock[i]);
	}	

	#pragma omp parallel for private(i)
	for (i = 0; i < NO_PHILO; i++)
	{
		philosophize(i);
	}

	getchar();
	return 0;
}