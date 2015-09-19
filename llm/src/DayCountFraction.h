#ifndef DAYCOUNTFRACTION_H_INCLUDED
#define DAYCOUNTFRACTION_H_INCLUDED

#include "fwd.h"

namespace lmm {
    double dayCountAct365(const date_t& start,
            const date_t& end);
} // namespace lmm

#endif // DAYCOUNTFRACTION_H_INCLUDED
