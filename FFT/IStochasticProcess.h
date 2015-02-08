#ifndef FINANCE_ISTOCHASTICPROCESS_H_INCLUDED
#define FINANCE_ISTOCHASTICPROCESS_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "ISde.h"

namespace finance {
    typedef boost::gregorian::date date_type;

    class IStochasticProcess {
    public:
        virtual ~IStochasticProcess() {}

        double operator()(const date_type& time) const
        {
            return doOperator(time);
        }

        boost::shared_ptr<IStochasticProcess> clone() const
        {
            return boost::shared_ptr<IStochasticProcess>(doClone());
        }

    private:
        virtual double doOperator(const date_type& time) const = 0;

        virtual IStochasticProcess* doClone() const = 0;

    };

    class NormalProcess : public IStochasticProcess {
    public:
        explicit NormalProcess(const double mu, const double sigma,
            const double initialValue, const date_type& initialDate)
        : _sde(mu, sigma), _initialValue(initialValue), 
            _initialDate(initialDate) 
        {
        }

        virtual ~NormalProcess() {}

        boost::shared_ptr<NormalProcess> clone() const
        {
            return boost::shared_ptr<NormalProcess>(doClone());
        }

    private:
        virtual double doOperator(const date_type& time) const
        {
            return _constant;
        }

        virtual NormalProcess* doClone() const
        {
            return new NormalProcess(*this);
        }

        const NormalSde _sde;
        const double _initialValue;
        const date_type _initialDate;
    };

} // namespace finance

#endif // FINANCE_ISTOCHASTICPROCESS_H_INCLUDED
