// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/PyScriptSyntaxHighlighter.h
//! @brief     Defines class PyScriptSyntaxHighlighter
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
