// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/ModelTuningWidget.h
//! @brief     Defines class ModelTuningWidget
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

class JobItem;
class SliderSettingsWidget;
class ModelTuningDelegate;
class JobModel;
class QTreeView;
class SampleModel;
class InstrumentModel;
class WarningSignWidget;
class ModelMapper;
class SessionItem;
class FitTools;

class ModelTuningWidget : public QWidget
{
    Q_OBJECT

public:
    ModelTuningWidget(JobModel *jobModel, QWidget *parent = 0);
    virtual ~ModelTuningWidget();

    void setCurrentItem(JobItem *item);

public slots:
    void onCurrentLinkChanged(SessionItem* item);
    void onSliderValueChanged(double value);
    void onLockZValueChanged(bool value);
    void restoreModelsOfCurrentJobItem();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onPropertyChanged(const QString &property_name);
    void updateParameterModel();

private:
    QPoint getPositionForWarningSign();

    JobModel *m_jobModel;
    JobItem *m_currentJobItem;
    SliderSettingsWidget *m_sliderSettingsWidget;
    QTreeView *m_treeView;
    ModelTuningDelegate *m_delegate;
    WarningSignWidget *m_warningSign;
    ModelMapper *m_mapper;
    FitTools *m_fitTools;
};

#endif
