// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleViewActions.h
//! @brief     Defines class SampleViewActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLEVIEWACTIONS_H
#define SAMPLEVIEWACTIONS_H

#include "WinDllMacros.h"
#include <QObject>

class SampleModel;
class QItemSelectionModel;

//! Holds all actions of SampleView.

class SampleViewActions : public QObject
{
    Q_OBJECT
public:
    SampleViewActions(SampleModel* model, QObject* parent);

    void setSelectionModel(QItemSelectionModel* selection_model);

private:
    SampleModel* m_model;
    QItemSelectionModel* m_selection_model;
};

#endif
