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

#include "CodedData.h"
#include "CoderFactory.h"

CodedData::CodedData()
{
    table = nullptr;
    data = nullptr;
    dataBitLength = 0;
}


CodedData::~CodedData()
{
    if (table != nullptr)
        delete table;
    if (data != nullptr)
        delete data;
}

void CodedData::setData(unsigned char* dataA, int bitlen){
    int byteLen = (bitlen + 7) / 8;
    data = new unsigned char[byteLen];
    for (int i = 0; i < byteLen; i++){
        data[i] = dataA[i];
    }
}

void CodedData::setTable(CodeTable* codeTable){
    table = codeTable;
}

unsigned char* CodedData::getData(){
    return data;
}

void CodedData::CalculateChar(char* data){
    int i = 0;
    //��������ַ����������м����¼����
    while (data[i] != '\0'){
        table->incCount(data[i]);
        i++;
    }
}

int CodedData::WriteHeader(ofstream &fout){
    //����汾���볤��
    char* version = "1.0.0";
    int verlen = strlen(version);
    fout.write((char*)(&verlen), sizeof(int));
    fout.write(version, verlen);
    //���뷽ʽ
    fout.write((char*)(&codeType), sizeof(int));
    //ԭ�ļ����ַ���
    int charC = table->GetCharCount();
    fout.write((char*)(&charC), sizeof(int));
    return codeType;
}

int CodedData::ReadHeader(ifstream &fin){
    //����汾��
    char* version;
    int verlen;
    fin.read((char*)(&verlen), sizeof(int));
    version = new char[verlen + 1];
    fin.read(version, verlen);
    version[verlen] = 0;
    //���뷽ʽ
    fin.read((char*)(&codeType), sizeof(int));
    table = CoderFactory::CreateTable(codeType);
    int charC = 0;
    fin.read((char*)(&charC), sizeof(int));
    table->SetCharCount(charC);
    return codeType;
}


void CodedData::Save(ofstream &fout){
    //�����ļ�ͷ
    WriteHeader(fout);
    //�����
    WriteCodeTable(fout);

    //�ѱ�������
    WriteCodedData(fout);

}

void CodedData::Load(ifstream &fin){
    //�����ļ�ͷ
    ReadHeader(fin);
    //�����
    ReadCodeTable(fin);

    //�ѱ�������
    ReadCodedData(fin);

}

int CodedData::WriteCodeTable(ofstream &fout){
    //д��CodeTable��itemCount��������Ҷ�ڵ㣩
    int itemCount = table->GetItemCount();
    fout.write((char*)(&itemCount),sizeof(int));
    //д��CodeTable������item
    CodeItem* item;
    for (int i = 0; i < table->GetItemCount(); i++){
        item = table->GetItemAt(i);
        item->Save(fout);
    }
    return itemCount;
}
int CodedData::WriteCodedData(ofstream &fout){
    fout.write((char*)&dataBitLength, sizeof(int));
    fout.write((char*)data, (dataBitLength + 7) / 8);
    return 0;
}
int CodedData::ReadCodeTable(ifstream &fin){
    //����CodeTable��itemCount��������Ҷ�ڵ㣩
    int itemCount;
    fin.read((char*)(&itemCount), sizeof(int));
    //����CodeTable������item
    CodeItem** items = CoderFactory::CreateItems(itemCount,codeType);
    for (int i = 0; i < itemCount; i++){
        items[i]->Load(fin);
    }
    table->SetItems(items, itemCount);
    return itemCount;
}
int CodedData::ReadCodedData(ifstream &fin){
    fin.read((char*)&dataBitLength, sizeof(int));
    int dataBytes = (dataBitLength + 7) / 8;
    data = new unsigned char[dataBytes];
    fin.read((char*)data, dataBytes);
    return 0;
}
