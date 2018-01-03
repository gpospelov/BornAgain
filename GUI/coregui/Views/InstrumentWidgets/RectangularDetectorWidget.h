// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/RectangularDetectorWidget.h
//! @brief     Defines class RectangularDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef RECTANGULARDETECTORWIDGET_H
#define RECTANGULARDETECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <memory>

class ColumnResizer;
class RectangularDetectorItem;
class ComponentEditor;
class QGridLayout;
class ColumnResizer;

class BA_CORE_API_ RectangularDetectorWidget : public QWidget
{
    Q_OBJECT
public:
    RectangularDetectorWidget(ColumnResizer* columnResizer, RectangularDetectorItem* detectorItem,
                              QWidget* parent = 0);
    virtual ~RectangularDetectorWidget();

    void setDetectorItem(RectangularDetectorItem* detectorItem);

public slots:
    void onPropertyChanged(const QString& propertyName);
    void onColumnResizerDestroyed(QObject* object);
    void setColumnResizer(ColumnResizer* columnResizer);

private:
    void create_editors();
    void init_editors();
    void init_alignment_editors();

    ColumnResizer* m_columnResizer;
    ComponentEditor* m_xAxisEditor;
    ComponentEditor* m_yAxisEditor;
    ComponentEditor* m_resolutionFunctionEditor;
    ComponentEditor* m_alignmentEditor;

    ComponentEditor* m_positionsEditor;
    ComponentEditor* m_normalEditor;
    ComponentEditor* m_directionEditor;

    QGridLayout* m_gridLayout;

    RectangularDetectorItem* m_detectorItem;
};

#endif // RECTANGULARDETECTORWIDGET_H
