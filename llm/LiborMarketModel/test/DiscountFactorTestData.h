/*
 *
 *
 *
 *
 */

#ifndef TEST_DISCOUNTFACTORTESTDATA_H_INCLUDED
#define TEST_DISCOUNTFACTORTESTDATA_H_INCLUDED

#include "fwd.h"
#include "DateTestData.h"

namespace test_lmm {
    class DiscountFactorTestData {
    public:
        static const lmm::date_t& today()
        {
            return DateTestData::today();
        }
        static const ublas::vector<double>& discountFactors()
        {
            static ublas::vector<double> dfs(22, 0.0);
            dfs(0) = 0.9997685; // spot
            dfs(1) = 0.9997107;
            dfs(2) = 0.9993636;
            dfs(3) = 0.9989588;
            dfs(4) = 0.9979767; // 1M
            dfs(5) = 0.9963442;
            dfs(6) = 0.9945224;
            dfs(7) = 0.9890361;
            dfs(8) = 0.9832707;
            dfs(9) = 0.9772395; // 1Y
            dfs(10) = 0.9507588;
            dfs(11) = 0.9217704;
            dfs(12) = 0.8908955;
            dfs(13) = 0.8589736; // 5Y
            dfs(14) = 0.8262486;
            dfs(15) = 0.7928704;
            dfs(16) = 0.7595743;
            dfs(17) = 0.7261153;
            dfs(18) = 0.6942849; // 10Y
            dfs(19) = 0.6348348;
            dfs(20) = 0.5521957; // 15Y
            dfs(21) = 0.4345583; // 20Y
            return dfs;
        }
        static const ublas::vector<lmm::date_t>& dates()
        {
            return DateTestData::dates();
        }
    };
} // namespace test_lmm {

#endif