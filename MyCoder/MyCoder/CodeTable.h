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

#define UNDEFINED_CODE 0
#define HUFFMAN_CODE 1
#define SHANNON_FANO_CODE 2

using namespace std;

class CodeTable
{
public:
    CodeTable();
    CodeTable(int max);
    virtual ~CodeTable();

private:
    CodeItem** items;
    int itemCount;//编码字符类型数
    int charCount;//文本字符总个数
    int maxsize;
    int type;

public:
    int AddItem(CodeItem* item, bool isLeaf);
    int RemoveItem(int index);
    int RemoveItem(char ch);
    CodeItem* GetItemAt(int index);
    CodeItem** GetAllItem();
    int IndexOf(char item);
    CodeItem* CodeOf(char ch);
    int GetCharCount();
    void SetCharCount(int count);
    int GetItemCount();
    void incCount(char ch);
    void SetItems(CodeItem** item, int count);
    virtual CodeItem* CreateItem(char ch) = 0;
    double AverageCodeLength();
//    void SetCode(char* code, char ch);
};

