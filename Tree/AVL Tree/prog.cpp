// Programa criado apenas para validar a AVL
#include "AVL.cpp"
#include <cassert>

int main()
{
	AVL t;

	t.insert(10);
	t.insert(20);
	t.insert(30);
	t.insert(40);
	t.insert(50);
	t.insert(60);
	t.insert(11);
	t.insert(17);
	t.insert(18);
	t.insert(26);
	t.insert(24);
	t.insert(39);
	t.insert(44);
	t.insert(66);
	t.insert(98);
	t.insert(6);
	t.insert(55);
	t.insert(36);
	
	auto root = t.begin();

	assert(t.search(10));
	assert(t.search(20));
	assert(t.search(30));
	assert(t.search(40));
	assert(t.search(50));
	assert(t.search(60));
	assert(t.search(11));
	assert(t.search(17));
	assert(t.search(18));
	assert(t.search(26));
	assert(t.search(24));
	assert(t.search(39));
	assert(t.search(44));
	assert(t.search(66));
	assert(t.search(98));
	assert(t.search(6));
	assert(t.search(55));
	assert(t.search(36));
	assert(root->key == 20);
	assert(root->l->key == 17);
	assert(root->l->r->key == 18);
	assert(root->r->key == 40);
	assert(root->r->l->key == 26);
	assert(root->r->r->key == 60);

	t.remove(6);
	t.remove(11);
	t.remove(20);
	t.remove(60);
	root = t.begin();

	assert(t.search(10));
	assert(!t.search(20));
	assert(t.search(30));
	assert(t.search(40));
	assert(t.search(50));
	assert(!t.search(60));
	assert(!t.search(11));
	assert(t.search(17));
	assert(t.search(18));
	assert(t.search(26));
	assert(t.search(24));
	assert(t.search(39));
	assert(t.search(44));
	assert(t.search(66));
	assert(t.search(98));
	assert(!t.search(6));
	assert(t.search(55));
	assert(t.search(36));
	assert(root->key == 40);
	assert(root->l->key == 24);
	assert(root->l->r->key == 36);
	assert(root->r->key == 66);
	assert(root->r->l->key == 50);
	assert(root->r->r->key == 98);

	t.remove(40);
	t.remove(44);
	t.remove(55);
	root = t.begin();

	assert(t.search(10));
	assert(t.search(30));
	assert(!t.search(40));
	assert(t.search(50));
	assert(t.search(17));
	assert(t.search(18));
	assert(t.search(26));
	assert(t.search(24));
	assert(t.search(39));
	assert(!t.search(44));
	assert(t.search(66));
	assert(t.search(98));
	assert(!t.search(55));
	assert(t.search(36));
	assert(root->key == 36);
	assert(root->l->key == 24);
	assert(root->l->r->key == 26);
	assert(root->r->key == 50);
	assert(root->r->l->key == 39);
	assert(root->r->r->key == 66);

	return 0;
}
