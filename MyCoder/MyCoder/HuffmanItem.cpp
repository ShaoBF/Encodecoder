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

#include "HuffmanItem.h"


HuffmanItem::HuffmanItem() :CodeItem(){
    left = -1;
    right = -1;
}
//HuffmanItem::HuffmanItem(char c, unsigned char* bits, int bitlen, int repeat) :CodeItem(c, bits, bitlen, repeat)
//{
//    left = -1;
//    right = -1;
//}
HuffmanItem::HuffmanItem(char c, int repeat, int l, int r) :CodeItem(c, repeat){
    left = l;
    right = r;
}

HuffmanItem::~HuffmanItem(){}

bool HuffmanItem::IsLeaf(){
    return (left == -1) && (right == -1);
}

void HuffmanItem::Save(ofstream &fout){
    CodeItem::Save(fout);
    fout.write((char*)&left, sizeof(int));
    fout.write((char*)&right, sizeof(int));
}
void HuffmanItem::Load(ifstream &fin){
    CodeItem::Load(fin);
    fin.read((char*)&left, sizeof(int));
    fin.read((char*)&right, sizeof(int));
}