/***************************************************************************
 * \file bmp.hpp
 * \author emma-campbell
 * \date 2019-04-30
 * 
 * The header file for our BMP class
 * 
 * DEPENDENCIES: <string>
 *               <vector>
 ***************************************************************************/
#ifndef BMP_H
#define BMP_H

#include <string>
#include <vector>

/**
 * Simple pixel class for storing the color data
 */ 
class Pixel {

    public:
    
        int red, green, blue;

        //CONSTRUCTORS    
        Pixel() : red(0), green(0), blue(0) {}
        Pixel(int r, int g, int b) : red(r), green(g), blue(b) {}
};

//I am lazy and don't want to type a lot so I am redefining a 2D Pixel vector as PixelMatrix
typedef std::vector< std::vector<Pixel> > PixelMatrix;

/**
 * Here is the BMP Class. You can find the methods in the file bmp.cpp
 * 
 * BASIC OPERATIONS:
 *      open(string)      -> opens a bmp from a string path to the file
 *      save(string)      -> saves the bmp using a string path to the save location
 *      isImage()         -> confirms that the opened image is a legit (not faulty) bmp
 *      toPixelMatrix()   -> returns the pixel data (i.e. for modification / filtering)
 *      fromPixelMatrix() -> replaces the pixel data (i.e. after modification or filtering)
 */     
class BMP {
   
    private:
        //PIXEL DATA
        PixelMatrix pixels;

    public:
        //BASIC OPERATIONS
        void open(std::string);
        void save(std::string);
        bool isImage();
        PixelMatrix toPixelMatrix();
        void fromPixelMatrix(const PixelMatrix &);
};

#endif

