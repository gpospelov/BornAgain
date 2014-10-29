#ifndef CRASHHANDLERDIALOG_H
#define CRASHHANDLERDIALOG_H

#include <QWidget>


class QLabel;
class QPushButton;
class QTextEdit;
class QClipboard;


class CrashHandlerDialog : public QWidget
{
    Q_OBJECT

public:
    CrashHandlerDialog(QString errorText = "", QWidget *parent = 0);

private slots:
    void onCopyButtonClicked();
    void onReportButtonClicked();
    void onCloseButtonClicked();

private:


    QLabel *m_titleLabel;
    QTextEdit *m_errorTextEdit;
    QPushButton *m_copyButton;
    QPushButton *m_reportButton;
    QPushButton *m_closeButton;

    QString m_errorText;
    QClipboard *m_clipboard;

};

#endif // CRASHHANDLERDIALOG_H
