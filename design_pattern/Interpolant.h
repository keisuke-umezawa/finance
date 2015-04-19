#ifndef INTERPOLANT_H_INCLUDED
#define INTERPOLANT_H_INCLUDED

#include "Fwd.h"
#include <limits>
#include <boost/shared_ptr.hpp>

namespace design_pattern {

    class Interpolant {
    public:
        virtual ~Interpolant() {}

        boost::shared_ptr<Interpolant> clone() const
        {
            return boost::shared_ptr<Interpolant>(doClone());
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

        virtual const double operator()(const double x) const
        {
            double previousAbscissa = std::numeric_limits<double>::min();
            double previousOrdinate = _ordinates(0);
            for (std::size_t i = 0; i < _abscissas.size(); ++i) {
                if (x < _abscissas(i)) {
                    return previousOrdinate 
                        + (_ordinates(i) - previousOrdinate) * (x - previousAbscissa)
                            / (_abscissas(i) - previousAbscissa);
                }
                previousAbscissa = _abscissas(i);
                previousOrdinate = _ordinates(i);
            }
            return _ordinates(_ordinates.size() - 1);
        }

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas)
        {
            _ordinates = ordinates;
            _abscissas = abscissas;
        }

    private:
        virtual LinearInterpolant* doClone() const
        {
            return new LinearInterpolant(*this);
        }

    private:
        ublas::vector<double> _ordinates;
        ublas::vector<double> _abscissas;
    };
        
}

#endif // INTERPOLANT_H_INCLUDED