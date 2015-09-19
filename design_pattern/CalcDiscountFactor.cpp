#include <boost/shared_ptr.hpp>
#include "fwd.h"
#include "IrDataBuilder.h"
#include "Parser.h"
#include "YieldCurve.h"
#include "YieldCurveCreator.h"
#include "CalcDiscountFactor.h"

namespace design_pattern {

    double calcDiscountFactor(
        const date_t& date, const YieldCurveCreator& factory)
    {
        // get database market data
        const std::string databasePath = "./data/ir_data.csv";
        MarketDataBuilder builder;
        IrDataParser parser(builder);
        parser.parse(databasePath);

        // YieldCurveCreator
        boost::shared_ptr<YieldCurve> ptrYield
            = factory.create(
                builder.depositeRateMarketData(), 
                builder.forwardRateAgreementMarketData(), 
                builder.swapRateMarketData());

        return ptrYield->discountFactor(date);
    }
        
}