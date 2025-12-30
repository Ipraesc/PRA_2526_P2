#include <iostream>
#include <stdexcept>
#include <string>
#include "BSTree.h"
#include "TableEntry.h"
#include "Dict.h" 

template <typename V>

class BSTreeDict : public Dict<V> {

  private:
    BSTree<TableEntry<V>>* tree;
    int entryCount;

  public:

    BSTreeDict() {

        tree = new BSTree<TableEntry<V>>();
        entryCount = 0;

    }

    ~BSTreeDict() {

        delete tree;

    }

    int entries() const override {

        return entryCount;

    }

    void insert(std::string key, V value) override {

      try {

        search(key);
        throw std::runtime_error("La clave ya existe");

      } 

      catch (const std::runtime_error&) {

        TableEntry<V> entry(key, value);
        tree->insert(entry);
        entryCount++;

      }
    }

    V remove(std::string key) override {

      try {

        TableEntry<V> entry(key);
        V value = tree->search(entry).value;
        tree->remove(entry);
        entryCount--;
        
        return value;

      }
      
      catch (...) {

        throw std::runtime_error("Elemento no encontrado");

      }
    }

    V search(std::string key) const override {

      try {

        TableEntry<V> entry(key, V());
        TableEntry<V> result = tree->search(entry);

        return result.value;

      }

      catch (const std::runtime_error&) {

        throw std::runtime_error("Elemento no encontrado");

      }
    }

    V operator[](std::string key) const {

      return search(key);

    }

    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &dict) {
      
      out << *dict.tree;

      return out;

    }
};
