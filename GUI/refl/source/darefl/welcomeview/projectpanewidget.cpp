// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <darefl/welcomeview/projectpanewidget.h>
#include "mvvm/widgets/widgetutils.h"

namespace {
int widget_height() {
    return ModelView::Utils::SizeOfLetterM().height() * 3;
}
} // namespace

namespace DaRefl {

ProjectPaneWidget::ProjectPaneWidget(QWidget* parent)
    : QWidget(parent)
    , m_currentProjectTitle(new QLabel(" "))
    , m_currentProjectDir(new QLabel(" "))
    , m_widgetColor(QColor(Qt::white)) {
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setFixedHeight(widget_height());
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_currentProjectTitle);
    layout->addWidget(m_currentProjectDir);
}

//! Sets current project dir to 'project_dir', adjust title according to 'is_modified'.

void ProjectPaneWidget::setCurrentProject(const QString& project_dir, bool is_modified) {
    m_active = true;
    m_projectDir = project_dir;

    auto trimmed_project_dir = ModelView::Utils::WithTildeHomePath(project_dir);
    auto project_title = ModelView::Utils::ProjectWindowTitle(project_dir, is_modified);

    m_currentProjectDir->setText(trimmed_project_dir);
    m_currentProjectDir->setToolTip(m_projectDir);
    m_currentProjectTitle->setText(project_title);
}

//! Clear content of widget and make it inactive. Inactive widget doesnt' send signals when
//! user click on it.

void ProjectPaneWidget::clear() {
    setActive(false);
    m_projectDir.clear();
    m_currentProjectDir->setText({});
    m_currentProjectDir->setToolTip({});
    m_currentProjectTitle->setText({});
}

//! Set 'active' flag to the given value. 'False' means that the widget only shows the project
//! title, but doesn't react on mouse clicks and doesn't change the background on mouse
//! hover events.
void ProjectPaneWidget::setActive(bool value) {
    m_active = value;
    update();
}

void ProjectPaneWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.fillRect(0, 0, size().width(), size().height(), m_widgetColor);
}

void ProjectPaneWidget::enterEvent(QEvent*) {
    if (m_active)
        m_widgetColor = QColor(Qt::lightGray);
    update();
}

void ProjectPaneWidget::leaveEvent(QEvent*) {
    m_widgetColor = QColor(Qt::white);
    update();
}

void ProjectPaneWidget::mousePressEvent(QMouseEvent* event) {
    if (m_active && event->button() == Qt::LeftButton)
        projectSelected(m_projectDir);
}

} // namespace DaRefl
