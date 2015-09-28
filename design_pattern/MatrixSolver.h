#ifndef MATRIXSOLVER_H_INCLUDED
#define MATRIXSOLVER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "fwd.h"

namespace design_pattern {

    class IMatrixSolver {
    public:
        virtual ~IMatrixSolver() {}

        virtual std::size_t size() const = 0;

        virtual ublas::matrix<double> operator()(
            const ublas::matrix<double>& matrix) const = 0;
    };

    // solve A * X = B
    class LinearEquationSolver : public IMatrixSolver {
    public:
        LinearEquationSolver(const ublas::matrix<double>& matrixA)
        : _size(matrixA.size1()), _matrixA(matrixA)
        {
        }

        virtual ~LinearEquationSolver() {}

        virtual std::size_t size() const
        {
            return _size;
        }

        virtual ublas::matrix<double> operator()(
            const ublas::matrix<double>& matrixB) const
        {
            ublas::matrix<double> result(this->size(), this->size(), 0.0);
            
            // TODO gauss-jordan elimination
            
            return result;
        }

    private:
        std::size_t _size;
        ublas::matrix<double> _matrixA;
    };

    class CachedLinearEquationSolver : public IMatrixSolver {
    public:
        CachedLinearEquationSolver(const ublas::matrix<double>& matrixA)
        : _calculatorPtr(
            boost::make_shared<LinearEquationSolver>(matrixA))
        {
            _inverseMatrix = (*_calculatorPtr)(
                ublas::identity_matrix<double>(matrixA.size1()));
        }

        virtual ~CachedLinearEquationSolver() {}

        virtual std::size_t size() const
        {
            return _calculatorPtr->size();
        }

        virtual ublas::matrix<double> operator()(
            const ublas::matrix<double>& matrixB) const
        {
            return ublas::prod(_inverseMatrix, matrixB);
        }

    private:
        boost::shared_ptr<LinearEquationSolver> _calculatorPtr;
        ublas::matrix<double> _inverseMatrix;
    };
}

#endif // MATRIXSOLVER_H_INCLUDED