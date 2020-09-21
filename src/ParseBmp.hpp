#pragma once
#include "Matrix.hpp"
#include <string>
namespace Bmp{
    /**
     * @brief the parse bmp class can parse bmp file.
     * it can rotate image and move it to a grayscale.
     * 
     */
    class ParseBmp
    {
    private:
        int32_t m_bitmapWidth;
        int32_t m_bitmapHeight;
        int32_t m_ofsetOfBitMap;
        uint16_t m_numOfColors;
        char m_NumOfBitisInpixel;
        const std::string  m_imagePath;
        const std::string m_outputPath;
        /**
         * @brief copy the dib header to the new image and swap the height and the width.
         * 
         */
        void copyDibForRotate();
        /**
         * @brief parse the file and save the important
         *  things from the header and the dib header.
         * 
         */
        void parseFile();
        /**
         * @brief make a bmp file with 8 bits per pixel to gray.
         * 
         */
        void Make8bitGray();
                /**
         * @brief make a bmp file with 24 bits per pixel to gray.
         * 
         */
        void make24Gray();
        /**
         * @brief copy the header of the bmp file to the new image.
         * 
         */
        void copyHeader();
        /**
         * @brief copy the dib header of the bmp file to the new image.
         * 
         */
        void copyDibHeader();
        /**
         * @brief rotate the image when there are 24 bits in a pizel.
         * 
         */
        void rotate24PixelImage();
        /**
         * @brief rotate the image when there are 8 bits in a pizel.
         * 
         */
        void rotate8PixelImage();
        /**
         * @brief copy the color pallete from the image to the output path
         * 
         */
        void copyColorPallete();
        matrix::Matrix& fromPixelsArrayToMatrix8bitCase();
        matrix::Matrix& fromPixelsArrayToMatrix24bitCase();
        void fromMatrixToPixelArray8bitCase(matrix::Matrix& matrix);
        void fromMatrixToPixelArray24bitCase(matrix::Matrix& matrix);
        /**
         * @brief get an array of bytes that represent a pixel and make it gray.
         * 
         * @param pixel a pixel in the image.
         * @param size the size of the pixel.
         */
        static void grayPixel(char* pixel, int size);
        static std::string readFileContent(const std::string& filePath);
    public:
        /**
         * @brief Construct a new Parse Bmp object
         * 
         * @param imagePath the path of the image
         * @param outputPath the path of the new image
         */
        ParseBmp(const std::string& imagePath, const std::string& outputPath);
        /**
         * @brief rotate the image from the path of the image
         * and put it in the path of the new image
         * 
         */
        void rotateImage();
        /**
         * @brief convert the image  from the path of the image to gray
         * and put it in the path of the new image
         * 
         */
        void convertToGray();
    };
        
}