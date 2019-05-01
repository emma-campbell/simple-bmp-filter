/***************************************************************************
 * \file main.cpp
 * \author emma-campbell
 * \date 2019-04-30
 * 
 * This is the main file for our filtering program. Here, we do all the filtering
 * and return the image (BMP class reads the file, and writes it)
 * 
 * DEPENDENCIES:    bmp.hpp
 *                  bmp.cpp              
 *                  <iostream>
 *                  <fstream>
 *                  <vector>
 *                  <cmath>
 ***************************************************************************/

// system dependencies
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

//user built dependencies
#include "bmp.hpp"
#include "bmp.cpp"

#define UNDEFINED 9999
//HSV structure --> used for filtering process
//it is simpler to convert to gray scale using HSV rather than RGB
typedef struct{
    double h;
    double s;
    double v;
} HSV;

//RGB structure --> used for the filtering process
//used for returning all the values of hsv2rgb at once
typedef struct {
    int r;
    int g;
    int b;
} RGB;

// /**
//  * \brief returns the largest of three doubles
//  * 
//  * \param a first double
//  * \param b second double
//  * \param c third double
//  * \return largest of a, b & c
//  */ 
// double largest(double a, double b, double c) {
//     if (a > b) {
//         if (a > c) {
//             return a;
//         }
//         else {
//             return c;
//         }
//     }
//     else {
//         if (b > c) {
//             return b;
//         }
//         else {
//             return c;
//         }
//     }
// }

// /**
//  * \brief returns the smallest of three doubles
//  * 
//  * \param a first double
//  * \param b second double
//  * \param c third double
//  * 
//  * \return smallest between a, b, & c.
//  */ 
// double smallest(double a, double b, double c) {
//     if (a < b) {
//         if (a < c) {
//             return a;
//         }
//         else {
//             return c;
//         }
//     }
//     else {
//         if (b < c) {
//             return b;
//         }
//         else {
//             return c;
//         }
//     }
// }

/**
 * \brief converts an RGB color into an HSV color
 * 
 * \param r red value
 * \param g green value
 * \param b blue value
 * 
 * \returns HSV (hue, saturation, value)
 * 
 * I found this awesome book online about computer graphics and just thought 
 * I would pass along the link if interested...Has cool psuedocode for translation
 * between color models if anyone finds it interesting
 * https://link.springer.com/book/10.1007/b138805
 * 
 * The relevant psuedocode for this function is found on p. 303.
 * 
 * Vist the link above for a more in depth description of the formula.
 */
HSV rgb2hsv(RGB in) {
    
    HSV out;
    double min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min < in.b ? min : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max > in.b ? max : in.b;

    out.v = max; // v
    delta = max - min;
    
    if (delta < 0.00001) {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    
    if (max > 0.0) {                          // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max); // s
    }

    else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN; // its now undefined
        return out;
    }

    if (in.r >= max) {                   
        out.h = (in.g - in.b) / delta; // between yellow & magenta
    }
    else if (in.g >= max) {
        out.h = 2.0 + (in.b - in.r) / delta; // between cyan & yellow
    }
    else {
        out.h = 4.0 + (in.r - in.g) / delta; // between magenta & cyan
    }

    out.h *= 60.0; // degrees

    if (out.h < 0.0) {
        out.h += 360.0;
    }

    return out;
}

/**
 * \brief converts an HSV color into a RGB color
 * 
 * \param hsv HSV structure (hue, saturation, value)
 * \return RGB structure (red, green, blue)
 * 
 * Again, the helpful psuedocode comes from: https://link.springer.com/book/10.1007/b138805
 * More details for HSV -> RGB found on p. 304
 * 
 * See the link above for more in depth description of the formula
 */
RGB hsv2rgb(HSV in) {
    
    double hh, p, q, t, ff;
    long i; 
    RGB out;

    if (in.s <= 0.0) {
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }

    hh = in.h;
    if (hh >= 360.0)
        hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch (i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
        }
    return out;
}

/**
 * \brief Performs the image filtering
 * 
 * \param bmp Pixel matrix of an image
 * \return modified Pixel matrix (all grayscale except red colors)
 * 
 * Filtering follows these general steps:
 *      1. Get the pixel
 *      2. Convert RGB -> HSV
 *      3. If the hue is not equal to red:
 *          4. Set saturation to 0
 *      5. Convert HSV -> RGB 
 *      6. Add the RGB pixel to the new filtered matrix
 */ 
std::vector< std::vector<Pixel> > filter(std::vector< std::vector<Pixel> > bmp) {
    
    std::vector< std::vector<Pixel> > newBMP; //filtered matrix
    RGB rgb;     //filtered temp pixel

    for (const auto &row : bmp) {
        std::vector<Pixel> temp;
        
        for (const auto &item : row) {
            Pixel p = item;

            rgb.r = p.red;
            rgb.g = p.green;
            rgb.b = p.blue;

            //conversion to HSV
            HSV h = rgb2hsv(rgb);

            //as specified by handout, red hue values generally lie between
            //-20 and 20 (also checks that it is not white)
            if (h.h > 20.0 && h.h < 340.0) {
                h.s = 0;
            }

            //convert back to RGB
            rgb = hsv2rgb(h);

            //create new pixel and add to row
            Pixel newPix = Pixel(rgb.r, rgb.g, rgb.b);
            temp.push_back(newPix);
        }
        //add row to the Matrix
        newBMP.push_back(temp);
    }

    //return the filtered matrix
    return newBMP;
}

int main(int argc, char* argv[]) {
    
    BMP img;    //BMP image class (bmp.hpp)
    
    //we can store the information that we are actually modifying (filtering) as a 2D array, so that
    //we dont accidentally touch the headers!
    std::vector<std::vector <Pixel> > bmp;
    
    //initializing the infile and outfile
    char *infile = NULL;
    char *outfile = NULL;

    if (argc != 3) { //ARGUMENTS MUST BE EQUAL TO 3 (INCLUE AN INFILE AND OUTFILE)
        std::cout << "Please be sure tp include in-file and out-file.\n";
        std::cout << "Program terminated" << std::endl;
        return -1;
    }
    else {
        
        //note -> argv[0] is the name of the executable
        infile = argv[1]; //infile at first argument
        outfile = argv[2]; //outfile at second 

        std::cout << "Opening " << infile << std::endl;
        
        img.open(infile);       //opens the image

        bool valid = img.isImage(); //checks that the image was opened correctly
        
        if (valid) { //if the image was opened correctly
            
            bmp = img.toPixelMatrix(); //get the pixel info

            std::cout << "Filtering image" << std::endl;
            bmp = filter(bmp);         //filter the pixel info

            img.fromPixelMatrix(bmp); //replace the previous pixel info with filtered pixels

            std::cout << "Saving file to " << outfile << std::endl;
            img.save(outfile);         //save to the outfile
        }
        else {  //couldn't open the image :(
            std::cout << "Image " << infile << " could not be loaded correctly." << std::endl;
            std::cout << "Program terminated" << std::endl;
            return -1;
        }
    }
    return 0; //mission success!
}
