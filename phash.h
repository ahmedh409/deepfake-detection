// phash.h

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"

// to read images: https://stackoverflow.com/questions/2076475/reading-an-image-file-in-c-c
// NOTE: pseudocode from http://hackerfactor.com/blog/index.php%3F/archives/432-Looks-Like-It.html

uint8_t* read_image(std::string file_name);

uint8_t* reduce_size(uint8_t* rgb_image);

uint8_t* grayscale(uint8_t* small_rgb_image);

uint8_t* DCT_computation(uint8_t* grayscale_image);

std::vector<int> reduce_DCT(uint8_t* DCT_image);

std::vector<int> discretize(std::vector<int> reduced_DCT);

std::string construct_hash(std::vector<int> discretized_DCT_bits);

std::string generate_phash(std::string file_name);