// phash.h

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"

// to read images: https://stackoverflow.com/questions/2076475/reading-an-image-file-in-c-c
// NOTE: pseudocode from http://hackerfactor.com/blog/index.php%3F/archives/432-Looks-Like-It.html


uint8_t* reduce_size(uint8_t* rgb_image);

uint8_t* grayscale(uint8_t* small_rgb_image);

uint8_t* DCT_computation(uint8_t* grayscale_image*);

uint8_t* reduce_DCT(uint8_t* DCT_image);

uint8_t* average_value(uint8_t* reduced_DCT);

uint8_t* discretize(uint8_t* averaged_DCT);

string construct_hash(uint8_t* discretized_DCT);

string generate_phash(uint8_t* input);