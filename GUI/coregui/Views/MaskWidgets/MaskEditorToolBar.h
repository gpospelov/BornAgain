// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorToolBar.h
//! @brief     Defines class MaskEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORTOOLBAR_H
#define MASKEDITORTOOLBAR_H

#include "WinDllMacros.h"
#include "MaskEditorFlags.h"
#include <QToolBar>

class QButtonGroup;

//! Main class to draw masks on top of intensity data map

class BA_CORE_API_ MaskEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaskEditorToolBar(QWidget *parent = 0);

signals:
    void activityModeChanged(MaskEditorFlags::Activity);
    void toolPanelRequest();
    void changeStackingOrderRequest(MaskEditorFlags::Stacking);
    void maskValueChanged(MaskEditorFlags::MaskValue);

public slots:
    void onChangeActivityRequest(MaskEditorFlags::Activity value);

private slots:
    void onActivityGroupChange(int value);
    void onMaskValueGroupChange(int value);
    void onStackingOrderGroupChange(int value);

private:
    void setup_selection_group();
    void setup_maskvalue_group();
    void setup_shapes_group();
    void setup_maskmodify_group();
    void setup_extratools_group();
    void add_separator();

    MaskEditorFlags::Activity getCurrentActivity() const;
    void setCurrentActivity(MaskEditorFlags::Activity value);

    QButtonGroup *m_activityButtonGroup;
    QButtonGroup *m_maskValueGroup;
    QButtonGroup *m_maskStackingOrderGroup;
    MaskEditorFlags::Activity m_previousActivity;
};


#endif
