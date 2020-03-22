#include "message.h"
#include <bitset>
#include <sstream>

Message::Message(std::string message) : message(std::move(message)){}

const std::string &Message::getMessage() const { return message; }

std::vector<std::bitset<8>> Message::toBinary() const {
  std::vector<std::bitset<8>> binaryMessage;
  binaryMessage.reserve(message.size());
  for (auto const &letter : message) {
    binaryMessage.emplace_back(std::bitset<8>{letter});
  }
  return binaryMessage;
}
std::string Message::binaryToString() const {
  std::ostringstream out;
  for (auto const &letter : toBinary())
  {
    out << letter.to_string() << " ";
  }
  return out.str();
}
