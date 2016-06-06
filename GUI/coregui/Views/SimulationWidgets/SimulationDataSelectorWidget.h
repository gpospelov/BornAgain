// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SimulationWidgets/SimulationDataSelectorWidget.h
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
class QPushButton;
class QLabel;
class MultiLayerItem;
class InstrumentItem;

//! The SimulationDataSelectorWidget class represents widget to select instrument, sample and
//! real data. Located at the top of SimulationView.

class BA_CORE_API_ SimulationDataSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationDataSelectorWidget(QWidget *parent = 0);

    void setApplicationModels(ApplicationModels *applicationModels);

    QString getSelectedInstrumentName() const;
    int getSelectedInstrumentIndex() const;

    QString getSelectedSampleName() const;
    int getSelectedSampleIndex() const;

    void updateViewElements();

    const MultiLayerItem *getSelectedMultiLayerItem() const;
    const InstrumentItem *getSelectedInstrumentItem() const;


public slots:
    void onOpenFile();

private:
    void updateSelectionBox(QComboBox *comboBox, QStringList itemList);

    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *selectRealData;
    QLabel *pathLabel;
    ApplicationModels *m_applicationModels;
};

#endif
