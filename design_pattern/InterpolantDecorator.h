#ifndef INTERPOLANTDECORATOR_H_INCLUDED
#define INTERPOLANTDECORATOR_H_INCLUDED

#include "Fwd.h"
#include <boost/shared_ptr.hpp>

namespace design_pattern {

    class InterpolantDecorator : public Interpolant {
    public:
        virtual ~InterpolantDecorator() {}

        virtual const double operator()(const double x) const = 0;

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas) = 0;

    private:
        virtual InterpolantDecorator* doClone() const = 0;
    };

    class LogInterpolantDecorator : public InterpolantDecorator {
    public:
        LogInterpolantDecorator(boost::shared_ptr<Interpolant> ptrInterpolant)
        : _ptrInterpolant(ptrInterpolant)
        {
        }

        virtual ~LogInterpolantDecorator() {}

        virtual const double operator()(const double x) const
        {
            return std::exp((*_ptrInterpolant)(x));
        }

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas)
        {
            ublas::vector<double> logOrdinates(ordinates.size(), 0.0);
            for (std::size_t i = 0; i < ordinates.size(); ++i) {
                logOrdinates(i) = std::log(ordinates(i));
            }
            _ptrInterpolant->init(logOrdinates, abscissas);
        }

    private:
        virtual LogInterpolantDecorator* doClone() const
        {
            return new LogInterpolantDecorator(*this);
        }

    private:
        boost::shared_ptr<Interpolant> _ptrInterpolant;
    };

    class ExpInterpolantDecorator : public InterpolantDecorator {
    public:
        ExpInterpolantDecorator(boost::shared_ptr<Interpolant> ptrInterpolant)
        : _ptrInterpolant(ptrInterpolant)
        {
        }

        virtual ~ExpInterpolantDecorator() {}

        virtual const double operator()(const double x) const
        {
            return std::log((*_ptrInterpolant)(x));
        }

        virtual void init(
            const ublas::vector<double>& ordinates,
            const ublas::vector<double>& abscissas)
        {
            ublas::vector<double> expOrdinates(ordinates.size(), 0.0);
            for (std::size_t i = 0; i < ordinates.size(); ++i) {
                expOrdinates(i) = std::exp(ordinates(i));
            }
            _ptrInterpolant->init(expOrdinates, abscissas);
        }

    private:
        virtual ExpInterpolantDecorator* doClone() const
        {
            return new ExpInterpolantDecorator(*this);
        }

    private:
        boost::shared_ptr<Interpolant> _ptrInterpolant;
    };
}

#endif // INTERPOLANTDECORATOR_H_INCLUDED