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

#ifndef IMPORTDATAWIDGET_H
#define IMPORTDATAWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QLineEdit;
class ColorMapPlot;
class FitModel;

class BA_CORE_API_ ImportDataWidget : public QWidget
{
    Q_OBJECT

public:
    //! TOY: loads file from path and plot data
    ImportDataWidget(FitModel *fitModel, QWidget *parent = 0);

    void showEvent(QShowEvent *);


public slots:
    //! when the text points to existing file, then plot file
    void onTextUpdate();

    void onUpdateGUI();

private:
    QLineEdit *m_line;
    ColorMapPlot *m_plot;
    FitModel *m_fitModel;
};

#endif
