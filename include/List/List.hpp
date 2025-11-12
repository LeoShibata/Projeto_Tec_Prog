#ifndef LIST_HPP
#define LIST_HPP

#include <List/Element.hpp>

namespace List {
    template <class TL>
    class List {
        private:
            Element<TL>* pFirst;
            Element<TL>* pLast;
            unsigned int size;
        
        public:
            List();
            ~List();
            
            void addElement(TL* element);
            void removeElement(TL* element);
            void removeElement(int pos);
            int getSize();
            TL* operator[](int pos);
    };

    template <class TL>
    List<TL>::List() :
        pFirst(nullptr),
        pLast(nullptr),
        size(0)
    {
        
    }

    template <class TL>
    List<TL>::~List() { }

    template <class TL>
    void List<TL>::addElement(TL* element) { 
        Element<TL>* newElement = new Element<TL>();
        newElement->setElement(element);
        if(pFirst == nullptr) {
            pFirst = newElement;
            pLast = newElement;
        } else {
            pLast->setNext(newElement);
            pLast = newElement;
        }
        size++;
    }

    template <class TL>
    void List<TL>::removeElement(TL* element) {
        Element<TL>* current = pFirst;
        Element<TL>* prev = nullptr;
       
        while(current != nullptr) {
            if(current->getElement() == element) {
                if (prev == nullptr){
                    pFirst = current->getNext();
                } else {
                    prev->setNext(current->getNext());
                }

                if(current == pLast) {
                    pLast = prev;
                }

                delete current;
                size--;
                return;
            }
            prev = current;
            current = current->getNext();
        }
   }

    template <class TL>
    void List<TL>::removeElement(int pos) {
        if(pos < 0 || pos >= (int)size)
            return;
        
        Element<TL>* current = pFirst;
        Element<TL>* prev = nullptr;
        
        for(int i = 0; i < pos; i++) {
            prev = current;
            current = current->getNext();
        }
        
        if(prev == nullptr) {
            pFirst = current->getNext();
        } else {
            prev->setNext(current->getNext());
        }
        
        if(current = pLast) {
            pLast = prev;
        }
        
        delete current;
        size--;
    }

    template <class TL>
    int List<TL>::getSize() {
        return (int)size;
    }

    template <class TL>
    TL* List<TL>::operator[](int pos) {
        if(pos < 0 || pos >= (int)size)
            return nullptr;
        
        Element<TL>* current = pFirst;
        for(int i = 0; i < pos; i++) {
            current = current->getNext();
        }

        return current->getElement();
    }
}

#endif