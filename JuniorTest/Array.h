#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
/*
Х зчитувати масиви з файлу - Reader
Х друкувати вм≥ст масив≥в - Printer
Х сортувати масиви без допомоги вбудованих функц≥й - Sorter
Х знаходити перетин масив≥в(двох з найб≥льшою довжиною ≥ вс≥х трьох) - CrossFinder
Х створювати в≥дсортоване в зворотному пор€дку масив, €кий м≥стить лише ун≥кальн≥ 
елементи з трьох представлених масив≥в - ReverseUniqueSorter
*/


template <class T> class Array
{
private:

	vector<string> str_first;
	vector<string> str_second;
	vector<string> str_third;


	void read()
	{
		vector<string> helper;

		ifstream file(path);
		if (file.is_open())
		{

			string str;
			while (!file.eof())
			{
				str = "";
				getline(file, str, ',');
				helper.push_back(str);
			}

		}
		file.close();

		ofstream out;
		out.open("C:\\help.txt");
		if (out.is_open())
		{
			for (size_t i = 0; i < helper.size(); i++)
			{
				out << helper[i] << " ";
			}

		}
		out.close();

		const string to_first_path = "C:\\first.txt";
		const string to_second_path = "C:\\second.txt";
		const string to_third_path = "C:\\third.txt";
		{

			string strs[3];

			ifstream f("C:\\help.txt");
			if (f.is_open())
			{
				int num = 1;
				string str;
				for (size_t i = 0; i < 3; i++)
				{
					str = "";
					getline(f, str);
					strs[i] = str;
				}
			}
			f.close();

			ofstream out_first;
			out_first.open(to_first_path);
			if (out_first.is_open())
			{
				out_first << strs[0];
			}
			out_first.close();

			ofstream out_second;
			out_second.open(to_second_path);
			if (out_second.is_open())
			{
				out_second << strs[1];
			}
			out_second.close();

			ofstream out_third;
			out_third.open(to_third_path);
			if (out_third.is_open())
			{
				out_third << strs[2];
			}
			out_third.close();
		}


		{
			ifstream file1(to_first_path);
			if (file1.is_open())
			{

				string str;
				while (!file1.eof())
				{
					str = "";
					getline(file1, str, ' ');
					str_first.push_back(str);
				}

			}
			file1.close();

			ifstream file2(to_second_path);
			if (file2.is_open())
			{

				string str;
				while (!file2.eof())
				{
					str = "";
					getline(file2, str, ' ');
					str_second.push_back(str);
				}

			}
			file2.close();

			ifstream file3(to_third_path);
			if (file3.is_open())
			{

				string str;
				while (!file3.eof())
				{
					str = "";
					getline(file3, str, ' ');
					str_third.push_back(str);
				}
				str_third.resize(str_third.size() - 1);
			}
			file3.close();
		};

	};

protected:

	vector<T> first;
	vector<T> second;
	vector<T> third;
	string path;

	vector<T> get_first()
	{
		const size_t size = str_first.size();
		vector<double> helper;

		for (size_t i = 0; i < size; i++)
		{
			helper.push_back(stod(str_first[i]));
		}

		for (size_t i = 0; i < size; i++)
		{
			first.push_back(static_cast<T>(helper[i]));
		}

		return first;
	};


	vector<T> get_second()
	{
		const size_t size = str_second.size();
		vector<double> helper;
		for (size_t i = 0; i < size; i++)
		{
			helper.push_back(stod(str_second[i]));
		}

		for (size_t i = 0; i < size; i++)
		{
			second.push_back(static_cast<T>(helper[i]));
		}

		return second;
	};


	vector<T> get_third()
	{
		const size_t size = str_third.size();

		vector<double> helper;
		for (size_t i = 0; i < size; i++)
		{
			helper.push_back(stod(str_third[i]));
		}

		for (size_t i = 0; i < size; i++)
		{
			third.push_back(static_cast<T>(helper[i]));
		}

		return third;
	};



	
public:

	Array(const string& p) :path(p)
	{
		this->read();
	};



	void print()
	{
		for (size_t i = 0; i < str_first.size(); i++)
			cout << str_first[i] << " ";
		
		cout << endl;

		for (size_t i = 0; i < str_second.size(); i++)
			cout << str_second[i] << " ";

		cout << endl;

		for (size_t i = 0; i < str_third.size(); i++)
			cout << str_third[i] << " ";
	}


	virtual void sort() {};


	virtual vector<T> first_array()  = 0;
	virtual vector<T> second_array() = 0;
	virtual vector<T> third_array() = 0;

};



template <class T> class SortedArray : public Array<T>
{
private:

	vector<T> a;
	vector<T> b;
	vector<T> c;

	vector<T> merge(vector<T> left, vector<T> right) 
	{
		vector<T> ret(left.size() + right.size(), -1);
		size_t left_position = 0;
		size_t right_position = 0;
		size_t ret_position = 0;

		while (left_position < left.size() && right_position < right.size()) 
		{
			T left_value = left[left_position];
			T right_value = right[right_position];
			if (left_value < right_value) 
			{
				ret[ret_position++] = left_value;
				left_position++;
			}
			else 
			{
				ret[ret_position++] = right_value;
				right_position++;
			}
		}
		while (left_position < left.size()) 
		{
			ret[ret_position++] = left[left_position++];
		}
		while (right_position < right.size()) 
		{
			ret[ret_position++] = right[right_position++];
		}
		return ret;
	}


	vector<T> mergeSort(vector<T> vec) 
	{
		if (vec.size() < 2) 
		{
			return vec;
		}
		size_t middle = vec.size() / 2;
		vector<T> left(vec.begin(), vec.begin() + middle);
		vector<T> right(vec.begin() + middle, vec.end());

		left = mergeSort(left);
		right = mergeSort(right);
		vector<T> ret = merge(left, right);
		return ret;
	}
	

	void sorting(vector<T>& vec)
	{
		vec = mergeSort(vec);
	}


	void sort()
	{
		{
			size_t s_a = this->get_first().size();
			vector<T> helper_a;
			for (size_t i = 0; i < s_a; i++)
				helper_a.push_back(this->get_first().at(i));

			sorting(helper_a);

			size_t as = helper_a.size();
			for (size_t i = 0; i < as; i++)
				a.push_back(helper_a.at(i));
		}
		
		{
			size_t s_b = this->get_second().size();
			vector<T> helper_b;
			for (size_t i = 0; i < s_b; i++)
				helper_b.push_back(this->get_second().at(i));

			sorting(helper_b);

			size_t bs = helper_b.size();
			for (size_t i = 0; i < bs; i++)
				b.push_back(helper_b.at(i));
		}

		{
			size_t as_c = this->get_third().size();
			vector<T> helper_c;
			for (size_t i = 0; i < as_c; i++)
				helper_c.push_back(this->get_third().at(i));

			sorting(helper_c);

			size_t sc = helper_c.size();
			for (size_t i = 0; i < sc; i++)
				c.push_back(helper_c.at(i));
		}

	}


public:

	SortedArray(const string& path) :Array<T>(path) 
	{
		sort();
	};

	virtual vector<T> first_array() 
	{
		return a;
	};

	virtual vector<T> second_array() 
	{
		return b;
	};

	virtual vector<T> third_array() 
	{
		return c;
	};

};


template <class T> class CrossedArray : public Array<T>
{
private:
	vector<T> a;
	vector<T> b;
	vector<T> c;


	virtual vector<T> first_array()
	{
		return a;
	}

	virtual vector<T> second_array()
	{
		return b;
	}

	virtual vector<T> third_array()
	{
		return c;
	}

	


	vector<T> two_crossing()
	{
		size_t s_a = a.size();
		size_t s_b = b.size();
		size_t s_c = c.size();
		 

		
		size_t max = 0;

		//auto min_max = minmax_element(sizes.begin(), sizes.end());

		if (s_a >= s_b && s_a >= s_c)
			max = s_a;
		if (s_b >= s_a && s_b >= s_c)
			max = s_b;
		if (s_c >= s_a && s_c >= s_b)
			max = s_c;




		for (size_t i = 0; i < s_a; i++)
		{
			for (size_t j = 0; j < s_b; j++)
			{

			}
		}
	}


	void three_crossing()
	{
		size_t s_a = a.size();
		vector<T> arr_a;
		for (size_t i = 0; i < s_a; i++)
			arr_a.push_back(a.at(i));

		size_t s_b = b.size();
		vector<T> arr_b;
		for (size_t i = 0; i < s_b; i++)
			arr_b.push_back(b.at(i));


		size_t s_c = c.size();
		vector<T> arr_c;
		for (size_t i = 0; i < s_c; i++)
			arr_c.push_back(c.at(i));

		vector<T> helper;

		for (size_t i = 0; i < s_a; i++)
		{
			for (size_t j = 0; j < s_b; j++)
			{
				if (arr_a.at(i) == arr_b.at(j))
				{
					helper.push_back(arr_a.at(i));
					arr_a.erase(arr_a.begin() + i);
					s_a = arr_a.size();
					arr_b.erase(arr_b.begin() + j);
					s_b = arr_b.size();
				}
			}
		}


		size_t s_h = helper.size();
		vector<T> helper_2;
		for (size_t i = 0; i <s_h ; i++)
		{
			for (size_t j = 0; j < s_c; j++)
			{
				if (helper.at(i) == arr_c.at(j))
				{
					helper_2.push_back(helper.at(i));
					helper.erase(helper.begin() + i);
					s_h = helper.size();
					arr_c.erase(arr_c.begin() + j);
					s_c = arr_c.size();
				}
			}
		}

		cout << endl;
		for (size_t i = 0; i < helper_2.size(); i++)
		{
			cout << helper_2[i] << " ";
		}
		cout << endl;


	}


public:
	CrossedArray(const string& path) :Array<T>(path)
	{
		{
			size_t s_a = this->get_first().size();
			for (size_t i = 0; i < s_a; i++)
				a.push_back(this->get_first().at(i));
		}

		{
			size_t s_b = this->get_second().size();
			for (size_t i = 0; i < s_b; i++)
				b.push_back(this->get_second().at(i));
		}

		{
			size_t s_c = this->get_third().size();
			for (size_t i = 0; i < s_c; i++)
				c.push_back(this->get_third().at(i));
		}


		three_crossing();

	};



	
	



};



template <class T> class UniqueReverseSortedArray : public Array<T>
{

};