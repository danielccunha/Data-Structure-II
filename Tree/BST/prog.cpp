// Programa criado apenas para validar a BST
#include "BST.cpp"
#include <cassert>

int main()
{
	BST t;
/*
          50
       /     \
      30      70
     /  \    /  \
   20   40  60   80 
*/
	t.insert(50);
	t.insert(30);
	t.insert(20);
	t.insert(40);
	t.insert(70);
	t.insert(60);
	t.insert(80);

	auto root = t.begin();

	assert(t.search(50));
	assert(t.search(30));
	assert(t.search(20));
	assert(t.search(40));
	assert(t.search(70));
	assert(t.search(60));
	assert(t.search(80));
	assert(root->key == 50);
	assert(root->l->key == 30);
	assert(root->r->key == 70);

	// Remove Nodo folha
	t.remove(20);
	assert(!t.search(20));
	assert(root->l->l == nullptr);

	// Remove Nodo com um filho
	t.remove(30);
	assert(!t.search(30));
	assert(t.search(40));
	assert(root->l->key == 40);
	assert(root->l->r == nullptr);

	// Remove Nodo com dois filhos
	t.remove(50);
	assert(!t.search(50));
	assert(t.search(60));
	assert(root->key == 60);
	assert(root->r->l == nullptr);

	return 0;
}