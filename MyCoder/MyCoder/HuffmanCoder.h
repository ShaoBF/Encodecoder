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
#include "DataCoder.h"
#include "HuffmanItem.h"
#include <string.h>

using namespace std;

class HuffmanCoder :
    public DataCoder
{
public:
    HuffmanCoder();
    virtual ~HuffmanCoder();
    CodedData* Encode(char* data);
    char* Decode(CodedData* data);
    void CreateHuffmanTree(CodeTable* table);
    void AdjustNodes(CodeTable* table, int startIndex);
    void GetCodeResult(CodedData* codedData);
    void EncodeData(char* data, CodedData *codedData);
    void Traverse(HuffmanItem** item, int index);
};

