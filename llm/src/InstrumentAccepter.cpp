/*
 * InstrumentAccepter.cpp
 *
 *  Created on: 2015/05/23
 *      Author: Keisuke
 */

#include "InstrumentAccepter.h"
#include "boost/shared_ptr.hpp"

namespace lmm {

    boost::shared_ptr<IInstrumentAccepter> IInstrumentAccepter::clone() const
    {
        return boost::shared_ptr<IInstrumentAccepter>(doClone());
    }

    void CapletAccepter::accept(IInstrumentVisitor& visitor) const
    {
        visitor.visit(*this);
    }

    CapletAccepter* CapletAccepter::doClone() const
    {
        return new CapletAccepter(*this);
    }
    void CapAccepter::accept(IInstrumentVisitor& visitor) const
    {
        visitor.visit(*this);
    }

    CapAccepter* CapAccepter::doClone() const
    {
        return new CapAccepter(*this);
    }

}  // namespace lmm



