// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/SphericalDetectorWidget.h
//! @brief     Defines class SphericalDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SPHERICALDETECTORWIDGET_H
#define SPHERICALDETECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class DetectorItem;
class QGridLayout;
class ColumnResizer;
class ComponentBoxEditor;

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
    ComponentBoxEditor *m_phiAxisEditor;
    ComponentBoxEditor *m_alphaAxisEditor;
    ComponentBoxEditor *m_resolutionFunctionEditor;
    QGridLayout *m_gridLayout;
};

#endif
