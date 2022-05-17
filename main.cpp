
#include "headers.h"

int main(int argc, const char* argv[]) {
    try {

        string file_name = "shapes.txt";
        ifstream inp;
        inp.open(file_name);

        std::vector<Shape*> shapes;
        string I;

        map<string, Factory*> factoryMap;
        factoryMap["sphere"] = new Factory_sphere;
        factoryMap["box"] = new Factory_box;
        factoryMap["tetra"] = new Factory_tetra;

        while (!inp.eof()) {
            inp >> I;

            auto Creator = factoryMap.find(I);
            if (Creator == factoryMap.end())
                throw runtime_error("There is no such class!");
            string stroka;
            getline(inp, stroka);

            shapes.push_back(Creator->second->create(stroka));

        }
        inp.close();

        string file_name1 = "data.txt";
        ifstream inp1;
        inp1.open(file_name1);
        Vec3 cam, light, normal, up;
        double screen = 0;
        double limit = 0;
        double alpha = 0;
        double width = 0;
        double height = 0;
        string A;

        while (!inp1.eof()) {
            inp1 >> A;
            if (A == "cam") {
                inp1 >> cam.x;
                inp1 >> cam.y;
                inp1 >> cam.z;
            }
            else if (A == "normal") {
                inp1 >> normal.x;
                inp1 >> normal.y;
                inp1 >> normal.z;
            }
            else if (A == "up") {
                inp1 >> up.x;
                inp1 >> up.y;
                inp1 >> up.z;
            }
            else if (A == "screen") {
                inp1 >> screen;
            }
            else if (A == "limit") {
                inp1 >> limit;
            }
            else if (A == "alpha") {
                inp1 >> alpha;
            }
            else if (A == "width") {
                inp1 >> width;
            }
            else if (A == "height") {
                inp1 >> height;
            }
            else if (A == "light") {
                inp1 >> light.x;
                inp1 >> light.y;
                inp1 >> light.z;
            }

        }
        inp1.close();

        Light light_ = { light, 1.0 };
        Screen scr = { cam, normal.normalize(), up, screen, limit, alpha, width, height };

        create_img(shapes, light_, scr);

    }
    catch (const exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
