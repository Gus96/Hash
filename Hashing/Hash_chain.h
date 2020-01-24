#pragma once

#include "main_header.h"

template <class T>
class Hash_Chain
{
	vector<list<T>> table;
	unsigned table_size;

	unsigned p;//������� �����
	unsigned a;//����� �� p
	unsigned intial_value;//��������� �������� ��� ����

	unsigned Hash(T key)
	{
		cout << "Type is not supported!\n";
		return 0;
	}

public:

	Hash_Chain(unsigned _table_size)
	{
		table_size = _table_size;
		table.resize(table_size);
		p = (gen() % (UINT_MAX - table_size)) + table_size;//������� �����
		a = gen() % p;//����� �� p
		intial_value = 1;
	}

	void Insert(T key)
	{
		unsigned index = Hash(key);//����������� ������
		table.at(index).push_back(key);//�������
	}

	void Delete(T key)
	{
		unsigned index = Hash(key);

		for (auto i = table[index].begin(); i != table[index].end(); ++i) //���� � ������� ����
		{
			if (*i == key) //���� ����� �����
			{
				table[index].erase(i);
				break;
			}
		}
	}

	unsigned Search(T key)//���� ����
	{
		unsigned index = Hash(key);//��������� ������

		for (auto x : table[index])
			if (key == x)
				return index;//���������� ������ �����, ���� ������

		return NULL;
	}

	void Show()
	{
		for (unsigned i = 0; i < table_size; ++i)
		{
			cout << i;
			for (auto x : table[i])
				cout << " " << x;
			cout << endl;
		}
	}
};

unsigned Hash_Chain<int>::Hash(int key)
{
	return ((a * key) % p) % table_size;
}

unsigned Hash_Chain<std::string>::Hash(std::string key)
{
	unsigned h = intial_value;
	for (unsigned i = 0; i < key.length(); i++)
	{
		h = (((h * a) + (int)key[i]) % p) % table_size;//���������� ���������� h �� ������ ����
	}
	return h;
}
