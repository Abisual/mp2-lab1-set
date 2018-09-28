// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbitfield.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������� ����

#include "tbitfield.h"

TBitField::TBitField(int len): BitLen(len)
{
    if (len<1)
        throw -1;
    MemLen=(len+sizeof(TELEM)*8-1)/(sizeof(TELEM)*8);
    pMem= new TELEM[MemLen];
    for (int i=0;i<MemLen;++i)
        pMem[i]=0;
}

TBitField::TBitField(const TBitField &bf) // ����������� �����������
{
    BitLen=bf.BitLen;
    MemLen=bf.MemLen;
    pMem=new TELEM[MemLen];
    for (int i=0;i<MemLen;++i)
        pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // ������ ��� ��� ���� n
{
    return (n+sizeof(TELEM)*8)/(sizeof(TELEM)*8)-1;
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
    return 1ull << (n%(sizeof(TELEM)*8));
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ���
{
    if ((n<0)||(n>=BitLen))
        throw -1;
    pMem[GetMemIndex(n)]|=GetMemMask(n);
}

void TBitField::ClrBit(const int n) // �������� ���
{
    if ((n<0)||(n>=BitLen))
        throw -1;
    pMem[GetMemIndex(n)]&=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
    if ((n<0)||(n>=BitLen))
        throw -1;
    if (pMem[GetMemIndex(n)]&GetMemMask(n))
        return 1;
    return 0;
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField &bf) // ������������
{
    if (&bf==this)
        return *this;
    delete[] pMem;
    BitLen=bf.BitLen;
    MemLen=bf.MemLen;
    pMem=new TELEM[MemLen];
    for (int i=0;i<MemLen;++i)
        pMem[i]=bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // ���������
{
    if (BitLen!=bf.BitLen)
        return 0;
    for (int i=0;i<bf.BitLen/(sizeof(TELEM)*8);++i)
        if (pMem[i]!=bf.pMem[i])
            return 0;
    for (int i=0;i<bf.BitLen%(sizeof(TELEM)*8);++i)
        if ((pMem[MemLen-1]&GetMemMask(i))!=(bf.pMem[MemLen-1]&GetMemMask(i)))
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // ���������
{
    if (BitLen!=bf.BitLen)
        return 1;
    for (int i=0;i<bf.BitLen/(sizeof(TELEM)*8);++i)
        if (pMem[i]!=bf.pMem[i])
            return 1;
    for (int i=0;i<bf.BitLen%(sizeof(TELEM)*8);++i)
        if ((pMem[MemLen-1]&GetMemMask(i))!=(bf.pMem[MemLen-1]&GetMemMask(i)))
            return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // �������� "���"
{
    if (BitLen>bf.BitLen)
    {
        TBitField tmp(*this);
        for (int i=0;i<bf.MemLen;++i)
            tmp.pMem[i]|=bf.pMem[i];
        return tmp;
    }
    else
    {
        TBitField tmp(bf);
        for (int i=0;i<MemLen;++i)
            tmp.pMem[i]|=pMem[i];
        return tmp;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // �������� "�"
{
    if (BitLen>bf.BitLen)
    {
        TBitField tmp(BitLen);
        for (int i=0;i<bf.MemLen;++i)
            tmp.pMem[i]=bf.pMem[i]&pMem[i];
        return tmp;
    }
    else
    {
        TBitField tmp(bf.BitLen);
        for (int i=0;i<MemLen;++i)
            tmp.pMem[i]=bf.pMem[i]&pMem[i];
        return tmp;
    }
}

TBitField TBitField::operator~(void) // ���������
{
    TBitField tmp(*this);
    for (int i=0;i<MemLen;++i)
        tmp.pMem[i]=~tmp.pMem[i];
    for (int i=(BitLen%(sizeof(TELEM)*8))?(BitLen%(sizeof(TELEM)*8)):sizeof(TELEM)*8;i<sizeof(TELEM)*8;++i)
        tmp.pMem[MemLen-1]&=~GetMemMask(i);
    return tmp;
}

// ����/�����

istream &operator>>(istream &istr, TBitField &bf) // ����
{
    char ch;
    int c,i=0;
    istr >> ch;
    c=ch;
    while (((c==49)||(c==48)))
    {
        if (c==49)
            bf.SetBit(i);
        else
            bf.ClrBit(i);
        ++i;
        c=istr.get();
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // �����
{
    TELEM tmp;
    for (int i=0;i<bf.BitLen/(sizeof(TELEM)*8);++i)
    {
        tmp=bf.pMem[i];
        for (int j=0;j<sizeof(TELEM)*8;++j)
        {
            ostr << (tmp&1ull);
            tmp=tmp >> 1;
        }
    }
    tmp=bf.pMem[bf.MemLen-1];
    for (int i=0;i<bf.BitLen%(sizeof(TELEM)*8);++i)
    {
        ostr << (tmp&1ull);
        tmp=tmp >> 1;
    }
    return ostr;
}
