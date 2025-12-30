#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../P1/ListLinked.h"

template <typename V>

class HashTable: public Dict<V> {

    private:
      
      int n;
      int max;

      ListLinked <TableEntry<V>>* table;

      int h(std::string key) const {
        
        int sum = 0;
        
        for (char c : key){
          
          sum += static_cast <int> (c);

        }

        return sum % max;

      }

    public:
      
      HashTable(int size) : n(0), max(size) {
        
        table = new ListLinked <TableEntry<V>> [max];

      }

      ~HashTable() {

        delete[] table;

      }

      void insert(std::string key, V value) override {

        int index = h(key);
        
        TableEntry<V> entry(key, value);
        
        if (table[index].search(TableEntry<V>(key)) != -1) {

          throw std::runtime_error("La clave ya existe en el diccionario.");

        }

        table[index].prepend(entry);
        n++;

      }

      V search(std::string key) const override {

        int index = h(key);
        int pos = table[index].search(TableEntry<V>(key));

        if (pos == -1) {

          throw std::runtime_error("Clave no encontrada.");

        }

        return table[index].get(pos).value;

      }

      V remove(std::string key) override {

        int index = h(key);
        int pos = table[index].search(TableEntry<V>(key));

        if (pos == -1) {
          
          throw std::runtime_error("Clave no encontrada.");

        }

        TableEntry<V> entry = table[index].get(pos);
        table[index].remove(pos);
        n--;

        return entry.value;

      }

      int entries() const override {

        return n;

      }

      int capacity() {

        return max;

      }

      V operator[](std::string key) {

        return search(key);

      }

      friend std::ostream& operator << (std::ostream& out, const HashTable<V>& ht) {

        for (int i = 0; i < ht.max; i++) {

          out << "Cubeta " << i << ": " <<ht.table[i] << "\n";

        }

        return out;

      }
};

#endif
