// phash.cpp

#include "phash.h"
#include <string>
#include <vector>


// NOTE: psuedocode from http://hackerfactor.com/blog/index.php%3F/archives/432-Looks-Like-It.html 


uint8_t* reduce_size(uint8_t* rgb_image) {
    // reduce image dimensions to 32x32
    uint8_t* small_rgb_image;
    return small_rgb_image;
}

uint8_t* grayscale(uint8_t* small_rgb_image) {
    // transform 32x32 image from RGB to grayscale
    uint8_t* grayscale_image;
    return grayscale_image;
}

uint8_t* DCT_computation(uint8_t* grayscale_image) {
    // perform Discrete Cosine Transform (DCT) on grayscale image
    uint8_t* DCT_image;
    return DCT_image;
}

std::vector<int> reduce_DCT(uint8_t* DCT_image) {
    // The DCT is 32x32, just keep the top-left 8x8 - those represent the lowest frequencies in the picture
    // return this 8x8 image as a vector<int> length 64 (attach each "row" of integer values on the end of the prev row)
    std::vector<int> reduced_DCT;
    return reduced_DCT;
}

std::vector<int> discretize(std::vector<int> reduced_DCT) {
    // compute the mean DCT value of reduced_DCT, but excluding the first term (which would throw off the average)
    // set the 64 hash bits from reduced_DCT to a 0 or a 1 based on the calculated threshold average value
    std::vector<int> discretized_DCT_bits;
    return discretized_DCT_bits;
}

std::string construct_hash(std::vector<int> discretized_DCT_bits) {
    // input is vector<int> (length 64) of 0s and 1s
    // take each set of 4 and convert into hexadecimal
    // concatenate each hex value (should have 16) and return as a string
    std::string hash;
    return hash;
}

std::string generate_phash(uint8_t* rgb_image) {
    // main helper function - input image, output hash
    uint8_t* grayscale_image = grayscale(reduce_size(rgb_image));
    std::vector<int> reduced_DCT = reduce_DCT(DCT_computation(grayscale_image));
    std::vector<int> discretized_DCT_bits = discretize(reduced_DCT);
    std::string hash = construct_hash(discretized_DCT_bits);
    return hash;
}