/*
 * InstrumentVisitor.cpp
 *
 *  Created on: 2015/05/23
 *      Author: Keisuke
 */

#include "InstrumentVisitor.h"
#include "InstrumentAdapter.h"

namespace lmm {
    boost::shared_ptr<IInstrumentVisitor> IInstrumentVisitor::clone() const
    {
        return boost::shared_ptr<IInstrumentVisitor>(doClone());
    }

    void IInstrumentVisitor::visit(const CapletAccepter& accepter)
    {
        doVisit(accepter);
    }

    void IInstrumentVisitor::visit(const CapAccepter& accepter)
    {
        doVisit(accepter);
    }

    void PremiumPricer::doVisit(const CapletAccepter& accepter)
    {
        //const lmm::Caplet& caplet = accepter.caplet();
        //_premium = BlackFormula(_rate, caplet.strike(), _volatility,
        //    dayCountAct365(caplet.start(), caplet.end()));
    }

    void PremiumPricer::doVisit(const CapAccepter& accepter)
    {
        _premium = 1.0;
    }

    PremiumPricer* PremiumPricer::doClone() const
    {
        return new PremiumPricer(*this);
    }
}  // namespace lmm



