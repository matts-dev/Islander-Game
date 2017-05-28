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
		void addNode(std::shared_ptr<HashNode<K, V>> newNode);
		void removeChild(std::shared_ptr < HashNode<K, V> > nodeToRemove);
	};

	//-------------------------------------------DEFINITIONS-----------------------------------------------
	//(https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file)

		//ctor
	template<typename K, typename V>
	inline ee::HashNode<K, V>::HashNode(const K& key, const V& value, HashNode* nextNode) :
		key(key), value(value), nextNode(nextNode)
	{
	}

	//dtor
	template<typename K, typename V>
	inline ee::HashNode<K, V>::~HashNode()
	{
	}

	//add new node to end of list
	template<typename K, typename V>
	inline void HashNode<K, V>::addNode(std::shared_ptr<HashNode> newNode)
	{
		//if there is a next node, recursively add it
		if (nextNode) {
			nextNode->addNode(newNode);
		}
		//next node is null, just add the new node! 
		else {
			nextNode = newNode;
		}
	}

	//Remove a child node if it exists
	template<typename K, typename V>
	inline void HashNode<K, V>::removeChild(std::shared_ptr<HashNode<K, V>> nodeToRemove)
	{
		if (nextNode == nodeToRemove) {
			nextNode = nodeToRemove->nextNode;
		}
		else if (nextNode != nullptr) {
			nextNode->removeChild(nodeToRemove);
		}
	}

}
