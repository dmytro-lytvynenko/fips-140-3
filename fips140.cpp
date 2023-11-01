#include "fips140.h"

bool Fips140::monobitTest(const std::vector<uint8_t> &sequence) const {
    size_t count1 = 0;
    for(auto &byte : sequence) {
        count1 += std::bitset<8>(byte).count();
    }
    return count1 >= MONOBIT_LOWER_THRESHOLD && count1 <= MONOBIT_UPPER_THRESHOLD;
}

bool Fips140::pokerTest(const std::vector<uint8_t> &sequence) const {
    size_t counts[16] = {0};
    for(size_t i = 0; i < BYTE_SIZE; i++) {
        uint8_t byte = sequence[i];
        counts[byte & 15]++;
        counts[(byte >> 4) & 15]++;
    }
    double x = 0;
    for(int i = 0; i < 16; i++) {
        x += counts[i] * counts[i];
    }
    x = (16.0/5000.0) * x - 5000;
    return x > POKER_LOWER_THRESHOLD && x < POKER_UPPER_THRESHOLD;
}

bool Fips140::runsTest(const std::vector<uint8_t> &sequence) const {
    size_t runsFor0[6] = {0};
    size_t runsFor1[6] = {0};

    size_t currentRunLength = 0;
    uint8_t currentBit = sequence[0] & 1;

    for(size_t i = 0; i < sequence.size(); i++) {
        uint8_t byte = sequence[i];
        for(int j = 0; j < 8; j++) {
            uint8_t bit = (byte >> j) & 1;
            if(bit == currentBit) {
                currentRunLength++;
            } else {
                if (currentRunLength <= 6) {
                    if (currentBit == 0) {
                        runsFor0[currentRunLength-1]++;
                    } else {
                        runsFor1[currentRunLength-1]++;
                    }
                } else {
                    if (currentBit == 0) {
                        runsFor0[5]++;
                    } else {
                        runsFor1[5]++;
                    }
                }
                currentBit = bit;
                currentRunLength = 1;
            }
        }
    }

    if (currentRunLength <= 6) {
        if (currentBit == 0) {
            runsFor0[currentRunLength-1]++;
        } else {
            runsFor1[currentRunLength-1]++;
        }
    } else {
        if (currentBit == 0) {
            runsFor0[5]++;
        } else {
            runsFor1[5]++;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (runsFor0[i] < RUNS_LOWER_THRESHOLDS[i] || runsFor0[i] > RUNS_UPPER_THRESHOLDS[i]) {
            return false;
        }
        if (runsFor1[i] < RUNS_LOWER_THRESHOLDS[i] || runsFor1[i] > RUNS_UPPER_THRESHOLDS[i]) {
            return false;
        }
    }

    return true;
}

bool Fips140::maxRunsTest(const std::vector<uint8_t> &sequence) const {
    size_t currentRunLength = 1;
    bool currentBit = sequence[0] & 1;
    for(size_t i = 0; i < sequence.size(); i++) {
        uint8_t byte = sequence[i];
        for(int j = 0; j < 8; j++) {
            bool bit = byte & (1 << j);
            if(bit == currentBit) {
                currentRunLength++;
                if(currentRunLength == RUNS_REJECTION_THRESHOLD) {
                    return false;
                }
            } else {
                currentBit = bit;
                currentRunLength = 1;
            }
        }
    }
    return true;
}

bool Fips140::test(const std::vector<uint8_t> &sequence) const {
    return monobitTest(sequence) && maxRunsTest(sequence) &&
        pokerTest(sequence) && runsTest(sequence);
}