#include "main_header.h"
#include "Hash_chain.h"
#include "Hash_open_addressing.h"
#include "Hash_Cuckoo.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	string FileName = "data.txt";

	unsigned table_size = 20000;//������ �������
	unsigned pushet_count = 0;//������� ���������
	unsigned size = 1000;//������ ������� ������

	for (size_t i = 0; i < 3; ++i)//������ ��� ������ pushet_count
	{
		if (i == 0) pushet_count = table_size / 2;
		else if (i == 1) pushet_count = table_size;
		else if (i == 2) pushet_count = table_size * 2;

		cout << "table_size = " << table_size << endl;
		cout << "pushet_count = " << pushet_count << endl;

		{//���� �����
			Hash_Chain<int> hash_chained(table_size);
			Hash_open_addressing<int> hash_open_addressing(table_size);
			Hash_Cuckoo<int> hash_cuckoo(table_size);
			map<int, int> map;
			unordered_map<int, int> hash;

			//���������� ������
			for (unsigned i = 0; i < pushet_count; i++)
				hash_chained.Insert(gen());
			cout << "����� ���� ��������� � ��� ������� ������ �������" << endl;
			//for (unsigned i = 0; i < pushet_count; i++)
				//hash_chained.Show();

			for (unsigned i = 0; i < pushet_count; i++)
				hash_open_addressing.Insert(gen());
			cout << "����� ���� ��������� � ��� ������� ������ �������� ���������" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash_cuckoo.Insert(gen());
			cout << "����� ���� ��������� � ��� ������� ������ �������" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				map.insert(pair<int, int>(gen(), gen()));
			cout << "����� ���� ��������� � Map" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash.insert(pair<int, int>(gen(), gen()));
			cout << "����� ���� ��������� � Hash map" << endl;

			//������������ ����� ��� �������
			vector<int> keys;
			for (size_t i = 0; i < size; i++)
				keys.push_back(gen());

			cout << "�������" << endl;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_chained.Insert(keys[i]);
			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			//������� ������ �������� ���������
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_open_addressing.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / size) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_cuckoo.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				map.insert(pair<int, int>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash.insert(pair<int, int>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			cout << "�����" << endl;
			//�����
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 1000; i++)
			{
				hash_chained.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_open_addressing.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_cuckoo.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				map.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			cout << "��������" << endl;
			//��������
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_chained.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_open_addressing.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / size) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash_cuckoo.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				map.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / size) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < size; i++)
			{
				hash.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / size) * 1000 << " ����������" << endl;
		}

		//������
		{
			Hash_Chain<string> hash_chained(table_size);
			Hash_open_addressing<string> hash_open_addressing(table_size);
			Hash_Cuckoo<string> hash_cuckoo(table_size);
			map<string, string> map;
			unordered_map<string, string> hash;

			//���������� ������
			for (unsigned i = 0; i < pushet_count; i++)
				hash_chained.Insert(random_string());
			cout << "������ ���� ��������� � ��� ������� ������ �������" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash_open_addressing.Insert(random_string());
			cout << "������ ���� ��������� � ��� ������� ������ �������� ���������" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash_cuckoo.Insert(random_string());
			cout << "������ ���� ��������� � ��� ������� ������ �������" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				map.insert(pair<string, string>(random_string(), random_string()));
			cout << "������ ���� ��������� � Map" << endl;

			for (unsigned i = 0; i < pushet_count; i++)
				hash.insert(pair<string, string>(random_string(), random_string()));
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
				hash_chained.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_open_addressing.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_cuckoo.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				map.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			cout << "�����" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_chained.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_open_addressing.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_cuckoo.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				map.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_chained.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_open_addressing.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash_cuckoo.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				map.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < 10; i++)
			{
				hash.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;
		}

		//�� �����
		{
			Hash_Chain<string> hash_chained(table_size);
			Hash_open_addressing<string> hash_open_addressing(table_size);
			Hash_Cuckoo<string> hash_cuckoo(table_size);
			map<string, string> map;
			unordered_map<string, string> hash;

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
				if (words == pushet_count) break;//����� ��������� ����������������
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
				hash_chained.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				hash_open_addressing.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				hash_cuckoo.Insert(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				map.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				hash.insert(pair<string, string>(keys[i], keys[i]));
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			cout << "�����" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); ++i)
			{
				hash_chained.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_open_addressing.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_cuckoo.Search(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				map.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash.find(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			cout << "��������" << endl;
			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_chained.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_open_addressing.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������� ���������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;


			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash_cuckoo.Delete(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "����� �������: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				map.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;

			t1 = high_resolution_clock::now();
			for (size_t i = 0; i < keys.size(); i++)
			{
				hash.erase(keys[i]);
			}
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			std::cout << "Hash map: " << (time_span.count() / 10) * 1000 << " ����������" << endl;
		}

	}


	return 0;
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