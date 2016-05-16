// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/ModelTuningWidget.h
//! @brief     Declares class ModelTuningWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MODELTUNINGWIDGET_H
#define MODELTUNINGWIDGET_H

#include <QWidget>
#include <memory>

class JobItem;
class SliderSettingsWidget;
class ModelTuningDelegate;
class JobModel;
class QTreeView;
class SampleModel;
class InstrumentModel;
class WarningSignWidget;
class SessionItem;
class FitTools;
class QItemSelectionModel;
class ParameterItem;

class ModelTuningWidget : public QWidget
{
    Q_OBJECT

public:
    ModelTuningWidget(JobModel *jobModel, QWidget *parent = 0);
    virtual ~ModelTuningWidget();

    void setItem(JobItem *item);

    QItemSelectionModel* selectionModel();

    QVector<ParameterItem *> getSelectedParameters();

signals:
    void itemContextMenuRequest(const QPoint &point);

public slots:
    void onCurrentLinkChanged(SessionItem* item);
    void onSliderValueChanged(double value);
    void onLockZValueChanged(bool value);
    void restoreModelsOfCurrentJobItem();

protected:
    void resizeEvent(QResizeEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void onPropertyChanged(const QString &property_name);
    void updateParameterModel();
    void onCustomContextMenuRequested(const QPoint &point);

private:
    QPoint getPositionForWarningSign();

    JobModel *m_jobModel;
    JobItem *m_currentJobItem;
    SliderSettingsWidget *m_sliderSettingsWidget;
    QTreeView *m_treeView;
    ModelTuningDelegate *m_delegate;
    WarningSignWidget *m_warningSign;
    FitTools *m_fitTools;
};

#endif
