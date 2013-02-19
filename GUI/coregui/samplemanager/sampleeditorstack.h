#ifndef SAMPLEEDITORSTACK_H
#define SAMPLEEDITORSTACK_H


#include <QStackedWidget>

class QDesignerFormEditorInterface;


// maintains stack of SampleEditor's
class SampleEditorStack : public QStackedWidget
{
    Q_OBJECT

public:
    explicit SampleEditorStack(QWidget *parent = 0);

};


#endif // SAMPLEEDITORSTACK_H
