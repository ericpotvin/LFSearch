/* UnitTest */
typedef int (*UnitTestFunction)(void);

extern int tests_ran;

int assertTrue(char * message, int valid);

int assertFalse(char * message, int valid);

