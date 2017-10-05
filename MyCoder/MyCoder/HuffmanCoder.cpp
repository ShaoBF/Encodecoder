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

#include "HuffmanCoder.h"
#include "HuffmanTable.h"

HuffmanCoder::HuffmanCoder()
{
}


HuffmanCoder::~HuffmanCoder()
{
}

void HuffmanCoder::AdjustNodes(CodeTable* table, int startIndex){
    //�±�startIndex�ڵ�֮�����нڵ��ӽڵ��±�+1��
    int itemCount = table->GetItemCount();
    for (int i = 0; i < itemCount; i++){
        HuffmanItem* item = (HuffmanItem*)(table->GetItemAt(i));
        //�ж����ӽڵ��Ƿ���Ч
        if(item->left>=startIndex){
            item->left++;
        }
        //�ж����ӽڵ��Ƿ���Ч
        if (item->right>=startIndex){
            item->right++;
        }
    }
}

void HuffmanCoder::CreateHuffmanTree(CodeTable* table){
    int extraNodeCount = 0;
    int leafCount = table->GetItemCount();
    //ѭ�����������루Ҷ�ڵ���-1�����½ڵ����������������
    for (extraNodeCount = 0; extraNodeCount < leafCount - 1; extraNodeCount++){
        //�������(2*extraNodeCount)���ڵ�
        int rightIndex = table->GetItemCount() - 1 - extraNodeCount*2;
        //�����ִ�����С��2�и��������Ϊ�½ڵ����
        int repeat = (table->GetItemAt(rightIndex)->count) + table->GetItemAt(rightIndex - 1)->count;
        //ͬʱ���øýڵ�������ӽڵ�Ϊ�ոյ�2���ڵ�
        HuffmanItem* item = new HuffmanItem('\0', repeat,rightIndex-1,rightIndex);
        int itemIndex = table->AddItem(item, false);
        //�����ڵ㡣
        AdjustNodes(table,itemIndex);
    }
}

void HuffmanCoder::Traverse(HuffmanItem** items, int rootIndex){
    //�������������������򷵻�
    //���ʸ��ڵ㣬ȡ��code�ַ���
    HuffmanItem* root = items[rootIndex];
    int codelen = root->bitLength;//strlen(root->code);
    int leftIndex = root->left;
    int rightIndex = root->right;
    //�����������������ӽڵ��code��ֵΪ����code+"0"��bitLength����1
    int bitLength = root->bitLength;
    if (leftIndex>0){
        HuffmanItem* leftNode = items[leftIndex];

        leftNode->SetCodeStr(root->code, codelen, '0');

        leftNode->SetCodeBits(root->bytes, bitLength, 0);
        Traverse(items, leftIndex);
    }
    //�����������������ӽڵ��code��ֵΪ����code+"1"
    if (rightIndex>0){
        HuffmanItem* rightNode = items[rightIndex];
        rightNode->SetCodeStr(root->code, codelen, '1');
        rightNode->SetCodeBits(root->bytes, bitLength, 1);

        Traverse(items, rightIndex);
    }
}


void HuffmanCoder::GetCodeResult(CodedData* codedData){
    HuffmanItem** items = (HuffmanItem**)(codedData->table->GetAllItem());
    items[0]->bytes = new unsigned char[1];
    items[0]->code = "";
    items[0]->bytes[0] = 0;
    items[0]->bitLength = 0;
    Traverse(items, 0);
}

void HuffmanCoder::EncodeData(char* data, CodedData *codedData){
    int i = 0;
    int curByte = 0;
    int curBit = 8;
    //�����ݽ���֮ǰ�������е����֣������Ϊ��������ʽ
    const unsigned char* bytes;
    int bitLength;
    int textLength = strlen(data);
    //���벢��ʼ�������Ʊ���Ļ�����
    codedData->data = new unsigned char[textLength];
    for (int j = 0; j < textLength; j++){
        codedData->data[j] = 0;
    }
    codedData->data[0] = 0x00;
    for (i = 0; data[i] != '\0';i++){
        //���һ���ַ�
        char ch = data[i];
        //�������뷽ʽ
        CodeItem* item = codedData->table->CodeOf(ch);
        if (item != nullptr){
            bytes = item->bytes;
            //���ֽ�/�γ��ȼ������ѱ��������С�
            //����������ƴ���ֳ��ֽڣ����ֽڼ�����������
            int bytelen = (item->bitLength + 7) / 8;
            for (int j = 0; j < bytelen; j++){
                if (j == bytelen - 1){
                    bitLength = (item->bitLength) % 8;
                    if (bitLength == 0){
                        bitLength = 8;
                    }
                }
                else{
                    bitLength = 8;
                }
                //�ж��ֽ�ʣ��λ���Ƿ��㹻��һ�ֽ�
                //�㹻����ֱ���������ĩλ
                if (bitLength <= curBit){
                    //���ַ�������������ǰλ֮��
                    codedData->data[curByte] |= bytes[j] >> (8 - curBit);
                    //�������λ��curBit���ٶ�Ӧλ��
                    curBit -= bitLength;
                }//�������ֳ�2�Σ�ǰ������ʣ�ಿ�֣���η�����һ�ֽڿ�ͷ
                else if (bitLength > curBit){
                    //������ǰ�ֽ�
                    codedData->data[curByte] |= bytes[j] >> (8 - curBit);
                    //��ǰ�ֽ��±�+1
                    curByte++;
                    //ʣ��λ������һ�ֽ�ǰ��
                    unsigned char front = bytes[j] << curBit;
                    codedData->data[curByte] = front;
                    //���㵱ǰλ��ֵ
                    curBit = curBit + 8 - bitLength;
                }
                codedData->dataBitLength += bitLength;
                if (curBit == 0){
                    curBit = 8;
                    curByte++;
                }
            }
        }
    }
}

CodedData* HuffmanCoder::Encode(char* data){
    //����items�����ռ䣬��ʼ������HuffmanItem���͵�table��CodedData
    HuffmanItem** items = new HuffmanItem*[256];
    HuffmanTable* table = new HuffmanTable();
    CodedData* codedData = new CodedData();
    codedData->SetCodeType(HUFFMAN);
    codedData->setTable(table);
    codedData->table->SetItems((CodeItem**)items, 0);
    //�������е��ַ����ִ�����������
    codedData->CalculateChar(data);
    //������������
    CreateHuffmanTree(codedData->table);
    //�����������������ÿ��Ҷ�ڵ������
    GetCodeResult(codedData);
    //����data����Ϊ��������ʽ
    EncodeData(data, codedData);
    return codedData;
}

char* HuffmanCoder::Decode(CodedData* data){
    char* textData = new char[data->table->GetCharCount()+1];
    int bitIndex;
    int byteIndex;
    int treeIndex;
    int charIndex = 0;

    treeIndex = 0;
    HuffmanItem* item = (HuffmanItem*)data->table->GetItemAt(treeIndex);
    for (int i = 0; i < data->dataBitLength; i++){
        byteIndex = i / 8;
        bitIndex = i % 8;
        //�ӵ�һλ��ʼ����λ��ȡ0/1
        int bit = (data->data[byteIndex] >> (8 - bitIndex - 1)) & 1;
        //��0��1�ҹ����������������Ҷ�ڵ�
        if (bit == 0){
            item = (HuffmanItem*)data->table->GetItemAt(item->left);
            //treeIndex = data->table->GetLeft(treeIndex);
            //((HuffmanItem*)(data->table->GetItemAt(treeIndex)))->left;
        } else{
            item = (HuffmanItem*)data->table->GetItemAt(item->right);
            //treeIndex = ((HuffmanItem*)(data->table->GetItemAt(treeIndex)))->right;
        }
        //��ԭ���ֽڣ�Ȼ�������ȡ��
        if (item->IsLeaf()){
            textData[charIndex] = item->ch;
            charIndex++;
            item = (HuffmanItem*)data->table->GetItemAt(0);
        }
    }
    textData[charIndex] = '\0';
    return textData;
}
