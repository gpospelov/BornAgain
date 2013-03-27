// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/LayerInterface.h
//! @brief     Defines class LayerInterface.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef LAYERINTERFACE_H
#define LAYERINTERFACE_H

#include "ICompositeSample.h"
#include "LayerRoughness.h"

class Layer;

//! @class LayerInterface
//! @brief Interface between two layers.
//!
//! Interface between two layers connects two layers and posses roughness.
//! We prevent usage of default/copy constructors and assignment
//! operator and provide clone functionality from MultiLayer interface

class LayerInterface : public ICompositeSample
{
 public:
    virtual ~LayerInterface();
    //! Creates smooth interface between two layers
    static LayerInterface* createSmoothInterface(const Layer *p_layer_top, const Layer *p_layer_bottom);
    //! Creates rough interface between two layers
    static LayerInterface* createRoughInterface(const Layer *p_layer_top, const Layer *p_layer_bottom, const LayerRoughness &roughness);

    //! link to the top layer
    inline void setLayerTop(const Layer* p_layer_top) { m_LayerTop = p_layer_top; }

    //! link to the bottom layer
    inline void setLayerBottom(const Layer* p_layer_bottom) { m_LayerBottom = p_layer_bottom; }

    //! link between layers above and below the interface
    inline void setLayersTopBottom(const Layer* p_layer_top, const Layer* p_layer_bottom) { setLayerTop(p_layer_top); setLayerBottom(p_layer_bottom); }

    //! Sets roughness of the interface
    inline void setRoughness(const LayerRoughness &roughness);

    //! Returns roughness of the interface
    inline const LayerRoughness *getRoughness() const { return m_roughness; }

    //! Returns top layer
    inline const Layer *getLayerTop() const { return m_LayerTop; }

    //! Returns bottom layer
    inline const Layer *getLayerBottom() const { return m_LayerBottom; }

    //! Prints class
    friend std::ostream &operator<<(std::ostream &ostr, const LayerInterface &m) { m.print(ostr); return ostr; }

 protected:
    //! Prints class
    void print(std::ostream &ostr) const;

 private:
    LayerInterface();

    LayerRoughness *m_roughness;   //!< roughness of the interface
    const Layer *m_LayerTop;       //!< pointer to the layer above interface
    const Layer *m_LayerBottom;    //!< pointer to the layer below interface
};

#endif // LAYERINTERFACE_H
