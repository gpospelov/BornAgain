// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpacePanel.h
//! @brief     Defines class RealSpacePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALSPACEPANEL_H
#define REALSPACEPANEL_H

#include "WinDllMacros.h"
#include <QWidget>

class QTreeView;
class ComponentEditor;
class SampleModel;
class FilterPropertyProxy;
class QItemSelection;

//! Panel with item selector, property editor on the right side of RealSpaceWidget.

class BA_CORE_API_ RealSpacePanel : public QWidget
{
    Q_OBJECT

public:
    RealSpacePanel(QWidget* parent = 0);

    void setModel(SampleModel* model);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void selectionChanged(const QModelIndex& index);

public slots:
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection&);

private:
    QTreeView* m_treeView;
    ComponentEditor* m_componentEditor;
    SampleModel* m_model;
    FilterPropertyProxy* m_proxy;
};

#endif // REALSPACEPANEL_H
