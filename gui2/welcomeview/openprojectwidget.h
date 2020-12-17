//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/welcomeview/openprojectwidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_WELCOMEVIEW_OPENPROJECTWIDGET_H
#define BORNAGAIN_GUI2_WELCOMEVIEW_OPENPROJECTWIDGET_H

#include "darefl_export.h"
#include <QWidget>
#include <memory>

class QBoxLayout;
class QPushButton;
class QLabel;

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_WELCOMEVIEW_OPENPROJECTWIDGET_H
