#include "ContractDispatcher.h"
#include "Instrument.h"


namespace design_pattern {

    void ContractDispatcher::doVisit(const Cap& accepter)
    {
        _contractType = Swap;
        _exerciseType = ExerciseTypeNone;
        _pathDependanceType = PathDependanceTypeNone;
        _underlyingType = InterestRate;
        _hasClosedFormula = true;
    }

    void ContractDispatcher::doVisit(const FxVanillaOption& accepter)
    {
        _contractType = Option;
        _exerciseType = European;
        _pathDependanceType = Vanilla;
        _underlyingType = Fx;
        _hasClosedFormula = false;
    }

    void ContractDispatcher::doVisit(const AmericanSwaption& accepter)
    {
        _contractType = Option;
        _exerciseType = American;
        _pathDependanceType = Vanilla;
        _underlyingType = InterestRate;
        _hasClosedFormula = false;
    }

    ContractDispatcher* ContractDispatcher::doClone() const
    {
        return new ContractDispatcher(*this);
    }
}  // namespace design_pattern



