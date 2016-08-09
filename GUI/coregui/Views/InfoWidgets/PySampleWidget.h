// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/PySampleWidget.h
//! @brief     Defines class PySampleWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PYSAMPLEWIDGET_H
#define PYSAMPLEWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class SampleModel;
class InstrumentModel;
class QTextEdit;
class QModelIndex;
class QTimer;
class PythonSyntaxHighlighter;
class WarningSignWidget;

//! The PySampleWidget displays Python script representing a MultiLayer at the bottom of SampleView
//! Belongs to InfoWidget
class BA_CORE_API_ PySampleWidget : public QWidget
{
    Q_OBJECT

public:
    PySampleWidget(QWidget *parent = 0);

    void setSampleModel(SampleModel *sampleModel);
    void setInstrumentModel(InstrumentModel *instrumentModel);

public slots:
    void onModifiedRow(const QModelIndex &, int, int);
    void onDataChanged(const QModelIndex &, const QModelIndex &);

    void scheduleUpdate();
    void updateEditor();

    void disableEditor();
    void enableEditor();

private slots:
    void onTimerTimeout();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QString generateCodeSnippet();
    QPoint getPositionForWarningSign();
    QString getWelcomeMessage();

    QTextEdit *m_textEdit;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    QTimer *m_timer;
    int m_time_to_update;
    int m_n_of_sceduled_updates;
    PythonSyntaxHighlighter *m_highlighter;
    WarningSignWidget *m_warningSign;
};

#endif // PYSAMPLEWIDGET_H
