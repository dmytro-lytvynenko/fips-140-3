#pragma once

#include <iostream>
#include <bitset>
#include <random>
#include <vector>

class Fips140 {
public:

    Fips140() = default;

    bool test(const std::vector<uint8_t> &sequence) const;

private:

    static constexpr size_t BIT_SIZE {20000};
    static constexpr size_t BYTE_SIZE {BIT_SIZE / 8};

    static constexpr size_t MONOBIT_LOWER_THRESHOLD {9654};
    static constexpr size_t MONOBIT_UPPER_THRESHOLD {10346};

    static constexpr size_t TWO_BIT_LOWER_THRESHOLD {4800};
    static constexpr size_t TWO_BIT_UPPER_THRESHOLD {5200};

    static constexpr double POKER_LOWER_THRESHOLD {1.03};
    static constexpr double POKER_UPPER_THRESHOLD {57.4};

    static constexpr size_t RUNS_REJECTION_THRESHOLD {37};

    static constexpr size_t RUNS_LOWER_THRESHOLDS[6] = {2267, 1079, 502, 223, 90, 90};
    static constexpr size_t RUNS_UPPER_THRESHOLDS[6] = {2733, 1421, 748, 402, 223, 223};

    bool monobitTest(const std::vector<uint8_t> &sequence) const;
    bool pokerTest(const std::vector<uint8_t> &sequence) const;
    bool runsTest(const std::vector<uint8_t> &sequence) const;
    bool maxRunsTest(const std::vector<uint8_t> &sequence) const;
};