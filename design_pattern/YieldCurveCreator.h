#ifndef YIELDCURVECREATOR_H_INCLUDED
#define YIELDCURVECREATOR_H_INCLUDED


#include <boost/shared_ptr.hpp>
#include "fwd.h"
#include "MarketData.h"
#include "MarketDataSet.h"
#include "YieldCurve.h"

namespace design_pattern {

    class YieldCurveCreator {
    public:
        virtual ~YieldCurveCreator() {}

        boost::shared_ptr<YieldCurve> create(
            const std::vector<DepositeRateMarketData>& depositeRates,
            const std::vector<ForwardRateAgreementMarketData>& forwardRates,
            const std::vector<SwapRateMarketData>& swapRates) const
        {
            boost::shared_ptr<YieldCurve> ptrYield
                = createInstance();

            YieldCurveDataSet dataset;

            for (std::size_t i = 0; i < depositeRates.size(); ++i) {
                setDepositeRate(dataset, depositeRates[i]);
            }
            for (std::size_t i = 0; i < forwardRates.size(); ++i) {
                setForwardRate(dataset, forwardRates[i]);
            }
            for (std::size_t i = 0; i < swapRates.size(); ++i) {
                setSwapRate(dataset, swapRates[i]);
            }

            build(ptrYield, dataset);

            return ptrYield;
        }
    
    private:
        //Factory Method
        virtual boost::shared_ptr<YieldCurve> createInstance() const = 0;

        virtual void setDepositeRate(YieldCurveDataSet& dataset,
            const DepositeRateMarketData& depositeRate) const = 0;

        virtual void setForwardRate(YieldCurveDataSet& dataset,
            const ForwardRateAgreementMarketData& forwardRate) const = 0;

        virtual void setSwapRate(YieldCurveDataSet& dataset,
            const SwapRateMarketData& swapRate) const = 0;

        virtual void build(boost::shared_ptr<YieldCurve>& yield,
            const YieldCurveDataSet& dataset) const = 0;
    };

    class LiborYieldCurveCreator : public YieldCurveCreator {
    public:
        virtual ~LiborYieldCurveCreator() {}
    
    private:
        virtual boost::shared_ptr<YieldCurve> createInstance() const
        {
            return boost::shared_ptr<YieldCurve>(new LiborYieldCurve());
        }

        virtual void setDepositeRate(YieldCurveDataSet& dataset,
            const DepositeRateMarketData& depositeRate) const
        {
            // dataset.insert(depositeRate);
        }

        virtual void setForwardRate(YieldCurveDataSet& dataset,
            const ForwardRateAgreementMarketData& forwardRate) const
        {
            // dataset.insert(forwardRate);
        }

        virtual void setSwapRate(YieldCurveDataSet& dataset,
            const SwapRateMarketData& swapRate) const
        {
            // dataset.insert(swapRate);
        }

        virtual void build(boost::shared_ptr<YieldCurve>& yield,
            const YieldCurveDataSet& dataset) const
        {
            yield->setYieldCurveDataSet(dataset);
            yield->build();
        }
    };

    class OisYieldCurveCreator : public YieldCurveCreator {
    public:
        virtual ~OisYieldCurveCreator() {}
    
    private:
        virtual boost::shared_ptr<YieldCurve> createInstance() const
        {
            return boost::shared_ptr<YieldCurve>(new OisYieldCurve());
        }

        virtual void setDepositeRate(YieldCurveDataSet& dataset,
            const DepositeRateMarketData& depositeRate) const
        {
            // some process for OisYieldCurve
            // dataset.insert(depositeRate);
        }

        virtual void setForwardRate(YieldCurveDataSet& dataset,
            const ForwardRateAgreementMarketData& forwardRate) const
        {
            // some process for OisYieldCurve
            // dataset.insert(forwardRate);
        }

        virtual void setSwapRate(YieldCurveDataSet& dataset,
            const SwapRateMarketData& swapRate) const
        {
            // some process for OisYieldCurve
            // dataset.insert(swapRate);
        }

        virtual void build(boost::shared_ptr<YieldCurve>& yield,
            const YieldCurveDataSet& dataset) const
        {
            yield->setYieldCurveDataSet(dataset);
            yield->build();
        }
    };

        
}

#endif // YIELDCURVECREATOR_H_INCLUDED