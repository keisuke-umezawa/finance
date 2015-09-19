/*
 * ClosedForm.h
 *
 *  Created on: 2015/05/06
 *      Author: Keisuke
 */

#ifndef CLOSEDFORM_H_INCLUDED
#define CLOSEDFORM_H_INCLUDED

#include "ModelParameter.h"

namespace lmm {
    const double evaluate(
        const CapletAdapter& caplet,
        const CevModelParameter& parameter);

    const double evaluate(
        const CapAdapter& cap,
        const CevModelParameter& parameter);
}

#endif // CLOSEDFORM_H_INCLUDED
