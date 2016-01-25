// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitProxyModel.h
//! @brief     Defines class FitProxyModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEFITPROXYMODEL_H
#define OBSOLETEFITPROXYMODEL_H


#include <QAbstractItemModel>

class ObsoleteFitModel;
class ParameterizedItem;

class BA_CORE_API_ ObsoleteFitProxyModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ObsoleteFitProxyModel(QObject *parent = 0);
    virtual ~ObsoleteFitProxyModel(){}

    // overriden methods
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int rowCount(const QModelIndex &parentIndex) const;
    virtual int columnCount(const QModelIndex &parentIndex) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parentIndex) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    //end if overriden methods

    void setFitModel(ObsoleteFitModel *fitModel);
    ObsoleteFitModel *getFitModel()
        { return m_fitModel; }

    ParameterizedItem *itemForIndex(const QModelIndex &index) const;

private:
    ObsoleteFitModel *m_fitModel;

};




#endif
