#include <iostream>
#include "Utilities/Macros.h"
#include "Geometry/Object3D.h"
#include "Math/Vector3.h"

class Plane : public virtual Object3D {
public:
    Plane() = default;
    Plane(const Vector3& normal, f32 d) : m_normal(normal), m_d(d) {};
    ~Plane() override = default;
    bool intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const override;
    void id() override {std::cout<<"Plane\n";};

    Vector3 m_normal;
    f32 m_d;
};
