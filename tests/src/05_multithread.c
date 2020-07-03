#include "tests.h"
#include <pthread.h>
#include <time.h>

void	malloc_lots_cumulate_mixed_multithread() {
	#define TRIES		6
	#define NB			800
	#define INT_THIRD	(__INT32_MAX__ / 3)

	char*			ptr[NB];
	size_t			alloc_size[NB];

	for (int seed = 0; seed < TRIES; seed++) {
		srandom(time(NULL));
		for (int i = 0; i < NB; i++) {
			alloc_size[i] = random();
			int mask = random();
			if (mask > INT_THIRD * 2)
				alloc_size[i] = i;
			else if (mask < INT_THIRD)
				alloc_size[i] = 2000 - i;
			alloc_size[i] %= 2000000LU;
			ptr[i] = malloc(alloc_size[i]);
			if (ptr[i])
				memset(ptr[i], 99, alloc_size[i]);
		}
		for (int i = 0; i < NB; i++) {
			if (ptr[i])
				for (size_t k=0; k<alloc_size[i]; k++) {assert(ptr[i][k] == 99);}
			free(ptr[i]);
		}
	}
}

void		launch_fn(size_t threads, void *fn)
{
	pthread_t	t[threads]; // YOLO VLA

	for (size_t i = 0; i < threads; i++)
		pthread_create(&t[i], NULL, (void*(*)(void*))fn, NULL);
	for (size_t i = 0; i < threads; i++)
		pthread_join(t[i], NULL);
}

void		test_05_multithread(void)
{
	free_all();
	write(1, "10 threads: malloc_lots_cumulate_mixed...\n", 42);
	launch_fn(10, malloc_lots_cumulate_mixed);
	// free_all();
	write(1, "10 threads: realloc_basic...\n", 29);
	launch_fn(10, realloc_basic);
	write(1, "fucj\n", 5);
	malloc_basic_small();
}


