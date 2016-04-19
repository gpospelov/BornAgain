// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/DistributionDialog.h
//! @brief     Declares class DistributionDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONDIALOG_H
#define DISTRIBUTIONDIALOG_H

#include <QDialog>
class DistributionEditor;
class SessionItem;

//! The dialog which shows an editor to change parameters of DistributionItem
class DistributionDialog : public QDialog
{
    Q_OBJECT

public:
    DistributionDialog(QWidget *parent = 0);
    virtual ~DistributionDialog(){}

    void setItem(SessionItem *item);
    void setNameOfEditor(const QString &name);

private:
    DistributionEditor *m_editor;
};

#endif
