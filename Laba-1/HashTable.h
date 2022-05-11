#pragma once
template < class K, class D>
class HashTable {
protected:
    TableForm<K, D>* Tform;
public:
    HashTable(int size) { 
        Tform = (TableForm<K, D>*) (new TableChain<K, D>(size)); 
    }
    bool Form();
    void ToChain(int size);
    void ToOpen(int size);
    unsigned int getSize() { 
        return Tform->getSize(); 
    }
    unsigned int getCapacity() { 
        return Tform->getCapacity(); 
    }
    bool IsEmpty() { 
        return Tform->IsEmpty(); 
    }
    unsigned int Probes() { 
        return Tform->Probes(); 
    }
    void Clear() { 
        Tform->Clear(); 
    }
    D& Data(K key) { 
        return Tform->Data(K key); 
    }
    bool Insert(K key, D data) {
        return Tform->Insert(key, data); 
    }
    bool Delete(K key) { 
        return Tform->Delete(key); 
    }
    void Print() { 
        Tform->Print(); 
    }

    class Iterator {
        ItForm* Iform;
    public:
        Iterator(HashTable& Table) { 
            Itform->Iterator(Table); 
        }
        D& operator *() { 
            return **Itform; 
        }
        void operator ++() { 
            return Itform->++(); 
        }
        bool operator==(const Iterator& it) { 
            return Itform-> == (); 
        }
        bool operator!=(const Iterator& it) { 
            return Itform-> != (); 
        }
    };

};
