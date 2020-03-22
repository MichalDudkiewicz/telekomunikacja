#ifndef OOPPROJECT_CODER_H
#define OOPPROJECT_CODER_H

#include <string>
#include "message.h"
#include <vector>

class Coder {
  Message message;

public:
  explicit Coder(Message message);
  std::vector<std::vector<bool>> code() const;
  std::string getCodedMessage() const;
};

#endif // OOPPROJECT_CODER_H
