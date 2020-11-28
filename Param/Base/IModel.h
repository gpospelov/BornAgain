//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Base/IModel.h
//! @brief     Defines interface IModel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_PARAM_BASE_IMODEL_H
#define BORNAGAIN_PARAM_BASE_IMODEL_H

//! Root of class hierarchy for sample and instrument model.

class IModel {
public:
    virtual ~IModel() {}
};

#endif // BORNAGAIN_PARAM_BASE_IMODEL_H
