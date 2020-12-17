// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/welcomeview/recentprojectwidget.h"
#include "gui2/mainwindow/styleutils.h"
#include "gui2/welcomeview/projectpanewidget.h"
#include "mvvm/widgets/adjustingscrollarea.h"
#include "mvvm/widgets/widgetutils.h"
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

namespace {
const int max_recent_project_count = 10;
const double section_label_scale = 1.25;
} // namespace

namespace gui2 {

RecentProjectWidget::RecentProjectWidget(QWidget* parent)
    : QWidget(parent), m_currentProjectPane(new ProjectPaneWidget) {
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 0, 10, 0);

    layout->addWidget(createRecentProjectScrollArea());
    layout->addStretch(1);
}

QSize RecentProjectWidget::sizeHint() const {
    return StyleUtils::DockSizeHint();
}

QSize RecentProjectWidget::minimumSizeHint() const {
    return StyleUtils::DockMinimumSizeHint();
}

//! Set current project title and label on appropriate widget.
void RecentProjectWidget::setCurrentProject(const QString& project_dir, bool is_modified) {
    m_currentProjectPane->setCurrentProject(project_dir, is_modified);
    m_currentProjectPane->setActive(false);
}

//! Set name of all recent projects to appropriate widgets.
void RecentProjectWidget::setRecentProjectsList(const QStringList& projects) {
    int widget_index{0};
    for (auto widget : m_recentProjectPanes) {
        if (widget_index < projects.size())
            widget->setCurrentProject(projects.at(widget_index), false);
        else
            widget->clear();

        ++widget_index;
    }
}

QBoxLayout* RecentProjectWidget::createCurrentProjectLayout() const {
    auto result = new QVBoxLayout;
    auto label = new QLabel("Current Project");
    ModelView::Utils::ScaleLabelFont(label, section_label_scale);
    result->addWidget(label);
    result->addWidget(m_currentProjectPane);
    return result;
}

QBoxLayout* RecentProjectWidget::createRecentProjectLayout() {
    auto result = new QVBoxLayout;
    auto label = new QLabel("Recent Projects");
    ModelView::Utils::ScaleLabelFont(label, section_label_scale);
    result->addWidget(label);

    for (int i = 0; i < max_recent_project_count; ++i) {
        auto widget = new ProjectPaneWidget;
        connect(widget, &ProjectPaneWidget::projectSelected, this,
                &RecentProjectWidget::projectSelected);
        m_recentProjectPanes.push_back(widget);
        result->addWidget(widget);
    }
    return result;
}

QWidget* RecentProjectWidget::createRecentProjectScrollArea() {
    auto result = new ModelView::AdjustingScrollArea;

    auto content = new QWidget;
    auto layout = new QVBoxLayout;
    layout->addLayout(createCurrentProjectLayout());
    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height());
    layout->addLayout(createRecentProjectLayout());
    content->setLayout(layout);

    result->setWidget(content);
    return result;
}

} // namespace gui2
