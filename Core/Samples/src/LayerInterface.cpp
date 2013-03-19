// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Samples/LayerInterface.cpp 
//! @brief     Implements class LayerInterface.
//
// ************************************************************************** //

#include "LayerInterface.h"
#include <iostream>
#include <iomanip>

LayerInterface::LayerInterface()
: m_roughness(0)
, m_LayerTop(0)
, m_LayerBottom(0)
{
    setName("LayerInterface");
}

LayerInterface::~LayerInterface()
{
    delete m_roughness;
}

LayerInterface *LayerInterface::createSmoothInterface(const Layer *p_layer_top, const Layer *p_layer_bottom)
{
    LayerInterface *lr = new LayerInterface();
    lr->setLayerTop(p_layer_top);
    lr->setLayerBottom(p_layer_bottom);
    return lr;
}

LayerInterface *LayerInterface::createRoughInterface(const Layer *p_layer_top, const Layer *p_layer_bottom, const LayerRoughness &roughness)
{
    LayerInterface *lr = new LayerInterface();
    lr->setLayerTop(p_layer_top);
    lr->setLayerBottom(p_layer_bottom);
    lr->setRoughness(roughness);
    return lr;
}

void LayerInterface::setRoughness(const LayerRoughness &roughness)
{
    if(m_roughness) {
        std::cout << "LayerInterface::setRoughness() -> Info. Roughness already assigned to given interface, removing it " << std::endl;
        deregisterChild(m_roughness);
        delete m_roughness;
        m_roughness=0;
    }
    //m_roughness = new LayerRoughness(roughness);
    m_roughness = roughness.clone();
    registerChild(m_roughness);
}

void LayerInterface::print(std::ostream &ostr) const
{
    ICompositeSample::print(ostr);
    ostr << " top:" << getLayerTop() << " bottom:" << getLayerBottom();
}
