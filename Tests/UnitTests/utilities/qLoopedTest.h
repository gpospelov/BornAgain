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

const complex_t I(0,1);

class QLoopedTest: public ::testing::TestWithParam<std::tuple<double, cvector_t>>
{
protected:
    QLoopedTest() {}
    virtual void SetUp()
    {
        double    qmag = std::get<0>(GetParam());
        cvector_t qdir = std::get<1>(GetParam());
        q = qmag * qdir;
    }
    cvector_t q;

    bool skip_q( double qmag_begin=1e-99, double qmag_end=1e99 ) {
        return q.mag()<qmag_begin || q.mag()>qmag_end;
    }
};


#endif // QLOOPEDTEST_H
