#include "HashNode.h"

template<typename K, typename V>
ee::HashNode<K, V>::HashNode(const K& key, const V& value, HashNode* nextNode) :
	key(key), value(value), nextNode(nextNode)
{
}


template<typename K, typename V>
ee::HashNode<K, V>::~HashNode()
{
}
