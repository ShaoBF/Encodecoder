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
#include "CoderFactory.h"
#include "HuffmanItem.h"
#include "CodedData.h"
#include "HuffmanCoder.h"
#include "HuffmanTable.h"

CoderFactory::CoderFactory()
{
}


CoderFactory::~CoderFactory()
{
}

CodeItem** CoderFactory::CreateItems(int count, int type){
    CodeItem** items = nullptr;
    switch (type)
    {
    case HUFFMAN:
        items = (CodeItem**)new HuffmanItem*[count];
        for (int i = 0; i < count; i++){
            items[i] = new HuffmanItem();
        }
        break;
    default:
        break;
    }
    return items;
}
DataCoder* CoderFactory::CreateCoder(int type){
    switch (type)
    {
    case HUFFMAN:
        return new HuffmanCoder();
        break;
    default:
        break;
    }
    return nullptr;
}

CodeTable* CoderFactory::CreateTable(int type){
    switch (type)
    {
    case HUFFMAN:
        return new HuffmanTable();
        break;
    default:
        break;
    }
    return nullptr;
}