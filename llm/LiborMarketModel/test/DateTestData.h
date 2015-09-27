/*
 *
 *
 *
 *
 */

#ifndef TEST_DATETEST_DATA_H_INCLUDED
#define TEST_DATETEST_DATA_H_INCLUDED

#include "fwd.h"

namespace test_lmm {
    class DateTestData {
    public:
        static const lmm::date_t& today()
        {
            static lmm::date_t d(2005, 1, 21);
            return d;
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
#endif // TEST_DATETEST_DATA_H_INCLUDED
