#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include "Vector.h"
#include "List.h"

template <typename T>
class Unordered_Set
{

private:
	Vector<List<T>> m_bucket;
	size_t m_size;

	size_t hashFunction(const T& val) const
	{
		return std::hash<T>()(val) % m_bucket.size();
	}

public:
	Unordered_Set(size_t bucketCount) : m_bucket(bucketCount), m_size(0) {}

	void insert(const T& val)
	{
		size_t index = hashFunction(val);
		auto& list = m_bucket[index];

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (*it == val) return;
		}

		list.push_back(val);
		m_size++;
	}

	bool find(const T& val) const
	{
		size_t index = hashFunction(val);
		auto& list = m_bucket[index];

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (*it == val) return true;
		}
		return false;
	}

	bool erase(const T& val)
	{
		size_t index = hashFunction(val);
		auto& list = m_bucket[index];

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (*it == val)
			{
				if (list.erase(it))
				{
					m_size--;
					return true;
				}
				return false;
			}
		}
		return false;
	}

	T* get_ptr(const T& val)
	{
		size_t index = hashFunction(val);
		auto& list = m_bucket[index];

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (*it == val)
			{
				return &(*it);
			}
		}
		return nullptr;
	}

	size_t size() const { return m_size; }
	bool empty() const { return m_size == 0; }
};

#endif // UNORDERED_SET_H