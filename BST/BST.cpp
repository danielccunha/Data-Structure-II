#include <algorithm>	// nothrow

// Estrutura do Nodo
struct Node
{
	int key;		// Chave
	Node *l, *r;	// Filho à esquerda, Filho à direita

	Node(int key)
	{
		this->key = key;
		l = r = nullptr;
	}
};

// Estrutura da BST
class BST
{
private:
	Node* root;	// Raiz da árvore

protected:
	Node* makeEmpty(Node* N);	// Destrói a árvore
	Node* getNewNode(int key);	// Aloca um novo Nodo
	Node* search(int key, Node* N);		// Função completa de busca
	Node* remove(int key, Node* N);		// Função completa de remoção
	void  insert(int key, Node* &N);	// Função completa de inserção
	int   minValueNode(Node* N);		// Retorna o valor do menor Nodo após a chamada

public:
	BST()  { root = nullptr; }			// Construtor
	~BST() { root = makeEmpty(root); }	// Destruidor
	Node* begin() { return root; }		// Retorna um ponteiro para a raiz da árvore
	Node* search(int key);	// Busca
	void insert(int key);	// Inserção
	void remove(int key);	// Remoção
};

// Destrói a árvore
Node* BST::makeEmpty(Node* N)
{
	if(N != nullptr)
	{
		N->l = makeEmpty(N->l);
		N->r = makeEmpty(N->r);
		delete N;
	}
	return nullptr;
}

// Aloca um novo nodo
Node* BST::getNewNode(int key)
{
	Node* tmp = new (std::nothrow) Node(key);
	return tmp;
}

// Inserção
void BST::insert(int key) { insert(key, root); }

void BST::insert(int key, Node* &N)
{
	if(N == nullptr)
		N = getNewNode(key);
	else if(key < N->key)
		insert(key, N->l);
	else if(key > N->key)
		insert(key, N->r);
}

// Busca. Retorna um ponteiro para o Nodo caso encontrado. Caso contrário retorna nullptr.
Node* BST::search(int key) {return search(key, root); }

Node* BST::search(int key, Node* N)
{
	if(N == nullptr)
		return nullptr;
	else if(key == N->key)
		return N;
	else if(key < N->key)
		return search(key, N->l);
	else
		return search(key, N->r);
}

// Retorna o valor da chave do menor Nodo da subárvore direita do Nodo atual
int BST::minValueNode(Node* N)
{
	return (N->l == nullptr) ? N->key : minValueNode(N->l);
}

// Remoção
void BST::remove(int key) { root = remove(key, root); }

Node* BST::remove(int key, Node* N)
{
	if(N == nullptr)
		return N;
	else if(key < N->key)
		N->l = remove(key, N->l);
	else if(key > N->key)
		N->r = remove(key, N->r);
	else
	{
		if(N->l == nullptr)
		{
			Node* tmp = N->r;
			delete N;
			return tmp;
		}
		else if(N->r == nullptr)
		{
			Node* tmp = N->l;
			delete N;
			return tmp;	
		}
		else
		{
			key = minValueNode(N->r);
			N->key = key;
			N->r = remove(key, N->r);
		}
	}

	return N;
}