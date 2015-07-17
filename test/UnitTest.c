#include <stdio.h>
#include "UnitTest.h"

/**
 * Define the Unit Tests
 */
int tests_ran = 0;

int assertTrue(char *message, int valid) {
	tests_ran++;

	if(!valid) {
		printf("  ** ERROR: %s\n", message);
	}
	return valid;
}

int assertFalse(char *message, int valid) {
	return assertTrue(message, !valid);
}

/**
 * Test all
 */
static int all_tests() {
	int i, success = 0;
	int nb = getNumberTest();
	char *list[nb];
	UnitTestFunction tests[nb];

	printf("\nTesting %d functions:\n\n", nb);

	getUnitTest(tests, list);

	for(i = 0; i < nb; i++) {
		printf("	Testing : %s\n", list[i]);
		success += tests[i]();
	}

	return success;
}

/**
 * See if this work
 */
void main() {
	int result = all_tests();
	printf("\n\nTests ran: %d\n", tests_ran);

	if (result != tests_ran) {
		printf("Tests passed: %d\n", result);
		printf("Tests failed: %d\n", tests_ran-result);
	}
	else {
		printf("\n** ALL TESTS PASSED **\n");
	}
	printf("\n");
}
