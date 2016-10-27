// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/aboutapplicationdialog.cpp
//! @brief     Implements class AboutApplicationDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "aboutapplicationdialog.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include <QDate>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>


AboutApplicationDialog::AboutApplicationDialog(QWidget *parent)
    : QDialog(parent)
{
    QColor bgColor(240,240,240,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    setFixedSize(550, 250);
    setWindowTitle("About BornAgain");

    //setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setWindowFlags( Qt::Dialog );


    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getLabelFontSize() + 2);
    titleFont.setBold(true);

    QFont normalFont;
    normalFont.setPointSize(DesignerHelper::getLabelFontSize());
    normalFont.setBold(false);


    QPixmap logo(":/images/about_icon.png");
    QLabel *logoLabel = new QLabel;
    logoLabel->setPixmap(logo.scaled(120,120,Qt::KeepAspectRatio));


    QLabel *aboutTitleLabel = new QLabel(QString("BornAgain version ")
                                         .append(GUIHelpers::getBornAgainVersionString()));
    aboutTitleLabel->setFont(titleFont);
    aboutTitleLabel->setContentsMargins(0,0,0,15);

    QDate date = QDate::currentDate();

    QString copyright = QString("Copyright: Forschungszentrum Jülich GmbH ").append(date.toString("yyyy"));
    QLabel *copyrightLabel = new QLabel(copyright);
    copyrightLabel->setFont(normalFont);
    //copyrightLabel->setWordWrap(true);
    copyrightLabel->setContentsMargins(0,0,0,15);

    QString description = "A software to simulate and fit grazing-incidence small-angle scattering (GISAS) using distorted wave Born approximation (DWBA).";
    QLabel *descriptionLabel = new QLabel(description);
    descriptionLabel->setFont(normalFont);
    descriptionLabel->setWordWrap(true);


    QLabel *linkLabel = new QLabel();
    linkLabel->setTextFormat(Qt::RichText);
    linkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    linkLabel->setText("<a href=\"http://www.bornagainproject.org\">www.bornagainproject.org</a>");
    linkLabel->setOpenExternalLinks(true);


    QVBoxLayout *logoLayout = new QVBoxLayout;
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch(1);
    logoLayout->setContentsMargins(5,5,5,5);

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->addWidget(aboutTitleLabel);
    textLayout->addWidget(descriptionLabel);
    textLayout->addStretch(1);
    textLayout->addWidget(copyrightLabel);
    textLayout->addWidget(linkLabel);
    textLayout->addStretch(1);
    textLayout->setContentsMargins(0,5,5,5);


    QHBoxLayout *detailsLayout = new QHBoxLayout;
    detailsLayout->addLayout(logoLayout);
    detailsLayout->addLayout(textLayout);


    m_closeButton = new QPushButton("Close");
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_closeButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(detailsLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}
