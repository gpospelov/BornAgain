// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_DATALOADERTOOLBAR_H
#define DAREFL_DATALOADER_DATALOADERTOOLBAR_H

#include <QToolBar>
#include "darefl_export.h"

namespace DaRefl {

//! Tool bar for DataLoaderDialog.

class DAREFLCORE_EXPORT DataLoaderToolBar : public QToolBar {
    Q_OBJECT

public:
    DataLoaderToolBar(QWidget* parent = nullptr);

signals:
    void addFilesRequest();
    void removeFilesRequest();
};

} // namespace DaRefl

#endif // DAREFL_DATALOADER_DATALOADERTOOLBAR_H
