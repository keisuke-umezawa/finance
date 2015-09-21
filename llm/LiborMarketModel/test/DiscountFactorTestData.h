/*
 *
 *
 *
 *
 */

#include "fwd.h"

namespace test_lmm {
    class DiscountFactorTestData {
    public:
        static const lmm::date_t& today()
        {
            static lmm::date_t d(2005, 1, 21);
            return d;
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
            static ublas::vector<lmm::date_t> dates(22);
            dates(0) = lmm::date_t(2005, 1, 25); // spot
            dates(1) = lmm::date_t(2005, 1, 26); 
            dates(2) = lmm::date_t(2005, 2, 1); 
            dates(3) = lmm::date_t(2005, 2, 8); 
            dates(4) = lmm::date_t(2005, 2, 25); // 1M
            dates(5) = lmm::date_t(2005, 3, 25); 
            dates(6) = lmm::date_t(2005, 4, 25); 
            dates(7) = lmm::date_t(2005, 7, 25); 
            dates(8) = lmm::date_t(2005, 10, 25); 
            dates(9) = lmm::date_t(2006, 1, 25); // 1Y
            dates(10) = lmm::date_t(2007, 1, 25); 
            dates(11) = lmm::date_t(2008, 1, 25); 
            dates(12) = lmm::date_t(2009, 1, 25); 
            dates(13) = lmm::date_t(2010, 1, 25); 
            dates(14) = lmm::date_t(2011, 1, 25); 
            dates(15) = lmm::date_t(2012, 1, 25); 
            dates(16) = lmm::date_t(2013, 1, 25); 
            dates(17) = lmm::date_t(2014, 1, 25); 
            dates(18) = lmm::date_t(2015, 1, 25); 
            dates(19) = lmm::date_t(2017, 1, 25); 
            dates(20) = lmm::date_t(2020, 1, 25); 
            dates(21) = lmm::date_t(2025, 1, 25); 
            return dates;
        }
    };
} // namespace test_lmm {
