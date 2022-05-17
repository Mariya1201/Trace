
#ifndef Shape_h
#define Shape_h

class Shape {
protected:
    string type = "sphere";
    Vec3 color = { 225,255,255 };

public:
    Shape() = default;
    Shape(const string& type_, const Vec3& color_) {
        type = type_;
        color = color_;
    }

    virtual bool rayIntersect(const Vec3& orig, const Vec3& dir, double& t0, Vec3& hit, Vec3& N) = 0;

    Vec3 getColor() {
        return color;
    }

    string getType() {
        return type;
    }
};

#endif /* Shape_h */
