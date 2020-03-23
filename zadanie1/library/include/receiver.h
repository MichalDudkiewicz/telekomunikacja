#ifndef OOPPROJECT_RECEIVER_H
#define OOPPROJECT_RECEIVER_H

#include <string>
#include <vector>

class Receiver {
    std::vector<std::vector<bool>> code;

public:
    explicit Receiver(std::vector<std::vector<bool>> code);
    bool checkCorrectness() const;
    std::vector<int> findErrorInWord(int wordNumber) const;
    void fixErrors();
    std::string getCode() const;
    const std::vector<std::vector<bool>>& getCodedMessage() const;
};

#endif // OOPPROJECT_RECEIVER_H
