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

#include "FileIO.h"


FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}

int FileIO::getFileSize(char * strFileName)
{
    FILE * fp = fopen(strFileName, "r");
    int size = getFileSize(fp);
    fclose(fp);
    return size;
}

int FileIO::getFileSize(FILE * fp)
{
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;
}

char* FileIO::InputTextData(char* src){
    FILE* fp = fopen(src, "rb");
    if (fp == NULL){
        printf("Invalid File Path!");
        return "";
    }
    char* data = new char[getFileSize(fp)+1];
    int i = 0;
    int size;
    do{
        //data[i] = fgetc(fp);
        size = fread(&data[i], 1, 1, fp);
        i++;
    } while (size != 0);//data[i - 1] != EOF);
    data[i - 1] = '\0';
    fclose(fp);
    return data;
}
CodedData* FileIO::InputCodedData(char* src){
    ifstream fin;
    CodedData* cd = new CodedData();
    fin.open(src, ifstream::binary);
    cd->Load(fin);
    fin.close();
    return cd;
}

void FileIO::OutputTextData(char* data, char* dest){
    FILE* fp = fopen(dest, "w+");
    fprintf(fp, "%s", data);
    fclose(fp);
}

void FileIO::OutputCodedData(CodedData *data, char* dest){
    ofstream fout;
    fout.open(dest, ofstream::binary);
    //写入已编码数据和编码对照表。
    data->Save(fout);
    fout.close();
}
