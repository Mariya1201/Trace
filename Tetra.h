
#ifndef Tetra_h
#define Tetra_h

class Tetra : public Shape {
private:
    Vec3 v1 = { 0.0, 0.0, 0.0 };
    Vec3 v2 = { 2.0, 2.0, 0.0 };
    Vec3 v3 = { 0.0, 2.0, 2.0 };
    Vec3 v4 = { 2.0, 0.0, 2.0 };
    int func(const Vec3& A, const Vec3& B, const Vec3& C, const Vec3& D, const Vec3& orig, const Vec3& dir, double& t1, Vec3& N) {
        double d = triangle_intersection(orig, dir, A, B, C);
        if (d <= 0)
            return -1;
        if (d > t1 && t1 > 0)
            return -1;

        auto n = cross(B - A, C - B).normalize();
        if (n * (D - C) >= 0)
            n = n * (-1);

        if (n * dir > 0)
            return -1;

        N = n;
        t1 = d;
        return 0;
    }
    double triangle_intersection(const Vec3& orig, const Vec3 dir, const Vec3& v0, const Vec3& v1, const Vec3& v2) {
        Vec3 e1 = v1 - v0;
        Vec3 e2 = v2 - v0;
        Vec3 pvec = cross(dir, e2);
        double det = e1 * pvec;

        if (det < 1e-8 && det > -1e-8) {
            return 0;
        }

        double inv_det = 1 / det;
        Vec3 tvec = orig - v0;
        double u = (tvec * pvec) * inv_det;
        if (u < 0 || u > 1) {
            return 0;
        }

        Vec3 qvec = cross(tvec, e1);
        double v = (dir * qvec) * inv_det;
        if (v < 0 || u + v > 1) {
            return 0;
        }
        return (e2 * qvec) * inv_det;
    }

public:
    Tetra() = default;
    Tetra(const string& type, const Vec3& color, const Vec3& v1, const Vec3& v2, const Vec3& v3, const Vec3& v4) : Shape(type, color) {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        this->v4 = v4;
    }


    bool rayIntersect(const Vec3& orig, const Vec3& dir, double& t0, Vec3& hit, Vec3& N) override {
        double t1 = -1;

        int f1 = func(v1, v2, v3, v4, orig, dir, t1, N);
        int f2 = func(v2, v3, v4, v1, orig, dir, t1, N);
        int f3 = func(v1, v4, v3, v2, orig, dir, t1, N);
        int f4 = func(v1, v2, v4, v3, orig, dir, t1, N);

        t0 = t1;
        hit = orig + dir * t0;
        if (f1 * f2 * f3 * f4 == 0)
            return true;
        return false;
    }

    Vec3 get_v1() {
        return v1;
    }
    Vec3 get_v2() {
        return v2;
    }
    Vec3 get_v3() {
        return v3;
    }
    Vec3 get_v4() {
        return v4;
    }
};

#endif /* Tetra_h */
