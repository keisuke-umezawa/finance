#ifndef INSTRUMENT_H_INCLUDED
#define INSTRUMENT_H_INCLUDED

#include "InstrumentVisitor.h"

namespace design_pattern {
    class IInstrumentVisitor;

    //class IInstrument {
    //public:
    //    virtual ~IInstrument() {}

    //    boost::shared_ptr<IInstrument> clone() const;

    //    virtual void accept(IInstrumentVisitor& visitor) const = 0;

    //private:
    //    virtual IInstrument* doClone() const = 0;
    //};

    //class Cap : public IInstrument {
    //public:
    //    Cap()
    //    {
    //    }

    //    virtual ~Cap() {}

    //    virtual void accept(IInstrumentVisitor& visitor) const;

    //private:
    //    virtual Cap* doClone() const;
    //};

    //class FxVanillaOption : public IInstrument {
    //public:
    //    FxVanillaOption()
    //    {
    //    }

    //    virtual ~FxVanillaOption() {}

    //    virtual void accept(IInstrumentVisitor& visitor) const;

    //private:
    //    virtual FxVanillaOption* doClone() const;
    //};

    //class AmericanSwaption : public IInstrument {
    //public:
    //    AmericanSwaption()
    //    {
    //    }

    //    virtual ~AmericanSwaption() {}

    //    virtual void accept(IInstrumentVisitor& visitor) const;

    //private:
    //    virtual AmericanSwaption* doClone() const;
    //};

}  // namespace design_pattern

#endif // INSTRUMENT_H_INCLUDED
