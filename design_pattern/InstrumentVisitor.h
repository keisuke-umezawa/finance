#ifndef INSTRUMENTVISITOR_H_INCLUDED
#define INSTRUMENTVISITOR_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include "Instrument.h"
#include "ContractTypeDefinitions.h"

namespace design_pattern {
    class Cap;
    class FxVanillaOption;
    class AmericanSwaption;

    class IInstrumentVisitor {
    public:
        virtual ~IInstrumentVisitor() {}

        boost::shared_ptr<IInstrumentVisitor> clone() const;

        virtual void visit(const Cap& accepter);
        virtual void visit(const FxVanillaOption& accepter);
        virtual void visit(const AmericanSwaption& accepter);

    private:
        virtual void doVisit(const Cap& accepter) = 0;
        virtual void doVisit(const FxVanillaOption& accepter) = 0;
        virtual void doVisit(const AmericanSwaption& accepter) = 0;
        virtual IInstrumentVisitor* doClone() const = 0;
    };
        
}  // namespace design_pattern

#endif // INSTRUMENTVISITOR_H_INCLUDED
