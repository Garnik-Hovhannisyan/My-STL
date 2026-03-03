#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Vector.h"
#include "List.h"


template <typename K, typename V>
class HashTable
{
protected:
	struct Pair
	{
		K key;
		V value;

		Pair(const K& k, const V& v) : key(k), value(v) {}
	};

private:
	Vector<List<Pair>> m_bucket;
	size_t m_size;

	size_t hashFunction(const K& key) const
	{
		return std::hash<K>()(key) % m_bucket.size();
	}

public:
	HashTable(size_t bucketCount) : m_bucket(bucketCount), m_size(0) {}

	void insert(const K& key, const V& value)
	{
		size_t index = hashFunction(key);
		auto& list = m_bucket[index];
		
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (it->key == key)
			{
				it->value = value;
				return;
			}
		}

		list.push_back(Pair(key, value));
		m_size++;
	}

	bool find(const K& key, V& value) const
	{
		size_t index = hashFunction(key);
		auto& list = m_bucket[index];

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (it->key == key)
			{
				value = it->value;
				return true;
			}
		}
		return false;
	}

	bool erase(const K& key)
	{
		size_t index = hashFunction(key);
		auto& list = m_bucket[index];

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if (it->key == key)
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

public:
	size_t size() const { return m_size; }
	bool empty() const { return m_size == 0; }

	V* get_ptr(const K& key)
	{
		size_t index = hashFunction(key);
		auto& list = m_bucket[index];

		for (auto it = list.begin(); it != list.end(); ++it) 
		{
			if (it->key == key) 
			{
				return &(it->value); 
			}
		}
		return nullptr;
	}
};

#endif // HASHTABLE_H