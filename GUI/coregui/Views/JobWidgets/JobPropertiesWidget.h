// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobPropertiesWidget.h
//! @brief     Defines class JobPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBPROPERTIESWIDGET_H
#define JOBPROPERTIESWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>
#include <memory>

class JobModel;
class JobItem;
class QTextEdit;
class QTabWidget;
class ComponentEditor;
class ModelMapper;

//! Widget to show and change properties of currently selected JobItem
//! Left buttom corner of JobView
class BA_CORE_API_ JobPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    enum ETabId { JOB_PROPERTIES, JOB_COMMENTS };
    explicit JobPropertiesWidget(QWidget *parent = 0);

    void setModel(JobModel *model);

    QSize sizeHint() const { return QSize(64, 256); }
    QSize minimumSizeHint() const { return QSize(64, 64); }

public slots:
    void setItem(JobItem *item);

private slots:
    void onTextChanged();

private:
    void updateItem(JobItem *item);

    JobModel *m_jobModel;
    JobItem *m_currentItem;
    QTabWidget *m_tabWidget;
    ComponentEditor *m_propertyEditor;
    QTextEdit *m_commentsEditor;
    bool m_block_update;
    std::unique_ptr<ModelMapper> m_mapper;
};

#endif
