
#include "hash.h"
#include "heap.h"
#include <iostream>
/*                      constructor 
accepts int - getting capacity of binary heap 

public member functions 

insert - new item into the heap 

remove - allows promgrammer to delete an item specified in the heap w specified ID from the heap 

deleteMin - removes and returns the item w lowest key from heap 

setKey 
  - increaseKey functionality 
  - decreaseKey functionality

percolate up - keeps the binary tree correct after insert or delete  
percolate down - keeps the binary tree correct after insert or delete  
*/

//constructor 
heap::heap(int capacity):hashMap(capacity*2){

  actualHeap.resize(1 + capacity); 

  cap = capacity ;
  curSize = 0; 

}
// the insert fucntion
int heap::insert(const std::string &id, int key, void *pv){
  if(curSize >= cap){
    return 1;
  }
  else if(hashMap.contains(id)){
    return 2;
  }
  else{
    actualHeap[++curSize].ID = id;
    actualHeap[curSize].key = key;
    actualHeap[curSize].pdata = pv;
//puts into hashtable 
    hashMap.insert(id, &actualHeap[curSize]);
//makes sure the tree is balenced correctly 
    percolateUp(curSize);

    return 0 ;
  }

}
// set a key to new value
int heap::setKey(const std::string &id, int key){
  bool a; 
  //
  heapNode *pn = static_cast<heapNode *> (hashMap.getPointer(id, &a));

    if(!a){
        return 1;
    }

    int previous = pn -> key;
    pn -> key = key;

    if (previous < key){
        percolateDown(getPos(pn));

    }

    if (previous > key){
        percolateUp(getPos(pn));

    }

    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
  if(curSize == 0 ){
    return 1;
  }
  //top node must be the smallest number
   heapNode minimum = actualHeap[1]; 
    
    if (pKey != nullptr){
      *pKey = minimum.key;
    }
    if (ppData != nullptr){
      *(static_cast<void **> (ppData)) = minimum.pdata;
    }
    if (pId != nullptr){
      *pId = minimum.ID;
    }

    hashMap.remove(minimum.ID);
//put the most recently inserted node to the top and perculate down 
    actualHeap[1] = actualHeap[curSize--];
//rebalence 
    percolateDown(1);

    return 0;

}
// removes any node in the heap 
int heap::remove(const std::string &id, int *pKey, void *ppData){
    bool a; 
    heapNode *pn = static_cast<heapNode *> (hashMap.getPointer(id, &a));

      if(!a){
        return 1;
      }

      if (ppData != nullptr){
        *(static_cast<void **> (ppData)) = pn -> pdata;
      }
      if (pKey != nullptr){
        *pKey = pn->key;
      }

      int old = pn->key;
      hashMap.remove(id);
      *pn = actualHeap[curSize--];

      if (old < pn->key){
        percolateDown(getPos(pn));
      }
      if (old > pn->key){
        percolateUp(getPos(pn));
      }

  return 0;
}
void heap::percolateUp(int posC){
   while (posC/2 > 0) {
    if (actualHeap[posC/2].key > actualHeap[posC].key) {
      //classic swap
      heapNode temp = actualHeap[posC/2];
      actualHeap[posC/2] = actualHeap[posC];
      actualHeap[posC] = temp;
      hashMap.setPointer(actualHeap[posC].ID, &actualHeap[posC]);
      posC = posC / 2;
      hashMap.setPointer(actualHeap[posC].ID, &actualHeap[posC]);
    }
    else{
      break;
    }
   }
    hashMap.setPointer(actualHeap[posC].ID,&actualHeap[posC]);

}
void heap::percolateDown(int posC){
// think of a moving empty space go up the tree 
    heapNode empty = actualHeap[posC];

    for(int pos; posC*2 <= curSize; posC = pos) {
        pos = posC*2;

        if (pos != curSize && (actualHeap[pos].key > actualHeap[pos+1].key)){ 
          ++pos;
        }

        if (actualHeap[pos].key < empty.key) {
            actualHeap[posC] = actualHeap[pos];
            hashMap.setPointer(actualHeap[posC].ID, &actualHeap[posC]);
        }
        else{
            break;
        }
    }
    actualHeap[posC] = empty;
    hashMap.setPointer(actualHeap[posC].ID, &actualHeap[posC]);
}
//return pos of certain 
int heap::getPos(heapNode *pn){
    int pos = pn - &actualHeap[0];
  return pos;
}
