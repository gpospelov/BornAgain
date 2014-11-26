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

    //this->showMessage("\t\t\t\t\t\tLoading application...", Qt::AlignBottom);
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

    //  int width = 150;
    //  int height = 8;
    //  // Set style for progressbar...
    //  QStyleOptionProgressBarV2 pbstyle;
//  pbstyle.initFrom(this);
//  pbstyle.state = QStyle::State_Enabled;
//  pbstyle.textVisible = false;
//  pbstyle.minimum = 0;
//  pbstyle.maximum = 100;
//  pbstyle.progress = m_progress;
//  pbstyle.invertedAppearance = false;
//  pbstyle.rect = QRect(m_width-width-35, m_height-height-12, width, height);
//  style()->drawControl(QStyle::CE_ProgressBar, &pbstyle, painter, this);

//    style()->drawItemText(painter,QRect(30,  m_height-25, 200, 20), 0, this->palette(), true, "Loading application...");


//    QFont serifFont("Monospace", DesignerHelper::getLabelFontSize(), QFont::Normal);
//    painter->setFont(serifFont);
    //    painter->drawText(textRect, Qt::AlignCenter, "ver 0.9.9");

    QRect textRect( 15.0, m_height-40, 100, 30);

    QString versionText = QString::fromStdString("version ").append(QString::fromStdString(BornAgain::GetVersionNumber()));
    style()->drawItemText(painter, textRect, 0, this->palette(), true, versionText);

    QString loadingText("loading . ");
    for(size_t i=0; i<size_t(m_progress/20); ++i) {
        loadingText.append(". ");
    }

    qDebug() << loadingText;

    QRect loadingRect( 380.0, m_height-40, 100, 30);
    style()->drawItemText(painter, loadingRect, 0, this->palette(), true, loadingText);

}
