
#ifndef vec3_h
#define vec3_h

class Vec3 {
public:
    double x;
    double y;
    double z;

    Vec3();
    Vec3(double x, double y, double z);
    Vec3(const Vec3& a) {
        x = a.x;
        y = a.y;
        z = a.z;
    }

    Vec3& operator=(const Vec3& v);
    const double& operator[](int i) const;

    double lenght();
    Vec3& normalize();
};

Vec3 operator+(const Vec3& v1, const Vec3& v2);
Vec3 operator-(const Vec3& v1, const Vec3& v2);
double operator*(const Vec3& v1, const Vec3& v2);
Vec3 operator*(const Vec3& v1, double F);
Vec3 operator*(double F, const Vec3& v1);
Vec3 cross(const Vec3& x, const Vec3& y);

#endif /* vec3_h */
