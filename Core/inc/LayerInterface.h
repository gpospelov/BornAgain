#ifndef LAYERINTERFACE_H
#define LAYERINTERFACE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   LayerInterface.h
//! @brief  Definition of LayerInterface class
//! @author JCNS Scientific Computing group
//! @date   01.04.2012

#include "LayerRoughness.h"

class Layer;


//- -------------------------------------------------------------------
//! @class LayerInterface
//! @brief Interface between two layers.
//!
//! Interface between two layers connects two layers and posses roughness.
//! We prevent usage of default/copy constructors and assignment
//! operator and provide clone functionality from MultiLayer interface
//- -------------------------------------------------------------------
class LayerInterface
{
public:
    ~LayerInterface();

    //! create smooth interface between two layers
    static LayerInterface* createSmoothInterface(const Layer *p_layer_top, const Layer *p_layer_bottom);

    //! create rough interface between two layers
    static LayerInterface* createRoughInterface(const Layer *p_layer_top, const Layer *p_layer_bottom, const LayerRoughness &roughness);

    //! link to the top layer
    inline void setLayerTop(const Layer* p_layer_top) { m_LayerTop = p_layer_top; }

    //! link to the bottom layer
    inline void setLayerBottom(const Layer* p_layer_bottom) { m_LayerBottom = p_layer_bottom; }

    //! link between layers above and below the interface
    inline void setLayersTopBottom(const Layer* p_layer_top, const Layer* p_layer_bottom) { setLayerTop(p_layer_top); setLayerBottom(p_layer_bottom); }

    //! set roughness of the interface
    inline void setRoughness(const LayerRoughness &roughness) { m_roughness = roughness; }

    //! get top layer
    inline const Layer *getLayerTop() const { return m_LayerTop; }

    //! get bottom layer
    inline const Layer *getLayerBottom() const { return m_LayerBottom; }

private:
    LayerInterface();
    LayerInterface(const LayerInterface &);
    LayerInterface &operator=(const LayerInterface &);

    LayerRoughness m_roughness;    //!< roughness of the interface
    const Layer *m_LayerTop;       //!< pointer to the layer above interface
    const Layer *m_LayerBottom;    //!< pointer to the layer below interface
};

#endif // LAYERINTERFACE_H
