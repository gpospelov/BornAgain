#ifndef SAMPLEEDITOR_H
#define SAMPLEEDITOR_H

#include <QObject>
#include <QStackedWidget>

class DesignerScene;
class DesignerView;


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

    DesignerScene *getEditorScene() { return m_designerScene; }
    DesignerView *getEditorView() { return m_designerView; }

    QWidget *getCentralWidget() { return m_editorStack; }

private:
    DesignerScene *m_designerScene; //! scene which holds all objects
    DesignerView *m_designerView;   //! graphical representation of scene with object
    QStackedWidget *m_editorStack;    //! stack for varaiety of SampleEditorView
};



#endif // SAMPLEEDITOR_H
