#include <algorithm>	// nothrow, max

// Estrutura do Nodo
struct Node
{
	int key;		// Chave
	int height;		// Altura
	Node *l, *r;	// Filho esquerdo e filho direito

	Node(int key)
	{
		this->key = key;
		height = 1;
		l = r = nullptr;
	}
};

// Estrutura da AVL
class AVL
{
private:
	Node* root;

protected:
	Node* makeEmpty(Node* root);	// Função que destroí a árvore
	Node* getNewNode(int key);		// Aloca um novo Nodo
	Node* rotateLeft(Node* N);		// Rotação à esquerda
	Node* rotateRight(Node* N);		// Rotação à direita
	Node* search(int key, Node* N);	// Busca
	Node* insert(int key, Node* N);	// Inserção
	Node* remove(int key, Node* N);	// Remoção
	int   minValueNode(Node *N);	// Retorna o valor do menor Nodo após a chamada
	int   height(Node* N);			// Retorna a altura do Nodo
	int   getBalance(Node* N);		// Retorna o FB do Nodo

public:
	AVL()  { root = nullptr; }			// Construtor
	~AVL() { root = makeEmpty(root); }	// Destruidor
	Node* begin() { return root; }		// Retorna um ponteiro para a raiz da árvore
	Node* search(int key);	// Busca
	void  insert(int key);	// Inserção
	void  remove(int key);	// Remoção
};

// Destrói a árvore liberando todos os nodos
Node* AVL::makeEmpty(Node* root)
{
    if(root != nullptr)
    {
        root->l = makeEmpty(root->l);
        root->r = makeEmpty(root->r);
        delete root;
    }
    return nullptr;
}

// Aloca um novo nodo
Node* AVL::getNewNode(int key)
{
	Node* tmp = new (std::nothrow) Node(key);
	return tmp;
}

// Busca. Retorna um ponteiro para o Nodo caso encontrado. Caso contrário retorna nullptr.
Node* AVL::search(int key) { return search(key, root); }

Node* AVL::search(int key, Node* N)
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

// Retorna a altura do Nodo
int AVL::height(Node* N) { return (N == nullptr) ? 0 : N->height; }

// Retorna o FB do Nodo
int AVL::getBalance(Node* N) { return (N == nullptr) ? 0 : (height(N->l) - height(N->r)); }

Node* AVL::rotateLeft(Node* N)
{
	Node* r = N->r;		// Filho à direita de N
	Node* r_l = r->l;	// Filho à esquerda de r

	// Realiza a rotação
	r->l = N;
	N->r = r_l;

	// Atualiza as alturas
	N->height = 1 + std::max(height(N->l), height(N->r));
	r->height = 1 + std::max(height(r->l), height(r->r));

	return r;
}

Node* AVL::rotateRight(Node* N)
{
	Node* l = N->l;		// Filho à esquerda de N
	Node* l_r = l->r;	// Filho à direita de l

	// Realiza a rotação
	l->r = N;
	N->l = l_r;

	// Atualiza as alturas
	N->height = 1 + std::max(height(N->l), height(N->r));
	l->height = 1 + std::max(height(l->l), height(l->r));

	return l;
}

// Inserção
void AVL::insert(int key) { root = insert(key, root); }

Node* AVL::insert(int key, Node* N)
{
	// Insere o Nodo
	if(N == nullptr)
		return getNewNode(key);

	if(key < N->key)
		N->l = insert(key, N->l);
	else if(key > N->key)
		N->r = insert(key, N->r);
	// Encontrou a chave. Nessa implementação não será permitida valores repetidos
	else
		return N;

	// Atualiza sua altura
	N->height = 1 + std::max(height(N->l), height(N->r));

	// Calcula o FB
	int FB = getBalance(N);

	// Rotação simples à direita
	if(FB >  1 && key < N->l->key)	// Left Left
		return rotateRight(N);

	// Rotação simples à esquerda
	if(FB < -1 && key > N->r->key)	// Right Right
		return rotateLeft(N);

	// Rotação dupla à direita
	if(FB >  1 && key > N->l->key)	// Left Right
	{
		N->l = rotateLeft(N->l);
		return rotateRight(N);
	}

	// Rotação dupla à esquerda
	if(FB < -1 && key < N->r->key)	// Right Left
	{
		N->r = rotateRight(N->r);
		return rotateLeft(N);
	}

	// Caso não ocorra nenhum alteração, retorna-se o nodo
	return N;
}

// Retorna o valor do menor Nodo após a chamada
int AVL::minValueNode(Node* N) { return (N->l == nullptr) ? N->key : minValueNode(N->l); }

// Remoção
void AVL::remove(int key) { root = remove(key, root); }

Node* AVL::remove(int key, Node* N)
{
	// Realiza a remoção
	if(N == nullptr)
		return N;

	if(key < N->key)
		N->l = remove(key, N->l);
	else if(key > N->key)
		N->r = remove(key, N->r);
	else
	{
		if(N->l == nullptr || N->r == nullptr)
		{
			// Caso N->l != null, tmp = N->l, caso contrário, tmp = N->r
			Node* tmp = (N->l) ? N->l : N->r;

			// Caso ambos sejam nullptr
			if(tmp == nullptr)
			{
				tmp = N;
				N = nullptr;
			}
			else
				*N = *tmp;

			delete tmp;
		}
		// Possui dois filhos
		else
		{
			key = minValueNode(N->r);
			N->key = key;
			N->r = remove(key, N->r);
		}
	}

		// Caso o nodo fosse folha, finaliza a função
		if(N == nullptr) return N;

		// Atualiza a altura do Nodo
		N->height = 1 + std::max(height(N->l), height(N->r));

		// Calcula o FB
		int FB = getBalance(N);

		// Realiza as rotações caso tenha se tornado desbalanceado
		// Rotação simples à direita
		if(FB > 1  && getBalance(N->l) >= 0) // Left Left
			return rotateRight(N);

		// Rotação dupla à direita
		if(FB > 1  && getBalance(N->l) <  0) // Left Right
		{
		 	N->l = rotateLeft(N->l);
			return rotateRight(N);
		}

		// Rotação simples à esquerda
		if(FB < -1 && getBalance(N->r) >= 0) // Right Right
		 	return rotateLeft(N);

		// Rotação dupla à esquerda
		if(FB < -1 && getBalance(N->r) <  0) // Right Left
		{
			N->r = rotateRight(N->r);
		 	return rotateLeft(N);
		}

	// Caso não houve desbalanceamento, simplesmente retorna o Nodo
	return N;
}