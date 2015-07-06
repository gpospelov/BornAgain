// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/ProjectLoadWarningDialog.h
//! @brief     Defines class ProjectLoadWarningDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROJECTLOADWARNINGDIALOG_H
#define PROJECTLOADWARNINGDIALOG_H

#include <QDialog>

//! @class ProjectLoadWarningDialog
//! @brief The dialog to inform user about encountered problems during the loading of old project

class ProjectLoadWarningDialog : public QDialog
{
    Q_OBJECT

public:
    ProjectLoadWarningDialog(QWidget *parent);


private:
    QWidget *createTopPanel();
    QWidget *createModelInfoPanel();
    QWidget *createExplanationPanel();
    QWidget *createDetailsPanel();
};

#endif
