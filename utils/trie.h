#ifndef _BDTAUNU_TRIE_H_
#define _BDTAUNU_TRIE_H_

// -------------------------------------------------------------------------
// A custom trie class template. 
//
// This trie stores keys as null terminated strings formed from an 
// alphabet. The value associated with the key is stored with the 
// null character node. 
//
// Usage: 
//
// Code:
// trie<int, int, -1, -1> t;
// t.insert({1, 1, 2, -1}, 112);
// std::cout << t.find({1, 1, 2, -1}) << std::endl;
// std::cout << t.find({1, 1, 3, -1}) << std::endl;
// 
// Output: 
// 112
// -1
//
// Template paratemers:
// A: Type of the Alphabet that makes up the key. 
// V: Type of the Value. 
// nullA: Null character indicating the end of the key. 
// nullV: Null value that is returned when key isn't found. 
//
// -------------------------------------------------------------------------

#include <vector>
#include <algorithm>

template<typename A, typename V,
         A nullA, V nullV>
class trie {

  private:
    struct node {
      A a;
      V v;
      std::vector<node*> links;

      node() : a(A()), v(V()) {};
      node(A a, V v = nullV) : a(a), v(v) {};
      ~node() { for (auto l : links) delete l; }
    };
    node *root;
    node *CopyNode(const node*);

  // API
  public:
    trie() { root = new node; }
    ~trie() { delete root; }
    trie(const trie &t) { root = CopyNode(t.root); }
    trie &operator=(const trie&);

    // Insert key into the trie with value v.
    void insert(std::vector<A> key, V v);

    // Find key and return its value. Returns nullV if not found.
    V find(std::vector<A> key) const;
};


// Makes a deep copy of a node pointed by t. 
// Returns a pointer to the copy. 
template<typename A, typename V,
         A nullA, V nullV>
typename trie<A, V, nullA, nullV>::node*
trie<A, V, nullA, nullV>::CopyNode(const node *t) {
  node *n = new node(t->a, t->v);
  for (auto l : t->links) (n->links).push_back(CopyNode(l));
  return n;
}

template<typename A, typename V,
         A nullA, V nullV>
trie<A, V, nullA, nullV>&
trie<A, V, nullA, nullV>::operator=(const trie &target) {
  if (this != &target) {
    delete root;
    root = CopyNode(target.root);
  }
  return *this;
}


template<typename A, typename V,
         A nullA, V nullV>
void trie<A, V, nullA, nullV>::insert(
    std::vector<A> key, V v) {
  node *p = root;
  for (auto a : key) {
    auto e_it = find_if((p->links).begin(), (p->links).end(), 
              [a] (const node *n) { return (n->a == a); });

    if (e_it == (p->links).end()) {
      node *n = new node(a);
      if (a == nullA) n->v = v;
      (p->links).push_back(n);
      p = n;
    } else {
      p = *e_it;
    }
  }
}


template<typename A, typename V,
         A nullA, V nullV>
V trie<A, V, nullA, nullV>::find(
    std::vector<A> key) const { 
  node *p = root;
  for (auto a : key) {
    auto e_it = find_if((p->links).begin(), (p->links).end(), 
              [a] (const node *n) { return (n->a == a); });
    if (e_it == (p->links.end())) return nullV; 
    p = *e_it;
  }
  return p->v;
}

#endif
