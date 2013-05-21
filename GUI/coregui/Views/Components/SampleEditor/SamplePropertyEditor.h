#ifndef SAMPLEPROPERTYEDITOR_H
#define SAMPLEPROPERTYEDITOR_H


#include <QWidget>

class QtVariantPropertyManager;
class QtTreePropertyBrowser;
class QtProperty;
class QVariant;

//class SamplePropertyEditorInterface : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit SamplePropertyEditorInterface(QWidget *parent = 0) : QWidget(parent)
//    {
//        setMinimumSize(128, 128);
//        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    }
//    virtual ~SamplePropertyEditorInterface(){}
//};


class SamplePropertyEditor : public QWidget
{
    Q_OBJECT

public:
    SamplePropertyEditor(QWidget *parent = 0);
    virtual ~SamplePropertyEditor(){}

private slots:
    void valueChanged(QtProperty *property, const QVariant &value);

private:
    class QtVariantPropertyManager *m_variantManager;
    class QtTreePropertyBrowser *m_propertyEditor;
};


#endif // SAMPLEPROPERTYEDITOR_H
