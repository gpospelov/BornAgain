#include "aboutapplicationdialog.h"
#include "mainwindow_constants.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include <iostream>

AboutApplicationDialog::AboutApplicationDialog(QWidget *parent)
    : QDialog(parent)

{
    QColor bgColor(240,240,240,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    setFixedSize(450, 230);
    setWindowTitle("About BornAgain");

    //setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setWindowFlags( Qt::Dialog );


    QFont titleFont;
    titleFont.setPointSize(18);
    titleFont.setBold(true);

    QFont normalFont;
    titleFont.setPointSize(14);
    titleFont.setBold(false);


    QPixmap logo(":/images/BornAgain.ico");
    QLabel *logoLabel = new QLabel;
    logoLabel->setPixmap(logo.scaled(120,120,Qt::KeepAspectRatio));


    QLabel *aboutTitleLabel = new QLabel(QString(Constants::APPLICATION_NAME).append(" ").append(Constants::APPLICATION_VERSION));
    aboutTitleLabel->setFont(titleFont);

    QString description = "A software to simulate and fit grazing-incidence small-angle scattering (GISAS), using distorted-wave Born approximation (DWBA). The software equally supports neutron and x-ray scattering (GISANS and GISAXS).";
    QLabel *descriptionLabel = new QLabel(description);
    descriptionLabel->setFont(normalFont);
    descriptionLabel->setWordWrap(true);

    QVBoxLayout *logoLayout = new QVBoxLayout;
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch(1);
    logoLayout->setContentsMargins(15,15,15,15);

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->addWidget(aboutTitleLabel);
    textLayout->addWidget(descriptionLabel);
    textLayout->addStretch(1);
    textLayout->setContentsMargins(0,15,5,5);


    QHBoxLayout *detailsLayout = new QHBoxLayout;
    detailsLayout->addLayout(logoLayout);
    detailsLayout->addLayout(textLayout);


    m_closeButton = new QPushButton(tr("Close"));
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_closeButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(detailsLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}


