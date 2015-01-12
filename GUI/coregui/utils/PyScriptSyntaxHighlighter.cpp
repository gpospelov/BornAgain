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
