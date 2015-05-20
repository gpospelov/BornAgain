#ifndef DISTRIBUTIONEDITOR_H_
#define DISTRIBUTIONEDITOR_H_

#include "AwesomePropertyEditor.h"
#include "BeamWavelengthItem.h"
#include "ParameterizedItem.h"
#include <QDebug>
#include "DistributionWidget.h"

class ParameterizedItem;
class AwesomePropertyEditor;

class DistributionEditor : public QWidget
{
    Q_OBJECT
public:
    DistributionEditor(QWidget *parent = 0);
    virtual ~DistributionEditor() {}
    void setItem(ParameterizedItem *item);
    void plotItem(ParameterizedItem *item);
    void setNameOfEditor(QString name);

private slots:
    void onSubItemChanged(const QString &property_name);

private:
    AwesomePropertyEditor *m_propertyEditor;
    ParameterizedItem *m_item;
    DistributionWidget *m_plotwidget;
    QString m_nameOfEditor;
    QGroupBox *m_box;
};

#endif
