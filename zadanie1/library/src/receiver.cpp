#include "receiver.h"
#include <algorithm>
#include <sstream>
#include <utility>

static const bool H[8][16] = {
    { 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }
};

bool checkWordCorrectness(std::vector<bool> word)
{
    bool temp;
    for (int i = 0; i < 8; ++i) {
        temp = word[i + 8];
        for (int j = 0; j < 8; ++j) {
            temp = temp ^ (word[j] & H[i][j]);
        }
        if (temp == 1)
            return false;
    }
    return true;
}

std::vector<bool> getErrorVector(std::vector<bool> word)
{
    std::vector<bool> error;
    error.reserve(8);
    int j = 8;
    for (auto const& h : H) {
        bool result = false;
        for (int i = 0; i < 8; ++i) {
            result = result ^ (h[i] & word[i]);
        }
        result = result ^ word[j];
        error.push_back(result);
        ++j;
    }
    return error;
}

std::vector<int> findError(std::vector<bool> word)
{
    auto errorVector = getErrorVector(std::move(word));
    std::vector<int> errorIndexes;
    errorIndexes.reserve(2);
    std::vector<bool> H_col;
    H_col.reserve(8);
    for (int column = 0; column < 16; ++column) {
        for (const auto& row : H) {
            H_col.push_back(row[column]);
        }
        if (std::equal(errorVector.begin(), errorVector.end(), H_col.begin())) {
            errorIndexes.push_back(column);
            return errorIndexes;
        }
        H_col.clear();
    }

    bool H_transposed[16][8];
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 16; ++j)
            H_transposed[j][i] = H[i][j];

    bool result[8];
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (i != j) {
                std::fill_n(result, 8, false);
                for (int k = 0; k < 8; ++k) {
                    result[k] = H_transposed[i][k] ^ H_transposed[j][k];
                }
                int n = sizeof(result) / sizeof(result[0]);
                std::vector<bool> resultVector(result, result + n);
                if (std::equal(errorVector.begin(), errorVector.end(), resultVector.begin())) {
                    errorIndexes.push_back(i);
                    errorIndexes.push_back(j);
                    return errorIndexes;
                }
                resultVector.clear();
            }
        }
    }
    return errorIndexes;
}

std::vector<int> Receiver::findErrorInWord(int wordNumber) const
{
    return findError(code[wordNumber]);
}

Receiver::Receiver(std::vector<std::vector<bool>> code)
    : code(std::move(code))
{
}

bool Receiver::checkCorrectness() const
{
    for (const auto& word : code) {
        if (!checkWordCorrectness(word))
            return false;
    }
    return true;
}

void Receiver::fixErrors()
{
    for (int i = 0; i < code.size(); ++i) {
        if (!checkWordCorrectness(code[i]))
            for (const auto& position : findErrorInWord(i))
                code[i][position] = !code[i][position];
    }
}

std::string Receiver::getCode() const
{
    std::ostringstream out;
    for (const auto& twoBytes : code) {
        for (const auto& bit : twoBytes) {
            out << bit;
        }
        out << " ";
    }
    return out.str();
}
const std::vector<std::vector<bool>>& Receiver::getCodedMessage() const
{
    return code;
}
