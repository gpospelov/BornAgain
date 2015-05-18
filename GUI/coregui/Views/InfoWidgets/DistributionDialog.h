#ifndef DISTRIBUTIONDIALOG_H_
#define DISTRIBUTIONDIALOG_H_

#include "DistributionEditor.h"
#include <QHBoxLayout>
#include <QDialog>

class DistributionDialog : public QDialog
{
     Q_OBJECT

public:
    DistributionDialog(QWidget *parent = 0);
    virtual ~DistributionDialog() {}
    void setItem(ParameterizedItem *item);

private:
    DistributionEditor *m_editor;
};

#endif
