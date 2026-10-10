#include <iostream>
#include <stdio.h>
#include "Image.hpp"
#define PI 3.14159
int main(int args, char* argc[])
{
    Image image("../images/image.jpg");

    if (image.mat().empty()) {
        std::cerr << "Failed to load image\n";
        return 1;
    }
    
    std::cout << "Width:  " << image.width() << '\n';
    std::cout << "Height: " << image.height() << '\n';

/*

    image.display("Hello, World!");
    if(args > 0){
    image.rotate(PI/std::stoi(argc[1])).display("Hi again.");
    }
    */
    for(auto ele: image.bitSlice())
	    ele.display();
    return 0;
}
