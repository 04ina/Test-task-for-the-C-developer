/*-------------------------------------------------------------------------
 *
 * test_quadratic_equation.c
 *  Тестирование модуля quadratic_equation
 *
 * IDENTIFICATION
 *    .../test/test_quadratic_equation.c
 * 
 *-------------------------------------------------------------------------
 */

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "quadratic_equation.h"

void
test_solve_equation(void);

char *tracefile = NULL;
FILE *trace = NULL;

/* Округление до миллионных для сравнения double-ов*/
#define RD(value) \
    ((round(value * 1000000))/1000000)

/* 
 * Запись доп. информации в trace
 */ 
#define PRINT_TRACE(header_text, ...)   \
    fprintf(trace, header_text);        \
    fputc('\n', trace);                 \
    fprintf(trace, __VA_ARGS__);        \
    fputc('\n', trace);

#define ADDITIONAL_INFO(...) \
    PRINT_TRACE("Additional info: ", __VA_ARGS__);

#define INPUT_VALUES(...)                         \
    fprintf(trace, "\nTEST %d\n", TestCounter);   \
    if (TestResult) fprintf(trace, "OK\n");       \
    else fprintf(trace, "ERROR\n");               \
    PRINT_TRACE("input: ", __VA_ARGS__);

#define OUTPUT_VALUES(...) \
    PRINT_TRACE("output: ", __VA_ARGS__);

#define EXPECTED_VALUES(...) \
    PRINT_TRACE("expected: ", __VA_ARGS__)      

/*
 * Проверка на равенство значений и вывод результата теста 
 */
#define TEST(_func, ...)                        \
    func_return = _func;                        \
    printf("TEST %d\n", TestCounter);           \
    TestResult = (__VA_ARGS__);                 \
    if (TestResult)                             \
        printf("OK\n");                         \
    else                                        \
        printf("ERROR\n");
    

int
main(int argc, char **argv)
{
    int     c;

	while ((c = getopt(argc, argv, "t:")) != -1)
	{
		switch (c)
		{
			case 't':			/* trace file */
				tracefile = strdup(optarg);
				break;
		}
	}

	
	
	/* Set the trace file, if requested */
	if (tracefile != NULL)
	{
		trace = fopen(tracefile, "w");
		if (trace == NULL)
		{
			fprintf(stderr, "could not open file \"%s\"", tracefile);
			return 0;
		}
            		
	}
	else
	{
		fprintf(stderr, "missing required argument \"-t\"");
		return 0;
	}
	
    
    test_solve_equation();

    fclose(trace);

	return 0;
}

void
test_solve_equation(void)
{
    int TestCounter = 1; 
    int TestResult = 0;

    int func_return = 0;
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;

    double ex_x1 = 0, ex_x2 = 0;
    int ex_func_return = 0;

    /********************* test 1 *********************/
    a = -1, b = 0, c = 4; 
    ex_x1 = -2, ex_x2 = 2, ex_func_return = QES_TwoSolution; 
    TEST 
    (
        solve_equation(&x1, &x2, a, b, c),
        RD(x1) == RD(ex_x1) && RD(x2) == RD(ex_x2) &&
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%lf b=%lf c=%lf", a, b, c);
    OUTPUT_VALUES("x1=%lf x2=%lf QEState=%d", x1, x2, func_return);
    EXPECTED_VALUES("x1=%lf x2=%lf QEState=%d", ex_x1, ex_x2, ex_func_return);   
    TestCounter++;

    /********************* test 2 *********************/
    a = -1, b = 0, c = 6; 
    ex_x1 = -2.449489743, ex_x2 = 2.449489743, ex_func_return = QES_TwoSolution; 
    TEST 
    (
        solve_equation(&x1, &x2, a, b, c),
        RD(x1) == RD(ex_x1) && RD(x2) == RD(ex_x2) &&
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%lf b=%lf c=%lf", a, b, c);
    OUTPUT_VALUES("x1=%lf x2=%lf QEState=%d", x1, x2, func_return);
    EXPECTED_VALUES("x1=%lf x2=%lf QEState=%d", ex_x1, ex_x2, ex_func_return);   
    TestCounter++;

    /********************* test 3 *********************/
    a = 0, b = 0, c = 0; 
    ex_func_return = QES_InfSolution; 
    TEST 
    (
        solve_equation(&x1, &x2, a, b, c),
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%lf b=%lf c=%lf", a, b, c);
    OUTPUT_VALUES("QEState=%d", func_return);
    EXPECTED_VALUES("QEState=%d", ex_func_return);   
    TestCounter++;

    /********************* test 4 *********************/
    a = 2, b = 2, c = 2; 
    ex_func_return = QES_NoSolution; 
    TEST 
    (
        solve_equation(&x1, &x2, a, b, c),
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%lf b=%lf c=%lf", a, b, c);
    OUTPUT_VALUES("QEState=%d", func_return);
    EXPECTED_VALUES("QEState=%d", ex_func_return);   
    TestCounter++;

    /********************* test 5 *********************/
    a = -4.9, b = 0, c = 0; 
    ex_x1 = 0, ex_x2 = 0, ex_func_return = QES_OneSolution; 
    TEST 
    (
        solve_equation(&x1, &x2, a, b, c),
        RD(x1) == RD(ex_x1) && RD(x2) == RD(ex_x2) &&
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%lf b=%lf c=%lf", a, b, c);
    OUTPUT_VALUES("x1=%lf x2=%lf QEState=%d", x1, x2, func_return);
    EXPECTED_VALUES("x1=%lf x2=%lf QEState=%d", ex_x1, ex_x2, ex_func_return);   
    TestCounter++;

    /********************* test 6 *********************/
    a = 1, b = 1, c = -0.7; 
    ex_x2 = 0.474679435, ex_func_return = QES_TwoSolution; 
    TEST 
    (
        solve_equation(NULL, &x2, a, b, c),
        RD(x2) == RD(ex_x2) &&
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%lf b=%lf c=%lf", a, b, c);
    OUTPUT_VALUES("x1=%lf x2=%lf QEState=%d", x1, x2, func_return);
    EXPECTED_VALUES("x1=%lf x2=%lf QEState=%d", ex_x1, ex_x2, ex_func_return);   
    ADDITIONAL_INFO("Тест на наличие NULL значения вместо указателя на первый корень");
    TestCounter++;

    /********************* test 7 *********************/
    a = 1e+40, b = 0, c = 1e-40; 
    ex_func_return = QES_NoSolution; 
    TEST 
    (
        solve_equation(&x1, &x2, a, b, c),
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%e b=%e c=%e", a, b, c);
    OUTPUT_VALUES("QEState=%d", func_return);
    EXPECTED_VALUES("QEState=%d", ex_func_return);   
    TestCounter++;

    /********************* test 8 *********************/
    a = 1e+40, b = 0, c = -1e-40; 
    ex_x1 = -1e-40, ex_x2 = 1e-40, ex_func_return = QES_TwoSolution; 
    TEST 
    (
        solve_equation(&x1, &x2, a, b, c),
        x1 == ex_x1 && x2 == ex_x2 &&
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%e b=%e c=%e", a, b, c);
    OUTPUT_VALUES("x1=%e x2=%e QEState=%d", x1, x2, func_return);
    EXPECTED_VALUES("x1=%e x2=%e QEState=%d", ex_x1, ex_x2, ex_func_return);   
    TestCounter++;

    /********************* test 9 *********************/
    a = INFINITY, b = NAN, c = 0; 
    ex_func_return = QES_ERROR; 
    TEST 
    (
        solve_equation(&x1, &x2, a, b, c),
        func_return == ex_func_return
    )
    INPUT_VALUES("a=%e b=%e c=%e", a, b, c);
    OUTPUT_VALUES("QEState=%d", func_return);
    EXPECTED_VALUES("QEState=%d", ex_func_return);   
    TestCounter++;

    printf("\nДетали можно посмотреть в директории test/traces\n");
}
