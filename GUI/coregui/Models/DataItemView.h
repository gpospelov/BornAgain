// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItemView.h
//! @brief     Defines class DataItemView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATAITEMVIEW_H
#define DATAITEMVIEW_H

#include "SessionItem.h"

class DataItem;
template<class T> class OutputData;

//! Base for DataItem1DView and DataItem2DView

class BA_CORE_API_ DataItemView : public SessionItem
{
    static const QString T_CHILDREN;

public:
    //! Implements a link to DataItem. If path name
    //! of a DataItem changes, the link becomes invalid.
    class DataItemLink : public SessionItem {
    public:
       static const QString P_LINK;

       DataItemLink();
       DataItemLink(DataItem* item);

       DataItem* dataItem();
    };

    ~DataItemView() override = default;

    bool addItem(DataItem* data_item);
    std::vector<DataItem*> dataItems();
    DataItem* dataItem(size_t i) const;

protected:
    DataItemView(const QString& model_type);
    const OutputData<double>* getOutputData(size_t i) const;
};

#endif // DATAITEMVIEW_H
