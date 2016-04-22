// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/ObsoleteImportDataWidget.h
//! @brief     Declares class ObsoleteImportDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEIMPORTDATAWIDGET_H
#define OBSOLETEIMPORTDATAWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QLineEdit;
class ColorMapPlot;
class ObsoleteFitModel;

class BA_CORE_API_ ObsoleteImportDataWidget : public QWidget
{
    Q_OBJECT

public:
    //! TOY: loads file from path and plot data
    ObsoleteImportDataWidget(ObsoleteFitModel *fitModel, QWidget *parent = 0);

    void showEvent(QShowEvent *);


public slots:
    //! when the text points to existing file, then plot file
    void onTextUpdate();

    void onUpdateGUI();

private:
    QLineEdit *m_line;
    ColorMapPlot *m_plot;
    ObsoleteFitModel *m_fitModel;
};

#endif
