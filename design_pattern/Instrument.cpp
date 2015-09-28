#include "boost/shared_ptr.hpp"
#include "Instrument.h"

namespace design_pattern {

    boost::shared_ptr<IInstrument> IInstrument::clone() const
    {
        return boost::shared_ptr<IInstrument>(doClone());
    }

    void Cap::accept(IInstrumentVisitor& visitor) const
    {
        visitor.visit(*this);
    }

    Cap* Cap::doClone() const
    {
        return new Cap(*this);
    }

    void FxVanillaOption::accept(IInstrumentVisitor& visitor) const
    {
        visitor.visit(*this);
    }

    FxVanillaOption* FxVanillaOption::doClone() const
    {
        return new FxVanillaOption(*this);
    }

    void AmericanSwaption::accept(IInstrumentVisitor& visitor) const
    {
        visitor.visit(*this);
    }

    AmericanSwaption* AmericanSwaption::doClone() const
    {
        return new AmericanSwaption(*this);
    }

}  // namespace design_pattern



