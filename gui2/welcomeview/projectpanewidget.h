// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_WELCOMEVIEW_PROJECTPANEWIDGET_H
#define BORNAGAIN_GUI2_WELCOMEVIEW_PROJECTPANEWIDGET_H

#include "darefl_export.h"
#include <QWidget>

class QLabel;

namespace gui2 {

//! Panel with labels to hold project name and project dir. When user clicks on it,
//! sends the request to open corresponding project. Part of RecentProjectsWidget.

class DAREFLCORE_EXPORT ProjectPaneWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProjectPaneWidget(QWidget* parent = nullptr);

    void setCurrentProject(const QString& project_dir, bool is_modified = false);

    void clear();

    void setActive(bool value);

signals:
    void projectSelected(const QString& project_dir);

protected:
    void paintEvent(QPaintEvent*) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QLabel* m_currentProjectTitle{nullptr};
    QLabel* m_currentProjectDir{nullptr};
    QColor m_widgetColor;
    bool m_active{false};
    QString m_projectDir;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_WELCOMEVIEW_PROJECTPANEWIDGET_H
