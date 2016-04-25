// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      qgenerator.h
//! @brief     Auxiliary utility to generate q vectors for tests.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef QGENERATOR_H
#define QGENERATOR_H

namespace qGenerator {
    static complex_t I(0,1);
    // different directions of q
    static const int nqdir = 13;
    static const cvector_t qdirs[nqdir] = {
        { 1., 0., 0 },
        { 1.+0.1*I, 0., 0 },
        { 0., 1., 0 },
        { 0., 0., 1.-.1*I },
        { 1., 1., 0 },
        { 1.+0.1*I, 1.+0.1*I, 0 },
        { 0., 1., 1. },
        { 1.-.1*I, 0., 1.-.1*I },
        { 1., 2., 0. },
        { 1.+0.01*I, 2.+0.4*I, 0. },
        { 1., 1., 1 },
        { 1.+0.1*I, 1.+0.1*I, 1.+0.1*I },
        { 2.17+.03*I, 3.49-.04*I, .752+.01*I }
    };
    // different magnitudes of q
    static const int nqmag = 23;
    //! Returns q for given index
    cvector_t q( size_t idx, double qmag_begin, double qmag_end)
    {
        size_t idir = idx/nqmag;
        size_t jmag = idx%nqmag;
        double qmag =
            pow( qmag_end,   jmag/(nqmag-1.) ) *
            pow( qmag_begin, (nqmag-1-jmag)/(nqmag-1.) );
        return qmag * qdirs[idir].unit();
    }
    size_t nq() { return nqdir * nqmag; }
}

#endif // QGENERATOR_H
