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

#pragma once
#include <fstream>

using namespace std;

class CodeItem
{
public:
    CodeItem();
    CodeItem(char c, int repeat);
    virtual ~CodeItem();

public:
    char ch;
    char* code;
    unsigned char* bytes;
    int bitLength;
    int count;
public:
    void SetBytes(unsigned char* byte, int bitLen);
    void AddBit(unsigned char bit);
    void SetCodeStr(char* code, int codelen, char bit);
    void SetCodeBits(unsigned char* codeBits, int bitLength, unsigned char bit);
    virtual void Save(ofstream &fout);
    virtual void Load(ifstream &fin);
};

