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

int		main(int argc, char** argv)
{
	SRunner	*sr;
	int		nf;

	if (argc == 1)
	{
		fprintf(stderr, "Usage: %s <custom_malloc_lib>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// load dyn lib
	void* lib_handle = dlopen(argv[1], RTLD_LAZY);
	if (lib_handle == NULL)
	{
		fprintf(stderr, "Failed to open libmalloc (%s)\n", argv[1]);
		return (EXIT_FAILURE);
	}
	my_malloc = dlsym(lib_handle, "malloc");
	my_free = dlsym(lib_handle, "free");
	my_realloc = dlsym(lib_handle, "realloc");
	my_print_allocs = dlsym(lib_handle, "print_allocs");

	srandom(time(NULL));
	sr = srunner_create(suite_create(""));

	srunner_add_suite(sr, build_suite_01_basic());
	srunner_add_suite(sr, build_suite_02_lots_basic());

	srunner_run_all(sr, CK_ENV);
	nf = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (nf == 0 ? 0 : 1);
}
