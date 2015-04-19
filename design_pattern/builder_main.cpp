#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "Fwd.h"
#include "MarketData.h"
#include "Parser.h"
#include "IrDataBuilder.h"


namespace {
    //const std::string csv_string 
    //    = "DEPO, 2015/5/1, 0.01\n\
    //    FRA, 2015/10/1, 2016/4/1, 0.02\n\
    //    SWAP, 2020/4/1, 6M, 0.5";
}


int main()
{
    //market data
    const std::string dirPath = "./data/ir_data.csv";

    {
        design_pattern::MarketDataBuilder builder;
        design_pattern::IrDataParser parser(builder);
        parser.parse(dirPath);
        std::vector<design_pattern::DepositeRateMarketData> depositeRates
            = builder.depositeRateMarketData();
        std::cout << depositeRates[0].startDate() << std::endl;
        std::cout << depositeRates[0].quote() << std::endl;
    }

    {
        design_pattern::MatrixDataBuilder builder;
        design_pattern::IrDataParser parser(builder);
        parser.parse(dirPath);
        std::cout << builder.getMatrix() << std::endl;
    }


    return 0;

}