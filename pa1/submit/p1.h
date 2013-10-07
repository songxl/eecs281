#include <string>
#include <iostream>
////08/06/2011 10:46:48
/////////////// 08/06/2011 12:03

using namespace std;

struct Tile{

	char type;
	char direction;
	bool taken;
	int index;

};
class Queue
{
    public:
    Queue(int size)
    {
        length = size;
        rout = new Tile[length];
        back = 0;
        front = 0;
        }

    ~Queue()
    {
        delete[] rout;
        }

    void enqueue(Tile item)
    {
        rout[back++] = item;
    }

    Tile *dequeue()
    {
        return &rout[front++];
    }

    bool isEmpty()
    {
        return (back == front);
    }

    private:
    int length;
    Tile *rout;
    int back,front;
};

class Dlist {
    // OVERVIEW: contains a double-ended list of Objects
 public:
    bool isEmpty();
    void insertBack(Tile *o);
    Tile *removeBack();

    Dlist();                                   // ctor
    Dlist(const Dlist &l);                     // copy ctor
    Dlist &operator=(const Dlist &l);          // assignment
    ~Dlist();                                  // dtor

 private:
    // A private type
    struct node {
	node   *next;
	node   *prev;
	Tile      *o;
    };
    node   *first; // The pointer to the first node (NULL if none)
    node   *last;  // The pointer to the last node (NULL if none)
    void makeEmpty();
    void removeAll();
    void copyAll(const Dlist &l);

};
bool Dlist::isEmpty()
{
    return ((first == NULL) && (last == NULL));
};
void Dlist::insertBack(Tile *o)
{
	node *np = new node;
	np -> o = o;
	np -> next = NULL;
	np -> prev = NULL;
	if(isEmpty()){
		last = first = np;
	}else{
		last -> next = np;
		np -> prev = last;
		last = np;
	}
};

Tile* Dlist::removeBack()
{
    try
    {
        if (isEmpty()) {Tile e; throw e;}
    }
    catch(Tile e){};///catch
    node *discard = last;
    Tile *element = discard->o;
    if(last->prev == NULL)
    {
        first = last = NULL;
    }
    else
    {
        last = discard->prev;
        last->next = NULL;
    }
    delete discard;
    return element;
};

void Dlist::makeEmpty()
{
    first = NULL;
    last = NULL;
};

void Dlist::removeAll()
{
    while (first != NULL)
    {
        node *discard = first;
        first = discard->next;
        delete discard->o;
        delete discard;
    }
        last = NULL;

};

void Dlist::copyAll(const Dlist &l)
{
    node *temp;
    temp = l.first;
    while(temp != NULL)
    {
        Tile *newo;
        newo = new Tile;
        *newo = *(temp->o);
        insertBack(newo);
        temp = temp->next;
    }
    delete temp;
}

Dlist::Dlist()
{
    makeEmpty();
};

Dlist ::Dlist(const Dlist &l)
{
    copyAll(l);
};

Dlist & Dlist::operator=(const Dlist &l)
{
	if (first == l.first)
	{return *this;}
	else{
	    removeAll();
	    copyAll(l);
	    return *this;
	    }
};

Dlist::~Dlist()
{
    removeAll();
};



class Stack
{
    public:
    Stack();
    ~Stack();
    void push(Tile stackFrame);
    Tile *pop();
    bool isEmpty();
    private:
    Dlist l;
};

Stack::Stack()
{
    Dlist();
};

Stack::~Stack()
{
    l.~Dlist();
};

void Stack::push(Tile stackFrame)
{
    Tile *o = new Tile;
    *o = stackFrame;
    l.insertBack(o);
};

Tile *Stack::pop()
{
    Tile *o;
    o = l.removeBack();
    Tile a;
    a = *o;
//    delete o;
    return o;
};

bool Stack::isEmpty()
{
    return (l.isEmpty());
};
