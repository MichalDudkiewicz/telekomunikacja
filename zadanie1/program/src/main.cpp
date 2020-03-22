#include "coder.h"
#include "message.h"
#include "receiver.h"
#include <iostream>
#include "decoder.h"
#include <vector>
#include <boost/lexical_cast.hpp>
#include <fstream>

using namespace std;

int main() {
    ifstream myfile;
    string messageFromFile;
    myfile.open("../../dataset/wiadomosc.txt");
    if (myfile.is_open())
    {
      getline (myfile,messageFromFile);
      myfile.close();
    }
    Message message(messageFromFile);
    Coder coder(message);
    std::cout<<coder.getCodedMessage();
    std::ofstream outfile ("../../dataset/kod.txt");
    for(const auto &word : coder.code())
    {
      for(const auto &bit : word)
      {
        outfile << bit;
      }
      outfile << endl;
    }
    outfile.close();
    std::ifstream infile ("../../dataset/kod.txt");
    string word;
    std::vector<std::vector<bool>> codeFromFile;
    codeFromFile.reserve(coder.code().size());
    while(!infile.eof())
    {
      getline(infile,word);
      if(word.length() > 0)
      {
        codeFromFile.emplace_back();
        std::bitset<16> bits(word);
        for(int i = 15; i >= 0; --i)
        {
          codeFromFile.back().push_back(bits[i]);
        }
      }
    }
    infile.close();

    Receiver receiver(codeFromFile);
    std::cout << endl << receiver.checkCorrectness();
    std::cout<<endl<<receiver.getCode();
    receiver.fixErrors();
    std::cout<<endl<<receiver.getCode();
    Decoder decoder(receiver.getCodedMessage());
    std::cout << endl << decoder.getCode();
    std::cout<< endl<< decoder.decode();
    return 0;
}