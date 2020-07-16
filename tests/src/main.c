#include <tests.h>
#include <dlfcn.h>
#include <unistd.h>

const char* str16 = "Proin consequat";
const char* str64 = "Sed ac posuere dui. Etiam fermentum libero nec eleifend nullam.";
const char* str128 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus gravida eu est sit amet euismod. Duis sapien nibh turpis duis.";
const char* str512 = "Aliquam erat volutpat. Aliquam nibh massa, lobortis sit amet vehicula et, imperdiet vel odio. Sed pharetra vel magna vitae ultricies. Fusce euismod elementum commodo. Aliquam malesuada vel lectus at dictum. Donec pharetra tortor quis neque vulputate, ut luctus diam dapibus. Nam gravida lorem posuere, volutpat lacus aliquet, suscipit erat. Vestibulum euismod varius tortor vitae auctor. Sed sed imperdiet enim, id sodales nunc. Vestibulum eget faucibus lorem, at fermentum diam. Proin sodales ligula non metus.";

const char *yolo_itoa(unsigned long i)
{
	static char buff[17];
	int j = 15;
	for (; i != 0; --j, i /= 10) { buff[j] = (i % 10) + '0'; }
	for (; j != -1; --j) { buff[j] = ' '; }
	return buff;
}

void	print_time_delta(struct timespec *t)
{
	struct timespec t1;

	clock_gettime(CLOCK_MONOTONIC, &t1);
	unsigned long telapsed = ((t1.tv_sec - t->tv_sec) * 1000)
					+ ((t1.tv_nsec - t->tv_nsec) / 1000000);
	write(1, "--> ", 4);
	write(1, yolo_itoa(telapsed), 16);
	write(1, " ms\n", 4);
	*t = t1;
}

int		main(int argc, char* argv[], char *envp[])
{
	(void)envp;

	if (argc == 2)
	{
		if (argv[1][0] == '1')
			test_01_basic();
		else if (argv[1][0] == '2')
			test_02_lots_basic();
		else if (argv[1][0] == '3')
			test_03_lots_cumulate();
		else if (argv[1][0] == '4')
			test_04_realloc();
		else if (argv[1][0] == '5')
			test_05_multithread();
		else
			write(1, "input 1-5 to run according test\n", 32);
		return 0;
	}

	srandom(time(NULL));
	struct timespec	t;
	clock_gettime(CLOCK_MONOTONIC, &t);

	write(1, "test_01_basic\n", 14);
	test_01_basic();
	print_time_delta(&t);
	write(1, "test_02_lots_basic\n", 19);
	test_02_lots_basic();
	print_time_delta(&t);
	write(1, "test_03_lots_cumulate\n", 22);
	test_03_lots_cumulate();
	print_time_delta(&t);
	write(1, "test_04_realloc\n", 16);
	test_04_realloc();
	print_time_delta(&t);
	write(1, "test_05_multithread\n", 20);
	test_05_multithread();
	print_time_delta(&t);

	return 0;
}
