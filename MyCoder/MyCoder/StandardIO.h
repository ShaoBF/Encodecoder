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
#include "DataIO.h"
class StandardIO :
    public DataIO
{
public:
    StandardIO();
    virtual ~StandardIO();
    char* InputTextData(char* src);
    CodedData* InputCodedData(char* src);
    void OutputTextData(char* data, char* dest);
    void OutputCodedData(CodedData* data, char* dest);
};

