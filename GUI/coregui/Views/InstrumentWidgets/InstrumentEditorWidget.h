// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/InstrumentEditorWidget.h
//! @brief     Defines class InstrumentEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENT_EDITOR_WIDGET_H
#define INSTRUMENT_EDITOR_WIDGET_H


#include "WinDllMacros.h"
#include <QWidget>
#include <QLabel>
#include <QMap>

class ParameterizedItem;
class DetectorEditorWidget;
class BeamEditorWidget;
class QLineEdit;
class QComboBox;
class InstrumentComponentsWidget;
class DetectorItem;

class BA_CORE_API_ InstrumentEditorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentEditorWidget(QWidget *parent = 0);
    QSize sizeHint() const { return QSize(600, 600); }

    void setInstrumentItem(ParameterizedItem *instrument);

signals:
    void extendedDetectorEditorRequest(DetectorItem *);

public slots:
    void onChangedEditor(const QString &);
    void onPropertyChanged(const QString &);

private:
    void updateWidgets();

    QLineEdit *m_nameLineEdit;
    QComboBox *m_typeComboBox;
    ParameterizedItem *m_currentItem;
    bool m_block_signals;
    InstrumentComponentsWidget *m_instrumentComponents;
};

#endif
