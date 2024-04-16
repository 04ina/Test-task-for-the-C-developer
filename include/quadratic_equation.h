/*-------------------------------------------------------------------------
 *
 * quadratic_equation.h
 *    Решение квадратных уравнений  
 *
 * IDENTIFICATION
 *    .../quadratic_equation.h
 * 
 *-------------------------------------------------------------------------
 */

#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H 

#include <math.h>
#include <stddef.h>

/*
 * Перечисление, определяющее состояние решения квадратного уравнения
 */
typedef enum 
{
    QES_OneSolution,
    QES_TwoSolution,
    QES_NoSolution,
    QES_InfSolution
} QEState;

int
solve_equation(double *Sol1, double *Sol2, double a, double b, double c);

#endif  /* QUADRATIC_EQUATION_H */
