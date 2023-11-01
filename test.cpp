#include "fips140.h"

#include <iostream>

constexpr size_t BIT_SIZE {20000};
static constexpr size_t BYTE_SIZE {BIT_SIZE / 8};

std::vector<uint8_t> generateRandomSequence() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    std::vector<uint8_t> sequence(BYTE_SIZE);
    for(auto &byte : sequence) {
        byte = static_cast<uint8_t>(distrib(gen));
    }
    return sequence;
}

int main() {
    std::vector<uint8_t> sequence = generateRandomSequence();

    Fips140 fips;
    if(fips.test(sequence)) {
        std::cout << "20,000 bits are random enough!" << std::endl;
    } else {
        std::cout << "20,000 bits are rejected!" << std::endl;
    }
    return 0;
}