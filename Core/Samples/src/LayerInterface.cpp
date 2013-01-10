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


/* ************************************************************************* */
// print
/* ************************************************************************* */
void LayerInterface::print(std::ostream &ostr) const
{
    ICompositeSample::print(ostr);
    ostr << " top:" << getLayerTop() << " bottom:" << getLayerBottom();
//    ostr << getName()
//         << " " << std::setw(12) << this
//         << " top:"<< getLayerTop() << " bottom:" << getLayerBottom() << "   ";
//    const LayerRoughness *roughness = getRoughness();
//    if(roughness) {
//        ostr << "> " << *roughness;
//    }else{
//        ostr << "> no roughness";
//    }
}
