// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ParameterTuningWidget.h
//! @brief     Defines class ParameterTuningWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERTUNINGWIDGET_H
#define PARAMETERTUNINGWIDGET_H

#include "SessionItemWidget.h"

class JobRealTimeToolBar;
class JobModel;
class JobItem;
class SessionItem;
class QItemSelectionModel;
class ParameterTuningDelegate;
class ParameterTuningModel;
class SliderSettingsWidget;
class QTreeView;
class WarningSign;
class ParameterItem;

//! Main widget for real time parameter tuning.
//! Contains a tree for parameter tuning and the model to provide drag-and-drop in FitActivityPanel.

class ParameterTuningWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit ParameterTuningWidget(QWidget* parent = 0);

    QItemSelectionModel* selectionModel();

    QVector<ParameterItem*> getSelectedParameters();

signals:
    void itemContextMenuRequest(const QPoint& point);

public slots:
    void onCurrentLinkChanged(SessionItem* item);
    void onSliderValueChanged(double value);
    void onLockZValueChanged(bool value);
    void restoreModelsOfCurrentJobItem();
    void makeSelected(ParameterItem* item);

protected:
    void resizeEvent(QResizeEvent* event);
    void contextMenuEvent(QContextMenuEvent*);
    void subscribeToItem();

private slots:
    void onPropertyChanged(const QString& property_name);
    void updateParameterModel();
    void onCustomContextMenuRequested(const QPoint& point);

private:
    JobItem* jobItem();
    void updateDragAndDropSettings();
    void setTuningDelegateEnabled(bool enabled);
    void closeActiveEditors();

    JobRealTimeToolBar* m_toolBar;
    JobModel* m_jobModel;
    ParameterTuningModel* m_parameterTuningModel;
    SliderSettingsWidget* m_sliderSettingsWidget;
    QTreeView* m_treeView;
    ParameterTuningDelegate* m_delegate;
    WarningSign* m_warningSign;
};

#endif // PARAMETERTUNINGWIDGET_H
