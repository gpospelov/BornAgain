// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/ComboSelectorDialog.h
//! @brief     Defines class ComboSelectorDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMBOSELECTORDIALOG_H
#define COMBOSELECTORDIALOG_H

#include "WinDllMacros.h"
#include <QDialog>
#include <QString>

class QLabel;
class QComboBox;
class QBoxLayout;

//! A dialog similar to standard QMessageBox with combo box selector.

class BA_CORE_API_ ComboSelectorDialog : public QDialog
{
    Q_OBJECT
public:
    ComboSelectorDialog(QWidget *parent = 0);

    void addItems(const QStringList& selection, const QString& currentItem = QString());
    void setTextTop(const QString& text);
    void setTextBottom(const QString& text);

    QString currentText() const;

private:
    QBoxLayout* createLogoLayout();
    QBoxLayout* createInfoLayout();
    QBoxLayout* createButtonLayout();

    QLabel* m_topLabel;
    QComboBox* m_comboSelector;
    QLabel* m_bottomLabel;
};

#endif
