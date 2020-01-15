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

	unsigned p;//простое число
	unsigned a;//число до p
	unsigned intial_value;//начальное значение для хеша

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
		p = (gen() % (UINT_MAX - table_size)) + table_size;//простое число
		a = gen() % p;//число до p
		intial_value = 1;
	}

	void Insert(T key)
	{
		unsigned index = Hash(key);//вычисляется индекс
		table.at(index).push_back(key);//вставка
	}

	void Delete(T key)
	{
		unsigned index = Hash(key);

		for (auto i = table[index].begin(); i != table[index].end(); ++i) //ищем в таблице ключ
		{
			if (*i == key) //если равен ключу
			{
				table[index].erase(i);
				break;
			}
		}
	}

	unsigned Search(T key)//ищет ключ
	{
		unsigned index = Hash(key);//вычисляет индекс

		for (auto x : table[index])
			if (key == x)
				return index;//возвращает индекс ключа, если найден

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
		h = (((h * a) + (int)key[i]) % p) % table_size;//использует предыдущий h на каждом шаге
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
		DetDefines();//инициализация флагов

		table_size = _table_size;
		table.resize(table_size);

		p = (gen() % (UINT_MAX - table_size)) + table_size;
		a = gen() % p;
		intial_value = 1;

		for (unsigned i = 0; i < table_size; ++i)//заполнение таблицы флагами
			table.at(i) = NIL;
	}

	void Insert(T key)
	{
		unsigned index = Hash(key);//вычисление индекса

		for (; index < table_size; ++index)
			if (table.at(index) == NIL || table.at(index) == DELETED)//если свободно или удалено
			{
				table[index] = key;
				break;
			}
	}

	void Delete(T key)
	{
		unsigned index = Search(key);//сначала находим ключ
		if (index != NULL)//если найден, то помечаем, как удаленный
			table[index] = DELETED;
	}

	unsigned Search(T key)//поиск
	{
		unsigned index = Hash(key);

		for (; index < table_size; ++index)//просматриваем таблицу
		{
			if (table[index] == NIL) break;//если не вставили, то и искать нечего
			else if (table[index] == key)
				return index;//возвращаем индекс
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
		h = (((h * a) + (int)key[i]) % p) % table_size;//смотрит каждый символ
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
		table_size_2 = table_size / 2;//вычисление размера второй части таблицы
		table_size -= table_size_2;//вычисляем размер первой части таблицы
		table.resize(table_size + table_size_2);

		p = (gen() % (UINT_MAX - table_size + table_size_2)) + table_size + table_size_2;
		p2 = gen() % p;
		a = gen() % p;
		intial_value = 1;

		for (unsigned i = 0; i < table_size + table_size_2; ++i)//инициализация флагами
			table[i] = NIL;
	}

	void Insert(T key)
	{
		unsigned index = Hash(key);
		unsigned index2 = Hash2(key);

		//if (table[index] != NIL && table[index] == table[index2]) return;//если не свободно и ключи совпадают
		//if (index + table_size == index2) return;

		if (table[index] == NIL)//если свободно, то записываем в "первую" таблицу
			table[index] = key;
		else if (table[index2] == NIL)//иначе, если во второй свободно, то записываем в нее
			table[index2] = key;
		else
		{
			T tmp = table[index2];//записываем значение из второй таблицы
			table[index2] = table[index];//во вторую таблицу записываем значение из первой
			table[index] = key;//и в первую записываем это значение

			T tmp2 = key;
			int i = 0;
			while (true)
			{
				if (table[index] != NIL && table[index] == table[index2]) return;//если не свободно и ключи совпадают
				if (index + table_size == index2) return;
				if (tmp2 == tmp || i >= 3 * log2(m))//если ключи равны или много итераций
				{
					ReHash();//перестраивает таблицу
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
					tmp = table[index2];//во временную записывается зачение из второй
					table[index2] = table[index];//из первой во вторую
					table[index] = tmp2;//записываем в первую временную
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

		vector<T> tmp(table_size + table_size_2);//временная таблица
		for (unsigned i = 0; i < table_size + table_size_2; i++)//копируем
			tmp[i] = table[i];

		table.clear();
		table.resize(table_size + table_size_2);
		for (unsigned i = 0; i < table_size + table_size_2; i++)//инициализируем
			table[i] = NIL;

		for (unsigned i = 0; i < table_size + table_size_2; i++)//записываем
			if (tmp[i] != NIL)//если записаны данные во временной таблице, записываем их в новую
				Insert(tmp[i]);
	}

	void Delete(T key)
	{
		unsigned index = Search(key);//сначала находим
		if (index != NULL)//если нашли, то удаляем
			table[index] = NIL;
	}

	unsigned Search(T key)//поиск
	{
		unsigned index = Hash(key);
		unsigned index_2 = Hash2(key);

		if (table[index] == key)//если в первой части таблицы
			return index;
		else if (table[index_2] == key)//если во второй части таблицы
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
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");//все возможные символы, которые будут использоваться
	//вихрь Мерсена
	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);//перемешиваем алфавит

	return str.substr(0, gen() % 15); //возвращает случайную подстроку длиной до 15
//substr S.substr(pos, count) - возвращает подстроку данной строки начиная с символа с индексом pos количеством count или до конца строки, если pos + count > S.size().      
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string FileName = "data.txt";

	unsigned m = 20000;//размер таблицы
	unsigned n = 0;//сколько вставляем
	unsigned size = 1000;//размер вектора ключей

	for (size_t i = 0; i < 3; ++i)//запуск для разных n
	{
		if (i == 0) n = m / 2;
		else if (i == 1) n = m;
		else if (i == 2) n = m * 2;

		cout << "m = " << m << endl;
		cout << "n = " << n << endl;

		{//блок жизни
			Chain_Hash<int> chained_int(m);
			Open_addressing_Hash<int> open_addressing_int(m);
			Cuckoo_Hash<int> cuckoo_int(m);
			map<int, int> M;
			unordered_map<int, int> H;

			//заполнение таблиц
			for (unsigned i = 0; i < n; i++)
				chained_int.Insert(gen());
			cout << "Числа были вставлены в хеш таблицу метода Цепочек" << endl;
			//for (unsigned i = 0; i < n; i++)
				//chained_int.Show();

			for (unsigned i = 0; i < n; i++)
				open_addressing_int.Insert(gen());
			cout << "Числа были вставлены в хеш таблицу метода Открытой адресации" << endl;

			for (unsigned i = 0; i < n; i++)
				cuckoo_int.Insert(gen());
			cout << "Числа были вставлены в хеш таблицу метода Кукушки" << endl;

			for (unsigned i = 0; i < n; i++)
				M.insert(pair<int, int>(gen(), gen()));
			cout << "Числа были вставлены в Map" << endl;

			for (unsigned i = 0; i < n; i++)
				H.insert(pair<int, int>(gen(), gen()));
			cout << "Числа были вставлены в Hash map" << endl;

			//генерируются ключи для вставки
			vector<int> keys;
			for (size_t i = 0; i < size; i++)
				keys.push_back(gen());

			cout << "Вставка" << endl;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				chained_int.Insert(keys[i]);
			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочек: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			//вставка метода открытой адресации
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				open_addressing_int.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				cuckoo_int.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				M.insert(pair<int, int>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				H.insert(pair<int, int>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			cout << "Поиск" << endl;
			//Поиск
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 1000; i++)
			{
				chained_int.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочек: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				open_addressing_int.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				cuckoo_int.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				M.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				H.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			cout << "Удаление" << endl;
			//Удаление
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				chained_int.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				open_addressing_int.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				cuckoo_int.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				M.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				H.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;
		}

		//Строки
		{
			Chain_Hash<string> chained_string(m);
			Open_addressing_Hash<string> open_addressing_string(m);
			Cuckoo_Hash<string> cuckoo_string(m);
			map<string, string> M;
			unordered_map<string, string> H;

			//заполнение таблиц
			for (unsigned i = 0; i < n; i++)
				chained_string.Insert(random_string());
			cout << "Строки были вставлены в хеш таблицу метода Цепочек" << endl;

			for (unsigned i = 0; i < n; i++)
				open_addressing_string.Insert(random_string());
			cout << "Строки были вставлены в хеш таблицу метода Открытой адресации" << endl;

			for (unsigned i = 0; i < n; i++)
				cuckoo_string.Insert(random_string());
			cout << "Строки были вставлены в хеш таблицу метода Кукушки" << endl;

			for (unsigned i = 0; i < n; i++)
				M.insert(pair<string, string>(random_string(), random_string()));
			cout << "Строки были вставлены в Map" << endl;

			for (unsigned i = 0; i < n; i++)
				H.insert(pair<string, string>(random_string(), random_string()));
			cout << "Строки были вставлены в Hash map" << endl;


			vector<string> keys;//генерация вектора строк, в котором будут случайные ключи
			for (size_t i = 0; i < 10; i++)
				keys.push_back(random_string());

			cout << "Вставка" << endl;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();//для замера времени
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				chained_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				open_addressing_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				cuckoo_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				M.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				H.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			cout << "Поиск" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				chained_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				open_addressing_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				cuckoo_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				M.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				H.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				chained_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				open_addressing_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				cuckoo_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				M.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				H.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;
		}

		//Из файла
		{
			Chain_Hash<string> chained_string(m);
			Open_addressing_Hash<string> open_addressing_string(m);
			Cuckoo_Hash<string> cuckoo_string(m);
			map<string, string> M;
			unordered_map<string, string> H;

			string str = "";
			ifstream TxtFile(FileName);//чтение файла

			if (!TxtFile.fail())
			{
				while (!TxtFile.eof())
					str += TxtFile.get();//запись из файла в переменную
				TxtFile.close();
			}
			else cout << "File does not exist" << endl;

			string tmp = "";

			string key;
			//инициализация
			int words = 0;
			int i = 0;
			for (; i < str.length() / 2; ++i)
			{
				if (words == n) break;//может полностью инициализировать
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
					tmp += str[i];//заполняем слово
				}
			}


			vector<string> keys;//создание ключей
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
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				open_addressing_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				cuckoo_string.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				M.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				H.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			cout << "Поиск" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				chained_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				open_addressing_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				cuckoo_string.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				M.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				H.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			cout << "Удаление" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				chained_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				open_addressing_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				cuckoo_string.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				M.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				H.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;
		}

	}


	return 0;
}
