/*
 * Calibrator.h
 *
 *  Created on: 2015/04/30
 *      Author: Keisuke
 */


#ifndef CALIBRATOR_H_INCLUDED
#define CALIBRATOR_H_INCLUDED

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "fwd.h"

namespace lmm {
    class IOptimizer {
    public:
        virtual ~IOptimizer() {}

        ublas::vector<double> optimize(
            const boost::function<double(ublas::vector<double>)>& f,
            const ublas::vector<double>& vec) const
        {
            return doOptimize(f, vec);
        }

        boost::shared_ptr<IOptimizer> clone() const
        {
            return boost::shared_ptr<IOptimizer>(doClone());
        }
    private:
        virtual IOptimizer* doClone() const = 0;
        virtual ublas::vector<double> doOptimize(
            const boost::function<double(ublas::vector<double>)>& f,
            const ublas::vector<double>& vec) const = 0;
    };

    class Calibrator {
    public:
        Calibrator(const IOptimizer& optimizer)
        : _optimizer(optimizer.clone())
        {
        }

        ublas::vector<double> calibrate(
            const boost::function<double(ublas::vector<double>)>& f,
            const ublas::vector<double>& vec) const
        {
            return _optimizer->optimize(f, vec);
        }

    private:
        const boost::shared_ptr<const IOptimizer> _optimizer;
    };
} // namespace lmm {

#endif // CALIBRATOR_H_INCLUDED
