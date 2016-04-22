// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidget.h
//! @brief     Declares class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
class ObsoleteFitModel;
class SessionItem;
class FitParameterModel;
class QItemSelection;
class QSplitter;
class DeleteEventFilter;

class BA_CORE_API_ FitParameterWidget : public QWidget
{
    Q_OBJECT

public:
    static const QString MIME_TYPE;
    FitParameterWidget(ObsoleteFitModel *fitModel, QWidget *parent = 0);

    void clearParameter();
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
    void buildTree(QStandardItem *root, SessionItem *top);
    void removeEmptyParameter();

    ObsoleteFitModel *m_fitModel;
    QTreeView *m_selectorTreeView;
    QTreeView *m_parameterTreeview;
    FitSelectorModel *m_selectorModel;
    FitParameterModel *m_parameterModel;
    QMenu *m_contextMenu;
    QAction *m_removeAction;
    QAction *m_addAction;
    QSplitter *m_splitter;
    DeleteEventFilter *m_keyboardFilter;
};




#endif
