#include "coder.h"
#include "message.h"
#include "receiver.h"
#include <iostream>
#include "decoder.h"
#include <vector>

using namespace std;

int main() {
    cout << "kot" << endl;
    Message message("kot");
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