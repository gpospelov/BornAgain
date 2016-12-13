// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerInterface.h
//! @brief     Defines class LayerInterface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERINTERFACE_H
#define LAYERINTERFACE_H

#include "ISample.h"
#include <memory>

class LayerRoughness;

//! Interface between two layers, possibly with roughness.
//! @ingroup samples_internal

class BA_CORE_API_ LayerInterface : public ISample
{
public:
    virtual ~LayerInterface();

    LayerInterface* clone() const;

    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    //! Creates smooth interface between two layers
    static LayerInterface* createSmoothInterface(const Layer* top_layer, const Layer* bottom_layer);

    //! Creates rough interface between two layers
    static LayerInterface* createRoughInterface(const Layer* top_layer, const Layer* bottom_layer,
                                                const LayerRoughness& roughness);

    //! Sets roughness of the interface.
    void setRoughness(const LayerRoughness& roughness);

    //! Returns roughness of the interface.
    const LayerRoughness* getRoughness() const;

    const Layer* topLayer() const;

    const Layer* bottomLayer() const;

    std::vector<const INode*> getChildren() const;

private:
    void setLayersTopBottom(const Layer* top_layer, const Layer* bottom_layer);
    LayerInterface();

    const Layer* m_topLayer;                     //!< pointer to the layer above interface
    const Layer* m_bottomLayer;                  //!< pointer to the layer below interface
    std::unique_ptr<LayerRoughness> m_roughness; //!< roughness of the interface
};

inline const LayerRoughness* LayerInterface::getRoughness() const
{
    return m_roughness.get();
}

inline const Layer* LayerInterface::topLayer() const
{
    return m_topLayer;
}

inline const Layer* LayerInterface::bottomLayer() const
{
    return m_bottomLayer;
}

#endif // LAYERINTERFACE_H
