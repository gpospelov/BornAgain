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
class DetectorItem;
class DetectorMaskDelegate;
class InstrumentModel;

//! The dialog which shows a MaskEditor

class ExtendedDetectorDialog : public QDialog
{
    Q_OBJECT

public:
    ExtendedDetectorDialog(QWidget *parent = 0);
    virtual ~ExtendedDetectorDialog(){}

public slots:
    void setDetectorContext(InstrumentModel *instrumentModel, DetectorItem *detectorItem);

private:
    void reject();

private:
    MaskEditor *m_maskEditor;
    DetectorMaskDelegate *m_detectorMaskDelegate;
    void readSettings();
    void writeSettings();
};

#endif
