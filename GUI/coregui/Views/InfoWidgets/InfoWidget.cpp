// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoWidget.cpp
//! @brief     Implements class InfoWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InfoWidget.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include "PythonSyntaxHighlighter.h"

InfoWidget::InfoWidget(QWidget *parent)
    : QWidget(parent)
    , m_textEdit(new QTextEdit)
{
    setWindowTitle(tr("Info Stream"));
    setObjectName(tr("InfoStream"));
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(m_textEdit);

//    setLayout(mainLayout);


////    PyScriptSyntaxHighlighter *highlighter = new PyScriptSyntaxHighlighter(m_textEdit->document());
//    PythonSyntaxHighlighter *highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
//    Q_UNUSED(highlighter);

//    QFile scriptFile("CylindersAndPrisms.py");
//    if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        return;
//    }
//    QTextStream fileStream(&scriptFile);
//    m_textEdit->setText(fileStream.readAll());
}
