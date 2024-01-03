#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict() : tree(new BSTree<TableEntry<V>>()) {}

        ~BSTreeDict(){
            delete tree;
        }

	friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
		out << bs.tree;
		return out;
	}

        V operator[](std::string key){
            return search(key);
        }

        void insert(std::string key, V value) override final{
            TableEntry<V>* entry = new TableEntry<V>(key, value);
            tree->insert(*entry);
        }

        V search(std::string key) override final{
            return tree->search(key).value;
        }

        V remove(std::string key) override final{
            return tree->remove(key).value;
        }

        int entries(){
            return tree->size();
        }
};

#endif
