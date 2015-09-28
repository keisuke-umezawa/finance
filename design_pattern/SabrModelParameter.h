#ifndef SABRMODELPARAMETER_H_INCLUDED
#define SABRMODELPARAMETER_H_INCLUDED

namespace design_pattern {

    class SabrModelParameter {
    public:
        SabrModelParameter()
        : _alpha(0.0), _rho(0.0), _nu(0.0)
        {
        }

        SabrModelParameter(
            const double alpha, const double rho, const double nu)
        : _alpha(alpha), _rho(rho), _nu(nu)
        {
        }

        const double alpha() const {return _alpha;}
        const double rho() const {return _rho;}
        const double nu() const {return _nu;}

        void setAlpha(const double alpha) {_alpha = alpha;}
        void setRho(const double rho) {_rho = rho;}
        void setNu(const double nu) {_nu = nu;}
    private:
        double _alpha;
        double _rho;
        double _nu;
    };


}  // namespace design_pattert



#endif // SABRMODELPARAMETER_H_INCLUDED
