#pragma once
#include "main_header.h"

template <class T>
class Hash_open_addressing
{
	vector<T> table;
	unsigned table_size;

	T DELETED;
	T NIL;

	unsigned p;
	unsigned a;
	unsigned intial_value;

	unsigned Hash(T key)
	{
		cout << "Type is not supported!\n";
		return 0;
	}

	void DetDefines()
	{
		cout << "Type is not supported!\n";
	}

public:

	Hash_open_addressing(unsigned _table_size)
	{
		DetDefines();//������������� ������

		table_size = _table_size;
		table.resize(table_size);

		p = (gen() % (UINT_MAX - table_size)) + table_size;
		a = gen() % p;
		intial_value = 1;

		for (unsigned i = 0; i < table_size; ++i)//���������� ������� �������
			table.at(i) = NIL;
	}

	void Insert(T key)
	{
		unsigned index = Hash(key);//���������� �������

		for (; index < table_size; ++index)
			if (table.at(index) == NIL || table.at(index) == DELETED)//���� �������� ��� �������
			{
				table[index] = key;
				break;
			}
	}

	void Delete(T key)
	{
		unsigned index = Search(key);//������� ������� ����
		if (index != NULL)//���� ������, �� ��������, ��� ���������
			table[index] = DELETED;
	}

	unsigned Search(T key)//�����
	{
		unsigned index = Hash(key);

		for (; index < table_size; ++index)//������������� �������
		{
			if (table[index] == NIL) break;//���� �� ��������, �� � ������ ������
			else if (table[index] == key)
				return index;//���������� ������
		}

		return NULL;
	}

	void Show()
	{
		for (unsigned i = 0; i < table_size; ++i)
		{
			cout << i << " ";
			if (table[i] != NIL && table[i] != DELETED)
				cout << table[i];
			cout << endl;
		}
	}
};

void Hash_open_addressing<int>::DetDefines()
{
	DELETED = INT_MIN;
	NIL = INT_MIN + 1;
}

void Hash_open_addressing<std::string>::DetDefines()
{
	DELETED = "DELETED DEF";
	NIL = "NIL DEF";
}

unsigned Hash_open_addressing<int>::Hash(int key)
{
	return ((a * key) % p) % table_size;
}

unsigned Hash_open_addressing<std::string>::Hash(std::string key)
{
	unsigned h = intial_value;
	for (unsigned i = 0; i < key.length(); i++)
	{
		h = (((h * a) + (int)key[i]) % p) % table_size;//������� ������ ������
	}
	return h;
}
