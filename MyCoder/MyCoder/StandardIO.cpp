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

#include "StandardIO.h"
#include <stdio.h>
#include <string.h>

StandardIO::StandardIO()
{
}


StandardIO::~StandardIO()
{
}

char* StandardIO::InputTextData(char* src){
    char* data = new char[1024];
    printf("输入一串字符，以回车结束：\n");
    gets(data);
    return data;
}

CodedData* StandardIO::InputCodedData(char* src){
    return nullptr;
}

void StandardIO::OutputTextData(char* data, char* dest){
    printf("%s", data);
}

void StandardIO::OutputCodedData(CodedData* data, char* dest){
    CodeTable* table = data->table;
    unsigned char* codedData = data->getData();
    printf("ch\tcode\tcount\n");
    for (int i = 0; i < table->GetItemCount(); i++){
        CodeItem* item = table->GetItemAt(i);
        if (item->ch != '\0'){
            printf("'%c' %x\t%s\t%d\n", item->ch, item->ch, item->code, item->count);
        }
    }
}
