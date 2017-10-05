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
#include "DataCoder.h"


class CoderFactory
{
public:
    CoderFactory();
    virtual ~CoderFactory();

public:
    static CodeItem** CreateItems(int count, int type);
    static DataCoder* CreateCoder(int type);
    static CodeTable* CreateTable(int type);
};

