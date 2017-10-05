#pragma once
#include "CodeTable.h"
class HuffmanTable :
    public CodeTable
{
public:
    HuffmanTable();
    virtual ~HuffmanTable();

public:
    CodeItem* CreateItem(char ch);
};

