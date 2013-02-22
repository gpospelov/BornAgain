#ifndef SAMPLEEDITOR_H
#define SAMPLEEDITOR_H

//#include <QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormEditorInterface>

class SampleEditor: public QDesignerFormEditorInterface
{
    Q_OBJECT
public:
    SampleEditor(QObject *parent = 0);
    virtual ~SampleEditor(){}
};

#endif // SAMPLEEDITOR_H
