#include <iostream>
using namespace std;
#include "cypher.h"

int main(){
    string plain = "1234567890/*-+;jkladsfhjklaeuk[];'/,\\=-```/.,,;.";
    string key  = " 123456";
    string encode = encode_string(plain, key);
    cout << "encode: " << encode << endl;
    string decode = decode_string(encode, key);
    cout << "decode: " << decode << endl;
	// decode == plain
    return 0;
}
