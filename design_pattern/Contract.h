#ifndef CONTRACT_H_INCLUDED
#define CONTRACT_H_INCLUDED

#include "ContractTypeDefinitions.h"

namespace design_pattern {

    class IContract {
    public:
        virtual ~IContract() {}

        boost::shared_ptr<IContract> clone() const;

        virtual ContractType contractType() const = 0;
        virtual ExerciseType exerciseType() const = 0;
        virtual PathDependanceType pathDependanceType() const = 0;
        virtual UnderlyingType underlyingType() const = 0;
        virtual bool hasClosedFormula() const = 0;

    private:
        virtual IContract* doClone() const = 0;
    };

    class Cap : public IContract {
    public:
        Cap()
        : _contractType(Swap),
            _exerciseType(ExerciseTypeNone),
            _pathDependanceType(PathDependanceTypeNone),
            _underlyingType(InterestRate),
            _hasClosedFormula(true)
        {
        }

        virtual ~Cap() {}

        virtual ContractType contractType() const {return _contractType;}
        virtual ExerciseType exerciseType() const {return _exerciseType;}
        virtual PathDependanceType pathDependanceType() const 
        {return _pathDependanceType;}
        virtual UnderlyingType underlyingType() const {return _underlyingType;}
        virtual bool hasClosedFormula() const {return _hasClosedFormula;}

    private:
        virtual Cap* doClone() const
        {
            return new Cap(*this);
        }

    private:
        ContractType _contractType;
        ExerciseType _exerciseType;
        PathDependanceType _pathDependanceType;
        UnderlyingType _underlyingType;
        bool _hasClosedFormula;
    };

    class FxVanillaOption : public IContract {
    public:
        FxVanillaOption()
        : _contractType(Option),
            _exerciseType(European),
            _pathDependanceType(Vanilla),
            _underlyingType(Fx),
            _hasClosedFormula(false)
        {
        }

        virtual ~FxVanillaOption() {}

        virtual ContractType contractType() const {return _contractType;}
        virtual ExerciseType exerciseType() const {return _exerciseType;}
        virtual PathDependanceType pathDependanceType() const 
        {return _pathDependanceType;}
        virtual UnderlyingType underlyingType() const {return _underlyingType;}
        virtual bool hasClosedFormula() const {return _hasClosedFormula;}

    private:
        virtual FxVanillaOption* doClone() const
        {
            return new FxVanillaOption(*this);
        }

    private:
        ContractType _contractType;
        ExerciseType _exerciseType;
        PathDependanceType _pathDependanceType;
        UnderlyingType _underlyingType;
        bool _hasClosedFormula;
    };

    class AmericanSwaption : public IContract {
    public:
        AmericanSwaption()
        : _contractType(Option),
            _exerciseType(American),
            _pathDependanceType(Vanilla),
            _underlyingType(InterestRate),
            _hasClosedFormula(false)
        {
        }

        virtual ~AmericanSwaption() {}

        virtual ContractType contractType() const {return _contractType;}
        virtual ExerciseType exerciseType() const {return _exerciseType;}
        virtual PathDependanceType pathDependanceType() const 
        {return _pathDependanceType;}
        virtual UnderlyingType underlyingType() const {return _underlyingType;}
        virtual bool hasClosedFormula() const {return _hasClosedFormula;}

    private:
        virtual AmericanSwaption* doClone() const
        {
            return new AmericanSwaption(*this);
        }

    private:
        ContractType _contractType;
        ExerciseType _exerciseType;
        PathDependanceType _pathDependanceType;
        UnderlyingType _underlyingType;
        bool _hasClosedFormula;
    };

}  // namespace design_pattern

#endif // CONTRACT_H_INCLUDED
