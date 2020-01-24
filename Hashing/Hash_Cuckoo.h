#pragma once

template <class T>
class Hash_Cuckoo
{
	vector<T> table;
	unsigned table_size;
	unsigned table_size_2;

	T NIL;

	unsigned p;
	unsigned p2;
	unsigned a;
	unsigned intial_value;

	unsigned Hash(T key) {}
	unsigned Hash2(T key) {}

	void DetDefines() {}

public:

	Hash_Cuckoo(unsigned _table_size)
	{
		table_size = _table_size;
		table_size_2 = table_size / 2;//���������� ������� ������ ����� �������
		table_size -= table_size_2;//��������� ������ ������ ����� �������
		table.resize(table_size + table_size_2);

		p = (gen() % (UINT_MAX - table_size + table_size_2)) + table_size + table_size_2;
		p2 = gen() % p;
		a = gen() % p;
		intial_value = 1;

		for (unsigned i = 0; i < table_size + table_size_2; ++i)//������������� �������
			table[i] = NIL;
	}

	void Insert(T key)
	{
		unsigned index = Hash(key);
		unsigned index2 = Hash2(key);

		//if (table[index] != NIL && table[index] == table[index2]) return;//���� �� �������� � ����� ���������
		//if (index + table_size == index2) return;

		if (table[index] == NIL)//���� ��������, �� ���������� � "������" �������
			table[index] = key;
		else if (table[index2] == NIL)//�����, ���� �� ������ ��������, �� ���������� � ���
			table[index2] = key;
		else
		{
			T tmp = table[index2];//���������� �������� �� ������ �������
			table[index2] = table[index];//�� ������ ������� ���������� �������� �� ������
			table[index] = key;//� � ������ ���������� ��� ��������

			T tmp2 = key;
			int i = 0;
			while (true)
			{
				if (table[index] != NIL && table[index] == table[index2]) return;//���� �� �������� � ����� ���������
				if (index + table_size == index2) return;//���� hash �-�� ������� ������ ������� ��� ������
				if (tmp2 == tmp || i >= 3 * log2(m))//���� ����� ����� ��� ����� ��������
				{
					ReHash();//������������� �������
					Insert(key);
					break;
				}

				tmp2 = tmp;
				index = Hash(tmp);
				index2 = Hash2(tmp);

				if (table[index] == NIL)
				{
					table[index] = tmp;
					break;
				}
				else if (table[index2] == NIL)
				{
					table[index2] = tmp;
					break;
				}
				else
				{
					tmp = table[index2];//�� ��������� ������������ ������� �� ������
					table[index2] = table[index];//�� ������ �� ������
					table[index] = tmp2;//���������� � ������ ���������
				}
				i++;
			}
		}
	}

	void ReHash()
	{
		p = (gen() % (UINT_MAX - table_size + table_size_2)) + table_size + table_size_2;
		p2 = gen() % p;
		a = gen() % p;

		vector<T> tmp(table_size + table_size_2);//��������� �������
		for (unsigned i = 0; i < table_size + table_size_2; i++)//��������
			tmp[i] = table[i];

		table.clear();
		table.resize(table_size + table_size_2);
		for (unsigned i = 0; i < table_size + table_size_2; i++)//��������������
			table[i] = NIL;

		for (unsigned i = 0; i < table_size + table_size_2; i++)//����������
			if (tmp[i] != NIL)//���� �������� ������ �� ��������� �������, ���������� �� � �����
				Insert(tmp[i]);
	}

	void Delete(T key)
	{
		unsigned index = Search(key);//������� �������
		if (index != NULL)//���� �����, �� �������
			table[index] = NIL;
	}

	unsigned Search(T key)//�����
	{
		unsigned index = Hash(key);
		unsigned index_2 = Hash2(key);

		if (table[index] == key)//���� � ������ ����� �������
			return index;
		else if (table[index_2] == key)//���� �� ������ ����� �������
			return index_2;

		return NULL;
	}

	void Show()
	{
		for (unsigned i = 0; i < table_size + table_size_2; ++i)
		{
			cout << i << " ";
			if (table[i] != NIL)
				cout << table[i];
			cout << endl;
		}
	}
};

void Hash_Cuckoo<int>::DetDefines()
{
	NIL = INT_MIN + 1;
}

void Hash_Cuckoo<std::string>::DetDefines()
{
	NIL = "NIL DEF";
}

unsigned Hash_Cuckoo<int>::Hash(int key)
{
	return ((a * key) % p) % table_size;
}

unsigned Hash_Cuckoo<std::string>::Hash(std::string key)
{
	unsigned h = intial_value;
	for (unsigned i = 0; i < key.length(); i++)
	{
		h = (((h * a) + (int)key[i]) % p) % table_size;
	}
	return h;
}

unsigned Hash_Cuckoo<int>::Hash2(int key)
{
	return ((((a * key) % p2) % p) % table_size_2) + table_size;
}

unsigned Hash_Cuckoo<std::string>::Hash2(std::string key)
{
	unsigned h = intial_value;
	for (unsigned i = 0; i < key.length(); i++)
	{
		h = (((((h * a) + (int)key[i]) % p2) % p) % table_size_2) + table_size;
	}
	return h;
}