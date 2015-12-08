// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/ExtendedDetectorDialog.h
//! @brief     Defines class DistributionDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef EXTENDEDDETECTORDIALOG_H
#define EXTENDEDDETECTORDIALOG_H

#include <QDialog>

class MaskEditor;

//! The dialog which shows an editor to change parameters of DistributionItem
class ExtendedDetectorDialog : public QDialog
{
    Q_OBJECT

public:
    ExtendedDetectorDialog(QWidget *parent = 0);
    virtual ~ExtendedDetectorDialog(){}

//    void setItem(ParameterizedItem *item);
//    void setNameOfEditor(const QString &name);

private:
//    ExtendedDetectorDialog *m_editor;
    MaskEditor *m_maskEditor;
};

#endif
