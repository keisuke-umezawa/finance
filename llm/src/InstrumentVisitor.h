/*
 * InstrumentVisitor.h
 *
 *  Created on: 2015/05/23
 *      Author: Keisuke
 */

#ifndef INSTRUMENTVISITOR_H_INCLUDED
#define INSTRUMENTVISITOR_H_INCLUDED

#include "Instrument.h"
#include "BlackScholesFormulas.h"
#include "DayCountFraction.h"
#include "InstrumentAccepter.h"

namespace lmm {
    class CapletAccepter;
    class CapAccepter;

    class IInstrumentVisitor {
    public:
        virtual ~IInstrumentVisitor() {}

        boost::shared_ptr<IInstrumentVisitor> clone() const;

        virtual void visit(const CapletAccepter& accepter);

        virtual void visit(const CapAccepter& accepter);

    private:
        virtual void doVisit(const CapletAccepter& accepter) = 0;
        virtual void doVisit(const CapAccepter& accepter) = 0;
        virtual IInstrumentVisitor* doClone() const = 0;
    };

    class PremiumPricer : public IInstrumentVisitor {
    public:
        PremiumPricer(const double rate, const double volatility)
        : _premium(0.0), _rate(rate), _volatility(volatility)
        {
        }
        virtual ~PremiumPricer() {}

        const double premium() const
        {
            return _premium;
        }

    private:
        virtual void doVisit(const CapletAccepter& accepter);
        virtual void doVisit(const CapAccepter& accepter);

        virtual PremiumPricer* doClone() const;
    private:
        double _premium;
        double _rate;
        double _volatility;
    };

}  // namespace lmm



#endif // INSTRUMENTVISITOR_H_INCLUDED
