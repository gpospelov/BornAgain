// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_MAINBARWIDGET_H
#define DAREFL_MAINWINDOW_MAINBARWIDGET_H

#include <QWidget>
#include <darefl/darefl_export.h>
#include <map>

class QStackedWidget;
class QHBoxLayout;
class QPushButton;

namespace DaRefl
{

class FancyTab;

//! Widget container with functionality similar to QTabWidget. Has large button bar on top,
//! and stacked widget at bottom.

class DAREFLCORE_EXPORT MainBarWidget : public QWidget
{
    Q_OBJECT

public:
    MainBarWidget(QWidget* parent = nullptr);
    ~MainBarWidget();

    void addWidget(QWidget* widget, const QString& title, bool is_enabled = true);

    void setCurrentIndex(int index);

private:
    QStackedWidget* m_stackedWidget{nullptr};
    QHBoxLayout* m_labelLayout{nullptr};
    std::map<int, FancyTab*> m_indexToTab;
};

} // namespace DaRefl

#endif // DAREFL_MAINWINDOW_MAINBARWIDGET_H
