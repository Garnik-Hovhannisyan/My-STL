#ifndef MAP_H
#define MAP_H

#include "Pair.h"

template <typename K, typename V>
class Map
{
private:
	struct Node
	{
		Pair<K, V> m_data;
		Node* left;
		Node* right;

		Node(const K& key, const V& value) : m_data(key, value), left(nullptr), right(nullptr) {}
	};

	Node* root;

	Node* recurse_insert(Node* node, const K& key, const V& value)
	{
		if (node == nullptr)
		{
			return new Node(key, value);
		}

		if (key < node->m_data.first)
		{
			node->left = recurse_insert(node->left, key, value);
		}
		else if (key > node->m_data.first)
		{
			node->right = recurse_insert(node->right, key, value);
		}
		else
		{
			node->m_data.second = value;
		}

		return node;
	}

	void clear(Node* node)
	{
		if (node != nullptr)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

public:
	Map() : root(nullptr) {}
	~Map() : { clear(root); }

	Map(const Map& other) = delete;
	Map& operator=(const Map& other) = delete;

	void insert(const K& key, const V& value)
	{
		root = recurse_insert(root, key, value);
	}

	V* find(const K& key) const 
	{
		Node* curr = root;

		while (curr)
		{
			if (key < curr->m_data.first) curr = curr->left;
			else if (key > curr->m_data.first) curr = curr->right;
			else return &(curr->m_data.second);
		}

		return nullptr;
	}

	V& operator [](const K& key)
	{
		V* val = find(key);
		if (val) return *val;

		insert(key, V());
		return *find(key);
	}
};

#endif // MAP_H