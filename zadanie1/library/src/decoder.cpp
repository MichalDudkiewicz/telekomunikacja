#include "decoder.h"
#include <bitset>
#include <math.h>
#include <sstream>

Decoder::Decoder(const std::vector<std::vector<bool>>& code)
{
    separatedCode.reserve(code.size());
    for (const auto& word : code) {
        separatedCode.emplace_back(std::begin(word), std::begin(word) + 8);
    }
}

const std::vector<std::vector<bool>>& Decoder::getCodedMessage() const
{
    return separatedCode;
}

std::string Decoder::getCode() const
{
    std::ostringstream out;
    for (const auto& word : separatedCode) {
        for (const auto& bit : word) {
            out << bit;
        }
    }
    return out.str();
}

std::string Decoder::decode() const
{
    std::string output;
    for (const auto& word : separatedCode) {
        int power = 0;
        int ascii = 0;
        for (const auto& bit : word) {
            if (bit != 0)
                ascii += pow(2, power);
            ++power;
        }
        char c = char(ascii);
        output += c;
    }
    return output;
}
