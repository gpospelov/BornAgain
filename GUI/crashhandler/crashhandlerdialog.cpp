#include "crashhandlerdialog.h"
#include <QClipboard>
#include <QPushButton>
#include <QTextEdit>
#include <QtWidgets>



CrashHandlerDialog::CrashHandlerDialog(QString errorText, QWidget *parent)
    : m_errorText(errorText)
    , QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_clipboard = QApplication::clipboard();

    m_titleLabel = new QLabel("BornAgain has been closed unexpectedly. We appologize for this. \nPlease fill bug report using info provided below.");

    m_errorTextEdit = new QTextEdit();
    m_errorTextEdit->setText(m_errorText);

    m_copyButton = new QPushButton("Copy to Clipboard");
    m_reportButton = new QPushButton("Report");
    m_closeButton = new QPushButton("Close");

    connect(m_copyButton, SIGNAL(clicked()), this, SLOT(onCopyButtonClicked()));
    connect(m_reportButton, SIGNAL(clicked()), this, SLOT(onReportButtonClicked()));
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(onCloseButtonClicked()));


    QHBoxLayout *buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(m_copyButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_reportButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_closeButton);




    mainLayout->addWidget(m_titleLabel);
    mainLayout->addWidget(m_errorTextEdit);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("BornAgain Crash Handler");
}

void CrashHandlerDialog::onCopyButtonClicked()
{

    m_clipboard->setText(m_errorTextEdit->toPlainText());
}

void CrashHandlerDialog::onReportButtonClicked()
{
    QUrl url("http://apps.jcns.fz-juelich.de/redmine/projects/bornagain/issues/new");
    QDesktopServices::openUrl(url);
}

void CrashHandlerDialog::onCloseButtonClicked()
{
    this->close();
}

