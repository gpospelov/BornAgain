#include "SplashScreen.h"
#include <QStyleOptionProgressBarV2>

SplashScreen::SplashScreen(QApplication *aApp, QWidget *parent) :
    QSplashScreen(parent), app(aApp), m_progress(0)

{
    m_width = 500;
    m_height = 500;

    this->setPixmap(QPixmap(":/images/BornAgain.ico").scaled(m_width, m_height, Qt::KeepAspectRatio));
    this->setCursor(Qt::BusyCursor);

    QFont font;
    font.setPointSize(10);
    font.setBold(false);
    this->setFont(font);

    //this->showMessage("\t\t\t\t\t\tLoading application...", Qt::AlignBottom);
}

void SplashScreen::drawContents(QPainter *painter)
{
  QSplashScreen::drawContents(painter);

  int width = 150;
  int height = 8;

  // Set style for progressbar...
  QStyleOptionProgressBarV2 pbstyle;
  pbstyle.initFrom(this);
  pbstyle.state = QStyle::State_Enabled;
  pbstyle.textVisible = false;
  pbstyle.minimum = 0;
  pbstyle.maximum = 100;
  pbstyle.progress = m_progress;
  pbstyle.invertedAppearance = false;
  pbstyle.rect = QRect(m_width-width-35, m_height-height-12, width, height);

  style()->drawControl(QStyle::CE_ProgressBar, &pbstyle, painter, this);

  style()->drawItemText(painter,QRect(30,  m_height-25, 200, 20),0, this->palette(), true, "Loading application...");
}
