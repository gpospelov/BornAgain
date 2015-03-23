// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/PySampleWidget.h
//! @brief     Defines class PySampleWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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

    void updateEditor();


private:
    QTextEdit *m_textEdit;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    bool m_block_update;
};

#endif
