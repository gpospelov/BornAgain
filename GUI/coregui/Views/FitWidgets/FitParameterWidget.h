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

#include <QWidget>
#include <QStandardItemModel>
#include <QPlainTextEdit>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QStringList>
#include <QModelIndex>

class QTreeView;
class MainWindow;



class DebugTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    void dropEvent ( QDropEvent * event )
    {

        const QMimeData *data = event->mimeData();
        appendPlainText(data->text());
    }

    void dragEnterEvent(QDragEnterEvent *e)
    {
        e->accept();
    }


};

class BA_CORE_API_ FitParameterWidget : public QWidget
{
    Q_OBJECT

public:
    FitParameterWidget(MainWindow *main, QWidget *parent = 0);

public slots:
    void updateParameters();

private:
    DebugTextEdit *m_textedit;
    QTreeView *m_treeview;
    MainWindow *m_main;
};

class FitParameterSelectionModel : public QStandardItemModel
{
    Q_OBJECT
public:
    Qt::DropActions supportedDropActions() const {
        return Qt::CopyAction | Qt::MoveAction;
    }
    QStringList mimeTypes() const
     {
         QStringList types;
         types << "application/vnd.text.list";
         return types;
     }
    QMimeData *mimeData(const QModelIndexList &indexes) const
     {
         QMimeData *mimeData = new QMimeData();

         QStringList list;
         foreach (QModelIndex index, indexes) {
                  if (index.isValid()) {
                      QStringList parents;
                      QStandardItem *cur = itemFromIndex(index);
                      while (cur) {
                          parents << cur->text();
                          cur = cur->parent();
                      }
                      parents.removeFirst();
                      std::reverse(parents.begin(), parents.end());
                      list << parents.join("/");
                  }
              }
         mimeData->setText(list.join(";"));
         return mimeData;
     }
    Qt::ItemFlags flags(const QModelIndex &index) const {
        return itemFromIndex(index)->flags();
    }
};

#endif
