/*
 * InstrumentAccepter.h
 *
 *  Created on: 2015/05/23
 *      Author: Keisuke
 */

#ifndef INSTRUMENTACCEPTER_H_INCLUDED
#define INSTRUMENTACCEPTER_H_INCLUDED

#include "Instrument.h"
#include "InstrumentVisitor.h"

namespace lmm {
    class IInstrumentVisitor;

    class IInstrumentAccepter {
    public:
        virtual ~IInstrumentAccepter() {}

        boost::shared_ptr<IInstrumentAccepter> clone() const;

        virtual void accept(IInstrumentVisitor& visitor) const = 0;

    private:
        virtual IInstrumentAccepter* doClone() const = 0;
    };

    class CapletAccepter : public IInstrumentAccepter {
    public:
        CapletAccepter(const Caplet& caplet)
        : _caplet(caplet)
        {
        }

        virtual ~CapletAccepter() {}

        virtual void accept(IInstrumentVisitor& visitor) const;

        const Caplet& caplet() const
        {
            return _caplet;
        }

    private:
        virtual CapletAccepter* doClone() const;

    private:
        const Caplet _caplet;
    };

    class CapAccepter  : public IInstrumentAccepter {
    public:
        CapAccepter(const Cap& cap)
        : _cap(cap)
        {
        }

        virtual ~CapAccepter() {}

        virtual void accept(IInstrumentVisitor& visitor) const;

        const Cap& cap() const
        {
            return _cap;
        }

    private:
        virtual CapAccepter* doClone() const;

    private:
        const Cap _cap;
    };


}  // namespace lmm



#endif // INSTRUMENTACCEPTER_H_INCLUDED
