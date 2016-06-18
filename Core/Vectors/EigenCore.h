// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vectors/EigenCore.h
//! @brief     Include to deal with Eigen alignment centrally
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef EIGENCORE_H
#define EIGENCORE_H

// This include file is introduced to deal with Eigen alignment
// see http://eigen.tuxfamily.org/dox-devel/group__TopicStructHavingEigenMembers.html

#ifndef SWIG
#ifndef _WIN32
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <Eigen/Core>
#pragma GCC diagnostic pop
#endif


#endif // EIGENCORE_H

