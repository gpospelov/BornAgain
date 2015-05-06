#include "TestView.h"
#include "TestItem.h"
#include "LayerItem.h"
#include "AwesomePropertyEditor.h"
#include "BeamWavelengthItem.h"
#include "ParameterizedItem.h"
#include <QGroupBox>
#include <QGridLayout>
#include <QDebug>
#include "qcustomplot.h"

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
private slots:
    void onPropertyChanged(const QString &property_name);
    void onSubItemChanged(const QString &property_name);
    void onSubItemPropertyChanged(const QString &property_group, const QString &property_name);
private:
    AwesomePropertyEditor *m_propertyEditor;
    QHBoxLayout *m_mainLayout;
    ParameterizedItem *m_item;
    QCustomPlot *m_plot;

};
