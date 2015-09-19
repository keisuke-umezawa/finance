/*
 * ModelParameter.h
 *
 *  Created on: 2015/05/06
 *      Author: Keisuke
 */

#ifndef MODELPARAMETER_H_INCLUDED
#define MODELPARAMETER_H_INCLUDED

namespace lmm {
    class CevModelParameter {
    public:
        explicit CevModelParameter(const double p)
        : _p(p), _alpha(0.0)
        {
        }

        CevModelParameter(const double p, const double alpha)
        : _p(p), _alpha(alpha)
        {
        }

        const double p() const
        {
            return _p;
        }

        const double alpha() const
        {
            return _alpha;
        }

    private:
        double _p;
        double _alpha;
    };
}

#endif // MODELPARAMETER_H_INCLUDED
