#include <iostream>
#include "MatrixSolver.h"

int main()
{
    namespace ublas = boost::numeric::ublas;
    const ublas::matrix<double> matrixA(ublas::identity_matrix<double>(5));
    const ublas::matrix<double> matrixB(ublas::identity_matrix<double>(5));

    const design_pattern::CachedLinearEquationSolver solver(matrixA);

    std::cout << solver(matrixB) << std::endl;

    return 0;
}