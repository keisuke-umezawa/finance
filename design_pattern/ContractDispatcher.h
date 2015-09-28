#ifndef CONTRACTDISPATCHER_H_INCLUDED
#define CONTRACTDISPATCHER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include "Instrument.h"
#include "InstrumentVisitor.h"
#include "ContractTypeDefinitions.h"

namespace design_pattern {
    class Cap;
    class FxVanillaOption;
    class AmericanSwaption;

    class ContractDispatcher : public IInstrumentVisitor {
    public:
        ContractDispatcher()
        : _contractType(ContractTypeNone),
            _exerciseType(ExerciseTypeNone),
            _pathDependanceType(PathDependanceTypeNone),
            _underlyingType(UnderlyingTypeNone),
            _hasClosedFormula(false)
        {
        }

        virtual ~ContractDispatcher() {}

        ContractType contractType() const {return _contractType;}
        ExerciseType exerciseType() const {return _exerciseType;}
        PathDependanceType pathDependanceType() const 
        {return _pathDependanceType;}
        UnderlyingType underlyingType() const {return _underlyingType;}
        bool hasClosedFormula() const {return _hasClosedFormula;}

    private:
        virtual void doVisit(const Cap& accepter);
        virtual void doVisit(const FxVanillaOption& accepter);
        virtual void doVisit(const AmericanSwaption& accepter);
        virtual ContractDispatcher* doClone() const;
    private:
        ContractType _contractType;
        ExerciseType _exerciseType;
        PathDependanceType _pathDependanceType;
        UnderlyingType _underlyingType;
        bool _hasClosedFormula;
    };

}  // namespace design_pattern



#endif // CONTRACTDISPATCHER_H_INCLUDED
