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
#include "CodeTable.h"
#include <fstream>

using namespace std;

enum CodeTypes{
    UNDEFINED = 0,
    HUFFMAN,
    SHANNON_FANO
};

class CodedData
{
public:
    CodedData();
    virtual ~CodedData();

public:
    unsigned char* data;
    CodeTable* table;
    int dataBitLength;
    int codeType;

public:
    void setData(unsigned char* dataA, int bitlen);
    void setTable(CodeTable* codeTable);
    unsigned char* getData();
    void CalculateChar(char* data);
    void Save(ofstream &fout);
    void Load(ifstream &fin);
    void SetCodeType(int codeType){
        this->codeType = codeType;
    }

protected:
    int WriteHeader(ofstream &fout);
    int ReadHeader(ifstream &fin);
    int WriteCodeTable(ofstream &fout);
    int WriteCodedData(ofstream &fout);
    int ReadCodeTable(ifstream &fin);
    int ReadCodedData(ifstream &fin);
};

