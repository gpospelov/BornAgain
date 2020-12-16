// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "gui2/mainwindow/fancytab.h"
#include "gui2/mainwindow/mainbarwidget.h"

namespace DaRefl {

MainBarWidget::MainBarWidget(QWidget* parent)
    : QWidget(parent), m_stackedWidget(new QStackedWidget), m_labelLayout(new QHBoxLayout) {
    m_labelLayout->setContentsMargins(0, 0, 0, 0);

    auto layout = new QVBoxLayout(this);
    layout->addLayout(m_labelLayout);
    layout->addWidget(m_stackedWidget);
    layout->setContentsMargins(0, 0, 0, 0);
}

MainBarWidget::~MainBarWidget() = default;

void MainBarWidget::addWidget(QWidget* widget, const QString& title, bool is_enabled) {
    int index = m_stackedWidget->addWidget(widget);

    auto tab = new FancyTab(title);
    tab->setEnabled(is_enabled);
    auto on_tab_clicked = [this, index]() { setCurrentIndex(index); };
    connect(tab, &FancyTab::clicked, on_tab_clicked);

    m_indexToTab[index] = tab;
    m_labelLayout->addWidget(tab);
}

void MainBarWidget::setCurrentIndex(int index) {
    for (auto it : m_indexToTab)
        it.second->setSelected(it.first == index);

    m_stackedWidget->setCurrentIndex(index);
}

} // namespace DaRefl
