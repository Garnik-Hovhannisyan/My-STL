#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include "HashTable.h"

template <typename K, typename V>
class Unordered_Map
{
private:
	HashTable<K, V> m_table;

public:
	Unordered_Map(size_t bucketCount) : m_table(bucketCount) {}

	void insert(const K& key, const V& value)
	{
		m_table.insert(key, value);
	}

	bool erase(const K& key)
	{
		return m_table.erase(key);
	}

	V& operator[](const K& key)
	{
		V* ptr = m_table.get_ptr(key);

		if (ptr) return *ptr;

		m_table.insert(key, V());
		return *(m_table.get_ptr(key));
	}

	size_t size() const
	{
		return m_table.size();
	}

	bool empty() const
	{
		return m_table.empty();
	}
};

#endif // UNORDERED_MAP_H