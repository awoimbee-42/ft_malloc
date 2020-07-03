#include <tests.h>
#include <dlfcn.h>
#include <unistd.h>

const char* str16 = "Proin consequat";
const char* str64 = "Sed ac posuere dui. Etiam fermentum libero nec eleifend nullam.";
const char* str128 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus gravida eu est sit amet euismod. Duis sapien nibh turpis duis.";
const char* str512 = "Aliquam erat volutpat. Aliquam nibh massa, lobortis sit amet vehicula et, imperdiet vel odio. Sed pharetra vel magna vitae ultricies. Fusce euismod elementum commodo. Aliquam malesuada vel lectus at dictum. Donec pharetra tortor quis neque vulputate, ut luctus diam dapibus. Nam gravida lorem posuere, volutpat lacus aliquet, suscipit erat. Vestibulum euismod varius tortor vitae auctor. Sed sed imperdiet enim, id sodales nunc. Vestibulum eget faucibus lorem, at fermentum diam. Proin sodales ligula non metus.";

void	print_time_delta(struct timespec *t)
{
	struct timespec t1;

	clock_gettime(CLOCK_MONOTONIC, &t1);

	float telapsed = ((t1.tv_sec - t->tv_sec) * 1e3)
					+ ((t1.tv_nsec - t->tv_nsec) / 1e6);
	printf("--> %4.0fms\n", telapsed);
	*t = t1;
}

int		main(int argc, char* argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;

	srandom(time(NULL));
	struct timespec	t;
	clock_gettime(CLOCK_MONOTONIC, &t);

	// write(1, "test_01_basic\n", 14);
	// test_01_basic();
	// print_time_delta(&t);
	// write(1, "test_02_lots_basic\n", 19);
	// test_02_lots_basic();
	// print_time_delta(&t);
	// write(1, "test_03_lots_cumulate\n", 22);
	// test_03_lots_cumulate();
	// print_time_delta(&t);
	write(1, "test_04_realloc\n", 16);
	test_04_realloc();
	print_time_delta(&t);
	write(1, "test_05_multithread\n", 20);
	test_05_multithread();
	print_time_delta(&t);

	return 0;
}
