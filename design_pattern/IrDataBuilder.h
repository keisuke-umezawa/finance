#ifndef IRDATABUILDER_H_INCLUDED
#define IRDATABUILDER_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Fwd.h"
#include "MarketData.h"

namespace design_pattern {
    class IrDataBuilder {
    public:
        virtual ~IrDataBuilder() {}

        virtual void buildDepositeRateData(
            const std::vector<std::string>& dataStrings) = 0;

        virtual void buildForwardRateAgreementData(
            const std::vector<std::string>& dataStrings) = 0;

        virtual void buildSwapRateData(
            const std::vector<std::string>& dataStrings) = 0;
    };

    class MarketDataBuilder : public IrDataBuilder {
    public:
        virtual ~MarketDataBuilder() {}

        virtual void buildDepositeRateData(
            const std::vector<std::string>& dataStrings)
        { 
            DepositeRateMarketData data;

            data.setStartDate(dataStrings[1]);

            std::istringstream is;
            is.str(dataStrings[2]);
            double x;
            is >> x;
            data.setQuote(x);

            _depositeRateMarketData.push_back(data);
        }

        virtual void buildForwardRateAgreementData(
            const std::vector<std::string>& dataStrings)
        {
            ForwardRateAgreementMarketData data;

            data.setStartDate(dataStrings[1]);
            data.setEndDate(dataStrings[2]);

            std::istringstream is;
            is.str(dataStrings[3]);
            double x;
            is >> x;
            data.setQuote(x);

            _forwardRateAgreementMarketData.push_back(data);
        }

        virtual void buildSwapRateData(
            const std::vector<std::string>& dataStrings)
        {
            SwapRateMarketData data;

            data.setStartDate(dataStrings[1]);
            data.setTenor(dataStrings[2]);

            std::istringstream is;
            is.str(dataStrings[3]);
            double x;
            is >> x;
            data.setQuote(x);

            _swapRateMarketData.push_back(data);
        }

        std::vector<DepositeRateMarketData> depositeRateMarketData() const 
        {
            return _depositeRateMarketData;
        }

        std::vector<ForwardRateAgreementMarketData> 
            forwardRateAgreementMarketData() const 
        {
            return _forwardRateAgreementMarketData;
        }

        std::vector<SwapRateMarketData> swapRateMarketData() const 
        {
            return _swapRateMarketData;
        }

    private:
        std::vector<DepositeRateMarketData> _depositeRateMarketData;
        std::vector<ForwardRateAgreementMarketData> 
            _forwardRateAgreementMarketData;
        std::vector<SwapRateMarketData> _swapRateMarketData;
    };

    class MatrixDataBuilder : public IrDataBuilder {
    public:
        virtual ~MatrixDataBuilder() {}

        virtual void buildDepositeRateData(
            const std::vector<std::string>& dataStrings)
        {
            // TODO
        }

        virtual void buildForwardRateAgreementData(
            const std::vector<std::string>& dataStrings)
        {
            // TODO
        }

        virtual void buildSwapRateData(
            const std::vector<std::string>& dataStrings)
        {
            // TODO
        }

        const ublas::matrix<double> getMatrix() const
        {
            return _irMatrix;
        }

    private:
        ublas::matrix<double> _irMatrix;
    };
} // namespace design_pattern

#endif // IRDATABUILDER_H_INCLUDED