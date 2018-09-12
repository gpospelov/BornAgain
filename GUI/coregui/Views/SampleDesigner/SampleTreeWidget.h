// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleTreeWidget.h
//! @brief     Defines class SampleTreeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLETREEWIDGET_H
#define SAMPLETREEWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QTreeView;

//! Holds tree to select top level sample items. Part of SampleView.

class BA_CORE_API_ SampleTreeWidget : public QWidget
{
    Q_OBJECT
public:
    SampleTreeWidget(QWidget* parent);

private:
    QTreeView* m_treeView;
};

#endif // SAMPLETREEWIDGET_H

