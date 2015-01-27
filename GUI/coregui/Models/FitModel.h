// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitModel.h
//! @brief     Defines class FitModel
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITMODEL_H
#define FITMODEL_H


#include "SessionModel.h"

class BA_CORE_API_ FitModel : public SessionModel
{
    Q_OBJECT

public:
    explicit FitModel(QObject *parent = 0);
    ~FitModel(){}

};




#endif
