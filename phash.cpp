// phash.cpp

#include "phash.h"
#include <string>
#include <vector>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


// NOTE: psuedocode from http://hackerfactor.com/blog/index.php%3F/archives/432-Looks-Like-It.html 

// global temporarily
int width, height, bpp;

// reads the image from the file system in RGB format
uint8_t* read_image(std::string file_name) {
    uint8_t* full_image = stbi_load(file_name.c_str(), &width, &height, &bpp, 3);
    return full_image;
}

// reduce image dimensions to something specified
uint8_t* reduce_size(uint8_t* rgb_image) {
    uint8_t* small_rgb_image = (uint8_t *) malloc(8 * 8 * 3);
    stbir_resize_uint8(rgb_image, width, height, 0,
                        small_rgb_image, 8, 8, 0, 3);
    
    stbi_write_png("./temp/out.png", 8, 8, 3, small_rgb_image, 8*3);
    return small_rgb_image;
}

// transform smaller image from RGB to grayscale
uint8_t* grayscale(uint8_t* small_rgb_image) {
    int w, h, b;
    uint8_t* grayscale_image = stbi_load("./temp/out.png",
                                    &w, &h, &b, 1);

    stbi_write_png("./temp/out2.png", w, h, 1, grayscale_image, w);
    return grayscale_image;
}

// currently not in use - 2/22/22
uint8_t* DCT_computation(uint8_t* grayscale_image) {
    // perform Discrete Cosine Transform (DCT) on grayscale image
    uint8_t* DCT_image;
    return DCT_image;
}

// currently not in use - 2/22/22
std::vector<int> reduce_DCT(uint8_t* DCT_image) {
    // The DCT is 32x32, just keep the top-left 8x8 - those represent the lowest frequencies in the picture
    // return this 8x8 image as a vector<int> length 64 (attach each "row" of integer values on the end of the prev row)
    std::vector<int> reduced_DCT;
    return reduced_DCT;
}

// currently not in use - 2/22/22
std::vector<int> discretize(std::vector<int> reduced_DCT) {
    // compute the mean DCT value of reduced_DCT, but excluding the first term (which would throw off the average)
    // set the 64 hash bits from reduced_DCT to a 0 or a 1 based on the calculated threshold average value
    std::vector<int> discretized_DCT_bits;
    return discretized_DCT_bits;
}

// input is vector<int> (length 64) of 0s and 1s
// take each set of 4 and convert into hexadecimal
// concatenate each hex value (should have 16) and return as a string
std::string construct_hash(std::vector<int> bits) {
    std::string hash = "";

    for (int i = 0; i < 64; i+=4) {
        int hex_digit = (8 * bits[i]) + (4 * bits[i+1]) + (2 * bits[i+2]) + bits[i+3];
        if (hex_digit < 10) {
            hash += std::to_string(hex_digit);
        } else {
            hash += ('a' + hex_digit - 10);
        }
    }

    std::cout << "DONE" << std::endl;
    return hash;
}

// main helper function - input image file name, output hash
std::string generate_phash(std::string file_name) {
    // DCT and discretization not used

    std::cout << "Starting hash...";

    uint8_t* full_image = read_image(file_name);
    uint8_t* small_rgb_image = reduce_size(full_image);
    uint8_t* grayscale_image = grayscale(small_rgb_image);

    std::cout << "matrix to vector...";
    // convert to vector
    std::vector<int> pixels_gray;
    int sum = 0;
    for (int i = 0; i < 64; i++) {
        pixels_gray.push_back(grayscale_image[i]);
        sum += grayscale_image[i];
    }

    std::cout << "discretizing...";
    int average = sum / 64;
    // if pixel value above threshold (average), then 1, else 0
    std::vector<int> bits;
    for (int i = 0; i < 64; i++) {
        bits.push_back(pixels_gray[i] > average);
    }
    
    /*
    use later (not currently implemented)
    uint8_t* grayscale_image = grayscale(reduce_size(rgb_image));
    std::vector<int> reduced_DCT = reduce_DCT(DCT_computation(grayscale_image));
    std::vector<int> discretized_DCT_bits = discretize(reduced_DCT);
    */

    std::cout << "hex conversion...";
    return construct_hash(bits);;
}

// testing
/*
int main() {
    std::cout << "Enter a file name: ";
    std::string file_name;
    std::cin >> file_name;
    std::cout << file_name << std::endl;

    std::cout << generate_phash(file_name) << std::endl;
}
*/