#ifndef FINANCE_IMODEL_H_INCLUDED
#define FINANCE_IMODEL_H_INCLUDED

#include <complex>
#include <cmath>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "DayCountFraction.h"

namespace finance {
    typedef boost::gregorian::date date_type;

    class IModel {
    public:
        virtual ~IModel() {}

        std::complex<double> calcCharacteristicFunction(
            const std::complex<double>& wave,
            const date_type& startDate, const date_type& endDate)
        {
            return doCalcCharacteristicFunction(wave, startDate, endDate);
        } 

        boost::shared_ptr<IModel> clone() const
        {
            return boost::shared_ptr<IModel>(doClone());
        }

    private:
        virtual std::complex<double> doCalcCharacteristicFunction(
            const std::complex<double>& wave,
            const date_type& startDate, const date_type& endDate) const = 0;

        virtual IModel* doClone() const = 0;

    };

    class BSModel : public IModel {
    public:
        BSModel(const double mu, const double sigma)
        : _mu(mu), _sigma(sigma)
        {
        }

        virtual ~BSModel() {}

        boost::shared_ptr<BSModel> clone() const
        {
            return boost::shared_ptr<BSModel>(doClone());
        }

    private:
        virtual std::complex<double> doCalcCharacteristicFunction(
            const std::complex<double>& wave,
            const date_type& startDate, const date_type& endDate) const
        {
            using namespace std::complex_literals;
            const double dcf = dayCountAct365(startDate, endDate);
            return std::exp(1.0i 
                    * wave * _mu * dcf 
                - 0.5 * _sigma * _sigma * wave * wave * dcf);
        }

        virtual BSModel* doClone() const { 
            return new BSModel(*this);
        }

        const double _mu;
        const double _sigma;
    };
} // namespace finance

#endif // FINANCE_IMODEL_H_INCLUDED
