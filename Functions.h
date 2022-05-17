
#ifndef Functions_h
#define Functions_h

bool Shapes_intersect(const Screen& scr, const Vec3& dir, vector<Shape*>& shapes, Vec3& hit, Vec3& N, Vec3& col);

Vec3 p_color(const Screen& scr, const Vec3& dir, vector<Shape*>& Shapes, const Light& light);

unsigned char* createBitmapInfoHeader(int height, int width);

unsigned char* createBitmapFileHeader(int height, int stride);

void generateBitmapImage(const unsigned char* image, int height, int width, char* imageFileName);

class FrameBuffer {
    std::vector<unsigned char> data;
    int width;
public:
    FrameBuffer(int width, int height) :data(width* height * 3), width(width) {

    }
    const unsigned char* ptr() const {
        return data.data();
    }

    unsigned char& operator()(int i, int j, int plane) {
        return data[(i + j * width) * 3 + plane];
    }

};

void create_img(vector<Shape*>& Shapes, Light& light, const Screen& scr) ;


#endif /* Functions_h */
