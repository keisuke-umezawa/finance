    ublas::vector<lmm::date_t> initDates()
    {
        ublas::vector<lmm::date_t> dates(21);
        dates(0)  = lmm::date_t(2015, 10, 1);
        dates(1)  = lmm::date_t(2016, 4, 1);
        dates(2)  = lmm::date_t(2016, 10, 1);
        dates(3)  = lmm::date_t(2017, 4, 1);
        dates(4)  = lmm::date_t(2017, 10, 1);
        dates(5)  = lmm::date_t(2018, 4, 1);
        dates(6)  = lmm::date_t(2018, 10, 1);
        dates(7)  = lmm::date_t(2019, 4, 1);
        dates(8)  = lmm::date_t(2019, 10, 1);
        dates(9)  = lmm::date_t(2020, 4, 1);
        dates(10)  = lmm::date_t(2020, 10, 1);
        dates(11)  = lmm::date_t(2021, 4, 1);
        dates(12)  = lmm::date_t(2021, 10, 1);
        dates(13)  = lmm::date_t(2022, 4, 1);
        dates(14)  = lmm::date_t(2022, 10, 1);
        dates(15)  = lmm::date_t(2023, 4, 1);
        dates(16)  = lmm::date_t(2023, 10, 1);
        dates(17)  = lmm::date_t(2024, 4, 1);
        dates(18)  = lmm::date_t(2024, 10, 1);
        dates(19)  = lmm::date_t(2025, 4, 1);
        dates(20)  = lmm::date_t(2025, 10, 1);
        return dates;
    }
    ublas::vector<double> initCapVolatilities()
    {
        ublas::vector<double> volatilities(20, 0);
        volatilities(0)  = 0.1641;
        volatilities(1)  = 0.1641;
        volatilities(2)  = 0.1889;
        volatilities(3)  = 0.2137;
        volatilities(4)  = 0.2186;
        volatilities(5)  = 0.2235;
        volatilities(6)  = 0.2212;
        volatilities(7)  = 0.2187;
        volatilities(8)  = 0.2158;
        volatilities(9)  = 0.2127;
        volatilities(10)  = 0.2100;
        volatilities(11)  = 0.2068;
        volatilities(12)  = 0.2030;
        volatilities(13)  = 0.2012;
        volatilities(14)  = 0.1970;
        volatilities(15)  = 0.1958;
        volatilities(16)  = 0.1925;
        volatilities(17)  = 0.1905;
        volatilities(18)  = 0.1875;
        volatilities(19)  = 0.1859;
        return volatilities;
    }

    ublas::vector<double> initCapStrikes()
    {
        ublas::vector<double> strikes(20, 0);
        strikes(0)  = 0.0219;
        strikes(1)  = 0.0230;
        strikes(2)  = 0.0242;
        strikes(3)  = 0.0254;
        strikes(4)  = 0.0263;
        strikes(5)  = 0.0272;
        strikes(6)  = 0.0281;
        strikes(7)  = 0.0289;
        strikes(8)  = 0.0296;
        strikes(9)  = 0.0303;
        strikes(10)  = 0.0309;
        strikes(11)  = 0.0316;
        strikes(12)  = 0.0320;
        strikes(13)  = 0.0328;
        strikes(14)  = 0.0333;
        strikes(15)  = 0.0339;
        strikes(16)  = 0.0345;
        strikes(17)  = 0.0350;
        strikes(18)  = 0.0354;
        strikes(19)  = 0.0358;
        return strikes;
    }

    ublas::vector<double> initDiscountFactors()
    {
        ublas::vector<double> discountFactors(20, 0);
        discountFactors(0) = 0.9892;
        discountFactors(1) = 0.9774;
        discountFactors(2) = 0.9648;
        discountFactors(3) = 0.9509;
        discountFactors(4) = 0.9369;
        discountFactors(5) = 0.9219;
        discountFactors(6) = 0.9068;
        discountFactors(7) = 0.8911;
        discountFactors(8) = 0.8754;
        discountFactors(9) = 0.8591;
        discountFactors(10) = 0.8430;
        discountFactors(11) = 0.8264;
        discountFactors(12) = 0.8000;
        discountFactors(13) = 0.7930;
        discountFactors(14) = 0.77;
        discountFactors(15) = 0.7597;
        discountFactors(16) = 0.74;
        discountFactors(17) = 0.7262;
        discountFactors(18) = 0.71;
        discountFactors(19) = 0.6944;
        return discountFactors;
    }
    ublas::vector<double> initLiborForwardRates()
    {
        ublas::vector<double> rates(20, 0);
        rates(0) = 0.0219;
        rates(1) = 0.0230;
        rates(2) = 0.0242;
        rates(3) = 0.0254;
        rates(4) = 0.0263;
        rates(5) = 0.0272;
        rates(6) = 0.0281;
        rates(7) = 0.0289;
        rates(8) = 0.0296;
        rates(9) = 0.0303;
        rates(10) = 0.0309;
        rates(11) = 0.0316;
        rates(12) = 0.0320;
        rates(13) = 0.0328;
        rates(14) = 0.0333;
        rates(15) = 0.0339;
        rates(16) = 0.0345;
        rates(17) = 0.0350;
        rates(18) = 0.0354;
        rates(19) = 0.0358;
        return rates;
    }
    const lmm::date_t today(2015, 4, 1);
    const ublas::vector<lmm::date_t> dates
        = initDates();
    const ublas::vector<double> capVolatilities
        = initCapVolatilities();
    const ublas::vector<double> capStrikes
        = initCapStrikes();
    const ublas::vector<double> liborForwardRates
        = initLiborForwardRates();
    const ublas::vector<double> discountFactors
        = initDiscountFactors();
