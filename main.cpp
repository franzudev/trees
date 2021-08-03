#include <iostream>

struct Node {
	int			key;
	bool		black;
	struct Node *parent;
	struct Node *left;
	struct Node *right;

	Node(int key): key(key), black(true), parent(nullptr), left(nullptr), right(nullptr) {}

	bool 		isLeft() {return parent && this == parent->left;}
	bool 		isRight() {return parent && this == parent->right;}
	Node		*uncle() {
		if (parent->parent && parent->isLeft()) {
			return parent->parent->right;
		}
		if (parent->parent && parent->isRight()) {
			return parent->parent->left;
		}
		return nullptr;
	}
};

class Tree {
public:
	typedef	Node	node;
	typedef Node&	node_ref;
	typedef Node*	node_ptr;

	node_ptr	root;
private:

	Tree(): root(nullptr) {}
	Tree(node_ref node): root(nullptr) {(void)node;}
	Tree& operator=(node_ref node) {(void)node; return *this;}
public:
	Tree(node_ptr root): root(root) {}

	node_ptr insert(node_ptr node, node_ptr n_node) {
		if (!node || !n_node || node->key == n_node->key)
			return n_node;
		if (n_node->key < node->key){
			if (!node->left)
				return setLeftNode(node, n_node);
			return insert(node->left, n_node);
		}
		if (n_node->key > node->key){
			if (!node->right)
				return setRightNode(node, n_node);
			return insert(node->right, n_node);
		}
		return node;
	}

private:

	void	balance(node_ptr ptr) {
		if (ptr == root) {
			ptr->black = true;
			return ;
		}
		if (!ptr)
			return ;
		if (!ptr->parent->black && !ptr->black) {
			if (ptr->uncle() && !ptr->uncle()->black) {
				ptr->parent->black = true;
				ptr->uncle()->black = true;
				ptr->parent->parent->black = false;
			}
			else {
				if (ptr->isLeft() && ptr->parent->isLeft())
					rightRotate(ptr->parent, ptr->parent->parent);
				else if (ptr->isRight() && ptr->parent->isRight())
					leftRotate(ptr->parent, ptr->parent->parent);
				else if (ptr->isLeft() && ptr->parent->isRight())
					rightLeftRotate(ptr, ptr->parent, ptr->parent->parent);
				else if (ptr->isRight() && ptr->parent->isLeft())
					leftRightRotate(ptr, ptr->parent, ptr->parent->parent);
			}
		}
		balance(ptr->parent);
	}

	void	 rightRotate(node_ptr parent, node_ptr gparent) {
		node_ptr buff = parent->right;
		parent->right = gparent;
		if (gparent->parent && gparent->isLeft())
			gparent->parent->left = parent;
		else if (gparent->parent && gparent->isRight())
			gparent->parent->right = parent;
		parent->parent = gparent->parent;
		gparent->parent = parent;
		if (buff)
			buff->parent = gparent;
		gparent->left = buff;
		if (!parent->parent)
			root = parent;
		gparent->black = false;
		parent->black = true;
	}

	void	leftRotate(node_ptr parent, node_ptr gparent) {
		node_ptr buff = parent->left;
		parent->left = gparent;
		if (gparent->parent && gparent->isLeft())
			gparent->parent->left = parent;
		else if (gparent->parent && gparent->isRight())
			gparent->parent->right = parent;
		parent->parent = gparent->parent;
		gparent->parent = parent;
		if (buff)
			buff->parent = gparent;
		gparent->right = buff;
		if (!parent->parent)
			root = parent;
		gparent->black = false;
		parent->black = true;
	}

	void	leftRightRotate(node_ptr child, node_ptr parent, node_ptr gparent) {
		gparent->left = child;
		child->parent = gparent;
		if (child->left) {
			parent->right = child->left;
			child->left->parent = parent;
		} else
			parent->right = nullptr;
		child->left = parent;
		parent->parent = child;
		rightRotate(child, gparent);
	}

	void	rightLeftRotate(node_ptr child, node_ptr parent, node_ptr gparent) {
		gparent->right = child;
		child->parent = gparent;
		if (child->right){
			parent->left = child->right;
			child->right->parent = parent;
		} else
			parent->left = nullptr;
		child->right = parent;
		parent->parent = child;
		leftRotate(child, gparent);
	}

	node_ptr setLeftNode(node_ptr parent, node_ptr child) {
		parent->left = child;
		child->parent = parent;
		child->black = false;
		balance(child);
		return child;
	}

	node_ptr setRightNode(node_ptr parent, node_ptr child) {
		parent->right = child;
		child->parent = parent;
		child->black = false;
		balance(child);
		return child;
	}

	void printTreeHelper(node_ptr root, int space)
	{
		int i;
		if(root != nullptr)
		{
			space = space + 10;
			printTreeHelper(root->right, space);
			std::cout << std::endl;
			for ( i = 10; i < space; i++)
			{
				std::cout << " ";
			}
			std::string color = root->black ? "" : "\e[31m";
			std::cout << color << root->key << "\e[0m" << std::endl;
			printTreeHelper(root->left, space);
		}
	}

public:
	void printTree()
	{
		printTreeHelper(root,0);
	}

};

#include <map>

int main()
{
//	std::map<std::string, int> prova;
//	prova.insert(std::pair<std::string, int>(std::string("ciao"), 1));
//	prova.insert(std::pair<std::string, int>(std::string("prova"), 2));
//	prova.insert(std::pair<std::string, int>(std::string("prova2"), 3));
//	prova.insert(std::pair<std::string, int>(std::string("cia"), 4));
//
//	std::map<std::string, int>::iterator provaInt = prova.begin();
//	for (;provaInt != prova.end(); provaInt++)
//		std::cout << provaInt->first << " " << provaInt->second << std::endl;
//	return 0;
	Node	*root = new Node(50);
	Tree	tree = Tree(root);
	size_t nInt;

	for (int i = 0; i < 20; i++){
		nInt = rand() % 1000;
		std::cout << "inserting: " << nInt << std::endl;
		tree.insert(tree.root,  new Node(nInt));
		tree.printTree();
	}

	return 0;
}
