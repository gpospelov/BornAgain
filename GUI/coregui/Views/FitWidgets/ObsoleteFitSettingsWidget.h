// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/ObsoleteFitSettingsWidget.h
//! @brief     Declares class ObsoleteFitSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEFITSETTINGSWIDGET_H
#define OBSOLETEFITSETTINGSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class ObsoleteFitModel;
class ObsoleteFitParameterWidget;
class QComboBox;


class BA_CORE_API_ ObsoleteFitSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    ObsoleteFitSettingsWidget(ObsoleteFitModel *fitModel, QWidget *parent);

    //! we update GUI when widget is shown
    void showEvent(QShowEvent *);

    //! connect and disconnect signals for comboboxes
    void connectCombos();
    void disconnectCombos();

public slots:
    //! call this slot to refresh comboboxes and fitparameters
    void onUpdateGUI();

    //! slots for sample/instrument changes
    void onSampleChanged(int index);
    void onInstrumentChanged(int index);

private:
    ObsoleteFitModel *m_fitModel;
    ObsoleteFitParameterWidget *m_fitParameter;
    QComboBox *m_sampleCombo;
    QComboBox *m_instrumentCombo;
};

#endif
