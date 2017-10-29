#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

template<class T>
class Queue{
public:
	Queue();
	~Queue();
	void enter_queue(T t);
	bool is_empty();
	T de_queue();
	T gettop();
private:
	class Node{
	public:
		T elem;
		Node * prev;
		Node * next;
	} *head;

};
template<class T>
Queue<T>::Queue(){
	head = new Node;
	head->next = head;
	head->prev = head;
}

#if 0
Queue& operator=(Queue q){
	;//TODO
}
#endif

template<class T>
Queue<T>::~Queue(){
	Node *t = head->prev;
	while(t != head){
		t = t->prev;
		delete t->next;
	}
	delete head;
}

template<class T>
T Queue<T>::de_queue(){
	T t=head->prev->elem;
	Node *n = head->prev;
	head->prev = n->prev;
	head->prev->next = n->next;
	delete n;
	return t;
}

template<class T>
void Queue<T>::enter_queue(T t){
	Node *n =new Node;
	n->elem = t;
	Node *tail = head->next;
	head->next = n;
	n->prev = head;
	n->next = tail;
	tail->prev = n;
}

template<class T>
T Queue<T>::gettop(){
	return head->prev->elem;
}

template<class T>
bool Queue<T>::is_empty(){
	return (head->prev == head);
}
#endif
