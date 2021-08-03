#include <iostream>

enum nodeColor {
	RED,
	BLACK
};

template <class T>
struct Node {
	T			key;
	bool		color;
	struct Node *parent;
	struct Node *left;
	struct Node *right;

	Node(T key): key(key), color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}

	bool 		isLeft() {return parent && this == parent->left;}
	bool 		isRight() {return parent && this == parent->right;}
	Node		*uncle() {
		if (parent->parent && parent->isLeft())
			return parent->parent->right;
		if (parent->parent && parent->isRight())
			return parent->parent->left;
		return nullptr;
	}
};

template <class T>
class Tree {
public:
	typedef	Node<T>	node;
	typedef node*	node_ptr;

	node_ptr	root;
private:
	Tree(node_ptr root): root(root) {}
	Tree(node& node): root(nullptr) {(void)node;}
	Tree& operator=(node& node) {(void)node; return *this;}
public:
	Tree(): root(nullptr) {}

	node_ptr insert(T val) {
		if (!root)
			return root = new node(val);
		return _insert(root, val);
	}

	node_ptr find(T val) {
		return _find(root, val);
	}

	node_ptr deletion(T val) {
		node_ptr toDelete = find(root, val);
		if (!toDelete)
			return nullptr;
		//case root
		if (!toDelete->parent) {}
		//case leaf
		if (toDelete->parent && !toDelete->left && !toDelete->right) {

		}
		// case inside
		if (toDelete->parent) {}

	}

	void printTree()
	{
		printTreeHelper(root,0);
	}

private:

	node_ptr _insert(node_ptr start, T val) {
		if (start->key == val)
			return start;
		if (val < start->key){
			if (!start->left)
				return setLeftNode(start, new node(val));
			return _insert(start->left, val);
		}
		if (val > start->key){
			if (!start->right)
				return setRightNode(start, new node(val));
			return _insert(start->right, val);
		}
		return start;
	}

	node_ptr _find(node_ptr node, T val) {
		if (!node)
			return nullptr;
		if (node->key == val)
			return node;
		if (val > node->key)
			return _find(node->right, val);
		if (val < node->key)
			return _find(node->left, val);
		return node;
	}

	void	balance(node_ptr ptr) {
		if (ptr == root) {
			ptr->color = BLACK;
			return ;
		}
		if (!ptr)
			return ;
		if (!ptr->parent->color && !ptr->color) {
			if (ptr->uncle() && !ptr->uncle()->color) {
				ptr->parent->color = BLACK;
				ptr->uncle()->color = BLACK;
				ptr->parent->parent->color = RED;
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
		gparent->color = RED;
		parent->color = BLACK;
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
		gparent->color = RED;
		parent->color = BLACK;
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

	node_ptr setNode(node_ptr parent, node_ptr child) {
		child->parent = parent;
		child->color = RED;
		balance(child);
		return child;
	}

	node_ptr setLeftNode(node_ptr parent, node_ptr child) {
		parent->left = child;
		return setNode(parent, child);
	}

	node_ptr setRightNode(node_ptr parent, node_ptr child) {
		parent->right = child;
		return setNode(parent, child);
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
			std::string color = root->color ? "" : "\e[31m";
			std::cout << color << root->key << "\e[0m" << std::endl;
			printTreeHelper(root->left, space);
		}
	}
};

#include <map>

int main()
{
	Tree<int>	tree;
	size_t nInt;

	tree.insert(1);
	tree.insert(0);

	for (int i = 0; i < 20; i++){
		nInt = rand() % 1000;
		std::cout << "inserting: " << nInt << std::endl;
		tree.insert(nInt);
	}
	tree.printTree();
	Node<int> *find = tree.find(0);

	return 0;
}
