// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/SplashScreen.cpp
//! @brief     Implements class SplashScreen
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SplashScreen.h"
#include "DesignerHelper.h"
#include "BAVersion.h"
#include <QStyleOptionProgressBarV2>
#include <QFont>
#include <QPainter>
#include <QDebug>

SplashScreen::SplashScreen(QWidget *parent) :
    QSplashScreen(parent),m_progress(0)

{
    m_width = 480;
    m_height = 380;

    this->setPixmap(QPixmap(":/images/splashscreen.png"));
    this->setCursor(Qt::BusyCursor);

    QFont font;
    font.setPointSize(10);
    font.setBold(false);
    this->setFont(font);
}

void SplashScreen::setProgress(int value)
{
    m_progress = value;
    if (m_progress > 100)
        m_progress = 100;
    if (m_progress < 0)
        m_progress = 0;
    update();
}

void SplashScreen::drawContents(QPainter *painter)
{
    QSplashScreen::drawContents(painter);

    QRect textRect( 15.0, m_height-40, 100, 30);

    QString versionText = QString::fromStdString("version ").append(QString::fromStdString(BornAgain::GetVersionNumber()));
    style()->drawItemText(painter, textRect, 0, this->palette(), true, versionText);

    QString loadingText("loading . ");
    for(size_t i=0; i<size_t(m_progress/20); ++i) {
        loadingText.append(". ");
    }

    QRect loadingRect( 380.0, m_height-40, 100, 30);
    style()->drawItemText(painter, loadingRect, 0, this->palette(), true, loadingText);

}
