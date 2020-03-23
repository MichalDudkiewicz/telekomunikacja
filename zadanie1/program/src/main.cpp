#include "coder.h"
#include "message.h"
#include "receiver.h"
#include <iostream>
#include "decoder.h"
#include <vector>
#include <fstream>

using namespace std;

int main() {
    cout << "MENU: \n"
            "1. zakoduj wiaodmosc z pliku wiadomosc.txt\n"
            "2. odkoduj wiadomosc z pliku kod.txt w konsoli\n";
    int choice;
    cin >> choice;
    if(choice == 1)
    {
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
      std::cout<<"wiadomosc: " + message.getMessage();
      std::cout<< "\nzakodowana wiadomosc: " + coder.getCodedMessage() + "\nzapisano do pliku kod.txt";
    }
    else if(choice == 2)
    {
      std::ifstream infile ("../../dataset/kod.txt");
      string word;
      std::vector<std::vector<bool>> codeFromFile;
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
      std::cout<<"\nzakodowana wiadomosc otrzymana: " + receiver.getCode();
      std::cout<<"\npoprawnosc slow kodowych: ";
      std::cout << std::boolalpha;
      std::cout << receiver.checkCorrectness();
      if(!receiver.checkCorrectness())
      {
        receiver.fixErrors();
        std::cout<<"\nwiadomosc poprawiona: "<<receiver.getCode();
      }
      Decoder decoder(receiver.getCodedMessage());
      std::cout<< "\nodkodowana wiadomosc: " + decoder.decode();
    }
    else
      return 0;
    return 0;
}