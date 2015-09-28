#include <boost/shared_ptr.hpp>
#include "InterpolantDecorator.h"

namespace design_pattern {
    void LogInterpolantDecorator::init(
        const ublas::vector<double>& ordinates,
        const ublas::vector<double>& abscissas)
    {
        ublas::vector<double> logOrdinates(ordinates.size(), 0.0);
        for (std::size_t i = 0; i < ordinates.size(); ++i) {
            logOrdinates(i) = std::log(ordinates(i));
        }
        InterpolantDecorator::init(logOrdinates, abscissas);
    }

    LogInterpolantDecorator* LogInterpolantDecorator::doClone() const
    {
        return new LogInterpolantDecorator(*this);
    }


    void ExpInterpolantDecorator::init(
        const ublas::vector<double>& ordinates,
        const ublas::vector<double>& abscissas)
    {
        ublas::vector<double> expOrdinates(ordinates.size(), 0.0);
        for (std::size_t i = 0; i < ordinates.size(); ++i) {
            expOrdinates(i) = std::exp(ordinates(i));
        }
        InterpolantDecorator::init(expOrdinates, abscissas);
    }

    ExpInterpolantDecorator* ExpInterpolantDecorator::doClone() const
    {
        return new ExpInterpolantDecorator(*this);
    }

    MaxInterpolantDecorator* MaxInterpolantDecorator::doClone() const
    {
        return new MaxInterpolantDecorator(*this);
    }

}

namespace design_pattern {

    const double ConstantExtrapolationDecorator::operator()(const double x) const
    {
        if (x < _minAbscissa) {
            return _minOrdinate;
        }
        if (x > _maxAbscissa) {
            return _maxOrdinate;
        }
        return InterpolantDecorator::operator()(x);
    }

    void ConstantExtrapolationDecorator::init(
        const ublas::vector<double>& ordinates,
        const ublas::vector<double>& abscissas)
    {
        _maxOrdinate = ordinates(ordinates.size() - 1);
        _maxAbscissa = abscissas(abscissas.size() - 1);
        _minOrdinate = ordinates(0);
        _minAbscissa = abscissas(0);

        InterpolantDecorator::init(ordinates, abscissas);
    }

    ConstantExtrapolationDecorator* ConstantExtrapolationDecorator::doClone() const
    {
        return new ConstantExtrapolationDecorator(*this);
    }

}