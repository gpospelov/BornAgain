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

#include <QWidget>
#include <memory>

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

class ParameterTuningWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterTuningWidget(QWidget* parent = 0);

    void setItem(JobItem* item);

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

private slots:
    void onPropertyChanged(const QString& property_name);
    void updateParameterModel();
    void onCustomContextMenuRequested(const QPoint& point);

private:
    void updateDragAndDropSettings();

    void setTuningDelegateEnabled(bool enabled);
    void closeActiveEditors();

    JobRealTimeToolBar* m_toolBar;
    JobModel* m_jobModel;
    JobItem* m_currentJobItem;
    ParameterTuningModel* m_parameterTuningModel;
    SliderSettingsWidget* m_sliderSettingsWidget;
    QTreeView* m_treeView;
    ParameterTuningDelegate* m_delegate;
    WarningSign* m_warningSign;
};

#endif // PARAMETERTUNINGWIDGET_H
