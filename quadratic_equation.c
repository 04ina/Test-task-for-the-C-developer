/*-------------------------------------------------------------------------
 *
 * quadratic_equation.c
 *    Решение квадратных уравнений  
 *
 * IDENTIFICATION
 *    .../quadratic_equation.c
 * 
 *-------------------------------------------------------------------------
 */

#include "quadratic_equation.h"

/*
 * solve_equation решает квадратные уравнения в вещественных числах
 * 
 * Входные параметры:
 * 1. указатели на переменные, в которые будет записан ответ.
 * 
 *    Если у уравнения несколько корней, то они запишутся в Sol1 и Sol2 в 
 *    возрастающем порядке.
 * 
 *    Можно указать NULL вместо аргументов Sol1 и Sol2, в таком случае мы 
 *    просто не получим корни уравнения. 
 *
 * 2. коэффициенты квадратного уравнения a, b и c
 *     
 * Возвращает состояние решения квадратного уравнения. 
 * Перечисление с состояниями QEState можно смотреть в quadratic_equation.h 
 *
 * Если аргументы или возвращаемые значения будут являться inf или nan,
 * функция вернет QES_ERROR 
 */
int
solve_equation(double *Sol1, double *Sol2, double a, double b, double c)
{
    double SwapBuf;
    double discriminant = 0;
    double x1 = 0;
    double x2 = 0;
   
    if (isfinite(a) == 0 || isfinite(b) == 0 || isfinite(c) == 0)
        return QES_ERROR;

    /* Бесконечное число решений */
    if (a == 0 && b == 0 && c == 0)
        return QES_InfSolution;

    /* Нет решений*/
    if (a == 0 && b == 0 && c != 0)
        return QES_NoSolution;

    /*
     * Вычисление ответа
     */
    discriminant = b * b - (4 * a * c);

    if (discriminant > 0)
    {
        /* Два разных корня */
        x1 = (- b - sqrt(discriminant)) / (2 * a);
        x2 = (- b + sqrt(discriminant)) / (2 * a);

        if (x1 > x2)
        {
            SwapBuf = x1;
            x1 = x2; 
            x2 = SwapBuf;
        }
    } 
    else if (discriminant == 0)
    {
        /* Два одинаковых корня */
        x1 = - b / (2 * a);
        x2 = x1;
    }
    else 
    {
        /* Нет корней */
        return QES_NoSolution;
    }

    if (isfinite(x1) == 0 || isfinite(x2) == 0)
        return QES_ERROR;

    if (Sol1 != NULL)
        *Sol1 = x1;  

    if (Sol2 != NULL)
        *Sol2 = x2;

    if (x1 == x2)
        return QES_OneSolution;
    else 
        return QES_TwoSolution;
}
