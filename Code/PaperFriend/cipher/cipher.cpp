#include <QCryptographicHash>
#include "Qt-AES-1.2/qaesencryption.h"
#include <iostream>
using namespace std;

//The two functions below should be used to avoid string coding problems

// The function used to convert std string to qstring
QString str2qstr(const string& str)
{
    return QString::fromLocal8Bit(str.data());
}

// The function used to convert qstring to std string
string qstr2str(const QString& qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}


string encode_string(string input, string key){
    string vector = "initial_vector";
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString inputqstr = str2qstr(input);
    // cout << "inputqstr: " << qstr2str(inputqstr) << endl;
    QString keyqstr = str2qstr(key);
    QString iv = str2qstr(vector);


    QByteArray hashKey = QCryptographicHash::hash(keyqstr.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encodeText = encryption.encode(inputqstr.toLocal8Bit(), hashKey, hashIV);

    // cout << "encodeText: " << qstr2str(str2qstr(encodeText.toHex().data())) << endl;
    string save_encode = encodeText.toHex().data();
    return save_encode;
}

string decode_string(string input, string key){
    string vector = "initial_vector";
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString inputqstr = str2qstr(input);
    QString keyqstr = str2qstr(key);
    QString iv = str2qstr(vector);

    QByteArray hashKey = QCryptographicHash::hash(keyqstr.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray decodeText = encryption.decode(QByteArray::fromHex(inputqstr.toLocal8Bit()), hashKey, hashIV);
    QString decodedString = QString(encryption.removePadding(decodeText));

    // cout << "decodeText: " << qstr2str(str2qstr(decodeText.data())) << endl;
    string save_decode = qstr2str(decodedString);
    return save_decode;
}




