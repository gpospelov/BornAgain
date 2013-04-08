#include "WelcomeView.h"

#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QtWebKit>
#include <QDesktopServices>

WelcomeView::WelcomeView(QWidget *parent)
    : QWebView(parent)
{
    load(QUrl("http://apps.jcns.fz-juelich.de/doku/sc/bornagain::start"));
    connect(this, SIGNAL(linkClicked(const QUrl &)), this, SLOT(onWebLinkClicked(const QUrl &)));
    page()->setLinkDelegationPolicy( QWebPage::DelegateAllLinks );
//    QGroupBox *configGroup = new QGroupBox(tr("Server configuration"));

//    QLabel *serverLabel = new QLabel(tr("Server:"));
//    QComboBox *serverCombo = new QComboBox;
//    serverCombo->addItem(tr("Qt (Australia)"));
//    serverCombo->addItem(tr("Qt (Germany)"));
//    serverCombo->addItem(tr("Qt (Norway)"));
//    serverCombo->addItem(tr("Qt (People's Republic of China)"));
//    serverCombo->addItem(tr("Qt (USA)"));

//    QHBoxLayout *serverLayout = new QHBoxLayout;
//    serverLayout->addWidget(serverLabel);
//    serverLayout->addWidget(serverCombo);

//    QVBoxLayout *configLayout = new QVBoxLayout;
//    configLayout->addLayout(serverLayout);
//    configGroup->setLayout(configLayout);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(configGroup);
//    mainLayout->addStretch(1);
//    setLayout(mainLayout);
}

void WelcomeView::onWebLinkClicked(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}
