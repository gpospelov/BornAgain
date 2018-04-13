// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceDialog.h
//! @brief     Implements class RealSpaceDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACEDIALOG_H
#define REALSPACEDIALOG_H

#include "WinDllMacros.h"
#include <QDialog>
#include <memory>
#include <SampleModel.h>
#include <QTreeView>

class MaterialModel;
class MaterialEditor;
class ExternalProperty;
class QBoxLayout;

//! Dialog to hold RealSpaceWidget.

class BA_CORE_API_ RealSpaceDialog : public QDialog
{
    Q_OBJECT

public:
    RealSpaceDialog(SampleModel* sampleModel = nullptr,
                          QItemSelectionModel* selectionModel = nullptr,
                          QWidget *parent = nullptr);

public slots:
    void closeEvent(QCloseEvent*);

private:
    void readSettings();
    void writeSettings();

    SampleModel *m_sampleModel;
    QItemSelectionModel *m_selectionModel;
};


#endif // REALSPACEDIALOG_H
