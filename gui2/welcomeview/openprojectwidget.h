// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_OPENPROJECTWIDGET_H
#define DAREFL_WELCOMEVIEW_OPENPROJECTWIDGET_H

#include <QWidget>
#include "darefl_export.h"
#include <memory>

class QBoxLayout;
class QPushButton;
class QLabel;

namespace DaRefl {

//! Widget with logo, name of the program and buttons to create new project or open existing one.
//! Occupies right part of WelcomeView.

class DAREFLCORE_EXPORT OpenProjectWidget : public QWidget {
    Q_OBJECT

public:
    explicit OpenProjectWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:
    void createNewProjectRequest();
    void openExistingProjectRequest();

private:
    QBoxLayout* createProjectTitleLayout();
    QBoxLayout* createLinkedLabelLayout();

    QLabel* m_newProjectLabel{nullptr};
    QLabel* m_openProjectLabel{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_WELCOMEVIEW_OPENPROJECTWIDGET_H
