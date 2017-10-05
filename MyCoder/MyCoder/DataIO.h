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

class DataIO
{
public:
    DataIO();
    virtual ~DataIO();
    virtual char* InputTextData(char* src) = 0;
    virtual CodedData* InputCodedData(char* src) = 0;
    virtual void OutputTextData(char* data, char* dest) = 0;
    virtual void OutputCodedData(CodedData* data, char* dest) = 0;
};

