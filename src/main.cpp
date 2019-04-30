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

//HSV structure --> used for filtering process
//it is simpler to convert to gray scale using HSV rather than RGB
struct HSV {
    double hue;
    double saturation;
    double value;
};

//RGB structure --> used for the filtering process
//used for returning all the values of hsv2rgb at once
struct RGB {
    int r;
    int g;
    int b;
};

/**
 * \brief returns the largest of three doubles
 * 
 * \param a first double
 * \param b second double
 * \param c third double
 * \return largest of a, b & c
 */ 
double largest(double a, double b, double c) {
    if (a > b) {
        if (a > c) {
            return a;
        }
        else {
            return c;
        }
    }
    else {
        if (b > c) {
            return b;
        }
        else {
            return c;
        }
    }
}

/**
 * \brief returns the smallest of three doubles
 * 
 * \param a first double
 * \param b second double
 * \param c third double
 * 
 * \return smallest between a, b, & c.
 */ 
double smallest(double a, double b, double c) {
    if (a < b) {
        if (a < c) {
            return a;
        }
        else {
            return c;
        }
    }
    else {
        if (b < c) {
            return b;
        }
        else {
            return c;
        }
    }
}


/**
 * \brief converts an RGB color into an HSV color
 * 
 * \param r red value
 * \param g green value
 * \param b blue value
 * 
 * \returns struct HSV (hue, saturation, value)
 * 
 * The formula for this comes from the following link:
 * https://www.rapidtables.com/convert/color/rgb-to-hsv.html
 * 
 * Vist the link above for a more in depth description of the formula.
 */
struct HSV rgb2hsv(int r, int g, int b) {

    double rPrime = 0.0, gPrime = 0.0, bPrime = 0.0, cMax = 0.0, cMin = 0.0, delta = 0.0;
    double hue = 0.0, saturation = 0.0, value = 0.0;

    rPrime = (double)((double)r / 255.0);
    gPrime = (double)((double)g / 255.0);
    bPrime = (double)((double)b / 255.0);

    cMax = largest(rPrime, gPrime, bPrime);
    cMin = smallest(rPrime, gPrime, bPrime);
    delta = cMax - cMin;     // the difference between the strongest color, and the weakest color

    if (delta == 0.0) {
        hue = 0.0; //white or red (depending on saturation)
    }
    else {
        if (cMax == rPrime) {
            hue = 60 * (double)((int)((gPrime - bPrime) / delta) % 6);
        }
        else if (cMax == gPrime) {
            hue = 60 * (((bPrime - rPrime) / delta) + 2);
        }
        else {
            hue = 60 * (((rPrime - gPrime) / delta) + 4);
        }
    }

    if (cMax != 0) {
        saturation = (delta / cMax);
    }
    else {
        saturation = 0.0;
    }

    value = cMax;

    struct HSV h;
    
    h.hue = hue;
    h.saturation = saturation;
    h.value = value;

    return h;
}

/**
 * \brief converts an HSV color into a RGB color
 * 
 * \param hsv HSV structure (hue, saturation, value)
 * \return RGB structure (red, green, blue)
 * 
 * The formula for this conversion is found here:
 * https://www.rapidtables.com/convert/color/hsv-to-rgb.html
 * 
 * See the link above for more in depth description of the formula
 */
struct RGB hsv2rgb(struct HSV hsv) {
    
    double h = 0.0, s = 0.0, v = 0.0;  //hue, saturation, value (respectively)
    double c = 0.0, x = 0.0, m = 0.0;
    double rgb[3];

    h = hsv.hue;            //get hue
    s = hsv.saturation;     //get saturation
    v = hsv.value;          //get value

    c = v * s;
    x = c * (double)(1 - abs(((int)(h / 60) % 2) - 1.0));
    m = v - c;

    if (h >= 0 && h < 60) {
        rgb[0] = c;
        rgb[1] = x;
        rgb[2] = 0.0;
    }
    else if (h >= 60 && h < 120) {
        rgb[0] = x;
        rgb[1] = c;
        rgb[2] = 0.0;
    }
    else if (h >= 120 && h < 180) {
        rgb[0] = 0.0;
        rgb[1] = c;
        rgb[2] = x;
    }
    else if (h >= 180 && h < 240) {
        rgb[0] = 0;
        rgb[1] = x;
        rgb[2] = c;
    }
    else if (h >= 240 && h < 300) {
        rgb[0] = x;
        rgb[1] = 0.0;
        rgb[2] = c;
    }
    else {
        rgb[0] = c;
        rgb[1] = 0.0;
        rgb[2] = x;
    }

    BYTE red = ((rgb[0] + m) * 255);
    BYTE green = ((rgb[1] + m) * 255);
    BYTE blue = ((rgb[2] + m) * 255);

    RGB newrgb;
    
    newrgb.r = red;
    newrgb.b = blue;
    newrgb.g = green;

    return newrgb; //return the HSV as a RGB
}

/**
 * \breif Performs the image filtering
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
    struct RGB rgb;     //filtered temp pixel

    for (const auto &row : bmp) {
        std::vector<Pixel> temp;
        
        for (const auto &item : row) {
            Pixel p = item;
            
            int r = p.red;
            int g = p.green;
            int b = p.blue;

            //conversion to HSV
            struct HSV h = rgb2hsv(r, g, b);

            //as specified by handout, red hue values generally lie between
            //-20 and 20 (also checks that it is not white)
            if (!((h.hue >= -20.0 && h.hue <= 20.0) && h.saturation != 0)) {
                h.saturation = 0;
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
