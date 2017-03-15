// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorEditorWidget.h
//! @brief     Defines class DetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DETECTOREDITORWIDGET_H
#define DETECTOREDITORWIDGET_H

#include "SessionItemWidget.h"

class GroupInfoBox;
class DetectorItem;
class ComponentBoxEditor;
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

private:
    void init_SubDetector_Widget();
    InstrumentItem* instrumentItem();

    ColumnResizer* m_columnResizer;
    ComponentBoxEditor* m_detectorTypeEditor;
    GroupInfoBox* m_groupBox;
    DetectorItem* m_currentDetector;
    QWidget* m_subDetectorWidget;
};

#endif // DETECTOREDITORWIDGET_H
