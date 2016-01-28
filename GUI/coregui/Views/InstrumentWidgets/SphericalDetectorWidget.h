// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/SphericalDetectorWidget.h
//! @brief     Defines class SphericalDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPHERICALDETECTORWIDGET_H
#define SPHERICALDETECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class DetectorItem;
class AwesomePropertyEditor;
class QGridLayout;
class ColumnResizer;

//! Widget for editing a spherical detector settings

class BA_CORE_API_ SphericalDetectorWidget : public QWidget
{
    Q_OBJECT
public:
    SphericalDetectorWidget(ColumnResizer *columnResizer,
                            DetectorItem *detectorItem, QWidget *parent = 0);
    virtual ~SphericalDetectorWidget();

    void setDetectorItem(DetectorItem *detectorItem);

public slots:
    void onColumnResizerDestroyed(QObject *object);

private:
    ColumnResizer *m_columnResizer;
    AwesomePropertyEditor *m_detectorTypeEditor;
    AwesomePropertyEditor *m_phiAxisEditor;
    AwesomePropertyEditor *m_alphaAxisEditor;
    AwesomePropertyEditor *m_resolutionFunctionEditor;
    QGridLayout *m_gridLayout;
};

#endif
