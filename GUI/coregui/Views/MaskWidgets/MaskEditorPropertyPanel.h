// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorPropertyPanel.h
//! @brief     Defines class MaskEditorPropertyPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORPROPERTYPANEL_H
#define MASKEDITORPROPERTYPANEL_H

#include "MaskEditorFlags.h"
#include <QModelIndex>
#include <QWidget>

class QListView;
class SessionModel;
class QModelIndex;
class ComponentEditor;
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
    ComponentEditor *m_maskPropertyEditor;
    ComponentEditor *m_plotPropertyEditor;
    AccordionWidget *m_accordion;
    SessionModel *m_maskModel;
    QModelIndex m_rootIndex;
    IntensityDataItem *m_intensityDataItem;
};

#endif // MASKEDITORPROPERTYPANEL_H
