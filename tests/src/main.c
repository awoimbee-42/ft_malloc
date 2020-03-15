#include <tests.h>
#include <dlfcn.h>
#include <unistd.h>

void*(*my_malloc)(size_t);
void(*my_free)(void*);
void*(*my_realloc)(void*, size_t);
void(*my_print_allocs)(void);
const char* str16 = "Proin consequat";
const char* str64 = "Sed ac posuere dui. Etiam fermentum libero nec eleifend nullam.";
const char* str128 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus gravida eu est sit amet euismod. Duis sapien nibh turpis duis.";
const char* str512 = "Aliquam erat volutpat. Aliquam nibh massa, lobortis sit amet vehicula et, imperdiet vel odio. Sed pharetra vel magna vitae ultricies. Fusce euismod elementum commodo. Aliquam malesuada vel lectus at dictum. Donec pharetra tortor quis neque vulputate, ut luctus diam dapibus. Nam gravida lorem posuere, volutpat lacus aliquet, suscipit erat. Vestibulum euismod varius tortor vitae auctor. Sed sed imperdiet enim, id sodales nunc. Vestibulum eget faucibus lorem, at fermentum diam. Proin sodales ligula non metus.";

void print_allocs2(void)
{
	write(1, "my_print_allocs is not available while using systems malloc\n", 60);
}

static void usage(char *pname)
{
	fprintf(stderr, "Usage: %s <custom_malloc_lib>\n", pname);
	exit(EXIT_FAILURE);
}

static void *load_lib(char *libpath)
{
	void *lib_handle = dlopen(libpath, RTLD_LAZY);
	if (lib_handle == NULL)
	{
		fprintf(stderr, "Failed to open libmalloc (%s)\n", libpath);
		exit(EXIT_FAILURE);
	}
	if (1)
	{
		my_malloc = dlsym(lib_handle, "malloc");
		my_free = dlsym(lib_handle, "free");
		my_realloc = dlsym(lib_handle, "realloc");
		my_print_allocs = dlsym(lib_handle, "print_allocs");
	}
	else
	{
		my_malloc = malloc;
		my_free = free;
		my_realloc = realloc;
		my_print_allocs = print_allocs2;
	}

	return (lib_handle);
}

int		main(int argc, char** argv)
{
	SRunner	*sr;
	int		nf;

	if (argc == 1)
		usage(argv[0]);
	void *ld_handle = load_lib(argv[1]);

	srandom(time(NULL));
	sr = srunner_create(suite_create(""));

	srunner_add_suite(sr, build_suite_01_basic());
	srunner_add_suite(sr, build_suite_02_lots_basic());
	srunner_add_suite(sr, build_suite_03_lots_cumulate());

	srunner_run_all(sr, CK_ENV);
	nf = srunner_ntests_failed(sr);
	srunner_free(sr);
	dlclose(ld_handle);

	return (nf == 0 ? 0 : 1);
}
