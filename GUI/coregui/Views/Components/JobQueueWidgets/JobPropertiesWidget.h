// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobPropertiesWidget.h
//! @brief     Defines class JobPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBPROPERTIESWIDGET_H
#define JOBPROPERTIESWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>

//class JobQueueModel;
//class JobItem;
class NJobModel;
class NJobItem;
class QtProperty;
class QtVariantProperty;
class QTextEdit;
class QTabWidget;
class ParameterizedItem;
class UniversalPropertyEditor;

//! Widget to show and change properties of currently selected JobItem
//! Left buttom corner of JobQueueView
class BA_CORE_API_ JobPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    enum ETabId { JOB_PROPERTIES, JOB_COMMENTS };
    explicit JobPropertiesWidget(QWidget *parent = 0);

    void setModel(NJobModel *model);

    QSize sizeHint() const { return QSize(64, 256); }
    QSize minimumSizeHint() const { return QSize(64, 64); }

public slots:    
    void setItem(NJobItem *item);
//    void dataChanged(const QModelIndex &, const QModelIndex &);

private slots:
//    void valueChanged(QtProperty *property, const QVariant &value);

private:
//    void updateExpandState();
//    void addProperty(QtVariantProperty *property, const QString &id);

//    JobQueueModel *m_jobQueueModel;

    //! clear editor


    NJobModel *m_jobModel;

//    QMap<QtProperty *, QString> propertyToId;
//    QMap<QString, QtVariantProperty *> idToProperty;
//    QMap<QString, bool> idToExpanded;

    NJobItem *m_currentItem;
    QTabWidget *m_tabWidget;
    UniversalPropertyEditor *m_propertyEditor;
    QTextEdit *m_commentsEditor;
};



#endif
