#ifndef OOPPROJECT_DECODER_H
#define OOPPROJECT_DECODER_H

#include <vector>
#include <string>

class Decoder {
  std::vector<std::vector<bool>> separatedCode;
public:
  explicit Decoder(const std::vector<std::vector<bool>> &code);
  const std::vector<std::vector<bool>>& getCodedMessage() const;
  std::string getCode() const;
  std::string decode() const;
};

#endif // OOPPROJECT_DECODER_H
