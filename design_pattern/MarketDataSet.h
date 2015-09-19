#ifndef MARKETDATASET_H_INCLUDED
#define MARKETDATASET_H_INCLUDED

#include "fwd.h"

namespace design_pattern {

    class VolatilityDataSet {
    };

    class YieldCurveDataSet {
    };

    VolatilityDataSet parseVolatilityDataSet(const std::string& filePath);

    YieldCurveDataSet parseYieldCurveDataSet(const std::string& filePath);
}

#endif // MARKETDATASET_H_INCLUDED
