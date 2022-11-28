#include <iostream>
#include <cstdlib>
#define T_S 5
using namespace std;
enum EntryType {Legi, Emp};
struct HashTableEntry {
   int e;
   enum EntryType info;
};
struct HashTable {
   int s;
   HashTableEntry *t;
};
int HashFunc1(int k, int s) {
   return k % s;
}
int HashFunc2(int k, int s) {
   return (k * s - 1) % s;
}
HashTable *initiateTable(int s) {
   HashTable *ht;
   if (s < T_S) {
      cout<<"Table Size is Too Small"<<endl;
      return NULL;
   }
   ht= new HashTable;
   if (ht == NULL) {
      cout<<"Out of Space"<<endl;
      return NULL;
   }
   ht->s = s;
   ht->t = new HashTableEntry[ht->s];
   if (ht->t== NULL) {
      cout<<"Table Size is Too Small"<<endl;
      return NULL;
   }
   for (int i = 0; i < ht->s; i++) {
      ht->t[i].info = Emp;
      ht->t[i].e=NULL;
   }
   return ht;
}
int SearchKey(int k, HashTable *ht) {
   int hashVal= HashFunc1(k, ht->s);
   int stepSize= HashFunc2(k, ht->s);
   while (ht->t[hashVal].info != Emp &&
      ht->t[hashVal].e != k) {
         hashVal = hashVal + stepSize;
         hashVal = hashVal % ht->s;
      }
      return hashVal;
}
void Insert(int k, HashTable *ht) {
   int pos = SearchKey(k, ht);
   if (ht->t[pos].info != Legi ) {
      ht->t[pos].info = Legi;
      ht->t[pos].e = k;
   }
}

HashTable *Rehash(HashTable *ht) {
   int s = ht->s;
   HashTableEntry *t= ht->t;
   ht = initiateTable(2*s);
   for (int i = 0; i < s; i++) {
      if (t[i].info == Legi)
         Insert(t[i].e, ht);
   }
   free(t);
   return ht;
}
int main() {
   int v, s, pos, i = 1;
   int c;
   HashTable *ht;
   while(1) {
      cout<<"1.Initialize size of the table"<<endl;
      cout<<"2.Insert element into the table"<<endl;
      cout<<"3.Rehash Hash Table"<<endl;
      cout<<"4.Exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>c;
      switch(c) {
         case 1:
            cout<<"Enter size of the Hash Table: ";
            cin>>s;
            ht = initiateTable(s);
         break;
         case 2:
            if (i > ht->s) {
               cout<<"Table is Full, Rehash the table"<<endl;
               continue;
            }
            cout<<"Enter element to be inserted: ";
            cin>>v;
            Insert(v, ht);
            i++;
         break;
         case 3:
            ht= Rehash(ht);
         break;
         case 4:
            exit(1);
         default:
         cout<<"Enter correct option";
      }
   }
   return 0;
}
