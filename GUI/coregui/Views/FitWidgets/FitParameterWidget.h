// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidget.h
//! @brief     Defines class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERWIDGET_H
#define FITPARAMETERWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QStandardItemModel>

class QTreeView;
class MainWindow;
class FitParameterModel;
class FitSelectorModel;
class QMenu;


class BA_CORE_API_ FitParameterWidget : public QWidget
{
    Q_OBJECT

public:
// FIXME_DAVID - suggestion: Change constructor to not to rely on MainWindow
// a) to provide looser coupling b) to avoid duplication parent <--> main
//
// Just use same approach as in other models, e.g. new SampleView(m_sampleModel, m_instrumentModel);

    FitParameterWidget(MainWindow *main, QWidget *parent = 0);
    void addParameter();
    FitSelectorModel *getSelectorModel();



public slots:
    void updateParameters();
    void expandFitPara();
    void onCustomContextMenu(const QPoint &point);
    void removeParameter();
    void onAddParameter();
    void onDataChanged(const QModelIndex &left, const QModelIndex &right);

private:
    QTreeView *m_treeview;
    QTreeView *m_fitpara;
    MainWindow *m_main;
    FitParameterModel *m_model;
    QMenu *m_contextMenu;
    QAction *m_remove;
    QAction *m_add;
    int m_parameter_count;
};




// -------------------------

class BA_CORE_API_ FitSelectorModel : public QStandardItemModel
{
    Q_OBJECT

public:
    QMimeData *mimeData(const QModelIndexList &indexes) const;
};



// -------------------------

class BA_CORE_API_ FitParameterModel : public QStandardItemModel
{
    Q_OBJECT

public:
    bool dropMimeData(const QMimeData *data,
         Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList mimeTypes() const;

signals:
    void dropFinished();
};

#endif
