// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/RectangularDetectorWidget.h
//! @brief     Defines class RectangularDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTANGULARDETECTORWIDGET_H
#define RECTANGULARDETECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class GroupBox;
class DetectorItem;
class AwesomePropertyEditor;
class QGridLayout;
class ColumnResizer;

class BA_CORE_API_ RectangularDetectorWidget : public QWidget
{
    Q_OBJECT
public:
    RectangularDetectorWidget(ColumnResizer *columnResizer,
                              DetectorItem *detectorItem, QWidget *parent = 0);

    void setDetectorItem(DetectorItem *detectorItem);

private:
    AwesomePropertyEditor *m_detectorTypeEditor;
    AwesomePropertyEditor *m_xAxisEditor;
    AwesomePropertyEditor *m_yAxisEditor;
    AwesomePropertyEditor *m_resolutionFunctionEditor;
    QGridLayout *m_gridLayout;
};

#endif
