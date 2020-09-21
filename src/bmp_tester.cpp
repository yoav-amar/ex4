#include "bmp_tester.hpp"
#include "ParseBmp.hpp"
void testing::bmp::rotate_image(const std::string& imagePath, const std::string& outputPath){
    Bmp::ParseBmp parser(imagePath, outputPath);
    parser.rotateImage();
}

void testing::bmp::convert_to_grayscale(const std::string& imagePath,
                        const std::string& outputPath){
                            Bmp::ParseBmp parser(imagePath, outputPath);
                            parser.convertToGray();
                        }