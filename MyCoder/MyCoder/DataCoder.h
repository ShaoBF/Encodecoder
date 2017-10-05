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
#include "CodedData.h"

using namespace std;

class DataCoder
{
public:
    DataCoder();
    virtual ~DataCoder();

public:
    virtual CodedData* Encode(char* data) = 0;
    virtual char* Decode(CodedData* data) = 0;
};

