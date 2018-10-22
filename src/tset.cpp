// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tset.cpp - Copyright (c) ������� �.�. 04.10.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ��������� - ���������� ����� ������� ����

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower=mp;
}

// ����������� �����������
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower=s.MaxPower;
}

// ����������� �������������� ����
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower=bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // �������� ����. �-�� ��-���
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // ������� ���������?
{
    if (BitField.GetBit(Elem))
        return 1;
    return 0;
}

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
{
    BitField.ClrBit(Elem);
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet &s) // ������������
{
    BitField=s.BitField;
    MaxPower=s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet &s) const // ���������
{
    if (BitField==s.BitField)
        return 1;
    return 0;
}

int TSet::operator!=(const TSet &s) const // ���������
{
    if (BitField!=s.BitField)
        return 1;
    return 0;
}

TSet TSet::operator+(const TSet &s) // �����������
{
    return TSet(BitField|s.BitField);
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
    TSet tmp(*this);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
    TSet tmp(*this);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // �����������
{
    return TSet(BitField&s.BitField);
}

TSet TSet::operator~(void) // ����������
{
    return TSet(~BitField);
}

// ���������� �����/������

istream &operator>>(istream &istr, TSet &s) // ����
{
    return istr >> s.BitField;
}

ostream& operator<<(ostream &ostr, const TSet &s) // �����
{
    return ostr << s.BitField;
}
