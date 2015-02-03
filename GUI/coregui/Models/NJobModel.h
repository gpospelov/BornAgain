// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.h
//! @brief     Defines class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef NJOBMODEL_H
#define NJOBMODEL_H

#include "SessionModel.h"

class BA_CORE_API_ NJobModel : public SessionModel
{
    Q_OBJECT

public:
    explicit NJobModel(QObject *parent = 0);
    ~NJobModel(){}


private:

};

#endif
