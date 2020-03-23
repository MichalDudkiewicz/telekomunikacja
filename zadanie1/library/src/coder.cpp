#include "coder.h"
#include "matrixH.h"
#include <bitset>
#include <sstream>

Coder::Coder(Message message)
    : message(std::move(message))
{
}

std::vector<bool> getParityBits(const std::bitset<8>& byteOfMessage)
{
    std::vector<bool> parityBits;
    parityBits.reserve(8);
    for (const auto& h : H) {
        bool c = false;
        for (int bitPosition = 0; bitPosition < 8; ++bitPosition) {
            c = c ^ (h[bitPosition] & byteOfMessage[bitPosition]);
        }
        parityBits.emplace_back(c);
    }
    return parityBits;
}

std::vector<bool> codeOneByte(const std::bitset<8>& byteOfMessage)
{
    std::vector<bool> coded;
    coded.reserve(16);
    for (int bitPosition = 0; bitPosition < 8; ++bitPosition) {
        coded.push_back(byteOfMessage[bitPosition]);
    }
    auto parityBits = getParityBits(byteOfMessage);
    coded.insert(coded.end(), parityBits.begin(), parityBits.end());
    return coded;
}

std::vector<std::vector<bool>> Coder::code() const
{
    std::vector<std::vector<bool>> coded;
    coded.reserve(message.getMessage().size());
    for (const auto& byte : message.toBinary()) {
        coded.push_back(codeOneByte(byte));
    }
    return coded;
}

std::string Coder::getCodedMessage() const
{
    auto codedMessage = code();
    std::ostringstream out;
    for (const auto& twoBytes : codedMessage) {
        for (const auto& bit : twoBytes) {
            out << bit;
        }
        out << " ";
    }
    return out.str();
}
