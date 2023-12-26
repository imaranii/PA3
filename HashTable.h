#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "ListLinked.h"  

template <typename V>
class HashTable: public Dict<V> {

    private:
	int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	
	int h(std::string key){
                std::size_t longitud = key.length();
                int l = static_cast<int>(longitud);
                int tot = 0;
                for(int i = 0 ; i < l ; i++){
                        char c = key.at(i);
                        tot += int(c);
                }
		
		tot = tot % max;
                return tot;
        }
	

    public:
        HashTable(int size){
		n = 0;
		max = size;
		table = new ListLinked<TableEntry<V>>[size];
	}

	~HashTable(){
		delete[] table;
	}
	
	V operator[](std::string key){
                return search(key);
        }
	

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){

		out << "Valores añadidos: " << th.n << "   Entradas: " << th.max << std::endl;

		for(int i = 0 ; i < th.max ; i++){
			out << "Cubeta num: "<< i << " [] "<< std::endl;
			for(int e = 0 ; e < th.table[i].size() ; e++){
				out << th.table[i].get(e).key << " => "<< th.table[i].get(e).value << std::endl;
			}
		}
		return out;

	}
	
	void insert(std::string key, V value) override final{
		TableEntry comp(key, value);
		int val = h(key);

		for(int i = 0 ; i < table[val].size() ; i++){
			if(table[val].get(i) == comp){
				throw std::runtime_error("Ya existe key");
			}
		}

		table[val].append(comp);
		n++;
	}



	V search(std::string key) override final{
		int val = h(key);
                int cas = table[val].size();

                for(int i = 0 ; i < cas ; i++){
                        TableEntry comp = table[val].get(i);
                        if(key == comp.key){
                                return comp.value;
                        }
                }
                throw std::runtime_error ("Casilla con key no encontrada");

			
	}

	V remove(std::string key) override final{
		int val = h(key);
		TableEntry<V> comp (key);

		for(int i = 0 ; i < table[val].size() ; i++){
			TableEntry<V> elim = table[val].get(i);

			if(elim == comp){
				V valor = elim.value;
				table[val].remove(i);
				n--;
				return valor;
			}
		}
		
		throw std::runtime_error("No se ha encontrado la palabra");
	}
	

	int entries() override final{
		return n;
	}


	int capacity(){
		return max;
	}


};
#endif
