// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaskModel.h
//! @brief     Defines MaskModel classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKMODEL_H
#define MASKMODEL_H

#include "SessionModel.h"

class BA_CORE_API_ MaskModel : public SessionModel
{
    Q_OBJECT

public:
    explicit MaskModel(QObject *parent = 0);
    virtual ~MaskModel() {}
};

#endif // MASKMODEL_H
