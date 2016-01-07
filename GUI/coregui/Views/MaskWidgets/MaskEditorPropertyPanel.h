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
class IntensityDataItem;
class AccordionWidget;

//! Tool widget for MaskEditor

class MaskEditorPropertyPanel : public QWidget
{
    Q_OBJECT
public:
    MaskEditorPropertyPanel(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(128, 128); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

    void setMaskContext(SessionModel *model, const QModelIndex &maskContainerIndex,
                        IntensityDataItem *intensityItem);

    QItemSelectionModel* selectionModel();

    void setPanelHidden(bool value);

signals:
    void itemContextMenuRequest(const QPoint &point);

private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onCustomContextMenuRequested(const QPoint &point);

private:
    void setup_MaskStack(AccordionWidget *accordion);
    void setup_MaskProperties(AccordionWidget *accordion);
    void setup_PlotProperties(AccordionWidget *accordion);

    QListView *m_listView;
    AwesomePropertyEditor *m_maskPropertyEditor;
    AwesomePropertyEditor *m_plotPropertyEditor;
    SessionModel *m_maskModel;
    QModelIndex m_rootIndex;
    IntensityDataItem *m_intensityDataItem;
};


#endif
