#include "Array.h"
#include "ArrayTransformer.h"

int main()
{
	string path = "C:\\arr.txt";
    

	/*{
		ArrayTransformer<double>* sort_factory = new SortFactory<double>();

		Array<double>* sorted = sort_factory->getArray(path);


		sorted->print();

		size_t s = sorted->first_array().size();
		cout << endl << endl;
		for (size_t i = 0; i < s; i++)
			cout << sorted->first_array().at(i) << " ";

		size_t a = sorted->second_array().size();
		cout << endl;
		for (size_t i = 0; i < a; i++)
			cout << sorted->second_array().at(i) << " ";

		size_t b = sorted->third_array().size();
		cout << endl;
		for (size_t i = 0; i < b; i++)
			cout << sorted->third_array().at(i) << " ";
	}*/

	ArrayTransformer<double>* crossed = new CrossedFactory<double>();
	Array<double>* cross = crossed->getArray(path);

	cross->print();


	return 1;
}