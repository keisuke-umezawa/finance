#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace ublas = boost::numeric::ublas;
typedef std::size_t date_t;

class MarketData {
};

class Interpolant {
public:
    boost::shared_ptr<Interpolant> clone() const
    {
        return boost::shared_ptr<Interpolant>(doClone());
    }

private:
    virtual Interpolant* doClone() const = 0;
};

class LinearInterpolant : public Interpolant {
private:
    virtual LinearInterpolant* doClone() const
    {
        return new LinearInterpolant(*this);
    }
};

class LogLinearInterpolant : public Interpolant {
private:
    virtual LogLinearInterpolant* doClone() const
    {
        return new LogLinearInterpolant(*this);
    }
};

class YieldCurve {
public:
    virtual ~YieldCurve() {}

    virtual const double discount(const date_t& date) const = 0;

    virtual void bootstrap(const MarketData& data) = 0;

    boost::shared_ptr<YieldCurve> clone() const
    {
        return boost::shared_ptr<YieldCurve>(doClone());
    }

private:
    virtual YieldCurve* doClone() const = 0;
};

class DisountFacterYieldCurve : public YieldCurve {
public:
    DisountFacterYieldCurve(const Interpolant& interpolant) 
    : _interpolant(interpolant.clone())
    {
    }

    virtual ~DisountFacterYieldCurve() {}

    virtual void bootstrap(const MarketData& data)
    {
        // TODO some operation for DisountFacterYieldCurve
        std::cout << "create DisountFacterYieldCurve" << std::endl;
    }

    virtual const double discount(const date_t& date) const
    {
        // TODO _interpolant(date);
        return 0.0;
    }

private:
    virtual DisountFacterYieldCurve* doClone() const
    {
        return new DisountFacterYieldCurve(*this);
    }

    boost::shared_ptr<Interpolant> _interpolant;
};

class ZeroRateYieldCurve : public YieldCurve {
public:
    ZeroRateYieldCurve(const Interpolant& interpolant) 
    : _interpolant(interpolant.clone())
    {   
    }

    virtual ~ZeroRateYieldCurve() {}

    virtual void bootstrap(const MarketData& data)
    {
        // TODO some operatoin for ZeroRateYieldCurve
        std::cout << "create ZeroRateYieldCurve" << std::endl;
    }

    virtual const double discount(const date_t& date) const
    {
        // TODO _interpolant(date);
        return 1.0;
    }

    const double rate(const date_t& date) const
    {
        // TODO _interpolant(date);
        return 2.0;
    }

private:
    virtual ZeroRateYieldCurve* doClone() const
    {
        return new ZeroRateYieldCurve(*this);
    }

    boost::shared_ptr<Interpolant> _interpolant;
};

class YieldCurveFactory {
public:
    virtual ~YieldCurveFactory() {}
    const boost::shared_ptr<YieldCurve> create(
        const MarketData& data, const Interpolant& interpolant) const
    {
        boost::shared_ptr<YieldCurve> yield = createInstance(interpolant);

        bootstrap(yield, data);

        return yield;
    }

private:
    virtual const boost::shared_ptr<YieldCurve> 
        createInstance(const Interpolant& interpolant) const = 0;

    virtual void bootstrap(const boost::shared_ptr<YieldCurve> yield,
        const MarketData& data) const = 0;
};

class DiscountFactorYieldCurveFactory : public YieldCurveFactory {
public:
    DiscountFactorYieldCurveFactory() {}

    virtual ~DiscountFactorYieldCurveFactory() {}

    virtual const boost::shared_ptr<YieldCurve> createInstance(
        const Interpolant& interpolant) const
    {
        return boost::shared_ptr<YieldCurve>(
            new DisountFacterYieldCurve(interpolant));
    }

    virtual void bootstrap(const boost::shared_ptr<YieldCurve> yield,
        const MarketData& data) const
    {
        yield->bootstrap(data);
    }
};

class ZeroRateYieldCurveFactory : public YieldCurveFactory {
public:
    ZeroRateYieldCurveFactory() {}

    virtual ~ZeroRateYieldCurveFactory() {}

    virtual const boost::shared_ptr<YieldCurve> createInstance(
        const Interpolant& interpolant) const
    {
        return boost::shared_ptr<YieldCurve>(
            new ZeroRateYieldCurve(interpolant));
    }

    virtual void bootstrap(const boost::shared_ptr<YieldCurve> yield,
        const MarketData& data) const
    {
        yield->bootstrap(data);
    }

};

int main()
{
    //market data
    //ublas::vector<date_t> grids(5, 0);
    //grids(0) = 1; grids(1) = 2; grids(2) = 3; grids(3) = 4; grids(4) = 5;
    //const ublas::vector<double> rates(5, 0.01);
    const MarketData data;

    {
        boost::shared_ptr<YieldCurveFactory> factory
            = boost::make_shared<DiscountFactorYieldCurveFactory>();

        boost::shared_ptr<YieldCurve> yieldCurve
            = factory->create(data, LinearInterpolant());

        std::cout << yieldCurve->discount(5) << std::endl;
    }

    {
        boost::shared_ptr<YieldCurveFactory> factory
            = boost::make_shared<ZeroRateYieldCurveFactory>();

        boost::shared_ptr<YieldCurve> yieldCurve
            = factory->create(data, LinearInterpolant());

        std::cout << yieldCurve->discount(5) << std::endl;
    }


    return 0;

}