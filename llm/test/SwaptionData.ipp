    ublas::vector<lmm::date_t> initDates()
    {
        ublas::vector<lmm::date_t> dates(6);
        dates(0)  = lmm::date_t(2016, 4, 1);
        dates(1)  = lmm::date_t(2017, 4, 1);
        dates(2)  = lmm::date_t(2018, 4, 1);
        dates(3)  = lmm::date_t(2019, 4, 1);
        dates(4)  = lmm::date_t(2020, 4, 1);
        dates(5)  = lmm::date_t(2021, 4, 1);
        return dates;
    }
    ublas::matrix<double> initSwaptionVolatilities()
    {
        ublas::matrix<double> volatilities(5, 5, 0.0);
        volatilities(0, 0) = 0.2270;
        volatilities(1, 0) = 0.2240;
        volatilities(2, 0) = 0.2090;
        volatilities(3, 0) = 0.1950;
        volatilities(4, 0) = 0.1820;
        volatilities(0, 1) = 0.23;
        volatilities(1, 1) = 0.215;
        volatilities(2, 1) = 0.201;
        volatilities(3, 1) = 0.187;
        volatilities(4, 1) = 0.174;
        volatilities(0, 2) = 0.221;
        volatilities(1, 2) = 0.205;
        volatilities(2, 2) = 0.19;
        volatilities(3, 2) = 0.177;
        volatilities(4, 2) = 0.165;
        volatilities(0, 3) = 0.209;
        volatilities(1, 3) = 0.194;
        volatilities(2, 3) = 0.18;
        volatilities(3, 3) = 0.168;
        volatilities(4, 3) = 0.158;
        volatilities(0, 4) = 0.196;
        volatilities(1, 4) = 0.183;
        volatilities(2, 4) = 0.17;
        volatilities(3, 4) = 0.16;
        volatilities(4, 4) = 0.151;
        return volatilities;
    }
    ublas::vector<double> initDiscountFactors()
    {
        ublas::vector<double> discountFactors(11, 0.0);
        discountFactors(0) = 0.9774;
        discountFactors(1) = 0.9509;
        discountFactors(2) = 0.9219;
        discountFactors(3) = 0.8911;
        discountFactors(4) = 0.8591;
        discountFactors(5) = 0.8264;
        discountFactors(6) = 0.7930;
        discountFactors(7) = 0.7597;
        discountFactors(8) = 0.7262;
        discountFactors(9) = 0.6944;
        discountFactors(10) = 0.6645;
        return discountFactors;
    }
    const lmm::date_t today(2015, 4, 1);
    const ublas::vector<lmm::date_t> dates
        = initDates();
    const ublas::matrix<double> swaptionVolatilities
        = initSwaptionVolatilities();
    const ublas::vector<double> discountFactors
        = initDiscountFactors();