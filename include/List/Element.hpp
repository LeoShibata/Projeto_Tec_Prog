#ifndef ELEMENT_HPP
#define ELEMENT_HPP 

namespace List {
    template <class TE>
    class Element {
        private:
            Element<TE>* next;
            TE* element;
        
            
        public:
            Element();
            ~Element();
            
            void setNext(Element<TE>* next);
            void setElement(TE* element);
            Element<TE>* getNext();
            TE* getElement();
    };

    template <class TE>
    Element<TE>::Element() :
        next(nullptr),
        element(nullptr)
    {

    }

    template <class TE>
    Element<TE>::~Element() { }

    template <class TE>
    void Element<TE>::setNext(Element<TE>* next) {
        this->next = next;
    }

    template <class TE>
    void Element<TE>::setElement(TE* element) {
        this->element = element;
    }

    template <class TE>
    Element<TE>* Element<TE>::getNext() {
        return next;
    }

    template <class TE>
    TE* Element<TE>::getElement() {
        return element;
    }
}

#endif