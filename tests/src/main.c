#include <tests.h>

int		main(void)
{
	SRunner	*sr;
	int		nf;

	printf(PRTF_GRN "Testing malloc..." PRTF_EOC "\n");
	srandom(time(NULL));
	sr = srunner_create(suite_create(""));

	srunner_add_suite(sr, build_suite_01_basic());

	srunner_run_all(sr, CK_ENV);
	nf = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (nf == 0 ? 0 : 1);
}
