// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorEditorWidget.h
//! @brief     Declares class DetectorEditorWidget
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

#include "WinDllMacros.h"
#include <QWidget>
#include <memory>

class GroupInfoBox;
class DetectorItem;
class ComponentBoxEditor;
class QGridLayout;
class SphericalDetectorWidget;
class ColumnResizer;

class BA_CORE_API_ DetectorEditorWidget : public QWidget
{
    Q_OBJECT
public:
    DetectorEditorWidget(ColumnResizer *columnResizer, QWidget *parent = 0);
    virtual ~DetectorEditorWidget();

    void setDetectorItem(DetectorItem *detectorItem);

signals:
    void extendedDetectorEditorRequest(DetectorItem *);

public slots:
    void onPropertyChanged(const QString &propertyName);

private slots:
    void onGroupBoxExtendedButton();

private:
    void init_SubDetector_Widget();
    ComponentBoxEditor *m_detectorTypeEditor;
    ColumnResizer *m_columnResizer;
    GroupInfoBox *m_groupBox;
    DetectorItem *m_detectorItem;
    QWidget *m_subDetectorWidget;
};

#endif
