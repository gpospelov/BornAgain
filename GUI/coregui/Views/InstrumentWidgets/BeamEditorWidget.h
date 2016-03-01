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

#ifndef BEAMEDITORWIDGET_H
#define BEAMEDITORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include "ParameterizedItem.h"

class BeamItem;
class ComponentEditor;
class ComponentEditorBox;
class QGridLayout;

class BA_CORE_API_ BeamEditorWidget : public QWidget
{
    Q_OBJECT
public:
    BeamEditorWidget(QWidget *parent = 0);

    void setBeamItem(BeamItem *beamItem);

    QGridLayout *getGridLayout() { return m_gridLayout;}

private slots:
    void onDialogRequest(ParameterizedItem *item, QString name);

private:
    ComponentEditor *m_intensityEditor;
    ComponentEditorBox *m_wavelengthPresenter;
    ComponentEditorBox *m_inclinationAnglePresenter;
    ComponentEditorBox *m_azimuthalAnglePresenter;
    QGridLayout *m_gridLayout;
    BeamItem *m_beamItem;
};

#endif
