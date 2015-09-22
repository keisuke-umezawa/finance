/*
 * LinearInterpolant.h
 *
 *  Created on: 2015/05/01
 *      Author: Keisuke
 */

#ifndef LINEARINTERPOLANT_H_INCLUDED
#define LINEARINTERPOLANT_H_INCLUDED

#include <algorithm>
#include <cmath>
#include <functional>
#include "fwd.h"

namespace lmm {
    // ------------------------------------------------------------------------
    // IInterpolant
    // ------------------------------------------------------------------------
    class IInterpolant {
    public:
        virtual ~IInterpolant() {}
        const double operator()(const date_t& x) const
        {
            return doOperator(x);
        }
        boost::shared_ptr<IInterpolant> clone() const
        {
            return boost::shared_ptr<IInterpolant>(doClone());
        }
    private:
        virtual const double doOperator(const date_t& x) const = 0;

        virtual IInterpolant* doClone() const = 0;
    };
    // ------------------------------------------------------------------------
    // LinearInterpolant
    // ------------------------------------------------------------------------
    class LinearInterpolant : public IInterpolant {
    public:
        virtual ~LinearInterpolant() {}

        LinearInterpolant(const ublas::vector<date_t>& abscissas,
            const ublas::vector<double>& ordinates)
        : _abscissas(abscissas), _ordinates(ordinates)
        {
        }
    private:
        virtual const double doOperator(const date_t& x) const
        {
            const std::size_t index
                = std::lower_bound(_abscissas.begin(), _abscissas.end(), x)
                    - _abscissas.begin();
            if (0 == index) {
                return _ordinates(index);
            }
            if (_abscissas.size() == index) {
                return _ordinates(index - 1);
            }
            return _ordinates(index - 1)
                + (_ordinates(index) - _ordinates(index - 1))
                * static_cast<double>((x - _abscissas(index - 1)).days())
                / static_cast<double>((_abscissas(index) - _abscissas(index - 1)).days());
        }
        virtual IInterpolant* doClone() const
        {
            return new LinearInterpolant(*this);
        }
    private:
        const ublas::vector<date_t> _abscissas;
        const ublas::vector<double> _ordinates;
    };
    // ------------------------------------------------------------------------
    // LogLinearInterpolant
    // ------------------------------------------------------------------------
    class LogLinearInterpolant : public IInterpolant {
    public:
        virtual ~LogLinearInterpolant() {}

        LogLinearInterpolant(const ublas::vector<date_t>& abscissas,
            const ublas::vector<double>& ordinates)
        : _linearInterpolant()
        {
            ublas::vector<double> copyOrdinates(ordinates.size(), 0.0);
            std::transform(ordinates.begin(), ordinates.end(),
                copyOrdinates.begin(), std::ptr_fun<double, double>(std::log));
            _linearInterpolant = boost::make_shared<LinearInterpolant>(
                abscissas, copyOrdinates);
        }
    private:
        virtual const double doOperator(const date_t& x) const
        {
            return std::exp((*_linearInterpolant)(x));
        }
        virtual IInterpolant* doClone() const
        {
            return new LogLinearInterpolant(*this);
        }
    private:
        boost::shared_ptr<LinearInterpolant> _linearInterpolant;
    };

}  // namespace llm

#endif // LINEARINTERPOLANT_H_INCLUDED
