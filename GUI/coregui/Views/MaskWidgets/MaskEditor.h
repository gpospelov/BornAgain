// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditor.h
//! @brief     Defines class MaskEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITOR_H
#define MASKEDITOR_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMainWindow>

class MaskEditorCanvas;
class MaskEditorToolPanel;
class QSplitter;
class MaskModel;

//! Main class to draw masks on top of intensity data map

class BA_CORE_API_ MaskEditor : public QMainWindow
{
    Q_OBJECT
public:
    MaskEditor(QWidget *parent = 0);


private:
    void init_test_model();

    MaskEditorCanvas *m_editorCanvas;
    MaskEditorToolPanel *m_editorToolPanel;
    QSplitter *m_splitter;
    MaskModel *m_maskModel;
};


#endif
