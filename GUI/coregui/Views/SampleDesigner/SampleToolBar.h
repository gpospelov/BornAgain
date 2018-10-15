// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleToolBar.h
//! @brief     Defines class SampleToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLETOOLBAR_H
#define SAMPLETOOLBAR_H

#include "StyledToolBar.h"
#include <QTreeView>

class QAction;
class QToolButton;
class QToolBar;
class QComboBox;
class QString;
class QButtonGroup;
class SampleModel;
class RealSpaceDialog;
class SampleViewActions;

//! The SampleToolBar class represents a main toolbar on top of SampleView window

class BA_CORE_API_ SampleToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit SampleToolBar(SampleViewActions* sampleActions = nullptr,
                           QWidget* parent = nullptr);

signals:
    void deleteItems();
    void selectionMode(int);
    void centerView();
    void smartAlign();
    void changeScale(double);
    void zoomIn();
    void zoomOut();

public slots:
    void onViewSelectionMode(int);
    void onScaleComboChanged(const QString&);
    void onMaterialEditorCall();
    void onRealSpaceViewerCall();

private:
    SampleModel* sampleModel();
    QItemSelectionModel* selectionModel();

    QButtonGroup* m_pointerModeGroup;
    QToolButton* m_removeButton;
    QToolButton* m_centerViewButton;
    QToolButton* m_alignItemsButton;
    QComboBox* m_scaleCombo;
    QToolButton* m_materialEditorButton;
    QAction* m_zoomInAction;
    QAction* m_zoomOutAction;

    QToolButton* m_RealSpaceViewerButton;
    QToolButton* m_RealSpaceViewerButton2;
    RealSpaceDialog* m_dialog;

    SampleViewActions* m_sampleViewActions;

    bool m_dialog_on;
};

#endif // SAMPLETOOLBAR_H
