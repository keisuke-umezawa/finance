#ifndef INTERPOLANTDECORATOR_H_INCLUDED
#define INTERPOLANTDECORATOR_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include "fwd.h"
#include "Interpolant.h"

namespace design_pattern {

    class InterpolantDecorator : public Interpolant {
    public:
        InterpolantDecorator(boost::shared_ptr<Interpolant>& interpolantPtr)
        : _interpolantPtr(interpolantPtr->clone())
        {
        }

        virtual ~InterpolantDecorator() {}

        virtual const double operator()(const double x) const
        {
            return (*_interpolantPtr)(x);
        }

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas)
        {
            _interpolantPtr->init(ordinates, abscissas);
        }

    private:
        virtual InterpolantDecorator* doClone() const = 0;

    private:
        boost::shared_ptr<Interpolant> _interpolantPtr;
    };
}

namespace design_pattern {
    class LogInterpolantDecorator : public InterpolantDecorator {
    public:
        LogInterpolantDecorator(
            const boost::shared_ptr<Interpolant>& interpolantPtr)
        : InterpolantDecorator(interpolantPtr->clone())
        {
        }

        virtual ~LogInterpolantDecorator() {}

        virtual const double operator()(const double x) const
        {
            return std::exp(InterpolantDecorator::operator()(x));
        }

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas);

    private:
        virtual LogInterpolantDecorator* doClone() const;        
    };

    class ExpInterpolantDecorator : public InterpolantDecorator {
    public:
        ExpInterpolantDecorator(
            const boost::shared_ptr<Interpolant>& interpolantPtr)
        : InterpolantDecorator(interpolantPtr->clone())
        {
        }

        virtual ~ExpInterpolantDecorator() {}

        virtual const double operator()(const double x) const
        {
            return std::log(InterpolantDecorator::operator()(x));
        }

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas);

    private:
        virtual ExpInterpolantDecorator* doClone() const;
    };

    class MaxInterpolantDecorator : public InterpolantDecorator {
    public:
        MaxInterpolantDecorator(
            const boost::shared_ptr<Interpolant>& interpolantPtr,
            const double floor)
        : InterpolantDecorator(interpolantPtr->clone()), _floor(floor)
        {
        }

        virtual ~MaxInterpolantDecorator() {}

        virtual const double operator()(const double x) const
        {
            return std::max(InterpolantDecorator::operator()(x), _floor);
        }

    private:
        virtual MaxInterpolantDecorator* doClone() const;

    private:
        const double _floor;
    };
}

namespace design_pattern {
    class ConstantExtrapolationDecorator : public InterpolantDecorator {
    public:
        ConstantExtrapolationDecorator(
            const boost::shared_ptr<Interpolant>& interpolantPtr)
        : InterpolantDecorator(interpolantPtr->clone())
        {
        }

        virtual ~ConstantExtrapolationDecorator() {}

        virtual const double operator()(const double x) const;

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas);

    private:
        virtual ConstantExtrapolationDecorator* doClone() const;

    private:
        double _maxOrdinate;
        double _maxAbscissa;
        double _minOrdinate;
        double _minAbscissa;
    };

}
#endif // INTERPOLANTDECORATOR_H_INCLUDED