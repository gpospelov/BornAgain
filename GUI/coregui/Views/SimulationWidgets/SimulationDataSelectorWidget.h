// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationDataSelectorWidget.h
//! @brief     Declares class SimulationDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONDATASELECTORWIDGET_H
#define SIMULATIONDATASELECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class ApplicationModels;
class QComboBox;
class MultiLayerItem;
class InstrumentItem;
class RealDataItem;

//! The SimulationDataSelectorWidget class represents widget to select instrument, sample and
//! real data. Located at the top of SimulationView.

class BA_CORE_API_ SimulationDataSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationDataSelectorWidget(QWidget *parent = 0);

    void setApplicationModels(ApplicationModels *applicationModels);

    const MultiLayerItem *selectedMultiLayerItem() const;
    const InstrumentItem *selectedInstrumentItem() const;
    const RealDataItem *selectedRealDataItem() const;

    void updateViewElements();

private:
    int selectedInstrumentIndex() const;
    int selectedSampleIndex() const;
    int selectedRealDataIndex() const;
    void updateSelection(QComboBox *comboBox, QStringList itemList, bool allow_none = false);

    QComboBox *m_instrumentCombo;
    QComboBox *m_sampleCombo;
    QComboBox *m_realDataCombo;
    ApplicationModels *m_applicationModels;
};

#endif // SIMULATIONDATASELECTORWIDGET_H
