// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/ExtendedDetectorDialog.h
//! @brief     Defines class DistributionDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
    void readSettings();
    void writeSettings();

    MaskEditor *m_maskEditor;
    DetectorMaskDelegate *m_detectorMaskDelegate;
};

#endif // EXTENDEDDETECTORDIALOG_H
