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

// MyCoder.cpp : �������̨Ӧ�ó������ڵ㡣
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
    int iLen = 2 * wcslen(tchStr);//CString,TCHAR������һ���ַ�����˲�����ͨ���㳤�� 
    char* chRtn = new char[iLen + 1];
    wcstombs(chRtn, tchStr, iLen + 1);//ת���ɹ�����Ϊ�Ǹ�ֵ 
    return chRtn;
}

int _tmain(int argc, _TCHAR* argv[])
{
    char* string;
    if (argc < 3){
        printf("Usage: \n\t%s srcFile destFile CodeType(1=Huffman,2=Shannon-Fano)", TCHAR2char(argv[0]));
        //system("pause");
        exit(1);
    }
    int codeType = HUFFMAN;
    char* filePath = TCHAR2char(argv[1]);//"D:\\ShaoBF\\test.txt";
    char* destFile = TCHAR2char(argv[2]);// "D:\\ShaoBF\\test.hfm";
    if (argc > 3){
        //ȡ���뷽ʽ(1=Huffman,2=Shannon-Fano)
        char* typestr = TCHAR2char(argv[3]);
        codeType = atoi(typestr);
        if (codeType != HUFFMAN){
            printf("Code type %s not available for now.\nSorry!\n", typestr);
            printf("There's only Huffman(1) available.");
            exit(1);
        }
    }
    FileIO fio;

    //��������
    string = fio.InputTextData(filePath);

    //����������
    DataCoder* coder = CoderFactory::CreateCoder(codeType);//new HuffmanCoder();
    CodedData* codedData = coder->Encode(string);
    char* decodedText = coder->Decode(codedData);

    //������
    StandardIO sio;
    sio.OutputCodedData(codedData, "");
    printf("AverageCodeLength = %.3f\n\n", codedData->table->AverageCodeLength());
    printf("Decoded form coded text.txt as below:\n%s\n\n", decodedText);

    fio.OutputCodedData(codedData, destFile);
    CodedData* testData = fio.InputCodedData(destFile);
    char* decodedText2 = coder->Decode(testData);
    printf("Decoded test.hfm text as below:\n%s\n", decodedText2);
    system("pause");
    return 0;
}

