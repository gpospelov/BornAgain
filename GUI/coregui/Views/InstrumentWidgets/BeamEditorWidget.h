// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/BeamEditorWidget.h
//! @brief     Defines class BeamEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAM_EDITOR_WIDGET_H
#define BEAM_EDITOR_WIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QComboBox;
class QDoubleSpinBox;
class QLineEdit;
class QLabel;
class BeamItem;
class QDoubleValidator;
class AngleProperty;

class BA_CORE_API_ BeamEditorWidget : public QWidget
{
    Q_OBJECT

public:
    BeamEditorWidget(QWidget *parent = 0);

    void initFromItem(BeamItem *item);

public slots:
    void onIntensityEditingFinished();
    void onChangedWavelength(const QString &);
    void onChangedAngle(const QString &);

    void onPropertyChanged(const QString &);

    void onAngleUnitsChanged(int);

private:
    void updateWidgets();
    void setBlockSignals(bool flag);
    void setAngleUnits(QDoubleSpinBox *, const AngleProperty &units, double min_deg = -90.0, double max_deg = 90.0);

    QLineEdit *m_intensityText;
    QDoubleValidator *m_intensityValidator;
    QDoubleSpinBox *m_wavelengthSpinBox;
    QComboBox *m_angleUnits;
    QDoubleSpinBox *m_inclinationAngleSpinBox;
    QDoubleSpinBox *m_azimuthalAngleSpinBox;
    QComboBox *m_beamTypeCombo;
    BeamItem *m_currentItem;
    bool m_block_signals;
};


#endif
