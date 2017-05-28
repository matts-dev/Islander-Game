#pragma once
#include<memory>
namespace ee {
	/**
	*	Essentially a singly linked list of nodes that can intelligently remove nodes from list.
	*	Data structure used to populate the hash buckets.
	*/
	template<typename K, typename V>
	class HashNode final
	{
	public:
		const K& key;
		const V& value;
	private:
		std::shared_ptr<HashNode> nextNode;

	public:
		HashNode(const K& key, const V& value, HashNode* nextNode);
		~HashNode();

	public:
		void setNextNode(std::shared_ptr<HashNode> nextNode) { this->nextNode = nextNode; };
		std::shared_ptr<HashNode> getNextNode() { return nextNode; };
	};
}
