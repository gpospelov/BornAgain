#ifndef TASKSELECTORWIDGET_H
#define TASKSELECTORWIDGET_H

#include <QWidget>

class QStackedLayout;
class QStatusBar;
class QStackedWidget;
class QIcon;
namespace Manhattan {
    class FancyTabBar;
}


class TaskSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    TaskSelectorWidget(QWidget *parent = 0);
    ~TaskSelectorWidget();

    void paintEvent(QPaintEvent *event);

    void insertTab(int index, QWidget *tab, const QIcon &icon, const QString &label);
//    void removeTab(int index);

signals:
    void currentAboutToShow(int index);
    void currentChanged(int index);

public slots:

private slots:
    void showWidget(int index);

private:
    Manhattan::FancyTabBar *m_tabBar;
    QWidget *m_cornerWidgetContainer;
    QWidget *m_selectionWidget;
    QStatusBar *m_statusBar;
    QStackedWidget *m_stackedWidgets;

};

#endif // FANCYTABWIDGET_H
