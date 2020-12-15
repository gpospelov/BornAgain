// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYEREDITORTOOLBAR_H
#define DAREFL_LAYEREDITOR_LAYEREDITORTOOLBAR_H

#include <QToolBar>
#include <QWidget>
#include <darefl/darefl_export.h>
#include <map>
#include <string>

namespace DaRefl
{

class LayerEditorActions;

//! Layer editor toolbar.

class DAREFLCORE_EXPORT LayerEditorToolBar : public QToolBar
{
    Q_OBJECT

public:
    LayerEditorToolBar(LayerEditorActions* actions, QWidget* parent = nullptr);
    ~LayerEditorToolBar() = default;

    void updateToolButtonStates(bool first_present, bool last_present);

private:
    QMenu* create_layer_menu(LayerEditorActions* editor_actions);
    std::map<std::string, QWidget*> m_toolbarWidgets;
};

} // namespace DaRefl

#endif // DAREFL_LAYEREDITOR_LAYEREDITORTOOLBAR_H
