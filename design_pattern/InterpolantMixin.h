#ifndef INTERPOLANTMIXIN_H_INCLUDED
#define INTERPOLANTMIXIN_H_INCLUDED

#include <limits>
#include <boost/shared_ptr.hpp>
#include "fwd.h"
#include "Interpolant.h"

namespace design_pattern {

    template <typename Base>
    class LogMixin : public Base {
    public:
        virtual ~LogMixin() {}

        virtual const double operator()(const double x) const
        {
            return std::exp(Base::operator()(x));
        }

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas)
        {
            ublas::vector<double> logOrdinates(ordinates.size(), 0.0);
            for (std::size_t i = 0; i < ordinates.size(); ++i) {
                logOrdinates(i) = std::log(ordinates(i));
            }
            Base::init(logOrdinates, abscissas);
        }
    };

    template <typename Base>
    class BothConstantExtrapolateMixin : public Base {
    public:
        virtual ~BothConstantExtrapolateMixin() {}

        virtual const double operator()(const double x) const
        {
            if (x < _minAbscissa) {
                return _minOrdinate;
            }
            if (x > _maxAbscissa) {
                return _maxOrdinate;
            }
            return Base::operator()(x);
        }

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas)
        {
            _maxOrdinate = ordinates(ordinates.size() - 1);
            _maxAbscissa = abscissas(abscissas.size() - 1);
            _minOrdinate = ordinates(0);
            _minAbscissa = abscissas(0);

            Base::init(ordinates, abscissas);
        }
    private:
        double _maxOrdinate;
        double _maxAbscissa;
        double _minOrdinate;
        double _minAbscissa;
    };
}

#endif // INTERPOLANTMIXIN_H_INCLUDED