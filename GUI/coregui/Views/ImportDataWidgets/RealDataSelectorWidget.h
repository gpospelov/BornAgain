// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.h
//! @brief     Declares class RealDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATASELECTORWIDGET_H
#define REALDATASELECTORWIDGET_H

#include <QWidget>
#include "WinDllMacros.h"

//! The RealDataSelectorWidget class holds QListView on the left side of ImportDataView to
//! switch between different RealDataItem's

class BA_CORE_API_ RealDataSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    RealDataSelectorWidget(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(200, 400); }
    QSize minimumSizeHint() const { return QSize(128, 200); }

private:
    class QListView *m_listView;
};

#endif // REALDATASELECTORWIDGET_H
