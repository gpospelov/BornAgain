// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/ProjectLoadWarningDialog.h
//! @brief     Defines class ProjectLoadWarningDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTLOADWARNINGDIALOG_H
#define PROJECTLOADWARNINGDIALOG_H

#include <QDialog>
#include <QStringList>

class WarningMessageService;
class QTableWidget;
class QLabel;
class QTableWidgetItem;

//! @class ProjectLoadWarningDialog
//! @brief The dialog to inform user about encountered problems during the loading of old project

class ProjectLoadWarningDialog : public QDialog
{
    Q_OBJECT

public:
    ProjectLoadWarningDialog(QWidget *parent, const WarningMessageService *messageService = 0,
            const QString &documentVersion = QString());

private:
    QWidget *createTopPanel();
    QWidget *createModelInfoPanel();
    QWidget *createExplanationPanel();
    QWidget *createDetailsPanel();
    QTableWidget *createTableWidget();
    int getNumberOfTableRows() const;
    QStringList getTableHeaderLabels() const;
    QTableWidgetItem *createTableItem(const QString &name);

    QStringList getModelNames() const;
    QLabel *createModelStatusLabel(const QString &model_name) const;

    QString getExplanationText() const;

    const WarningMessageService *m_messageService;
    QString m_projectDocumentVersion;
};

#endif
