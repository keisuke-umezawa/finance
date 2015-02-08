#ifndef FINANCE_IMODEL_H_INCLUDED
#define FINANCE_IMODEL_H_INCLUDED

#include <complex>
#include <iostream>
#include <boost/function.hpp>
#include <boost/shard_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace finance {
    namespace ublas = boost::numeric::ublas;
    typedef boost::gregorian::date date_type;

    ublas::vector<std::complex<double> >
        fft(ublas::vector<std::complex<double> > x);

    class IFourierTransformSolver {
    public:
        virtual ~IFourierTransformSolver() {}

        ublas::vector<double> solve(
                const double spot, 
                const double upperStrike,
                const std::size_t numberOfDivisionPower) const;
    private:
        virtual IFourierTransformSolver* doClone() const = 0;
        virtual ublas::vector<double> doSolve(
                const double spot, 
                const double upperStrike,
                const std::size_t numberOfDivisionPower) 
                const = 0;
    };
} // namespace finance

#endif // FINANCE_IMODEL_H_INCLUDED
