/*******************************************************************************
// Copyright 2017-2022 Shao BoFeng
// Module:  MyCoder
// Created: 2017/10/05
// Author:  Shao BoFeng (1048747682@qq.com)
//
// Discription:	This is an Implimentation of a Huffman Encoder/Decoder in C++
//
// Keeping this Copyright statement, you can use this source freely.
//
*******************************************************************************/

#include "CodeItem.h"
#include <string.h>
#include <math.h>

CodeItem::CodeItem()
{
    ch = '\0';
    code = nullptr;
    count = 0;
    bytes = nullptr;
    bitLength = 0;
}

CodeItem::CodeItem(char c, int repeat)
{
    ch = c;
    count = repeat;
    bytes = nullptr;
    bitLength = 0;
}


CodeItem::~CodeItem()
{
    if (code != nullptr)
        delete code;
    if (bytes != nullptr)
        delete bytes;
}

void CodeItem::SetBytes(unsigned char* byte, int bitLen){
    bytes = byte;
    bitLength = bitLen;
}

void CodeItem::AddBit(unsigned char bit){

}

void CodeItem::SetCodeStr(char* codeIn, int codelen, char bit){
    code = new char[codelen + 2];
    strcpy(code, codeIn);
    code[codelen] = bit;
    code[codelen + 1] = '\0';
}

void CodeItem::SetCodeBits(unsigned char* codeBits, int bitLength, unsigned char bit){
    int originByteLen = (bitLength + 7) / 8;
    bitLength++;
    //为node的bytes申请bitLength/8（向上取整）长度的空间。
    int bytelen = (int)ceil((double)bitLength / 8.0);
    bytes = new unsigned char[bytelen];
    //按字节复制codeBits到node的bytes中
    for (int i = 0; i < originByteLen; i++){
        bytes[i] = codeBits[i];
    }
    if (bytelen > originByteLen){
        bytes[bytelen - 1] = 0;
    }
    //将node的bytes最后设置一位bit。
    int bitToMove = 8 - bitLength % 8;
    if (bitToMove == 8){
        bitToMove = 0;
    }
    bytes[bytelen - 1] |= bit << bitToMove;
    this->bitLength = bitLength;
}
void CodeItem::Save(ofstream &fout){
/*    char ch;
    char* code;
    unsigned char* bytes;
    int bitLength;
    int count;*/

    fout.write(&ch, sizeof(char));
    fout.write((char*)&bitLength, sizeof(int));
    fout.write((char*)bytes, (bitLength + 7) / 8);
    fout.write((char*)&count, sizeof(int));
}
void CodeItem::Load(ifstream &fin){
    fin.read(&ch, sizeof(char));
    fin.read((char*)&bitLength, sizeof(int));
    if (bitLength > 0){
        int bytelen = (bitLength + 7) / 8;
        bytes = new unsigned char[bytelen];
        fin.read((char*)bytes, bytelen);
    }
    fin.read((char*)&count, sizeof(int));
    code = new char[bitLength + 1];
    for (int i = 0; i < bitLength; i++){
        int curbit = i % 8;
        int curbyte = i / 8;
        int bit = (bytes[curbyte] >> (7 - curbit)) & 1;
        code[i] = bit + '0';
    }
    code[bitLength] = '\0';
}