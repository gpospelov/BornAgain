// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidget.h
//! @brief     Declares class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERWIDGET_H
#define FITPARAMETERWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <memory>

class JobItem;
class ParameterTuningWidget;
class QTreeView;
class QSignalMapper;
class QAction;
class QMenu;
class FitParameterModel;
class FitParameterAbsModel;
class ParameterItem;
class FitParameterItem;
class FitParameterLinkItem;
class QItemSelection;
class SessionModelDelegate;
class DeleteEventFilter;
class InfoLabelController;

//! The FitParametersWidget class contains a tree view to set fit parameters (fix/release,
//! starting value, min/max bounds). It occupies buttom right corner of JobView.

class BA_CORE_API_ FitParameterWidget : public QWidget
{
    Q_OBJECT
public:
    FitParameterWidget(QWidget *parent = 0);

    void setItem(JobItem *jobItem);
    void setParameterTuningWidget(ParameterTuningWidget *tuningWidget);

public slots:
    void onTuningWidgetContextMenu(const QPoint &point);
    void onFitParameterTreeContextMenu(const QPoint &point);
    void onTuningWidgetSelectionChanged(const QItemSelection&selection);
    void onFitParametersSelectionChanged(const QItemSelection &selection);

private slots:
    void onCreateFitParAction();
    void onRemoveFromFitParAction();
    void onRemoveFitParAction();
    void onAddToFitParAction(int ipar);
    void spanParameters();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void init_actions();
    void initTuningWidgetContextMenu(QMenu &menu);
    void initFitParameterTreeContextMenu(QMenu &menu);

    void init_fit_model();
    void init_fit_containers();

    bool canCreateFitParameter();
    bool canRemoveFromFitParameters();

    void setActionsEnabled(bool value);
    void connectTuningWidgetSelection(bool active);
    void connectFitParametersSelection(bool active);

    QVector<FitParameterItem *> selectedFitParameters();
    QVector<FitParameterLinkItem *> selectedFitParameterLinks();

    QTreeView *m_treeView;
    JobItem *m_jobItem;
    ParameterTuningWidget *m_tuningWidget;
    QAction *m_createFitParAction;
    QAction *m_removeFromFitParAction;
    QAction *m_removeFitParAction;
    QSignalMapper *m_signalMapper;
    FitParameterAbsModel* m_fitParameterModel;
    SessionModelDelegate *m_delegate;
    DeleteEventFilter *m_keyboardFilter;
    InfoLabelController *m_infoLabel;
};

#endif
