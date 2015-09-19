#include "DayCountFraction.h"

namespace lmm {
    double dayCountAct365(const date_t& start, const date_t& end)
    {
        return (end - start).days() / 365.0;
    }
} // namespace
