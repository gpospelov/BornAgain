#ifndef PYSCRIPTSYNTAXHIGHLIGHTER_H
#define PYSCRIPTSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class PyScriptSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    enum ElementType {
        Keyword,
        Comment,
        LastElementType = Comment
    };

    PyScriptSyntaxHighlighter(QTextDocument *document);
    virtual ~PyScriptSyntaxHighlighter() {}

    void setFormatForElementType(ElementType element_type,
                                 const QTextCharFormat &format);
    QTextCharFormat formatFor(ElementType element_type) const {
        return m_formats[element_type];
    }

protected:
    enum State {
        NormalState = -1,
        InsideCommentState
    };

    virtual void highlightBlock(const QString &text);
private:
    bool isKeyword(const QString &text) const;
    QTextCharFormat m_formats[LastElementType + 1];
};

#endif // PYSCRIPTSYNTAXHIGHLIGHTER_H
