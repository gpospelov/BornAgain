// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      qLoopedTest.h
//! @brief     Auxiliary utility to loop over q vectors for tests.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef QLOOPEDTEST_H
#define QLOOPEDTEST_H

#include <tuple>

const complex_t I(0,1);

class QLoopedTest:
public ::testing::TestWithParam<std::tuple<cvector_t, cvector_t, double, complex_t>>
{
protected:
    QLoopedTest() {}
    virtual void SetUp()
    {
        cvector_t qdir = std::get<0>(GetParam());
        cvector_t qdev = std::get<1>(GetParam());
        double    qmag = std::get<2>(GetParam());
        complex_t qeps = std::get<3>(GetParam());
        q = qmag * (qdir + qeps*qdev).unit();
    }
    cvector_t q;

    bool skip_q( double qmag_begin=1e-99, double qmag_end=1e99 ) {
        return q.mag()<qmag_begin || q.mag()>qmag_end;
    }
};

auto qlist = testing::Combine(
    testing::Values(
        cvector_t({ 1, 0, 0 }),
        cvector_t({ 0, 1, 0 }),
        cvector_t({ 0, 0, 1 }),
        cvector_t({ 1, 1, 0 }),
        cvector_t({ 1, 0, 1 }),
        cvector_t({ 1, 0, 1 }),
        cvector_t({ 1, 1, 1 })
        ),
    testing::Values(
        cvector_t({ 1, 0, 0 }),
        cvector_t({ 0, 1, 0 }),
        cvector_t({ 0, 0, 1 }),
        cvector_t({ 1, 1, 0 }),
        cvector_t({ 1, 0, 1 }),
        cvector_t({ 1, 0, 1 }),
        cvector_t({ 1, 1, 1 })
        ),
    testing::Values(
        1e-19, 1e-17, 1e-15, 1e-13, 1e-11, 1e-9, 1e-7, 1e-5, 1e-4, 1e-3, 1e-2, .1,
        1., 1e1, 1e2, 1e3, 1e4 ),
    testing::Values(
        -1e-15, +1e-14, -1e-13*I, +1e-12*I,
        -1e-11, +1e-10, -1e-9*I, +1e-8*I,
        -1e-7, +1e-6, -1e-5*I, +1e-4*I,
        -1e-3, +1e-2, -1e-1*I, +1e-1*I,
        .9, -.99, .999, -.9999 )
    );

#endif // QLOOPEDTEST_H
