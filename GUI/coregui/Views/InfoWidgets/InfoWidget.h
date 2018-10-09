// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/InfoWidget.h
//! @brief     Defines class InfoWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include "InfoPanel.h"

class SampleModel;
class InstrumentModel;
class PySampleWidget;

//! The InfoWidget resides at the bottom of SampleView and displays a Python script.

class BA_CORE_API_ InfoWidget : public InfoPanel
{
    Q_OBJECT

public:
    explicit InfoWidget(QWidget* parent = nullptr);

    void setSampleModel(SampleModel* sampleModel);
    void setInstrumentModel(InstrumentModel* instrumentModel);

private:
    PySampleWidget* m_pySampleWidget;
};

#endif // INFOWIDGET_H
