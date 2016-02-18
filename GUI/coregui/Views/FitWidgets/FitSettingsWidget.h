// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.h
//! @brief     Defines class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSETTINGSWIDGET_H
#define FITSETTINGSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class FitModel;
class FitParameterWidget;
class QComboBox;


class BA_CORE_API_ FitSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    FitSettingsWidget(FitModel *fitModel, QWidget *parent);

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
    FitModel *m_fitModel;
    FitParameterWidget *m_fitParameter;
    QComboBox *m_sampleCombo;
    QComboBox *m_instrumentCombo;
};

#endif
