// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/PyScriptSyntaxHighlighter.cpp
//! @brief     Implements class PyScriptSyntaxHighlighter
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyScriptSyntaxHighlighter.h"

PyScriptSyntaxHighlighter::PyScriptSyntaxHighlighter(QTextDocument *document)
    : QSyntaxHighlighter(document)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkRed);
    setFormatForElementType(KEYWORD, keywordFormat);

    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::blue);
    setFormatForElementType(COMMENT, commentFormat);
}

void PyScriptSyntaxHighlighter::setFormatForElementType(EElementType element_type,
                                    const QTextCharFormat &format)
{
    m_formats[element_type] = format;
    rehighlight();
}

void PyScriptSyntaxHighlighter::highlightBlock(const QString &text)
{
    int state = previousBlockState();
    int line_length = text.length();
    int pos = 0;

    while (pos<line_length)
    {
        switch (state)
        {
        case NORMAL:
        default:
            if (text.at(pos) == '#') {
                setFormat(pos, line_length - pos, formatFor(COMMENT));
                pos = line_length;
                break;
            } else {
                ++pos;
            }
        }
    }
}

bool PyScriptSyntaxHighlighter::isKeyword(const QString &text) const
{
    (void)text;
    return false;
}
