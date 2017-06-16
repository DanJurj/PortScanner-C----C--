#pragma once
#include"Exception.h"
template<class T>
class Coada
{
	T elem;
	Coada<T>*next;
public:
	Coada();
	void addElem(T &p);
	T &getElem();
	void setNext(Coada<T>*next);
	void addNext(T &elem);
	Coada<T> *getNext();
	void destroy();
	void afisare();
	int get_lenght();
	~Coada();
};
template<class T>
Coada<T>::Coada()
{
	next=NULL;
};
template<class T>
void Coada<T>::addElem(T &p)
{
	elem=p;
};
template<class T>
T& Coada<T>::getElem()
{
	return elem;
};
template<class T>
void Coada<T>::setNext(Coada<T> *next)
{
	this->next=next;
};
template<class T>
void Coada<T>::addNext(T &elem)
{
	Coada<T> *p=this;
	Coada<T> *q=new Coada<T>;
	q->addElem(elem);

	while(p->next)
		p=p->getNext();
	p->setNext(q);
};
template<class T>
Coada<T>* Coada<T>::getNext()
{
	return next;
};
template<class T>
void Coada<T>::destroy()
{
	Coada<T> *p=this,*q;
	while(p)
	{
		q=p;
		p=p->getNext();
		delete q;
	}
};
template<class T>
void Coada<T>::afisare()
{
	Coada<T> *p=this;
	while(p)
	{
		cout<<p->getElem()<<" ";
		p=p->getNext();
	}
};
template<class T>
int Coada<T>::get_lenght()
{
	int i=1;
	for(Coada<T> *aux=next;aux;aux=aux->getNext())
		i++;
	return i;
}
template<class T>
Coada<T>::~Coada()
{
	
};
