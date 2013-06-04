#ifndef MATERIALBROWSERVIEW_H
#define MATERIALBROWSERVIEW_H

#include <QDialog>
#include <QTableView>

class MaterialBrowserModel;
class QTableView;
class QStatusBar;
class QToolBar;

class MyTableView : public QTableView
{
public:
    MyTableView(QWidget *parent) : QTableView(parent){}
};


class MaterialBrowserView : public QDialog
{
    Q_OBJECT
public:
    explicit MaterialBrowserView(QWidget *parent = 0);
    virtual ~MaterialBrowserView();

signals:
    void WindowClosed();

public slots:
    void addMaterial();
    void removeMaterial();

protected:
    void closeEvent(QCloseEvent *event);
private:
    void SetupActions();

    MyTableView *m_tableView;
    MaterialBrowserModel *m_tableModel;
    QStatusBar *m_statusBar;
    QToolBar *m_toolBar;
    static int m_nmaterial;
};

#endif // MATERIALBROWSERVIEW_H

