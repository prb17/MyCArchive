#ifndef BSTNODE_CPP
#define BSTNODE_CPP

template<typename T>
Node_t<T>::Node_t(T data, Node_t<T>* left, Node_t<T>* right)
: data(data), left(left), right(right)
{}

template<typename T>
Node_t<T>::~Node_t()
{}


template<typename T>
T Node_t<T>::getData() const
{
	return data;
}

template<typename T>
Node_t<T>* Node_t<T>::getLeft() const
{
	return left;
}

template<typename T>
Node_t<T>* Node_t<T>::getRight() const
{
	return right;
}

template<typename T>
T Node_t<T>::setData(T data)
{
	return this->data = data;
}

template<typename T>
Node_t<T>* Node_t<T>::setLeft( Node_t<T>* ptr)
{
	return left = ptr;
}

template<typename T>
Node_t<T>* Node_t<T>::setRight( Node_t<T>* ptr)
{
	return right = ptr;
}

#endif
