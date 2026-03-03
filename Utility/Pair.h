#ifndef PAIR_H
#define PAIR_H

template <typename T1, typename T2>
class Pair
{
public:
	T1 first;
	T2 second;

	Pair() = default;

	Pair(const T1& firstValue, const T2& secondValue) : first(firstValue), second(secondValue) {}

	Pair(const Pair& other) : first(other.first), second(other.second) {}

	Pair& operator=(const Pair& other)
	{
		if (this != &other)
		{
			first = other.first;
			second = other.second;
		}
		return *this;
	}

	~Pair() = default;

	T1 getFirst() const { return first; }
	T2 getSecond() const { return second; }

	bool operator < (const Pair& other) const { return first < other.first; };
	bool operator > (const Pair& other) const { return first > other.first; };
	bool operator == (const Pair& other) const { return first == other.first; };
	bool operator != (const Pair& other) const { return first != other.first; };
};

#endif // PAIR_H