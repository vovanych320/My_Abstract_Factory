#pragma once
#include "Array.h"



template<class T> class ArrayTransformer
{
public:

	virtual Array<T>* getArray(const string& path) = 0;

};



template <class T> class SortFactory :public ArrayTransformer<T>
{
public:
	virtual Array<T>* getArray(const string& path)
	{
		return new SortedArray<T>(path);
	}
};


template <class T> class CrossedFactory :public ArrayTransformer<T>
{
public:
	virtual Array<T>* getArray(const string& path)
	{
		return new CrossedArray<T>(path);
	}
};
