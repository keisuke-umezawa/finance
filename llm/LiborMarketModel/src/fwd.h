/*
 * fwd.h
 *
 *  Created on: 2015/05/01
 *      Author: Keisuke
 */

#ifndef FWD_H_INCLUDED
#define FWD_H_INCLUDED

#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace ublas = boost::numeric::ublas;

namespace lmm {
    typedef boost::gregorian::date date_t;
}  // namespace llm

#endif // FWD_H_INCLUDED
