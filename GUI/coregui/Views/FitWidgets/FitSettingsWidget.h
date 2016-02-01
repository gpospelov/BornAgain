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
class SampleModel;
class InstrumentModel;
class FitParameterWidget;
class QComboBox;
class SessionModel;


class BA_CORE_API_ FitSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    FitSettingsWidget(FitModel *fitModel, SampleModel *sampleModel,
                      InstrumentModel *instrumentModel, QWidget *parent);

    void showEvent(QShowEvent *);
public slots:
    void onUpdateGUI();
    void onSampleChanged(int index);
    void onInstrumentChanged(int index);

private:
    FitModel *m_fitModel;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    FitParameterWidget *m_fitParameter;
    QComboBox *m_sampleCombo;
    QComboBox *m_instrumentCombo;

    void updateComboBox(QComboBox *combo, SessionModel *model, const QString &type, const QString &selectionType);
    void setFitSelection(QComboBox *combo, int index, const QString &prop);
};





#endif
