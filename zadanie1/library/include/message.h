#ifndef OOPPROJECT_MESSAGE_H
#define OOPPROJECT_MESSAGE_H

#include <string>
#include <bitset>
#include <vector>

class Message {
private:
  std::string message;

public:
  explicit Message(std::string message);
  const std::string& getMessage() const;
  std::vector<std::bitset<8>> toBinary() const;
  std::string binaryToString() const;
};

#endif // OOPPROJECT_MESSAGE_H
