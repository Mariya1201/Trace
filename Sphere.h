
#ifndef Sphere_h
#define Sphere_h

class Sphere : public Shape {
private:
    Vec3 center = { 0.0, 0.0, 0.0 };
    double radius = 2.0;
public:
    Sphere() = default;
    Sphere(const string& type, const Vec3& color, const Vec3& center, const double& radius) : Shape(type, color) {
        this->center = center;
        this->radius = radius;
    }

    bool rayIntersect(const Vec3& orig, const Vec3& dir, double& t0, Vec3& hit, Vec3& N) override {
        bool s = true;
        Vec3 L = center - orig;
        float tca = L * dir;
        float d2 = L * L - tca * tca;
        if (d2 > radius * radius) s = false;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;

        if (t0 < 0) t0 = t1;
        if (t0 < 0) s = false;

        hit = orig + dir * t0;
        N = (hit - getCenter()).normalize();

        return s;
    }

    Vec3 getCenter() {
        return center;
    }

    double getRadius() {
        return radius;
    }
};

#endif /* Sphere_h */
