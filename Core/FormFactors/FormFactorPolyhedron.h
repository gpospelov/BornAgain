
//! One edge of a polygon, for form factor computation.

class PolyhedralEdge {
public:
    PolyhedralEdge( const kvector_t _Vlow, const kvector_t _Vhig ) :
        E((_Vhig-_Vlow)/2), R((_Vhig+_Vlow)/2) {};
    kvector_t E; //!< vector pointing from mid of edge to upper vertex
    kvector_t R; //!< position vector of edge midpoint
    cmplx contrib(int m, cvector_t prevec, cvector_t qpa) const;
};


//! A polygon, for form factor computation.

class PolyhedralFace {
protected:
    static const double qpa_limit_series; //!< determines when use power series
    bool sym_S2; //!< if true, then edges obtainable by inversion are not provided
    std::vector<PolyhedralEdge> edges;
    double area;
    kvector_t normal; //!< normal vector of this polygon's plane
    double rperp; //!< distance of this polygon's plane from the origin, along 'normal'
    double radius_2d; //!< radius of enclosing cylinder
    void decompose_q( const cvector_t q, cmplx& qperp, cvector_t& qpa ) const;
    cmplx ff_n_core( int m, const cvector_t qpa ) const;
public:
    double radius_3d; //!< radius of enclosing sphere
    PolyhedralFace( const std::vector<kvector_t>& _V, bool _sym_S2=false );
    double getPyramidalVolume() const;
    cmplx ff_n( int m, const cvector_t q ) const;
    cmplx ff( const cvector_t q, const bool sym_Ci ) const;
    void assert_Ci( const PolyhedralFace& other ) const;
};


//! A polyhedron, for form factor computation.

class FormFactorPolyhedron {
protected:
    double z_origin;
    bool sym_Ci; //!< if true, then faces obtainable by inversion are not provided
    double radius;
    double volume;
    static const double q_limit_series;
    std::vector<PolyhedralFace> faces;
    virtual cmplx evaluate_centered( cvector_t q ) const;
public:
    FormFactorPolyhedron( const std::vector<PolyhedralFace>& _faces,
                          const double _z_origin, const bool _sym_Ci=false );
    cmplx evaluate_for_q( cvector_t q ) const;
    double getVolume() const { return volume; }

    // test methods:
    void assert_platonic() const;
};


#ifdef POLYHEDRAL_DIAGNOSTIC
//! Information about the latest form factor evaluation. Not thread-safe.
//! Used only by external test program.
class Diagnosis {
public:
    int maxOrder;
    int nExpandedFaces;
    bool operator!=( const Diagnosis& other ) const {
        return maxOrder!=other.maxOrder || nExpandedFaces!=other.nExpandedFaces; }
    friend std::ostream& operator<< (std::ostream& stream, const Diagnosis& diag) {
        return stream<<" ["<<diag.nExpandedFaces<<":"<<diag.maxOrder<<"]";
    }
};
#endif
