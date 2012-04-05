#ifndef LAYER_H
#define LAYER_H

#include "ISample.h"
#include "IMaterial.h"

class Layer : public ISample
{
public:
    Layer();
    virtual ~Layer();

    virtual void setThickness(double thickness);
    virtual const double getThickness() const { return m_thickness; }
    virtual void setBulkMaterial(IMaterial* p_material) { mp_bulk_material = p_material; }
    virtual IMaterial* getBulkMaterial() { return mp_bulk_material; }

private:
    IMaterial* mp_bulk_material;
    double m_thickness;
//    LayerRoughness* mp_top_roughness;
//    LayerRoughness* mp_bottom_roughness;

};

#endif // LAYER_H
