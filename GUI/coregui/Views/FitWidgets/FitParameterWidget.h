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
class QSplitter;
class KeyboardFilter;

class BA_CORE_API_ FitParameterWidget : public QWidget
{
    Q_OBJECT

public:
    static const QString MIME_TYPE;
    FitParameterWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel,
                       FitModel *fitModel, QWidget *parent = 0);
public slots:
    void updateSelector();
    void spanParameters();
    void removeSelectedItem();

    void onCustomContextMenu(const QPoint &point);
    void onRemoveParameter();

    void onParameterSelectionChanged(const QItemSelection&selection);
    void onSelectorSelectionChanged(const QItemSelection &selection);

    void onDoubleclick(const QModelIndex index);

private:
    void buildSelectorModel();
    void connectSelectorView(bool active = true);
    void connectParameterView(bool active = true);

    FitModel *m_fitModel;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    QTreeView *m_selectorTreeView;
    QTreeView *m_parameterTreeview;
    FitSelectorModel *m_selectorModel;
    FitParameterModel *m_parameterModel;
    QMenu *m_contextMenu;
    QAction *m_removeAction;
    QAction *m_addAction;
    QSplitter *m_splitter;
    KeyboardFilter *m_keyboardFilter;
};


class KeyboardFilter : public QObject
{
    Q_OBJECT
public:
  KeyboardFilter( QObject *parent = 0 ) : QObject( parent ) {}

protected:
  bool eventFilter( QObject *dist, QEvent *event );

signals:
  void removeItem();
};



// -------------------------

class BA_CORE_API_ FitSelectorModel : public QStandardItemModel
{
    Q_OBJECT

public:
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    QString getPathFromIndex(const QModelIndex &index) const;
    QStandardItem *getItemFromPath(const QString &path);
};



// -------------------------

class BA_CORE_API_ FitParameterModel : public SessionModel
{
    Q_OBJECT

public:
    explicit FitParameterModel(FitModel *fitmodel, QWidget *parent);
    ~FitParameterModel();
    QModelIndex itemForLink(const QString &link) const;

    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                             const QModelIndex &parent) const Q_DECL_OVERRIDE;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;

public slots:
    ParameterizedItem *addParameter();

private:
    QMap<int, QString> *m_columnNames;
};

#endif
