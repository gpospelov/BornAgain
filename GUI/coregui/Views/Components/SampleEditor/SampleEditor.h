#ifndef SAMPLEEDITOR_H
#define SAMPLEEDITOR_H

#include <QObject>
#include <QStackedWidget>

class SampleEditorScene;
class SampleEditorView;


//- -------------------------------------------------------------------
//! @class ISampleEditor
//! @brief Interface for SampleEditor
//- -------------------------------------------------------------------
class ISampleEditor : public QObject
{
    Q_OBJECT

public:
    ISampleEditor(QObject *parent = 0) : QObject(parent){}
    virtual ~ISampleEditor() { }

};


//- -------------------------------------------------------------------
//! @class SampleEditor
//! @brief Main class for editing sample
//- -------------------------------------------------------------------
class SampleEditor: public ISampleEditor
{
    Q_OBJECT
public:
    SampleEditor(QWidget *parent = 0);
    virtual ~SampleEditor(){}

    SampleEditorScene *getEditorScene() { return m_editorScene; }
    SampleEditorView *getEditorView() { return m_editorView; }

    QWidget *getCentralWidget() { return m_editorStack; }

private:
    SampleEditorScene *m_editorScene;
    SampleEditorView *m_editorView;
    QStackedWidget *m_editorStack;
};



#endif // SAMPLEEDITOR_H
