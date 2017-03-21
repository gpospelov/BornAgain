// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentEditorWidget.h
//! @brief     Defines class InstrumentEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTEDITORWIDGET_H
#define INSTRUMENTEDITORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class SessionItem;
class DetectorItem;
class QLineEdit;
class QComboBox;
class InstrumentComponentsWidget;

//! Main widget of InstrumentView. Contains InstrumentComponentsWidget with beam and detector
//! settings.

class BA_CORE_API_ InstrumentEditorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentEditorWidget(QWidget* parent = 0);

    QSize sizeHint() const;

    void setInstrumentItem(SessionItem* instrument);

signals:
    void extendedDetectorEditorRequest(DetectorItem*);

public slots:
    void onChangedEditor(const QString&);

private:
    QLayout* create_NameAndTypeLayout();
    void updateWidgets();

    QLineEdit* m_nameLineEdit;
    QComboBox* m_typeComboBox;
    InstrumentComponentsWidget* m_instrumentComponents;
    SessionItem* m_currentItem;
    bool m_block_signals;
};

#endif // INSTRUMENTEDITORWIDGET_H
