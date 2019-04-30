/***************************************************************************
 * \file bmp.cpp
 * \author emma-campbell
 * \date 2019-04-30
 * 
 * The exectuable file for bmp.hpp (i.e. BMP class). This file defined all the 
 * methods initialized in bmp.hpp.
 * 
 * DEPENDENCIES: bmp.hpp
 *              <iostream>
 *              <fstream>
 *              <cstdlib>
 ***************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "bmp.hpp"

//These type defs come straight from microsoft (and are short for lazy typers like myself)
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned short int WORD;
typedef signed int LONG;

const int MIN_RGB = 0;      //min rgb val
const int MAX_RGB = 255;    //max rgb val
const int BMP_MAGIC_ID = 2;

// Windows BMP-specific format data
// One of the first type checking steps to see if the BMP
// image provided is legit
struct bmpfile_magic
{
    BYTE magic[BMP_MAGIC_ID];
};

//https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-tagbitmapfileheader
struct BITMAPFILEHEADER
{
    DWORD file_size;
    WORD creator1;
    WORD creator2;
    DWORD bmp_offset;
};

//https://docs.microsoft.com/en-us/previous-versions//dd183376(v=vs.85)
struct BITMAPINFOHEADER
{
    DWORD header_size;
    LONG width;
    LONG height;
    WORD num_planes;
    WORD bits_per_pixel;
    DWORD compression;
    DWORD bmp_byte_size;
    LONG hres;
    LONG vres;
    DWORD num_colors;
    DWORD num_important_colors;
};

/**
 * \brief opens a bmp from a string path to the file
 * 
 * \param filename name of the file that is being opened
 * \return nothing
 */
void BMP::open(std::string filename) {
    
    std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);

    //clear any previously existing info --> this happens whether you are able to open
    //the file, or not
    for (int i = 0; i < pixels.size(); i++) {
        pixels[i].clear();
    }
    pixels.clear();

    //this is checking if we have an error opening the file
    if (file.fail()) {
        std::cout << filename << " could not be opened. Does it exist? "
                  << "Is it already open by another program?" << std::endl;
    }
    else {
        
        bmpfile_magic magic; //first checking
        file.read((char *)(&magic), sizeof(magic));

        // Check to make sure that the first two bytes of the file are the "BM"
        // identifier that identifies a bitmap image.
        if (magic.magic[0] != 'B' || magic.magic[1] != 'M') {
            std::cout << filename << " is not in proper BMP format.\n";
        }
        else {
            BITMAPFILEHEADER header; //Now, into the 'fun' stuff
            file.read((char *)(&header), sizeof(header));

            BITMAPINFOHEADER info;
            file.read((char *)(&info), sizeof(info));

            // Check for this here and so that we know later whether we need to insert
            // each row at the bottom or top of the image.
            bool flip = true;
            if (info.height < 0) {
                flip = false;
                info.height = -info.height;
            }

            // Only support for 24-bit images
            if (info.bits_per_pixel != 24) {
                std::cout << filename << " uses " << info.bits_per_pixel
                          << "bits per pixel (bit depth). BMP only supports 24bit.\n";
            }

            // No support for compressed images
            if (info.compression != 0) {
                std::cout << filename << " is compressed. "
                          << "BMP only supports uncompressed images.\n";
            }

            file.seekg(header.bmp_offset); //FIND THE OFFSET!!

            // Now that we have the offset, we can read the pixel data
            for (int row = 0; row < info.height; row++)
            {
                std::vector<Pixel> row_data;

                for (int col = 0; col < info.width; col++) {
                    //each byte is the color. BMPs use the scheme BGR (rather than RGB)
                    int blue = file.get(); 
                    int green = file.get();
                    int red = file.get();

                    row_data.push_back(Pixel(red, green, blue)); //add to row
                }

                // Rows are padded so that they're always a multiple of 4 bytes.
                // file.seekg() will skip this padding
                file.seekg(info.width % 4, std::ios::cur);

                if (flip) {
                    //put pixels at top of matrix
                    pixels.insert(pixels.begin(), row_data);
                }
                else {
                    //put pixels at bottom
                    pixels.push_back(row_data);
                }
            }

            file.close();
        } 
    } 
}

/**
 * \brief saves the bmp using the specified filename
 * 
 * \param filename name of the output file
 * \return nothing
 */
void BMP::save(std::string filename)
{
    std::ofstream file(filename.c_str(), std::ios::out | std::ios::binary);

    //check that it was opened correctly
    if (file.fail()) {
        std::cout << filename << " could not be opened for editing. "
                  << "Is it already open by another program or is it read-only?\n";
    }
    else if (!isImage()) {
        std::cout << "BMP cannot be saved. It is not a valid image.\n";
    }
    else {
        
        // Now we can write all the info in the BMP structure
        bmpfile_magic magic;
        magic.magic[0] = 'B';
        magic.magic[1] = 'M';
        file.write((char *)(&magic), sizeof(magic));

        //WRITING BITMAPFILEHEADER
        BITMAPFILEHEADER header = {0};
        header.bmp_offset = sizeof(bmpfile_magic) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        header.file_size = header.bmp_offset + (pixels.size() * 3 + pixels[0].size() % 4) * pixels.size();
        file.write((char *)(&header), sizeof(header));

        //WRITING BITMAPINFOHEADER
        BITMAPINFOHEADER info = {0};
        info.header_size = sizeof(BITMAPINFOHEADER);
        info.width = pixels[0].size();
        info.height = pixels.size();
        info.num_planes = 1;
        info.bits_per_pixel = 24;
        info.compression = 0;
        info.bmp_byte_size = 0;
        info.hres = 2835;
        info.vres = 2835;
        info.num_colors = 0;
        info.num_important_colors = 0;
        file.write((char *)(&info), sizeof(info));

        // Write each row and column of Pixels into the image file -- note BMP writes rows upside down
        for (int row = pixels.size() - 1; row >= 0; row--) {
            const std::vector<Pixel> &row_data = pixels[row];

            for (int col = 0; col < row_data.size(); col++) {
                const Pixel &pix = row_data[col];
                
                //be sure that you use BGR
                file.put((BYTE)(pix.blue));
                file.put((BYTE)(pix.green));
                file.put((BYTE)(pix.red));
            }

            // Rows are padded so that they're always a multiple of 4 bytes. Skip the padding.
            for (int i = 0; i < row_data.size() % 4; i++) {
                file.put(0);
            }
        }

        file.close();
    }
}

/**
 * \brief confirms that the opened image is a legit (not faulty) bmp
 * \return {@code true} if the image is valid, {@code false} otherwise. 
 */
bool BMP::isImage()
{
    const int height = pixels.size();

    //can't have an image with no height (or a row with no pixels)
    if (height == 0 || pixels[0].size() == 0) {
        return false;
    }

    const int width = pixels[0].size();

    for (int row = 0; row < height; row++) {
        
        //check that the width is correct (same as expected)
        if (pixels[row].size() != width) {
            return false;
        }
        
        //now lets check that our RGB values are correct (that they fall between [0, 255])
        for (int column = 0; column < width; column++) {
            
            Pixel current = pixels[row][column];

            if (current.red > MAX_RGB || current.red < MIN_RGB ||
                current.green > MAX_RGB || current.green < MIN_RGB ||
                current.blue > MAX_RGB || current.blue < MIN_RGB)
                return false;
        }
    }

    return true;
}

/**
 * \brief returns the pixel data (i.e. for modification / filtering)
 * \return 2D array of pixels
 */
PixelMatrix BMP::toPixelMatrix() {
    
    if (isImage()) {
        return pixels;
    }
    else {
        return PixelMatrix();
    }
}

/**
 * \brief replaces the pixel data (i.e. after modification or filtering)
 * \return nothing
 */
void BMP::fromPixelMatrix(const PixelMatrix &values) {
    pixels = values;
}