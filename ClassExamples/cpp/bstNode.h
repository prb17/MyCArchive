#ifndef BSTNODE_H
#define BSTNODE_H

template<typename T>
class Node_t
{
public:
	Node_t(T data, Node_t<T>* left, Node_t<T>* right);
	~Node_t();

	T getData() const;
	Node_t<T>* getLeft() const;
	Node_t<T>* getRight() const;

	T setData(T data);
	Node_t<T>* setLeft(Node_t<T>* ptr);
	Node_t<T>* setRight(Node_t<T>* ptr);


private:
	T data;
	Node_t<T> *left, *right;
};

//Because we are a templated class, need to include the implementation file.
//Don't need to compile bstNode.cpp
#include"bstNode.cpp"
#endif
