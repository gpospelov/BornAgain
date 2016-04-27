// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParametersWidget.h
//! @brief     Declares class FitParametersWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERSWIDGET_H
#define FITPARAMETERSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <memory>

class JobItem;
class ModelTuningWidget;
class QTreeView;
class QSignalMapper;
class QAction;
class QMenu;
class FitParameterModel;
class ParameterItem;

//! The FitParametersWidget class contains a tree view to set fit parameters (fix/release,
//! starting value, min/max bounds). It occupies buttom right corner of JobView.

class BA_CORE_API_ FitParametersWidget : public QWidget
{
    Q_OBJECT
public:
    FitParametersWidget(QWidget *parent = 0);
    ~FitParametersWidget();

    void setItem(JobItem *jobItem);
    void setModelTuningWidget(ModelTuningWidget *tuningWidget);

public slots:
    void onTuningWidgetContextMenu(const QPoint &point);

private slots:
    void onCreateFitParAction();
    void onRemoveFromFitParAction();
    void onAddToFitParAction(int ipar);

private:
    void init_actions();
    void initTuningWidgetContextMenu(QMenu &menu);
    void stop_tracking_job_item();
    void init_job_item();
    void spanParameters();

    bool isCreateFitParameterPossible();

    void setActionsEnabled(bool value);


    QVector<ParameterItem *> getSelectedParameters();

    QTreeView *m_treeView;
    JobItem *m_jobItem;
    ModelTuningWidget *m_tuningWidget;
    QAction *m_createFitParAction;
    QAction *m_removeFromFitParAction;
    QSignalMapper *m_signalMapper;
    std::unique_ptr<FitParameterModel> m_fitParameterModel;
};

#endif
