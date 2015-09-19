/*
 * Normals.h
 *
 *  Created on: 2015/04/30
 *      Author: Keisuke
 */

#ifndef NORMALS_H_INCLUDED
#define NORMALS_H_INCLUDED

namespace lmm {
    double NormalDensity(double x);

    double CumulativeNormal(double x);

    double InverseCumulativeNormal(double x);
} // namespace lmm {

#endif // NORMALS_H_INCLUDED
