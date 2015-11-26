// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorPropertyPanel.h
//! @brief     Defines class MaskEditorPropertyPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORPROPERTYPANEL_H
#define MASKEDITORPROPERTYPANEL_H

#include "MaskEditorFlags.h"
#include <QWidget>
#include <QModelIndex>

class QListView;
class SessionModel;
class QModelIndex;
class AwesomePropertyEditor;
class QItemSelection;
class QItemSelectionModel;
class QButtonGroup;

//! Tool widget for MaskEditor

class MaskEditorPropertyPanel : public QWidget
{
    Q_OBJECT
public:
    MaskEditorPropertyPanel(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(128, 128); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

    void setModel(SessionModel *model, const QModelIndex &root_index);
    QItemSelectionModel* selectionModel();

    void setPanelHidden(bool value);

signals:
    void itemContextMenuRequest(const QPoint &point);

private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onCustomContextMenuRequested(const QPoint &point);

private:
    QListView *m_listView;
    AwesomePropertyEditor *m_maskPropertyEditor;
    AwesomePropertyEditor *m_plotPropertyEditor;
    SessionModel *m_maskModel;
    QModelIndex m_rootIndex;
};


#endif
