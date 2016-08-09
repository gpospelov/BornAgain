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
#include <QLabel>
#include <QMap>
#include <QWidget>

class SessionItem;
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

    void setInstrumentItem(SessionItem *instrument);

signals:
    void extendedDetectorEditorRequest(DetectorItem *);

public slots:
    void onChangedEditor(const QString &);
    void onPropertyChanged(const QString &);

private:
    QLayout *create_NameAndTypeLayout();

    void updateWidgets();

    QLineEdit *m_nameLineEdit;
    QComboBox *m_typeComboBox;
    SessionItem *m_currentItem;
    bool m_block_signals;
    InstrumentComponentsWidget *m_instrumentComponents;
};

#endif // INSTRUMENTEDITORWIDGET_H
