#ifndef FINANCE_ISHORTRATE_H_INCLUDED
#define FINANCE_ISHORTRATE_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/shared_ptr.hpp>

namespace finance {
    typedef boost::gregorian::date date_type;

    class IShortRate {
    public:
        virtual ~IShortRate() {}

        double operator()(const date_type& date) const
        {
            return doOperator(date);
        }
        
        boost::shared_ptr<IShortRate> clone() const
        {
            return boost::shared_ptr<IShortRate>(doClone());
        }

    private:
        virtual double doOperator(const date_type& date) const = 0;

        virtual IShortRate* doClone() const = 0;
    };

    class ConstantShortRate : public IShortRate {
    public:
        ConstantShortRate(const double rate) : _rate(rate)
        {
        }

        virtual ~ConstantShortRate() {}

        boost::shared_ptr<ConstantShortRate> clone() const
        {
            return boost::shared_ptr<ConstantShortRate>(doClone());
        }

    private:
        virtual double doOperator(const date_type& date) const
        {
            return _rate;
        }

        virtual ConstantShortRate* doClone() const
        {
            return new ConstantShortRate(*this);
        }
        
        const double _rate;
    };
} // namespace finance

#endif // FINANCE_ISHORTRATE_H_INCLUDED
