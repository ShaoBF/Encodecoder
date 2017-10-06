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

// MyCoder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "FileIO.h"
#include "DataCoder.h"
#include "HuffmanCoder.h"
#include "StandardIO.h"
#include "CoderFactory.h"

using namespace std;

#define MODE_STDIO 0
#define MODE_FILE 1
#define MODE_NETWORK

char* TCHAR2char(TCHAR* tchStr)
{
    int iLen = 2 * wcslen(tchStr);//CString,TCHAR汉字算一个字符，因此不用普通计算长度 
    char* chRtn = new char[iLen + 1];
    wcstombs(chRtn, tchStr, iLen + 1);//转换成功返回为非负值 
    return chRtn;
}

CodedData* Encode(char* srcPath, char* destPath, int codeType){
    FileIO fio;
    //生成编码器
    DataCoder* coder = CoderFactory::CreateCoder(codeType);//new HuffmanCoder();
    //输入数据
    char* string = fio.InputTextData(srcPath);
    //编码
    CodedData* codedData = coder->Encode(string);
    fio.OutputCodedData(codedData, destPath);
    return codedData;
}
char* Decode(char* srcPath, char* destPath, int codeType){
    FileIO fio;
    //生成编码器
    DataCoder* coder = CoderFactory::CreateCoder(codeType);//new HuffmanCoder();
    //输入数据
    CodedData* codedData = fio.InputCodedData(srcPath);
    //解码
    char* string = coder->Decode(codedData);
    fio.OutputTextData(string, destPath);
    return string;
}

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc < 4){
        printf("Usage: \n\t%s e|d(e=encode d=decode) srcFile destFile CodeType(1=Huffman 2=Shannon-Fano)", TCHAR2char(argv[0]));
        //system("pause");
        exit(1);
    }
    int codeType = HUFFMAN;
    //获取操作选项
    char* option = TCHAR2char(argv[1]);
    option = _strlwr(option);
    char* srcPath = TCHAR2char(argv[2]);//"D:\\ShaoBF\\test.txt";
    char* destPath = TCHAR2char(argv[3]);// "D:\\ShaoBF\\test.hfm";
    if (argc > 4){
        //取编码方式(1=Huffman,2=Shannon-Fano)
        char* typestr = TCHAR2char(argv[4]);
        codeType = atoi(typestr);
        if (codeType != HUFFMAN){
            printf("Code type %s not available for now.\nSorry!\n", typestr);
            printf("There's only Huffman(1) available.");
            exit(1);
        }
    }
    CodedData* codedData;
    char* decodedText;
    StandardIO sio;

    //如果是E操作，读入文本文档，编码，输出二进制文档
    if (strcmp(option,"e")==0){
        codedData=Encode(srcPath, destPath, codeType);
        //输出到屏幕
        sio.OutputCodedData(codedData, "");
        printf("AverageCodeLength = %.3f\n\n", codedData->table->AverageCodeLength());
        
        //printf("Decoded form coded text.txt as below:\n%s\n\n", decodedText);
    }
    else if (strcmp(option, "d") == 0){
        decodedText = Decode(srcPath, destPath, codeType);
        //输出到屏幕
        printf("Decoded test.hfm text as below:\n");
        sio.OutputTextData(decodedText, "");
        printf("\n");
    }
    system("pause");
    return 0;
}

