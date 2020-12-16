// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_DATALOADER_DATALOADERTOOLBAR_H
#define BORNAGAIN_GUI2_DATALOADER_DATALOADERTOOLBAR_H

#include "darefl_export.h"
#include <QToolBar>

namespace gui2 {

//! Tool bar for DataLoaderDialog.

class DAREFLCORE_EXPORT DataLoaderToolBar : public QToolBar {
    Q_OBJECT

public:
    DataLoaderToolBar(QWidget* parent = nullptr);

signals:
    void addFilesRequest();
    void removeFilesRequest();
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_DATALOADERTOOLBAR_H
