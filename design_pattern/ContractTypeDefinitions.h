#ifndef CONTRACTTYPEDEFINITION_H_INCLUDED
#define CONTRACTTYPEDEFINITION_H_INCLUDED

namespace design_pattern {
    enum ContractType {
        ContractTypeNone = 0,
        Future,
        Forward,
        Swap,
        Option
    };


    enum ExerciseType {
        ExerciseTypeNone = 0,
        European,
        Bermudan,
        American
    };

    enum PathDependanceType {
        PathDependanceTypeNone = 0,
        Vanilla,
        Exotic
    };

    enum UnderlyingType {
        UnderlyingTypeNone = 0,
        Equity,
        Fx,
        InterestRate,
        Comodity,
        Credit
    };
} // namespace design_pattern {

#endif // CONTRACTTYPEDEFINITION_H_INCLUDED