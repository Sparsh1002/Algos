#include<bits/stdc++.h>

using namespace std;

struct Node
{
	int data, degree;
	Node *child, *sibling, *parent;
};

class BHeap
{
    list<Node*> heap;
    public:

    Node *newNode(int key)
    {
        Node *temp = new Node;
        temp->data = key;
        temp->degree = 0;
        temp->child = temp->parent = temp->sibling = NULL;
        return temp;
    }


    Node *mergeBTrees(Node *b1, Node *b2)
    {

        if (b1->data > b2->data)
            swap(b1, b2);


        b2->parent = b1;
        b2->sibling = b1->child;
        b1->child = b2;
        b1->degree++;

        return b1;
    }


    list<Node *> Union(list<Node *> &h1,
                                    list<Node *> &h2)
    {

        list<Node *> _new;
        list<Node *>::iterator it = h1.begin();
        list<Node *>::iterator ot = h2.begin();
        while (it != h1.end() && ot != h2.end())
        {
            if ((*it)->degree <= (*ot)->degree)
            {
                _new.push_back(*it);
                it++;
            }

            else
            {
                _new.push_back(*ot);
                ot++;
            }
        }

        while (it != h1.end())
        {
            _new.push_back(*it);
            it++;
        }

        while (ot != h2.end())
        {
            _new.push_back(*ot);
            ot++;
        }
        return _new;
    }


    void adjust()
    {
        if (heap.size() <= 1)
            return ;
        list<Node *> newheap;
        list<Node *>::iterator it1, it2, it3;
        it1 = it2 = it3 = heap.begin();

        if (heap.size() == 2)
        {
            it2 = it1;
            it2++;
            it3 = heap.end();
        }
        else
        {
            it2++;
            it3 = it2;
            it3++;
        }
        while (it1 != heap.end())
        {
            if (it2 == heap.end())
                it1++;

            else if ((*it1)->degree < (*it2)->degree)
            {
                it1++;
                it2++;
                if (it3 != heap.end())
                    it3++;
            }
            else if (it3 != heap.end() &&
                     (*it1)->degree == (*it2)->degree &&
                     (*it1)->degree == (*it3)->degree)
            {
                it1++;
                it2++;
                it3++;
            }

            else if ((*it1)->degree == (*it2)->degree)
            {
                Node *temp;
                *it1 = mergeBTrees(*it1, *it2);
                it2 = heap.erase(it2);
                if (it3 != heap.end())
                    it3++;
            }
        }
    }


    void insertTree(Node *tree)
    {

        list<Node *> temp;

        temp.push_back(tree);


        heap = Union(heap, temp);

        adjust();
    }


    void insert(int key)
    {
        Node *temp = newNode(key);
        insertTree(temp);
    }

    list<Node *> removeMinTree(Node *tree)
    {
        list<Node *> _heap;
        Node *temp = tree->child;
        Node *lo;


        while (temp)
        {
            lo = temp;
            temp = temp->sibling;
            lo->sibling = NULL;
            _heap.push_front(lo);
        }
        return _heap;
    }


    Node *getMin()
    {
        list<Node *>::iterator it = heap.begin();
        Node *temp = *it;
        while (it != heap.end())
        {
            if ((*it)->data < temp->data)
                temp = *it;
            it++;
        }
        return temp;
    }

    void extractMin()
    {
        list<Node *> newheap, lo;
        Node *temp;


        temp = getMin();
        list<Node *>::iterator it;
        it = heap.begin();
        while (it != heap.end())
        {
            if (*it != temp)
            {

                newheap.push_back(*it);
            }
            it++;
        }
        lo = removeMinTree(temp);
        heap = Union(newheap, lo);
        adjust();
    }

    // Function to search for an element
    Node * findNode(Node * it, int val)
    {
        if (it == NULL)
            return NULL;


        if (it->data == val)
            return it;


        Node *res = findNode(it->child, val);
        if (res != NULL)
            return res;

        return findNode(it->sibling, val);
    }


    void decreaseKey( int old_val,
                          int new_val)
    {
        list<Node *>::iterator it=heap.begin();
        Node *node = NULL;
        while (it != heap.end() && node == NULL)
        {
            node = findNode(*it, old_val);
            it++;
        }

        if (node == NULL)
            return;


        node->data = new_val;
        Node *parent = node->parent;

        while (parent != NULL && node->data < parent->data)
        {
            swap(node->data, parent->data);
            node = parent;
            parent = parent->parent;
        }
    }

    void Delete(int val)
    {
        decreaseKey(val, INT_MIN);

        extractMin();
    }

};

int main()
{
    int c,key;
    BHeap bh;
    while (1)
    {
        cout<<"1)Insert Element in the heap"<<endl;
        cout<<"2)Delete a node"<<endl;
        cout<<"3)Exit"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>c;
        switch(c)
        {
        case 1:
            cout<<"Enter the element to be inserted: ";
            cin>>key;
            bh.insert(key);
            cout << "Element inserted successfully." << endl;
            break;
        case 2:
            cout<<"Enter the key to be deleted: ";
            cin>>key;
            bh.Delete(key);
            cout << "Element deleted successfully." << endl;
            break;
        case 3:
            exit(1);

	  }
	  cout << endl;
    }
    return 0;
}
