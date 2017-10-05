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

#include "stdafx.h"
#include "HuffmanTable.h"
#include "HuffmanItem.h"


HuffmanTable::HuffmanTable()
{
}


HuffmanTable::~HuffmanTable()
{
}

CodeItem* HuffmanTable::CreateItem(char ch){
    return new HuffmanItem(ch, 1, -1, -1);
}