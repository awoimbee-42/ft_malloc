#include <tests.h>
#include <dlfcn.h>
#include <unistd.h>

const char* str16 = "Proin consequat";
const char* str64 = "Sed ac posuere dui. Etiam fermentum libero nec eleifend nullam.";
const char* str128 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus gravida eu est sit amet euismod. Duis sapien nibh turpis duis.";
const char* str512 = "Aliquam erat volutpat. Aliquam nibh massa, lobortis sit amet vehicula et, imperdiet vel odio. Sed pharetra vel magna vitae ultricies. Fusce euismod elementum commodo. Aliquam malesuada vel lectus at dictum. Donec pharetra tortor quis neque vulputate, ut luctus diam dapibus. Nam gravida lorem posuere, volutpat lacus aliquet, suscipit erat. Vestibulum euismod varius tortor vitae auctor. Sed sed imperdiet enim, id sodales nunc. Vestibulum eget faucibus lorem, at fermentum diam. Proin sodales ligula non metus.";

int		main(int argc, char* argv[], char *envp[])
{
	srandom(time(NULL));

	test_01_basic();
	test_02_lots_basic();
	test_03_lots_cumulate();
	test_04_realloc();

	return 0;
}
