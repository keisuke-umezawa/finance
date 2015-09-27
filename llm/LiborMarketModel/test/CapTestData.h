#ifndef TEST_CAPTESTDATA_H_INCLUDED
#define TEST_CAPTESTDATA_H_INCLUDED


#include <boost/numeric/ublas/vector_proxy.hpp>
#include "fwd.h"
#include "DateTestData.h"

namespace test_lmm {
    class CapTestData {
    public:
        static const lmm::date_t& today()
        {
            return DateTestData::today();
        }
        static const ublas::vector<double>& volatilities()
        {
            static ublas::vector<double> vols(13, 0.0);
            vols(0) = 0.1641; // 1Y
            vols(1) = 0.2137;
            vols(2) = 0.2235;
            vols(3) = 0.2188;
            vols(4) = 0.2127;
            vols(5) = 0.2068;
            vols(6) = 0.2012;
            vols(7) = 0.1958;
            vols(8) = 0.1905;
            vols(9) = 0.1859;
            vols(10) = 0.1806;
            vols(11) = 0.1699;
            vols(12) = 0.1567;
            return vols;
        }
        static const ublas::vector<lmm::date_t>& dates()
        {
            static ublas::vector<lmm::date_t> dates
                = ublas::subrange(
                    DateTestData::dates(), 9, DateTestData::dates().size());
            return dates;
        }
    };
} // namespace test_lmm {

#endif // TEST_CAPTESTDATA_H_INCLUDED