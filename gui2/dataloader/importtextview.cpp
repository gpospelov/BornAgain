//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/dataloader/importtextview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/dataloader/importtextview.h"
#include "mvvm/widgets/widgetutils.h"

//! Based on Qt example "codeeditor"
//! Copyright (C) 2016 The Qt Company Ltd.

#include <QPainter>
#include <QTextBlock>

namespace gui2 {

namespace {
const int line_number_gap = 4;
}

ImportTextView::ImportTextView(QWidget* parent) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);

    connect(this, &ImportTextView::blockCountChanged, this,
            &ImportTextView::updateLineNumberAreaWidth);
    connect(this, &ImportTextView::updateRequest, this, &ImportTextView::updateLineNumberArea);
    connect(this, &ImportTextView::cursorPositionChanged, this,
            &ImportTextView::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    //    highlightCurrentLine();

    setReadOnly(true);
    setWordWrapMode(QTextOption::NoWrap);

    setFont(QFont("Monospace", ModelView::Utils::SystemPointSize() * 0.8, QFont::Light));
}

int ImportTextView::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = line_number_gap * 2 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void ImportTextView::updateLineNumberAreaWidth(int /* newBlockCount */) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void ImportTextView::updateLineNumberArea(const QRect& rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void ImportTextView::resizeEvent(QResizeEvent* e) {
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void ImportTextView::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void ImportTextView::lineNumberAreaPaintEvent(QPaintEvent* event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width() - line_number_gap,
                             fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

} // namespace gui2
