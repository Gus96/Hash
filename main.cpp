#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <random>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <time.h> 
#include <chrono>
#include <cmath>

using namespace std::chrono;

using namespace std;


unsigned m;
std::random_device rd;
std::mt19937 gen(rd());

template <class T>
class Chain_Hash
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

	Chain_Hash(unsigned _table_size)
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

unsigned Chain_Hash<int>::Hash(int key)
{
	return ((a * key) % p) % table_size;
}

unsigned Chain_Hash<std::string>::Hash(std::string key)
{
	unsigned h = intial_value;
	for (unsigned i = 0; i < key.length(); i++)
	{
		h = (((h * a) + (int)key[i]) % p) % table_size;//���������� ���������� h �� ������ ����
	}
	return h;
}

template <class T>
class Open_addressing_Hash
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

	Open_addressing_Hash(unsigned _table_size)
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

void Open_addressing_Hash<int>::DetDefines()
{
	DELETED = INT_MIN;
	NIL = INT_MIN + 1;
}

void Open_addressing_Hash<std::string>::DetDefines()
{
	DELETED = "DELETED DEF";
	NIL = "NIL DEF";
}

unsigned Open_addressing_Hash<int>::Hash(int key)
{
	return ((a * key) % p) % table_size;
}

unsigned Open_addressing_Hash<std::string>::Hash(std::string key)
{
	unsigned h = intial_value;
	for (unsigned i = 0; i < key.length(); i++)
	{
		h = (((h * a) + (int)key[i]) % p) % table_size;//������� ������ ������
	}
	return h;
}



template <class T>
class Cuckoo_Hash
{
	vector<T> table;
	unsigned table_size;
	unsigned table_size_2;

	T NIL;

	unsigned p;
	unsigned p2;
	unsigned a;
	unsigned intial_value;

	unsigned Hash(T key)
	{
		cout << "Type is not supported!\n";
		return 0;
	}
	unsigned Hash2(T key)
	{
		cout << "Type is not supported!\n";
		return 0;
	}

	void DetDefines()
	{
		cout << "Type is not supported!\n";
	}

public:

	Cuckoo_Hash(unsigned _table_size)
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
				if (index + table_size == index2) return;
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

void Cuckoo_Hash<int>::DetDefines()
{
	NIL = INT_MIN + 1;
}

void Cuckoo_Hash<std::string>::DetDefines()
{
	NIL = "NIL DEF";
}

unsigned Cuckoo_Hash<int>::Hash(int key)
{
	return ((a * key) % p) % table_size;
}

unsigned Cuckoo_Hash<std::string>::Hash(std::string key)
{
	unsigned h = intial_value;
	for (unsigned i = 0; i < key.length(); i++)
	{
		h = (((h * a) + (int)key[i]) % p) % table_size;
	}
	return h;
}

unsigned Cuckoo_Hash<int>::Hash2(int key)
{
	return ((((a * key) % p2) % p) % table_size_2) + table_size;
}

unsigned Cuckoo_Hash<std::string>::Hash2(std::string key)
{
	unsigned h = intial_value;
	for (unsigned i = 0; i < key.length(); i++)
	{
		h = (((((h * a) + (int)key[i]) % p2) % p) % table_size_2) + table_size;
	}
	return h;
}


std::string random_string()
{
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");//��� ��������� �������, ������� ����� ��������������
	//����� �������
	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);//������������ �������

	return str.substr(0, gen() % 15); //���������� ��������� ��������� ������ �� 15
//substr S.substr(pos, count) - ���������� ��������� ������ ������ ������� � ������� � �������� pos ����������� count ��� �� ����� ������, ���� pos + count > S.size().      
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string FileName = "data.txt";

	unsigned m = 20000;//������ �������
	unsigned n = 0;//������� ���������
	unsigned size = 1000;//������ ������� ������

	for (size_t i = 0; i < 3; ++i)//������ ��� ������ n
	{
		if (i == 0) n = m / 2;
		else if (i == 1) n = m;
		else if (i == 2) n = m * 2;

		cout << "m = " << m << endl;
		cout << "n = " << n << endl;

		{//���� �����
			Chain_Hash<int> chained_int(m);
			Open_addressing_Hash<int> open_addressing_int(m);
			Cuckoo_Hash<int> cuckoo_int(m);
			map<int, int> M;
			unordered_map<int, int> H;

			//���������� ������
			for (unsigned i = 0; i < n; i++)
				chained_int.Insert(gen());
			cout << "����� ���� ��������� � ��� ������� ������ �������" << endl;
			//for (unsigned i = 0; i < n; i++)
				//chained_int.Show();

			for (unsigned i = 0; i < n; i++)
				open_addressing_int.Insert(gen());
			cout << "����� ���� ��������� � ��� ������� ������ �������� ���������" << endl;

			for (unsigned i = 0; i < n; i++)
				cuckoo_int.Insert(gen());
			cout << "����� ���� ��������� � ��� ������� ������ �������" << endl;

			for (unsigned i = 0; i < n; i++)
				M.insert(pair<int, int>(gen(), gen()));
			cout << "����� ���� ��������� � Map" << endl;

			for (unsigned i = 0; i < n; i++)
				H.insert(pair<int, int>(gen(), gen()));
			cout << "����� ���� ��������� � Hash map" << endl;

			//������������ ����� ��� �������
			vector<int> keys;
			for (size_t i = 0; i < size; i++)
				keys.push_back(gen());

			cout << "�������" << endl;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				chained_int.Insert(keys[i]);
			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			//������� ������ �������� ���������
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				open_addressing_int.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / size) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				cuckoo_int.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				M.insert(pair<int, int>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				H.insert(pair<int, int>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			cout << "�����" << endl;
			//�����
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 1000; i++)
			{
				chained_int.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				open_addressing_int.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				cuckoo_int.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				M.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				H.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			cout << "��������" << endl;
			//��������
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				chained_int.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				open_addressing_int.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / size) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				cuckoo_int.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				M.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				H.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " ����������" << endl;
		}

		//������
		{
			Chain_Hash<string> chained_string(m);
			Open_addressing_Hash<string> open_addressing_string(m);
			Cuckoo_Hash<string> cuckoo_string(m);
			map<string, string> M;
			unordered_map<string, string> H;

			//���������� ������
			for (unsigned i = 0; i < n; i++)
				chained_string.Insert(random_string());
			cout << "������ ���� ��������� � ��� ������� ������ �������" << endl;

			for (unsigned i = 0; i < n; i++)
				open_addressing_string.Insert(random_string());
			cout << "������ ���� ��������� � ��� ������� ������ �������� ���������" << endl;

			for (unsigned i = 0; i < n; i++)
				cuckoo_string.Insert(random_string());
			cout << "������ ���� ��������� � ��� ������� ������ �������" << endl;

			for (unsigned i = 0; i < n; i++)
				M.insert(pair<string, string>(random_string(), random_string()));
			cout << "������ ���� ��������� � Map" << endl;

			for (unsigned i = 0; i < n; i++)
				H.insert(pair<string, string>(random_string(), random_string()));
			cout << "������ ���� ��������� � Hash map" << endl;


			vector<string> keys;//��������� ������� �����, � ������� ����� ��������� �����
			for (size_t i = 0; i < 10; i++)
				keys.push_back(random_string());

			cout << "�������" << endl;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();//��� ������ �������
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				chained_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				open_addressing_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				cuckoo_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				M.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				H.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			cout << "�����" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				chained_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				open_addressing_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				cuckoo_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				M.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				H.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				chained_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				open_addressing_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				cuckoo_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				M.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				H.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;
		}

		//�� �����
		{
			Chain_Hash<string> chained_string(m);
			Open_addressing_Hash<string> open_addressing_string(m);
			Cuckoo_Hash<string> cuckoo_string(m);
			map<string, string> M;
			unordered_map<string, string> H;

			string str = "";
			ifstream TxtFile(FileName);//������ �����

			if (!TxtFile.fail())
			{
				while (!TxtFile.eof())
					str += TxtFile.get();//������ �� ����� � ����������
				TxtFile.close();
			}
			else cout << "File does not exist" << endl;

			string tmp = "";

			string key;
			//�������������
			int words = 0;
			int i = 0;
			for (; i < str.length() / 2; ++i)
			{
				if (words == n) break;//����� ��������� ����������������
				if (str[i] == ' ')
				{
					key = tmp;
					chained_string.Insert(key);
					open_addressing_string.Insert(key);
					cuckoo_string.Insert(key);
					tmp = "";
					words++;
				}
				else
				{
					tmp += str[i];//��������� �����
				}
			}


			vector<string> keys;//�������� ������
			tmp = "";
			words = 0;
			for (; i < str.length(); ++i)
			{
				if (words == 10) break;
				if (str[i] == ' ')
				{
					key = tmp;
					keys.push_back(key);
					tmp = "";
					words++;
				}
				else
				{
					tmp += str[i];
				}
			}


			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				chained_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				open_addressing_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				cuckoo_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				M.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				H.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			cout << "�����" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				chained_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				open_addressing_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				cuckoo_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				M.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				H.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			cout << "��������" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				chained_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				open_addressing_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				cuckoo_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				M.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				H.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;
		}

	}


	return 0;
}
