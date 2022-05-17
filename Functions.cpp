
#include "headers.h"

bool Shapes_intersect(const Screen& scr, const Vec3& dir, vector<Shape*>& shapes, Vec3& hit, Vec3& N, Vec3& col) {
    Vec3 hit_ = hit;
    Vec3 N_ = N;
    double min_dist = std::numeric_limits<double>::max();
    for (size_t i = 0; i < shapes.size(); i++) {
        double temp_dist = std::numeric_limits<double>::max();
        if (shapes[i]->rayIntersect(scr.cam, dir, temp_dist, hit_, N_) && temp_dist < min_dist) {
            min_dist = temp_dist;
            N = N_;
            hit = hit_;
            col = shapes[i]->getColor();
        }
    }
    return min_dist <= 1000; 
}
Vec3 p_color(const Screen& scr, const Vec3& dir, vector<Shape*>& Shapes, const Light& light) {
    Vec3 point, N, col;
    if (Shapes_intersect(scr, dir, Shapes, point, N, col) == false) {
        return Vec3(250, 200, 241);
    }
    
    double diffuse_light_intensity = 0;
    double spec_light_intensity = 0;
    double ns = 0.3;
    double ks =130;
    Vec3 L = (light.position - point).normalize();
    Vec3 R = (N * 2.0 * (N * L) - L).normalize();
    Vec3 C = (scr.cam - point).normalize();
    Vec3 H =(L+C).normalize();
    double F = N * H;
    double F1 = R * C;
    diffuse_light_intensity = light.intensity * std::max(0.0, double(L * N));
    spec_light_intensity = light.intensity * (pow((max(0.0, F)), ks));
    Vec3 qq = col * ( diffuse_light_intensity + spec_light_intensity*ns );
    if (qq.x > 255)
    {
        qq.x = 255;
    }
    if (qq.y > 255)
    {
        qq.y = 255;
    }
    if (qq.z > 255)
    {
        qq.z = 255;
    }
    return qq;
}


unsigned char* createBitmapInfoHeader(int height, int width) {
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[0] = (unsigned char)(40);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(3 * 8);

    return infoHeader;
}

unsigned char* createBitmapFileHeader(int height, int stride) {
    int fileSize = 14 + 40 + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(14 + 40);

    return fileHeader;
}

void generateBitmapImage(const unsigned char* image, int height, int width, char* imageFileName) {
    int widthInBytes = width * 3;

    unsigned char padding[3] = { 0, 0, 0 };
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes)+paddingSize;

    FILE* imageFile = fopen(imageFileName, "wb");

    unsigned char* fileHeader = createBitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, 14, imageFile);

    unsigned char* infoHeader = createBitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, 40, imageFile);

    int i;
    for (i = 0; i < height; i++) {
        fwrite(image + (i * widthInBytes), 3, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

void create_img(vector<Shape*>& Shapes, Light& light, const Screen& scr) {
    const int height = scr.height;
    const int width = scr.width;
    Vec3 te = scr.normal;
    Vec3 t = te.normalize();
    Vec3 up = scr.up;
    Vec3 f = cross(up, t).normalize();
    Vec3 a = cross(t, f);
    double d = scr.screen;
    double alpha = scr.alpha;
    double fov = alpha / 180 * 3.149;
    double w = d * tan(fov / 2.);
    double h = w * (double(height) / double(width));
    
    std::vector<Vec3> pixels(width * height);

    FrameBuffer image(width, height);

    auto start_for = std::chrono::steady_clock::now();
#pragma omp parallel for
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {

            double dir_[3];
            for (int k = 0; k < 3; k++) {
                dir_[k] = t[k] * d - w * f[k] - h * a[k] + (i * 2 * w) * f[k] / (width - 1) + ((height - j) * 2 * h) * a[k] / (height - 1);
            }
            Vec3 dir = Vec3(dir_[0], dir_[1], dir_[2]).normalize();

            pixels[i + j * width] = p_color(scr, dir, Shapes, light);
        }
    }
    auto end_for = std::chrono::steady_clock::now();
    std::cout << "Time is " << std::chrono::duration<double, std::milli>(end_for - start_for).count() << " ms" << "\n";


    char* FileName = (char*)"rez.bmp";

    int i, j;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            image(i, j, 2) = pixels[i + j * width][2]; 
            image(i, j, 1) = pixels[i + j * width][1]; 
            image(i, j, 0) = pixels[i + j * width][0]; 
        }
    }
    generateBitmapImage(image.ptr(), height, width, FileName);
}
