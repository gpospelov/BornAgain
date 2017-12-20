// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorEditorWidget.h
//! @brief     Defines class DetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTOREDITORWIDGET_H
#define DETECTOREDITORWIDGET_H

#include "SessionItemWidget.h"

class GroupInfoBox;
class DetectorItem;
class ComponentEditor;
class QGridLayout;
class ColumnResizer;
class InstrumentItem;

class BA_CORE_API_ DetectorEditorWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    DetectorEditorWidget(ColumnResizer* columnResizer, QWidget* parent = 0);

signals:
    void extendedDetectorEditorRequest(DetectorItem*);

private slots:
    void onGroupBoxExtendedButton();

protected:
    virtual void subscribeToItem();
    virtual void unsubscribeFromItem();

private:
    void init_SubDetector_Widget();
    void remove_SubDetectorWidget();
    InstrumentItem* instrumentItem();

    ColumnResizer* m_columnResizer;
    ComponentEditor* m_detectorTypeEditor;
    GroupInfoBox* m_groupBox;
    DetectorItem* m_currentDetector;
    QWidget* m_subDetectorWidget;
};

#endif // DETECTOREDITORWIDGET_H
