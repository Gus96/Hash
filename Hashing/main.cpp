#include "main_header.h"
#include "Hash_chain.h"
#include "Hash_open_addressing.h"
#include "Hash_Cuckoo.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	string FileName = "data.txt";

	unsigned table_size = 20000;//размер таблицы
	unsigned pushet_count = 0;//сколько вставляем
	unsigned size = 1000;//размер вектора ключей

	for (size_t i = 0; i < 3; ++i)//запуск для разных pushet_count
	{
		if (i == 0) pushet_count = table_size / 2;
		else if (i == 1) pushet_count = table_size;
		else if (i == 2) pushet_count = table_size * 2;

		cout << "table_size = " << table_size << endl;
		cout << "pushet_count = " << pushet_count << endl;

		{//блок жизни
			Hash_Chain<int> hash_chained(table_size);
			Hash_open_addressing<int> hash_open_addressing(table_size);
			Hash_Cuckoo<int> hash_cuckoo(table_size);
			map<int, int> map;
			unordered_map<int, int> hash;

			//заполнение таблиц
			for (unsigned i = 0; i < pushet_count; i++)
				hash_chained.Insert(gen());
			cout << "Числа были вставлены в хеш таблицу метода Цепочек" << endl;
			//for (unsigned i = 0; i < pushet_count; i++)
				//hash_chained.Show();

			for (unsigned i = 0; i < pushet_count; i++)
				hash_open_addressing.Insert(gen());
			cout << "Числа были вставлены в хеш таблицу метода Открытой адресации" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash_cuckoo.Insert(gen());
			cout << "Числа были вставлены в хеш таблицу метода Кукушки" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				map.insert(pair<int, int>(gen(), gen()));
			cout << "Числа были вставлены в Map" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash.insert(pair<int, int>(gen(), gen()));
			cout << "Числа были вставлены в Hash map" << endl;

			//генерируются ключи для вставки
			vector<int> keys;
			for (size_t i = 0; i < size; i++)
				keys.push_back(gen());

			cout << "Вставка" << endl;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_chained.Insert(keys[i]);
			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочек: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			//вставка метода открытой адресации
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_open_addressing.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_cuckoo.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				map.insert(pair<int, int>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash.insert(pair<int, int>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			cout << "Поиск" << endl;
			//Поиск
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 1000; i++)
			{
				hash_chained.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочек: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_open_addressing.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_cuckoo.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				map.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			cout << "Удаление" << endl;
			//Удаление
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_chained.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_open_addressing.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_cuckoo.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				map.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " милисекунд" << endl;
		}

		//Строки
		{
			Hash_Chain<string> hash_chained(table_size);
			Hash_open_addressing<string> hash_open_addressing(table_size);
			Hash_Cuckoo<string> hash_cuckoo(table_size);
			map<string, string> map;
			unordered_map<string, string> hash;

			//заполнение таблиц
			for (unsigned i = 0; i < pushet_count; i++)
				hash_chained.Insert(random_string());
			cout << "Строки были вставлены в хеш таблицу метода Цепочек" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash_open_addressing.Insert(random_string());
			cout << "Строки были вставлены в хеш таблицу метода Открытой адресации" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash_cuckoo.Insert(random_string());
			cout << "Строки были вставлены в хеш таблицу метода Кукушки" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				map.insert(pair<string, string>(random_string(), random_string()));
			cout << "Строки были вставлены в Map" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash.insert(pair<string, string>(random_string(), random_string()));
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
				hash_chained.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_open_addressing.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_cuckoo.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				map.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			cout << "Поиск" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_chained.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_open_addressing.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_cuckoo.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				map.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_chained.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_open_addressing.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_cuckoo.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				map.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;
		}

		//Из файла
		{
			Hash_Chain<string> hash_chained(table_size);
			Hash_open_addressing<string> hash_open_addressing(table_size);
			Hash_Cuckoo<string> hash_cuckoo(table_size);
			map<string, string> map;
			unordered_map<string, string> hash;

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
				if (words == pushet_count) break;//может полностью инициализировать
				if (str[i] == ' ')
				{
					key = tmp;
					hash_chained.Insert(key);
					hash_open_addressing.Insert(key);
					hash_cuckoo.Insert(key);
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
				hash_chained.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				hash_open_addressing.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				hash_cuckoo.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				map.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				hash.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			cout << "Поиск" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				hash_chained.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_open_addressing.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_cuckoo.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				map.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			cout << "Удаление" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_chained.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Цепочки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_open_addressing.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Открытой адресации: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_cuckoo.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Метод Кукушки: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				map.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " милисекунд" << endl;
		}

	}


	return 0;
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