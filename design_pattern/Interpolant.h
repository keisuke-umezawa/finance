#ifndef INTERPOLANT_H_INCLUDED
#define INTERPOLANT_H_INCLUDED

#include <limits>
#include <boost/shared_ptr.hpp>
#include "fwd.h"

namespace design_pattern {

    class Interpolant {
    public:
        virtual ~Interpolant() {}

        boost::shared_ptr<Interpolant> clone() const
        {
            return boost::shared_ptr<Interpolant>(this->doClone());
        }

        virtual const double operator()(const double x) const = 0;

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas) = 0;
    
    private:
        virtual Interpolant* doClone() const = 0;
    };

    class LinearInterpolant : public Interpolant {
    public:
        virtual ~LinearInterpolant() {}

        virtual const double operator()(const double x) const;

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas);

    private:
        virtual LinearInterpolant* doClone() const;

    private:
        ublas::vector<double> _ordinates;
        ublas::vector<double> _abscissas;
    };
        
}

#endif // INTERPOLANT_H_INCLUDED