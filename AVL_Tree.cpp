#include<bits/stdc++.h>

using namespace std;

class avl
{
    public:
	    int val;
	    avl *left;
	    avl *right;
	    int height;
};

int height(avl *node)
{
    if (node == NULL)
        return 0;

    return node->height;
}


int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

avl* newNode(int val)
{
    avl* node = new avl();
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

int bal(avl *node)
{
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

avl *rR(avl *y)
{
    avl *x = y->left;
    avl *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    return x;
}


avl* lR(avl *x)
{
    avl *y = x->right;
    avl *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;


    return y;
}

avl* insert(avl* node, int val)
{

    if (node == NULL)
        return newNode(val);

    if (val < node->val)
        node->left = insert(node->left, val);
    else if (val > node->val)
        node->right = insert(node->right, val);
    else
        return node;

    node->height = 1 + max(height(node->left),
                        height(node->right));

    int balance = bal(node);

    if (balance > 1 && val < node->left->val)
        return rR(node);


    if (balance < -1 && val > node->right->val)
        return lR(node);

    if (balance > 1 && val > node->left->val)
    {
        node->left = lR(node->left);
        return rR(node);
    }

    if (balance < -1 && val < node->right->val)
    {
        node->right = rR(node->right);
        return lR(node);
    }

    return node;
}

avl* elements(avl* node)
    {
	if (node == NULL)
	{
		return NULL;
	}
	cout<<node->val<<" ";

	elements(node->left);
	elements(node->right);

	return NULL;

    }


avl *nodeWithMimumValue(avl *node)
{
  avl *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}


avl* deleteNode(avl *root, int val) {

  if (root == NULL)
    return root;

  if (val < root->val)
    root->left = deleteNode(root->left, val);
  else if (val > root->val)
    root->right = deleteNode(root->right, val);
  else {
    if ((root->left == NULL) || (root->right == NULL))
    {
      avl *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      }
      else
        *root = *temp;
      free(temp);
    }
    else
    {
      avl *temp = nodeWithMimumValue(root->right);
      root->val = temp->val;
      root->right = deleteNode(root->right,temp->val);
    }
  }

  if (root == NULL)
    return root;

  root->height = 1 + max(height(root->left),height(root->right));

  int balanceFactor = bal(root);

  if (balanceFactor > 1)
  {
    if (bal(root->left) >= 0)
      return rR(root);
    else
    {
      root->left = lR(root->left);
      return rR(root);
    }
  }
  if (balanceFactor < -1)
  {
    if (bal(root->right) <= 0)
      return lR(root);
    else
    {
      root->right = rR(root->right);
      return lR(root);
    }
  }
  return root;
}

avl *searchNode(avl *root,int val)
{
    if (root == NULL)
        return 0;
    if (root->val == val)
        return root;
    else if (root->val > val)
        return searchNode(root->left,val);
    else
        return searchNode(root->right,val);
}

int main()
{
    avl *root = NULL;

    while (1)
    {
        cout<<endl;
        cout<<"1. Insert number"<<endl;
        cout<<"2. Delete a Node"<<endl;
        cout<<"3. Search for a node"<<endl;
        cout<<"4. Exit"<<endl;

        int choice;
        cout<<"* Pick an option to perform : ";
        cin>>choice;

        int key;

        if (choice == 1)
        {
            cout<<"Enter value to insert : ";
            cin>>key;
            root = insert(root,key);
            cout<<"Node inserted successfully"<<endl;
        }
        else if(choice == 2)
        {
            cout<<"Enter node to delete : ";
            cin>>key;
            deleteNode(root,key);
            cout<<"Node deleted successfully."<<endl;
        }
        else if(choice == 3)
        {
            cout<<"Enter val to search : ";
            cin>>key;
            if (searchNode(root,key))
                cout<<"Node Found"<<endl;
            else
                cout<<"Node not Found"<<endl;
        }
        else
            break;

    }

    return 0;

 }
