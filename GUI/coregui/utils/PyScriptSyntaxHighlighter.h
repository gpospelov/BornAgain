#ifndef PYSCRIPTSYNTAXHIGHLIGHTER_H
#define PYSCRIPTSYNTAXHIGHLIGHTER_H

#include "WinDllMacros.h"
#include <QSyntaxHighlighter>

class BA_CORE_API_  PyScriptSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    enum EElementType {
        KEYWORD,
        COMMENT,
        LAST_ELEMENT_TYPE = COMMENT
    };

    PyScriptSyntaxHighlighter(QTextDocument *document);
    virtual ~PyScriptSyntaxHighlighter() {}

    void setFormatForElementType(EElementType element_type,
                                 const QTextCharFormat &format);
    QTextCharFormat formatFor(EElementType element_type) const {
        return m_formats[element_type];
    }

protected:
    enum EState {
        NORMAL = -1,
        INSIDE_COMMENT
    };

    virtual void highlightBlock(const QString &text);
private:
    bool isKeyword(const QString &text) const;
    QTextCharFormat m_formats[LAST_ELEMENT_TYPE + 1];
};

#endif // PYSCRIPTSYNTAXHIGHLIGHTER_H
