// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbitfield.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������� ����

#include "tbitfield.h"

TBitField::TBitField(int len)   // ��������������, ��� len - ��� �� ������, � ����������
{
    BitLen = len;
    MemLen = ((len)/((sizeof(TELEM))*8));  // ��� ����� 32 ��� (� ������� �����) ����� ������� - 1.
    if ((len)%((sizeof(TELEM))*8) > 0)  // ���� ���������� ������ ��� ������ �����, ������� 32, �� ��������� ��� ������.
    {
        MemLen++;
    }
    TELEM * pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &bf) // ����������� �����������
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    TELEM * pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)  // �������� �� ������ �������� ������������� �������
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
    BitLen = 0;
    MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // ������ ��� ��� ���� n
{
    int SizeOfTelem = sizeof(TELEM)*8; // � �����
    return n / SizeOfTelem;
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
    int number = n % (sizeof(TELEM)*8); // ������� ���� � �����
    TELEM mask = 0;
    mask = 1 << number;
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
  return BitLen;
  //return 0;
}

void TBitField::SetBit(const int n) // ���������� ���
{
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    TELEM[memindex] = TELEM[memindex] | mask;
}

void TBitField::ClrBit(const int n) // �������� ���
{
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    mask = ~mask;
    TELEM[memindex] = TELEM[memindex] & mask;
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    return TELEM[memindex] & mask;
  //return 0;
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField &bf) // ������������
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        TELEM * pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)  // �������� �� ������ �������� ������������� �������
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // ���������
{
    // ��������� ������� ������� ����� ���������� ��������
    if (BitLen == bf.BitLen)  // ���� ����� ����� � �����
    {
        if (MemLen == bf.MemLen) // ���� ��������� ���-�� �����
        {
            for (int i = 0; i < MemLen - 2; i++) // ��������� ��� ������, ����� ��������� (memlen - ��� ����������, � �� ������)
            {
                if (pMem[i] != bf.pMem[i]) // ���� �����-�� ������ �� �������
                    return 0;
            }

            for (int i = BitLen - 1; i > BitLen - ((BitLen - 1) % (sizeof(TELEM)*8 * BitLen / (sizeof(TELEM)*8))) ; i--) // �������� �� ����� ���������� �������� �������, ������� �� ��������
            {
                if (GetBit(i) != bf.GetBit(i)
                    return 0;
            }

            return 1; // ������ 1 � ��� ������, ���� �� �������

        }
    }
    return 0; // ���� ���-�� �� �����
}

int TBitField::operator!=(const TBitField &bf) const // ���������
{
    // ��� operator==, �� ��������
    if (BitLen == bf.BitLen)  // ���� ����� ����� � �����
    {
        if (MemLen == bf.MemLen) // ���� ��������� ���-�� �����
        {
            for (int i = 0; i < MemLen - 2; i++) // ��������� ��� ������, ����� ��������� (memlen - ��� ����������, � �� ������)
            {
                if (pMem[i] != bf.pMem[i]) // ���� �����-�� ������ �� �������
                    return 1;
            }

            for (int i = BitLen - 1; i > BitLen - ((BitLen - 1) % (sizeof(TELEM)*8 * BitLen / (sizeof(TELEM)*8))) ; i--) // �������� �� ����� ���������� �������� �������, ������� �� ��������
            {
                if (GetBit(i) != bf.GetBit(i)
                    return 1;
            }

            return 0; // ������ 1 � ��� ������, ���� �� �������

        }
    }
    return 1; // ���� ���-�� �� �����
}

TBitField TBitField::operator|(const TBitField &bf) // �������� "���"
{
    if (BitLen >= bf.BitLen)     // ������� ������ � ���������� ������
        TBitField tmp(BitLen);
    else
        TBitField tmp(bf.BitLen);

    for (int i = 0; i < tmp.BitLen; i++)
    {
        if (GetBit(i) || bf.GetBit(i))
            tmp.SetBit(i);
    }

    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // �������� "�"
{
    if (BitLen >= bf.BitLen)     // ������� ������ � ���������� ������
        TBitField tmp(BitLen);
    else
        TBitField tmp(bf.BitLen);

    for (int i = 0; i < tmp.BitLen; i++)
    {
        if (GetBit(i) && bf.GetBit(i))
            tmp.SetBit(i);
    }

    return tmp;
}

TBitField TBitField::operator~(void) // ���������
{
    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i))
            ClrBit(i);
        else
            SetBit(i);
    }
}

// ����/�����

istream &operator>>(istream &istr, TBitField &bf) // ����
{
    int bit;

    for (int i = 0; i < bf.BitLen; i++)
    {
        cin >> bit;
        if (bit)
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // �����
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        cout << bf.GetBit(i);
    }
    cout << endl;

    return ostr;
}
