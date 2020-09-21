#include "ParseBmp.hpp"
#include<string>
#include <iostream>
#include <fstream>
#include<byteswap.h>
#include<cmath>
#include <vector>


Bmp::ParseBmp::ParseBmp(const std::string& imagePath, const std::string& outputPath) : 
    m_imagePath(imagePath), m_outputPath(outputPath){
    parseFile();
}
void Bmp :: ParseBmp :: copyHeader() {
    try{
    std::ifstream imageFile;
    imageFile.open(m_imagePath, std::ios::in | std::ios::binary);
    char readingArray[14];
    imageFile.read(readingArray, 14);
    imageFile.close();
    std :: ofstream outputFile;
    outputFile.open(m_outputPath, std::ios::out | std::ios::binary |std::ios::trunc);
    outputFile.write(readingArray, 14);
    outputFile.close();
    }
    catch (...) {
        std:: cout <<"something went wrong";
    }
}

void Bmp :: ParseBmp :: copyDibHeader() {
    try {
    std::ifstream imageFile;
    imageFile.open(m_imagePath, std::ios::in |  std::ios::binary);
    imageFile.seekg(14, std::ios::beg);
    char readingArray[40];
    imageFile.read(readingArray, 40);
    imageFile.close();
    std :: ofstream outputFile;
    outputFile.open(m_outputPath, std::ios::out | std::ios::app | std::ios::binary);
    outputFile.write(readingArray, 40);
    outputFile.close();
    }
    catch(...) {
        std:: cout <<"something went wrong";
    }
}


void Bmp::ParseBmp::copyColorPallete(){
    if(m_NumOfBitisInpixel != 8){
        //error here
    }
    std::ifstream imageFile;
    imageFile.open(m_imagePath, std::ios::in |  std::ios::binary);
    imageFile.seekg(54, std::ios::beg);
    char* readingArray = (char*) malloc(sizeof(char) * 4 * m_numOfColors);
    if(readingArray == nullptr){
        //error
    }
    imageFile.read(readingArray, 4 * m_numOfColors);
    imageFile.close();
        std :: ofstream outputFile;
    outputFile.open(m_outputPath, std::ios::out | std::ios::app | std::ios::binary);
    outputFile.write(readingArray, 4 * m_numOfColors);
    outputFile.close();
    free(readingArray);
    
}

void Bmp::ParseBmp::make24Gray() {
    int size;
    if((m_bitmapWidth * 3) % 4 == 0) {
        size = 3;
    }
    else {
        size = 4;
    }
    char* readingArray = (char*)malloc(size*sizeof(char));
    if( readingArray==NULL){
        //error
    }
    std::ifstream imageFile;
    imageFile.open(m_imagePath, std::ios::in | std::ios::app | std::ios::binary);
    imageFile.seekg(54, std::ios::beg);
    std::ofstream outputfile;
    outputfile.open(m_outputPath, std::ios::binary | std::ios::app);
    outputfile.seekp(54, std::ios::beg);
    for( int i = 0; i < m_bitmapWidth * m_bitmapHeight; ++i ) {
        imageFile.read(readingArray, size);
        grayPixel(readingArray, size);
        outputfile.write(readingArray, size);
    }
    imageFile.close();
    outputfile.close();
    free(readingArray);
}

void Bmp::ParseBmp::Make8bitGray(){
    try {
        //if(m_NumOfBytes != 8){
            //error her
        //}
        std::ofstream ofile;
        ofile.open(m_outputPath, std::ios::binary | std::ios::app);
        std::ifstream ifile;
        ifile.open(m_imagePath, std::ios::binary);
        ofile.seekp(54, std::ios::beg);
        ifile.seekg(54, std::ios::beg);
        char readingArray[4];
        for (int i = 0; i < m_numOfColors; ++i)
        {
            ifile.read(readingArray, 4);
            grayPixel(readingArray, 4);
            ofile.write(readingArray, 4);
        }

        std::streampos curr, end;
        curr = ifile.tellg();
        ifile.seekg(0, std::ios::end);
        end = ifile.tellg();
        int sizeOfRest = end - curr;
        char* restOfFile = (char*) malloc(sizeof(char) * sizeOfRest);
        if( restOfFile == NULL){
        //error
        }
        ifile.seekg(curr, std::ios::beg);
        ifile.read(restOfFile, sizeOfRest);
        ofile.write(restOfFile, sizeOfRest);
        ifile.close();
        ofile.close();
        free(restOfFile);
    }
    catch (...) {
        std::cout << "something went wrong";
    }
}
void Bmp::ParseBmp::convertToGray(){
    copyHeader();
    copyDibHeader();
    if (m_NumOfBitisInpixel == 8){
        Make8bitGray();
    }
    else if (m_NumOfBitisInpixel == 24)
    {
        make24Gray();
    }
    //trow    
}

void Bmp :: ParseBmp :: grayPixel(char* pixel, int size) {
    char grayFormulaResult = std::round(0.212 * static_cast<uint8_t>(pixel[0]) + 0.7152 * static_cast<uint8_t>(pixel[1]) + 0.0722 * static_cast<uint8_t>(pixel[2]));
    for(int i = 0; i < size; ++i) {
        pixel[i] = grayFormulaResult;
    }
}
/**
 * @brief Read the content of a file at path filePath.
 *
 * @param filePath The relative or absolute path to the file.
 * @return std::string File's content
 */
std::string  Bmp :: ParseBmp :: readFileContent(const std::string& filePath) {
  // Opens input-only file (ifstream) in binary mode.
  std::ifstream in(filePath, std::ios::binary);

  // The file is in a bad state. The error can be retrieved
  //	using the global `errno` in linux (#include <cerrno>).
  if (!in) {
    // Error here...
  }

  // Read the file to a vector. This is not the most effecient
  //	method to read a file.
  auto content = std::string{std::istreambuf_iterator<char>{in},
                             std::istreambuf_iterator<char>{}};

  // After reading the file, it should meet EOF (end of file). If
  //  it did not, it means that an error occurred.
  if (!in.eof()) {
    // Unlikly to happen error here...
  }

  return content;
}
void Bmp::ParseBmp::parseFile(){
    std::string result = Bmp::ParseBmp::readFileContent(m_imagePath);
    if (result[0] != 'B' || result[1] != 'M') {
        std::cout << "the file isn't a bmp file";
    }
    std::ifstream ifile;
    ifile.open(m_imagePath, std::ios::binary);
    char tmp[4];
    ifile.seekg(10, std::ios::beg);
    ifile.read(tmp, 4);
    int* ptr = (int*)tmp;
    m_ofsetOfBitMap = *ptr;
    ifile.seekg(28, std::ios::beg);
    char mem[2];
    ifile.read(mem, 2);
    m_NumOfBitisInpixel = mem[0];
    int32_t* byteWidth = (int32_t*) (result.substr(18, 4).data());
    m_bitmapWidth = *byteWidth;
    int32_t* byteHight = (int32_t*)result.substr(22, 4).data();
    m_bitmapHeight = *byteHight;
    uint16_t* byteNumOfColor = (uint16_t*)result.substr(46, 4).data();
    m_numOfColors = *byteNumOfColor;
    if (m_numOfColors == 0) {
        m_numOfColors = 256;
    }
}
void Bmp::ParseBmp::copyDibForRotate(){
    try {
    std::ifstream imageFile;
    imageFile.open(m_imagePath, std::ios::in | std::ios::app | std::ios::binary);
    imageFile.seekg(14, std::ios::beg);
    char readingArray[40];
    imageFile.read(readingArray, 40);
    char tmp;
    for (uint32_t i = 0; i < 4; ++i)
    {
        tmp = readingArray[8 + i];
        readingArray[8 + i] = readingArray[4 + i];
        readingArray[4 + i] = tmp;
    }
    imageFile.close();
    std :: ofstream outputFile;
    outputFile.open(m_outputPath, std::ios::out | std::ios::app | std::ios::binary);
    outputFile.write(readingArray, 40);
    outputFile.close();
    }
    catch(...) {
        std:: cout <<"something went wrong";
    }
}
void Bmp::ParseBmp::rotateImage() {
    copyHeader();
    copyDibForRotate();
    if (m_NumOfBitisInpixel == 8) {
       rotate8PixelImage();
    }
    else {
         rotate24PixelImage();
    }
}
void Bmp::ParseBmp::rotate24PixelImage() {
    matrix::Matrix bitmapMatrix(std::move(fromPixelsArrayToMatrix24bitCase()));
    matrix::Matrix newBitmapMatrix(std::move(bitmapMatrix.rotateMatrix()));
    fromMatrixToPixelArray24bitCase(newBitmapMatrix);
 }

void Bmp::ParseBmp::rotate8PixelImage() {
    copyColorPallete();
    matrix::Matrix bitmapMatrix(std::move(fromPixelsArrayToMatrix8bitCase()));
    matrix::Matrix newBitmapMatrix(std::move(bitmapMatrix.rotateMatrix()));
    fromMatrixToPixelArray8bitCase(newBitmapMatrix);
 }

matrix::Matrix& Bmp::ParseBmp::fromPixelsArrayToMatrix8bitCase() {
    std::ifstream imageFile;
    imageFile.open(m_imagePath, std::ios::in | std::ios::app | std::ios::binary);
    imageFile.seekg(54 + m_numOfColors * 4, std::ios::beg);
    matrix::Matrix* matrix = new matrix::Matrix(m_bitmapHeight, m_bitmapWidth);
    int size;
    if((3 * m_bitmapWidth) % 4 ==0 ) {
        size = 3;
    }
    else {
        size = 4;
    }
    for (int i = 0; i < m_bitmapHeight; i++) {
        for (int j = 0; j < m_bitmapWidth; j++) {
            char* pixelReader = (char*) malloc(size);
            imageFile.read(pixelReader, size);
            matrix->setValue(i, j,*pixelReader);
        }
    }
    return *matrix;
}

matrix::Matrix& Bmp::ParseBmp::fromPixelsArrayToMatrix24bitCase() {
    std::ifstream imageFile;
    imageFile.open(m_imagePath, std::ios::in | std::ios::app | std::ios::binary);
    imageFile.seekg(54, std::ios::beg);
    matrix::Matrix* matrix = new matrix::Matrix(m_bitmapHeight, m_bitmapWidth);
    int size;
    if((m_bitmapWidth) % 4 ==0 ) {
        size = 3;
    }
    else {
        size = 4;
    }
    char* pixelReader = (char*) malloc(size);
    for (int i = 0; i < m_bitmapHeight; i++) {
        for (int j = 0; j < m_bitmapWidth; j++) {
            imageFile.read(pixelReader, size);
            matrix->setValue(i, j,*pixelReader);
        }
    }
    free(pixelReader);
    return *matrix;
}

void Bmp::ParseBmp::fromMatrixToPixelArray8bitCase(matrix::Matrix& matrix){
    std :: ofstream outputFile;
    outputFile.open(m_outputPath, std::ios::out | std::ios::app | std::ios::binary);
    outputFile.seekp(54 + 4 * m_numOfColors, std::ios::beg);
    int size;
    if(matrix.getWidth() % 4 == 0) {
        size = 1;
    }
    else {
        size = 2;
    }
    double* pixelWriter;
    for (uint32_t i = 0; i < matrix.getHight(); i++) {
        for (uint32_t j = 0; j < matrix.getWidth(); j++) {
            double tmp = matrix.getValue(i, j);
            pixelWriter = &tmp;
            outputFile.write((char*)pixelWriter, size);
        }
    }
}

void Bmp::ParseBmp::fromMatrixToPixelArray24bitCase(matrix::Matrix& matrix){
    std :: ofstream outputFile;
    outputFile.open(m_outputPath, std::ios::out | std::ios::app | std::ios::binary);
    outputFile.seekp(54, std::ios::beg);
    int size;
    if((matrix.getWidth() * 3) % 4 == 0) {
        size = 3;
    }
    else {
        size = 4;
    }
    double* pixelWriter;
    for (uint32_t i = 0; i < matrix.getHight(); i++) {
        for (uint32_t j = 0; j < matrix.getWidth(); j++) {
            double tmp = matrix.getValue(i, j);
            pixelWriter = &tmp;
            outputFile.write((char*)pixelWriter, size);
        }
    }
}


















































