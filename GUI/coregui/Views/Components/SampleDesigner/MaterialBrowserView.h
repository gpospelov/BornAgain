#ifndef MATERIALBROWSERVIEW_H
#define MATERIALBROWSERVIEW_H

#include <QDialog>
#include <QTableView>

class MaterialBrowserModel;
class QTableView;
class QStatusBar;
class QToolBar;

#include <iostream>


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

