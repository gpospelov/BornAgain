#ifndef MATERIALBROWSERVIEW_H
#define MATERIALBROWSERVIEW_H

#include <QDialog>
#include <QTableView>

class MaterialBrowserModel;
class QTableView;
class QStatusBar;
class QToolBar;

#include <iostream>

class MyTableView : public QTableView
{
public:
    explicit MyTableView(QWidget *parent = 0) : QTableView(parent){}
//    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
//     {
//       return QSize(50,50);
//     }

    int sizeHintForRow(int row) const
    {
        std::cout << "AAAAA " << QTableView::sizeHintForRow(row) << std::endl;
        return 10;
    }
    int sizeHintForColumn(int column) const
    {
        int result = QTableView::sizeHintForColumn(column);
        if(column == 0) result *= 1.4;
        return result;
    }

};


class MaterialBrowserView : public QDialog
{
    Q_OBJECT
public:
    explicit MaterialBrowserView(MaterialBrowserModel *tableModel, QWidget *parent = 0);
    virtual ~MaterialBrowserView();

signals:
    void WindowClosed();

public slots:
    void addMaterial();
    void removeMaterial();
    void showMessage(const QString &message);
    void closeButtonClicked();
    void close();

protected:
    //void closeEvent(QCloseEvent *event);
private:
    void SetupActions();

    QTableView *m_tableView;
    MaterialBrowserModel *m_tableModel;
    QStatusBar *m_statusBar;
    QToolBar *m_toolBar;
    static int m_IndexOfUnnamed;
};

#endif // MATERIALBROWSERVIEW_H

