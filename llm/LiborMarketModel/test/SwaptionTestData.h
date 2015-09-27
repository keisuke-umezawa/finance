#ifndef TEST_SWAPTIONTESTDATA_H_INCLUDED
#define TEST_SWAPTIONTESTDATA_H_INCLUDED

#include "fwd.h"
#include "Tenor.h"
#include "DateTestData.h"

namespace test_lmm {
    class SwaptionTestData {
    public:
        static const lmm::date_t& today()
        {
            return DateTestData::today();
        }
        static const ublas::matrix<double>& volatilities()
        {
            static ublas::matrix<double> vols(10, 10, 0.0);
            vols(0, 0) = 0.227; 
            vols(0, 1) = 0.23; 
            vols(0, 2) = 0.221; 
            vols(0, 3) = 0.209; 
            vols(0, 4) = 0.196; 
            vols(0, 5) = 0.186; 
            vols(0, 6) = 0.176; 
            vols(0, 7) = 0.169; 
            vols(0, 8) = 0.163; 
            vols(0, 9) = 0.159; 
            
            vols(1, 0) = 0.224; 
            vols(1, 1) = 0.215; 
            vols(1, 2) = 0.205; 
            vols(1, 3) = 0.194; 
            vols(1, 4) = 0.183; 
            vols(1, 5) = 0.174; 
            vols(1, 6) = 0.167; 
            vols(1, 7) = 0.162; 
            vols(1, 8) = 0.158; 
            vols(1, 9) = 0.154; 

            vols(2, 0) = 0.209; 
            vols(2, 1) = 0.201; 
            vols(2, 2) = 0.19; 
            vols(2, 3) = 0.18; 
            vols(2, 4) = 0.17; 
            vols(2, 5) = 0.163; 
            vols(2, 6) = 0.158; 
            vols(2, 7) = 0.155; 
            vols(2, 8) = 0.152; 
            vols(2, 9) = 0.15; 

            vols(3, 0) = 0.195; 
            vols(3, 1) = 0.187; 
            vols(3, 2) = 0.177; 
            vols(3, 3) = 0.168; 
            vols(3, 4) = 0.16; 
            vols(3, 5) = 0.155; 
            vols(3, 6) = 0.151; 
            vols(3, 7) = 0.148; 
            vols(3, 8) = 0.147; 
            vols(3, 9) = 0.145; 

            vols(4, 0) = 0.182; 
            vols(4, 1) = 0.174; 
            vols(4, 2) = 0.165; 
            vols(4, 3) = 0.158; 
            vols(4, 4) = 0.151; 
            vols(4, 5) = 0.148; 
            vols(4, 6) = 0.145; 
            vols(4, 7) = 0.143; 
            vols(4, 8) = 0.142; 
            vols(4, 9) = 0.14; 

            vols(5, 0) = 0.1746; 
            vols(5, 1) = 0.1674; 
            vols(5, 2) = 0.159; 
            vols(5, 3) = 0.1524; 
            vols(5, 4) = 0.1462; 
            vols(5, 5) = 0.1436; 
            vols(5, 6) = 0.141; 
            vols(5, 7) = 0.1394; 
            vols(5, 8) = 0.1384; 
            vols(5, 9) = 0.1368; 

            vols(6, 0) = 0.1672; 
            vols(6, 1) = 0.1608; 
            vols(6, 2) = 0.153; 
            vols(6, 3) = 0.1468; 
            vols(6, 4) = 0.1414; 
            vols(6, 5) = 0.1392; 
            vols(6, 6) = 0.137; 
            vols(6, 7) = 0.1358; 
            vols(6, 8) = 0.1348; 
            vols(6, 9) = 0.1336; 

            vols(7, 0) = 0.1598; 
            vols(7, 1) = 0.1542; 
            vols(7, 2) = 0.147; 
            vols(7, 3) = 0.1412; 
            vols(7, 4) = 0.1366; 
            vols(7, 5) = 0.1348; 
            vols(7, 6) = 0.133; 
            vols(7, 7) = 0.1322; 
            vols(7, 8) = 0.1312; 
            vols(7, 9) = 0.1304;

            vols(8, 0) = 0.1524; 
            vols(8, 1) = 0.1476; 
            vols(8, 2) = 0.141; 
            vols(8, 3) = 0.1356; 
            vols(8, 4) = 0.1318; 
            vols(8, 5) = 0.1304; 
            vols(8, 6) = 0.129; 
            vols(8, 7) = 0.1286; 
            vols(8, 8) = 0.1276; 
            vols(8, 9) = 0.1272;

            vols(9, 0) = 0.145; 
            vols(9, 1) = 0.141; 
            vols(9, 2) = 0.1435; 
            vols(9, 3) = 0.13; 
            vols(9, 4) = 0.127; 
            vols(9, 5) = 0.126; 
            vols(9, 6) = 0.125; 
            vols(9, 7) = 0.125; 
            vols(9, 8) = 0.124; 
            vols(9, 9) = 0.124;
            return vols;
        }
        static const ublas::vector<lmm::Tenor> tenors()
        {
            static ublas::vector<lmm::Tenor> tenors(10);
            tenors(0) = lmm::Tenor(1, lmm::TenorUnit::Year);
            tenors(1) = lmm::Tenor(2, lmm::TenorUnit::Year);
            tenors(2) = lmm::Tenor(3, lmm::TenorUnit::Year);
            tenors(3) = lmm::Tenor(4, lmm::TenorUnit::Year);
            tenors(4) = lmm::Tenor(5, lmm::TenorUnit::Year);
            tenors(5) = lmm::Tenor(6, lmm::TenorUnit::Year);
            tenors(6) = lmm::Tenor(7, lmm::TenorUnit::Year);
            tenors(7) = lmm::Tenor(8, lmm::TenorUnit::Year);
            tenors(8) = lmm::Tenor(9, lmm::TenorUnit::Year);
            tenors(9) = lmm::Tenor(10, lmm::TenorUnit::Year);
            return tenors;
        }
    };
} // namespace test_lmm {

#endif // TEST_SWAPTIONTESTDATA_H_INCLUDED