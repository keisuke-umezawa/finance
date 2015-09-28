#ifndef INTERPOLANTPROTOTYPEFACTORY_H_INCLUDED
#define INTERPOLANTPROTOTYPEFACTORY_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "fwd.h"
#include "Interpolant.h"

namespace design_pattern {
    class InterpolantPrototypeFactory {
    public:
        InterpolantPrototypeFactory(
            const InterpolantPrototypeFactory& factory)
        : _interpolant(factory.create())
        {
        }

        explicit InterpolantPrototypeFactory(
            const Interpolant& interpolant)
        : _interpolant(interpolant.clone())
        {
        }

        boost::shared_ptr<Interpolant> create() const
        {
            return _interpolant->clone();
        }
    private:
        const boost::shared_ptr<const Interpolant> _interpolant;
    };

    InterpolantPrototypeFactory log(
        const InterpolantPrototypeFactory& factory)
    {
        return InterpolantPrototypeFactory(
            design_pattern::LogInterpolantDecorator(factory.create()));
    }

    InterpolantPrototypeFactory exp(
        const InterpolantPrototypeFactory& factory)
    {
        return InterpolantPrototypeFactory(
            design_pattern::ExpInterpolantDecorator(factory.create()));
    }

}  // namespace design_pattern

#endif // INTERPOLANTPROTOTYPEFACTORY_H_INCLUDED
