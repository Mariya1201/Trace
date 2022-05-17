
#ifndef Box_h
#define Box_h

class Box : public Shape {
private:
    Vec3 v_min = { 0.0, 0.0, 0.0 };
    Vec3 v_max = { 2.0, 2.0, 2.0 };

    int func(const Vec3& A, const Vec3& B, const Vec3& C, const Vec3& D, const Vec3& orig, const Vec3& dir, double& t1, Vec3& N) {
        double d = triangle_intersection(orig, dir, A, B, C);
        if (d == 0)
            d = triangle_intersection(orig, dir, A, C, D);
        if (d <= 0)
            return -1;
        if (d > t1 && t1 > 0)
            return -1;

        N = cross(B - A, D - A).normalize();
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
    Box() = default;
    Box(const string& type, const Vec3& color, const Vec3& v_min, const Vec3& v_max) : Shape(type, color) {
        this->v_min = v_min;
        this->v_max = v_max;
    }

    bool rayIntersect(const Vec3& orig, const Vec3& dir, double& t0, Vec3& hit, Vec3& N) override {
        double t1 = -1;

        Vec3 A = v_min;
        Vec3 A1 = Vec3(v_min[0], v_max[1], v_min[2]);
        Vec3 B = Vec3(v_max[0], v_min[1], v_min[2]);
        Vec3 B1 = Vec3(v_max[0], v_max[1], v_min[2]);
        Vec3 C = Vec3(v_max[0], v_min[1], v_max[2]);
        Vec3 C1 = v_max;
        Vec3 D = Vec3(v_min[0], v_min[1], v_max[2]);
        Vec3 D1 = Vec3(v_min[0], v_max[1], v_max[2]);

        int f1 = func(A, B, B1, A1, orig, dir, t1, N);

        int f2 = func(B, C, C1, B1, orig, dir, t1, N);
        int f3 = func(C, D, D1, C1, orig, dir, t1, N);
        int f4 = func(D, A, A1, D1, orig, dir, t1, N);
        int f5 = func(A1, B1, C1, D1, orig, dir, t1, N);

        int f6 = func(D, C, B, A, orig, dir, t1, N);

        t0 = t1;
        hit = orig + dir * t0;
        if (f1 * f2 * f3 * f4 * f5 * f6 == 0)
            return true;
        return false;
    }

    Vec3 get_v_min() {
        return v_min;
    }

    Vec3 get_v_max() {
        return v_max;
    }
};

#endif /* Box_h */
