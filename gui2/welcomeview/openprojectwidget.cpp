//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/welcomeview/openprojectwidget.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/welcomeview/openprojectwidget.h"
#include "BAVersion.h"
#include "gui2/mainwindow/styleutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
int logo_width()
{
    return ModelView::Utils::SizeOfLetterM().height() * 40;
}

const QString str_open = "Open";
const QString str_new = "New";

} // namespace

namespace gui2 {

OpenProjectWidget::OpenProjectWidget(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    QPixmap logo(":/icons/F-letter_1000x.png");
    auto label = new QLabel;
    label->setPixmap(logo.scaled(logo_width(), logo_width(), Qt::KeepAspectRatio));

    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height() * 1.5);
    layout->addWidget(label, 0, Qt::AlignHCenter);
    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height());
    layout->addLayout(createProjectTitleLayout());
    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height());
    layout->addLayout(createLinkedLabelLayout());
    layout->addStretch();
}

QSize OpenProjectWidget::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize OpenProjectWidget::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

QBoxLayout* OpenProjectWidget::createProjectTitleLayout()
{
    auto result = new QHBoxLayout;
    QString title =
        "BornAgain " + QString::fromStdString(BornAgain::GetVersionNumber()) + ", gui2 preview";
    auto label = new QLabel(title);
    ModelView::Utils::ScaleLabelFont(label, 1.25);

    result->addWidget(label, 0, Qt::AlignHCenter);
    return result;
}

QBoxLayout* OpenProjectWidget::createLinkedLabelLayout()
{
    auto result = new QHBoxLayout;

    m_newProjectLabel = new QLabel(ModelView::Utils::ClickableText(str_new));
    m_newProjectLabel->setToolTip("Create new project");
    connect(m_newProjectLabel, &QLabel::linkActivated, [this](auto) { createNewProjectRequest(); });
    ModelView::Utils::ScaleLabelFont(m_newProjectLabel, 1.25);

    m_openProjectLabel = new QLabel(ModelView::Utils::ClickableText(str_open));
    m_openProjectLabel->setToolTip("Open existing project");
    connect(m_openProjectLabel, &QLabel::linkActivated,
            [this](auto) { openExistingProjectRequest(); });
    ModelView::Utils::ScaleLabelFont(m_openProjectLabel, 1.15);

    result->addStretch(1);
    result->addWidget(m_newProjectLabel);
    result->addSpacing(ModelView::Utils::WidthOfLetterM());
    result->addWidget(m_openProjectLabel);
    result->addStretch(1);

    return result;
}

} // namespace gui2
