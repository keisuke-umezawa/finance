#ifndef CALCDISCOUNTFACTOR_H_INCLUDED
#define CALCDISCOUNTFACTOR_H_INCLUDED



namespace design_pattern {
    class YieldCurveCreator;

    double calcDiscountFactor(
        const date_t& date, const YieldCurveCreator& factory);
    
}

#endif // CALCDISCOUNTFACTOR_H_INCLUDED