#ifndef LAYER_H
#define LAYER_H

#include "ISample.h"
#include "IMaterial.h"
#include "Types.h"
#include "HomogeneousMaterial.h"

class Layer : public ISample
{
public:
    Layer();
    virtual ~Layer();

    virtual void setThickness(double thickness);
    virtual double getThickness() const { return m_thickness; }
    virtual void setMaterial(IMaterial* p_material) { mp_bulk_material = p_material; }
    virtual void setMaterial(IMaterial* p_material, double thickness);
    virtual IMaterial* getMaterial() { return mp_bulk_material; }
    virtual complex_t getRefractiveIndex() const { return (dynamic_cast<HomogeneousMaterial *>(mp_bulk_material))->getRefractiveIndex(); }

private:
    IMaterial* mp_bulk_material;
    double m_thickness;
//    LayerRoughness* mp_top_roughness;
//    LayerRoughness* mp_bottom_roughness;

};

#endif // LAYER_H
