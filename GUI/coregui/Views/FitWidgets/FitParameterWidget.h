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
#include "SessionModel.h"
#include <QWidget>
#include <QStandardItemModel>
#include <QAbstractItemModel>

class QTreeView;
class MainWindow;
class FitSelectorModel;
class QMenu;
class SampleModel;
class InstrumentModel;
class FitModel;
class ParameterizedItem;
class FitParameterModel;
class QItemSelection;


class BA_CORE_API_ FitParameterWidget : public QWidget
{
    Q_OBJECT

public:
    FitParameterWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel,
                       FitModel *fitModel, QWidget *parent = 0);
    void addParameter();
    FitSelectorModel *buildSelectorModel();

public slots:
    void updateParameters();
    void expandFitPara();
    void onCustomContextMenu(const QPoint &point);
    void removeParameter();
    void onDataChanged(const QModelIndex &left, const QModelIndex &right);
    void onSelectionChanged(const QItemSelection&se, const QItemSelection&);

    void onSelectionChanged2(const QItemSelection &se);
private:
    QTreeView *m_treeview;
    QTreeView *m_fitpara;
    FitParameterModel *m_model;
    QMenu *m_contextMenu;
    QAction *m_remove;
    QAction *m_add;
    int m_parameter_count;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    FitModel *m_fitModel;
    FitSelectorModel *m_selector;
};



// -------------------------

class BA_CORE_API_ FitSelectorModel : public QStandardItemModel
{
    Q_OBJECT

public:
    QMimeData *mimeData(const QModelIndexList &indexes) const;
};



// -------------------------

class BA_CORE_API_ FitParameterModel : public SessionModel
{
    Q_OBJECT

public:
    explicit FitParameterModel(FitModel *fitmodel, QWidget *parent);
    ~FitParameterModel();
    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QStringList mimeTypes() const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                             const QModelIndex &parent) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const;
public slots:
    void addParameter();
private:
    FitModel *m_fitmodel;
};

#endif
