#include "hash.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
// "capacity" is current cap ,,, "filled" is occupied number in table 
//list of prime numbers, each one around double the previous
int primes[] = { 53, 107, 211, 431, 857, 1697, 3253, 6521, 13009, 26053, 52103, 104231, 208433, 316847, 733433, 1400387, 2801401, 5602309, 11204023, 22408063, 44816053, 89624737, 179250007, 350500069, 717000001, 1433000071 };


//constructer for the intial size of hash table 
hashTable::hashTable(int size){
    this -> capacity = getPrime(size);
    data = vector<hashTable::hashItem>(this -> capacity);
}
  // success Returns 0 
  // key already exists in hash table return 1
  // rehash fails return 2
  // string key to be inserted 
  int hashTable::insert(const std::string &key, void *pv){
    if(2 * filled > capacity){
        if (!rehash())
            return 2;
    }

    int pos = hash(key); 

    if (contains(key))
        return 1; 

     // linear probe for open spot
    while(data[pos].isOccupied == true && data[pos].isDeleted == false ) {
        //reset the pos for next linear probe
        if(++pos == capacity) 
        pos = 0;
    }
     // set postion w key,  isOccupied -  true, and isDeleted- false , optional pointer to value 

     data[pos].key = key ; 
     data[pos].isOccupied = true ; 
     data[pos].isDeleted = false ; 
     data[pos].pv = pv ; 
     filled++; 

     return 0; 
  }

  // Check if the specified key is in the hash table.
  // If so, return true; otherwise, return false.
  bool hashTable::contains(const std::string &key){
    int pos = findPos(key);
    return data[pos].isOccupied ; 
  }

  // Get the pointer associated with the specified key.
  // If the key does not exist in the hash table, return nullptr.
  // If an optional pointer to a bool is provided,
  // set the bool to true if the key is in the hash table,
  // and set the bool to false otherwise.
  void *hashTable::getPointer(const std::string &key, bool *b){
      int pos = findPos(key);
      if(b)
        *b = (pos != -1) ;  

      if(pos == -1 )
        return nullptr; 
    return data[pos].pv; 
    
  }
  // success: 0 failure(not exist): 1 
  int hashTable::setPointer(const std::string &key, void *pv){
    int pos = findPos(key);
    if(pos == -1 )
        return 1; 

    else {
      data[pos].pv = pv; 
      return 0; 
    }
     
  }
  // Delete the item with the specified key.
  // Returns true on success,
  // false if the specified key is not in the hash table.
  bool hashTable::remove(const std::string &key){
    int pos = findPos(key); 
    if(pos == -1 )
        return false; 
    data[pos].isDeleted = true; 
    filled-- ; 
    return true; 
  }
  //hashing function
  int hashTable::hash(const std::string &key){
    unsigned int hashVal = 0; 
    for (char ch: key)
        hashVal = 37 * hashVal + ch; 
    return hashVal % capacity; 
  }

//return pos, if -1 return false 
  int hashTable::findPos(const std::string &key){
    int pos = hash(key);

    while (data[pos].isOccupied){
        if (data[pos].key == key && !data[pos].isDeleted)
            return pos;
        else if (++pos == capacity)
            pos = 0;
    }
    return -1;
  }
  //fucntion to rehash the table 
  bool hashTable::rehash(){
    if(getPrime(capacity) == capacity)
        return false; 

    capacity = getPrime(capacity); 
    vector<hashItem> oldlist = data; 
    data.clear();
    data.resize(capacity); 
        
//load em back in 
    filled = 0; 
    for(hashItem thislist: oldlist){
        if(thislist.isOccupied)
            insert(thislist.key, thislist.pv);
    }
    return true; 
  }
//gets the next prime number for the size of hash
 unsigned int hashTable::getPrime(int size){ 
    for(int j : primes){
        //cout << "the prime is: " << j << " The value is " << size << endl;
        if(j > size) 
            return j;
    }
    return 1433000071;
}

