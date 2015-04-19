#ifndef FINANCE_IDETERMINISTICPROCESS_H_INCLUDED
#define FINANCE_IDETERMINISTICPROCESS_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace finance {
    typedef boost::gregorian::date date_t;

    class IDeterministicProcess {
    public:
        virtual ~IDeterministicProcess() {}

        double operator()(const date_t& time) const
        {
            return apply(time);
        }

        boost::shared_ptr<IDeterministicProcess> clone() const
        {
            return boost::shared_ptr<IDeterministicProcess>(
                 this->doClone());
        }

    private:
        virtual double apply(const date_t& time) const = 0;

        virtual IDeterministicProcess* doClone() const = 0;

    };

    class ConstantProcess : public IDeterministicProcess {
    public:
        explicit ConstantProcess(const double constant)
        : _value(constant)
        {
        }

        virtual ~ConstantProcess() {}

        boost::shared_ptr<ConstantProcess> clone() const
        {
            return boost::shared_ptr<ConstantProcess>(this->doClone());
        }

    private:
        virtual double apply(const date_t& time) const
        {
            return _value;
        }

        virtual ConstantProcess* doClone() const
        {
            return new ConstantProcess(*this);
        }

        const double _value;
    };

} // namespace finance

#endif // FINANCE_IDETERMINISTICPROCESS_H_INCLUDED
