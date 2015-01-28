// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/InstrumentWidgets/DetectorEditorWidget.h
//! @brief     Defines class DetectorEditorWidget
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTOR_EDITOR_WIDGET_H
#define DETECTOR_EDITOR_WIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QComboBox;
class QLabel;
class ParameterizedItem;
class QSpinBox;
class QDoubleSpinBox;
class AngleProperty;

class BA_CORE_API_ DetectorEditorWidget : public QWidget
{
    Q_OBJECT

public:
    DetectorEditorWidget(QWidget *parent = 0);

    void initFromItem(ParameterizedItem *item);

public slots:
    void onPropertyChanged(const QString &);
    void onDetectorTypeChanged(int);
    void onAngleUnitsChanged(int);
    void onBinningTypeChanged(int);
    void onAngleEditorChanged(const QString &);

private:
    void updateWidgets();
    void setAngleUnits(QDoubleSpinBox *editor, const AngleProperty &units, double min_deg = -90.0, double max_deg = 90.0);

    QComboBox *m_detectorTypeCombo;
    QComboBox *m_unitsCombo;
    QComboBox *m_binningTypeCombo;

    QLabel *m_axis0Label;
    QLabel *m_axis1Label;

    QDoubleSpinBox *m_phiMinEdit;
    QDoubleSpinBox *m_phiMaxEdit;
    QSpinBox *m_nphiEdit;
    QDoubleSpinBox *m_alphaMinEdit;
    QDoubleSpinBox *m_alphaMaxEdit;
    QSpinBox *m_nalphaEdit;

    ParameterizedItem *m_currentItem;
    bool m_block_signals;
};

#endif
