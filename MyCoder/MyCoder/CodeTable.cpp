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

#include "CodeTable.h"


CodeTable::CodeTable() :CodeTable(128)
{
}

CodeTable::CodeTable(int max)
{
    maxsize = max;
    items = nullptr;
    itemCount = 0;
    charCount = 0;
}

CodeTable::~CodeTable()
{
    if (items != nullptr){
        delete items;
    }
}

/**
 * Add one item to the table
 *
 * @return the index item added to
 *
 * @param the item to be added
 */
int CodeTable::AddItem(CodeItem* item, bool isLeaf = true){
    int index;
    for (index = 0; index < itemCount; index++){
        if (item->count > items[index]->count){
            break;
        }
    }
    for (int i = itemCount; i > index; i--){
        items[i] = items[i - 1];
    }
    items[index] = item;
    itemCount++;
    if (isLeaf){
        charCount += item->count;
    }
    return index;
}
int CodeTable::RemoveItem(int index){
    if (index >= itemCount){
        return -1;
    }
    else{
        CodeItem* item = items[index];
        charCount -= item->count;
        for (int i = index; i < itemCount - 1; i++){
            items[index] = items[index + 1];
        }
        itemCount--;
        delete item;
        return index;
    }
}
int CodeTable::RemoveItem(char ch){
    int index;
    index = IndexOf(ch);
    if (index != -1){
        return RemoveItem(index);
    }
    return -1;
}
CodeItem* CodeTable::GetItemAt(int index){
    return items[index];
}
CodeItem** CodeTable::GetAllItem(){
    return items;
}
int CodeTable::IndexOf(char item){
    int index;
    for (index = 0; index < itemCount; index++){
        if (items[index]->ch == item){
            return index;
        }
    }
    return -1;
}
CodeItem* CodeTable::CodeOf(char ch){
    int index = IndexOf(ch);
    return GetItemAt(index);
}
void CodeTable::SetCharCount(int count){
    charCount = count;
}
int CodeTable::GetCharCount(){
    return charCount;
}

/*
 *������ch�ַ���ӦԪ�ص�ͳ�Ƹ���������������+1��Ȼ����������
 */
void CodeTable::incCount(char ch){
    //�ж��Ƿ���д����ַ�Ϊch�ļ�¼
    int index = IndexOf(ch);
    if (index == -1){
        //�������ڣ��½���¼���ظ���������Ϊ1�������ĩ
        CodeItem* item = CreateItem(ch);//new CodeItem(ch, 1);
        items[itemCount] = item;
        itemCount++;
    }
    else {
        //�����ڣ�����Ӧ��¼+1��������ǰһ��Ŀ�Ƚ��Ƿ���Ҫ����λ��ֱ������С��ǰһ��Ŀ��
        items[index]->count++;
        while (index != 0 && items[index]->count > items[index - 1]->count){
            //��ǰһ���λ��
            CodeItem* tmpItem = items[index];
            items[index] = items[index - 1];
            items[index - 1] = tmpItem;
            index--;
        }
    }
    charCount++;
}

void CodeTable::SetItems(CodeItem** item, int count){
    if (items != nullptr){
        for (int i = 0; i < itemCount; i++){
            delete items[i];
        }
        delete items;
    }
    items = item;
    itemCount = count;
}
int CodeTable::GetItemCount(){
    return itemCount;
}

double CodeTable::AverageCodeLength(){
    //ƽ���볤=�����ַ��볤�����ָ��ʣ�
    double sumCodeLength = 0.0;
    for (int i = 0; i < itemCount; i++){
        CodeItem* item = items[i];
        if (item->ch != '\0'){
            sumCodeLength += item->bitLength*item->count;
        }
    }
    sumCodeLength /= charCount;
    return sumCodeLength;
}
