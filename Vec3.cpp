
#include "headers.h"

Vec3::Vec3() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vec3::Vec3(double x_, double y_, double z_) {
    x = x_;
    y = y_;
    z = z_;
}

Vec3& Vec3::operator=(const Vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

const double& Vec3::operator[](const int i) const {
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else if (i == 2)
        return z;
    return x;
}

double Vec3::lenght() {
    return sqrt(x * x + y * y + z * z);
}

Vec3& Vec3::normalize() {
    double l = this->lenght();
    x = x / l;
    y = y / l;
    z = z / l;
    return *this;
}

Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

double operator*(const Vec3& v1, const Vec3& v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

Vec3 operator*(const Vec3& v1, double F) {
    return Vec3(v1[0] * F, v1[1] * F, v1[2] * F);
}

Vec3 operator*(double F, const Vec3& v1) {
    return Vec3(v1[0] * F, v1[1] * F, v1[2] * F);
}

Vec3 cross(const Vec3& x, const Vec3& y) {
    return Vec3(x[1] * y[2] - x[2] * y[1], x[2] * y[0] - x[0] * y[2], x[0] * y[1] - x[1] * y[0]);
}
