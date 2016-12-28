#pragma once
#include <string>
#include <memory>

using namespace std;

class CStringList
{
	struct Node
	{
		Node(const string & data, Node * prev, unique_ptr<Node> && next)
			: data(data), prev(prev), next(move(next))
		{
		}
		string data;
		Node *prev;
		unique_ptr<Node> next;
	};

public:
	CStringList() = default;
	~CStringList();

	void Append(const string & data);
	void PushFront(const string & data);

	size_t GetSize()const;
	bool IsEmpty() const;

	void Clear();

	class CIterator
	{
		friend CStringList;
		CIterator(Node *node, bool isReverse);
		public:
			CIterator() = default;
			string & operator*()const;
			CIterator & operator++();
			Node * operator->()const;

			bool operator==(CIterator const & other) const;
			bool operator!=(CIterator const & other) const;
			bool m_isReverse = false;
		private:
			Node *m_node = nullptr;
	};

	void Insert(const CIterator & it, const string & data);
	void Erase(const CIterator & it);

	CIterator begin();
	CIterator end();
	CIterator const cbegin() const;
	CIterator const cend() const;

	string & GetBackElement();
	string const& GetBackElement()const;
	string & GetFrontElement();
	string const& GetFrontElement()const;

	CIterator rbegin();
	CIterator rend();
	CIterator const crbegin() const;
	CIterator const crend() const;
private:
	size_t m_size = 0;
	unique_ptr<Node> m_firstNode;
	Node * m_lastNode = nullptr;
};