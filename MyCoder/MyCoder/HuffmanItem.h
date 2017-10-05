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
#include "CodeItem.h"
#include <fstream>

class HuffmanItem :
    public CodeItem
{
public:
    HuffmanItem();
//    HuffmanItem(char c, unsigned char* bits, int bitlen, int repeat);
    HuffmanItem(char c, int repeat, int l, int r);
    virtual ~HuffmanItem();

public:
    int left;
    int right;

public:
    bool IsLeaf();
    virtual void Save(ofstream &fout);
    virtual void Load(ifstream &fin);
};
