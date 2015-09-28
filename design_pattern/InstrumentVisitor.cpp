#include "InstrumentVisitor.h"
#include "Instrument.h"

namespace design_pattern {
    boost::shared_ptr<IInstrumentVisitor> IInstrumentVisitor::clone() const
    {
        return boost::shared_ptr<IInstrumentVisitor>(doClone());
    }

    void IInstrumentVisitor::visit(const Cap& accepter)
    {
        doVisit(accepter);
    }

    void IInstrumentVisitor::visit(const FxVanillaOption& accepter)
    {
        doVisit(accepter);
    }

    void IInstrumentVisitor::visit(const AmericanSwaption& accepter)
    {
        doVisit(accepter);
    }
}  // namespace design_pattern



