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
    //下标startIndex节点之后所有节点子节点下标+1。
    int itemCount = table->GetItemCount();
    for (int i = 0; i < itemCount; i++){
        HuffmanItem* item = (HuffmanItem*)(table->GetItemAt(i));
        //判断左子节点是否有效
        if(item->left>=startIndex){
            item->left++;
        }
        //判断右子节点是否有效
        if (item->right>=startIndex){
            item->right++;
        }
    }
}

void HuffmanCoder::CreateHuffmanTree(CodeTable* table){
    int extraNodeCount = 0;
    int leafCount = table->GetItemCount();
    //循环操作，插入（叶节点数-1）个新节点后霍夫曼树构建完成
    for (extraNodeCount = 0; extraNodeCount < leafCount - 1; extraNodeCount++){
        //忽略最后(2*extraNodeCount)个节点
        int rightIndex = table->GetItemCount() - 1 - extraNodeCount*2;
        //将出现次数最小的2中概率相加作为新节点插入
        int repeat = (table->GetItemAt(rightIndex)->count) + table->GetItemAt(rightIndex - 1)->count;
        //同时设置该节点的左右子节点为刚刚的2个节点
        HuffmanItem* item = new HuffmanItem('\0', repeat,rightIndex-1,rightIndex);
        int itemIndex = table->AddItem(item, false);
        //调整节点。
        AdjustNodes(table,itemIndex);
    }
}

void HuffmanCoder::Traverse(HuffmanItem** items, int rootIndex){
    //若左右子树都不存在则返回
    //访问根节点，取得code字符串
    HuffmanItem* root = items[rootIndex];
    int codelen = root->bitLength;//strlen(root->code);
    int leftIndex = root->left;
    int rightIndex = root->right;
    //访问左子树，将左子节点的code赋值为自身code+"0"，bitLength自增1
    int bitLength = root->bitLength;
    if (leftIndex>0){
        HuffmanItem* leftNode = items[leftIndex];

        leftNode->SetCodeStr(root->code, codelen, '0');

        leftNode->SetCodeBits(root->bytes, bitLength, 0);
        Traverse(items, leftIndex);
    }
    //访问右子树，将右子节点的code赋值为自身code+"1"
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
    //在数据结束之前编码所有的文字，将其变为二进制形式
    const unsigned char* bytes;
    int bitLength;
    int textLength = strlen(data);
    //申请并初始化二进制编码的缓存区
    codedData->data = new unsigned char[textLength];
    for (int j = 0; j < textLength; j++){
        codedData->data[j] = 0;
    }
    codedData->data[0] = 0x00;
    for (i = 0; data[i] != '\0';i++){
        //获得一个字符
        char ch = data[i];
        //获得其编码方式
        CodeItem* item = codedData->table->CodeOf(ch);
        if (item != nullptr){
            bytes = item->bytes;
            //按字节/段长度加入至已编码数据中。
            //将编码二进制串拆分成字节，按字节加入整个数据
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
                //判断字节剩余位数是否足够下一字节
                //足够，则直接整体加入末位
                if (bitLength <= curBit){
                    //将字符编码右移至当前位之后
                    codedData->data[curByte] |= bytes[j] >> (8 - curBit);
                    //加入编码位，curBit减少对应位数
                    curBit -= bitLength;
                }//不足则拆分成2段，前段填满剩余部分，后段放入下一字节开头
                else if (bitLength > curBit){
                    //填满当前字节
                    codedData->data[curByte] |= bytes[j] >> (8 - curBit);
                    //当前字节下标+1
                    curByte++;
                    //剩余位补入下一字节前段
                    unsigned char front = bytes[j] << curBit;
                    codedData->data[curByte] = front;
                    //计算当前位的值
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
    //申请items变量空间，初始化包含HuffmanItem类型的table的CodedData
    HuffmanItem** items = new HuffmanItem*[256];
    HuffmanTable* table = new HuffmanTable();
    CodedData* codedData = new CodedData();
    codedData->SetCodeType(HUFFMAN);
    codedData->setTable(table);
    codedData->table->SetItems((CodeItem**)items, 0);
    //计算所有的字符出现次数和总字数
    codedData->CalculateChar(data);
    //构建霍夫曼树
    CreateHuffmanTree(codedData->table);
    //遍历霍夫曼树，获得每个叶节点编码结果
    GetCodeResult(codedData);
    //编码data，变为二进制形式
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
        //从第一位开始，逐位读取0/1
        int bit = (data->data[byteIndex] >> (8 - bitIndex - 1)) & 1;
        //按0左1右规则遍历霍夫曼树至叶节点
        if (bit == 0){
            item = (HuffmanItem*)data->table->GetItemAt(item->left);
            //treeIndex = data->table->GetLeft(treeIndex);
            //((HuffmanItem*)(data->table->GetItemAt(treeIndex)))->left;
        } else{
            item = (HuffmanItem*)data->table->GetItemAt(item->right);
            //treeIndex = ((HuffmanItem*)(data->table->GetItemAt(treeIndex)))->right;
        }
        //还原该字节，然后继续读取。
        if (item->IsLeaf()){
            textData[charIndex] = item->ch;
            charIndex++;
            item = (HuffmanItem*)data->table->GetItemAt(0);
        }
    }
    textData[charIndex] = '\0';
    return textData;
}
