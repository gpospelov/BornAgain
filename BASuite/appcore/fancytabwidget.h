#ifndef FANCYTABWIDGET_H
#define FANCYTABWIDGET_H

#include <QWidget>

class FancyTabBar;
class FancyTabBar2;
class QStackedLayout;
class QStatusBar;
class QStackedWidget;
class QIcon;


class FancyTabWidget : public QWidget
{
    Q_OBJECT

public:
    FancyTabWidget(QWidget *parent = 0);
    ~FancyTabWidget();

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

    FancyTabBar2 *m_tabBar;
//    FancyTabBar *m_tabBar;
    QWidget *m_cornerWidgetContainer;
    QWidget *m_selectionWidget;
    QStatusBar *m_statusBar;
    QStackedWidget *m_stackedWidgets;

};

#endif // FANCYTABWIDGET_H
