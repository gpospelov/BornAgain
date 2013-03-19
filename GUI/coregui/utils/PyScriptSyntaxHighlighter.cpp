#include "PyScriptSyntaxHighlighter.h"

PyScriptSyntaxHighlighter::PyScriptSyntaxHighlighter(QTextDocument *document)
    : QSyntaxHighlighter(document)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkRed);
    setFormatForElementType(Keyword, keywordFormat);

    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::blue);
    setFormatForElementType(Comment, commentFormat);
}

void PyScriptSyntaxHighlighter::setFormatForElementType(ElementType element_type,
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
        case NormalState:
        default:
            if (text.at(pos) == '#') {
                setFormat(pos, line_length - pos, formatFor(Comment));
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
