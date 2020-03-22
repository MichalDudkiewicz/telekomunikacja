#include "coder.h"
#include "message.h"
#include "receiver.h"
#include <iostream>
#include "decoder.h"
#include <vector>
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
    auto kodzik = coder.code();
    kodzik[0][6] = !kodzik[0][6];
    kodzik[0][7] = !kodzik[0][7];
    Receiver receiver(kodzik);
    std::cout << endl << receiver.checkCorrectness();
    std::cout<<endl<<receiver.getCode();
    receiver.fixErrors();
    std::cout<<endl<<receiver.getCode();
    Decoder decoder(receiver.getCodedMessage());
    std::cout << endl << decoder.getCode();
    std::cout<< endl<< decoder.decode();
    return 0;
}