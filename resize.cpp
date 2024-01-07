// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.hpp"
#include "Image.hpp"
#include "processing.hpp"
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    if(argc < 4)
    {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }
    string filename = argv[1];
    string newfile = argv[2];
    int newWidth = atoi(argv[3]);
    int newHeight;
        
    ifstream fin(filename);
    if(!(fin.is_open()))
    {
        cout << "Error opening file: " << filename << endl;
    }
    
    Image* img = new Image;
    Image_init(img, fin);
    fin.close();
    
    if(argc == 5)
    {
        newHeight = atoi(argv[4]);
    }
    else
    {
        newHeight = Image_height(img);
    }
    
    if(newWidth > Image_width(img) || newWidth <= 0 ||
       newHeight > Image_height(img) || newHeight <= 0)
    {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }
    
    seam_carve(img, newWidth, newHeight);
    ofstream fout;
    fout.open(newfile);
    Image_print(img, fout);
    delete img;
    fout.close();
    
    return 0;
}
