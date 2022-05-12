
namespace lasd {

/* ************************************************************************** */

template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& lc) {
    for (ulong i = 0; i < lc.Size(); i++){
        Insert( lc[i] );
    }
}

template<typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst) {
    BinaryTreeLnk<Data>::operator=( bst ); 
    return *this;
}

template<typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
    BinaryTreeLnk<Data>::operator=( std::move(bst) ); 
    return *this;
}

template<typename Data>
inline bool BST<Data>::operator==(const BST<Data>& bst) const noexcept {
    if(size == bst.size) {
        BTInOrderIterator<Data> iter_1(*this);
        BTInOrderIterator<Data> iter_2(bst);

        for(; !iter_1.Terminated(); ++iter_1, ++iter_2) {
            if( *iter_1 != *iter_2 ) {
                return false;
            }
        }

        return true;
    } else {
        return false;
    }
}

template<typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept {
    return !(*this == bst);
}

/******* SPECIFIC MEMBER FUNCTIONS *******/
template<typename Data>
const Data& BST<Data>::Min() const {
    if (root == nullptr) {
        throw std::length_error("Errore: bst vuoto!");
    } else {
        return ( FindPointerToMin(&(this->Root()))->Element() );
    }
}

template<typename Data>
Data BST<Data>::MinNRemove() {
    // if (root == nullptr) {
    //     throw std::length_error("Errore: bst vuoto!");
    // } else {

    // }
}

template<typename Data>
void BST<Data>::RemoveMin() {

}

// ...

template<typename Data>
const Data& BST<Data>::Max() const {
    if (root == nullptr) {
        throw std::length_error("Errore: bst vuoto!");
    } else {
        return ( FindPointerToMax(&(this->Root()))->Element() );
    }
}

template<typename Data>
Data BST<Data>::MaxNRemove() {
  
}

template<typename Data>
void BST<Data>::RemoveMax() {
    
}

// ...

template<typename Data>
const Data& BST<Data>::Predecessor(const Data& data) const {
    // (concrete function must throw std::length_error when not found)
} 

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& data) {
    // (concrete function must throw std::length_error when not found)
}

template<typename Data>
void BST<Data>::RemovePredecessor(const Data& data) {
    // (concrete function must throw std::length_error when not found)
} 

// ... 

template<typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
    // (concrete function must throw std::length_error when not found)
}
  
template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& data) {
    // (concrete function must throw std::length_error when not found)
}

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& data){
    // (concrete function must throw std::length_error when not found)
}

// ... 

template<typename Data>
void BST<Data>::Insert(const Data& data) {
    NodeLnk* newnode = new NodeLnk(data);
    NodeLnk* parent = nullptr;
    NodeLnk* current = root;

    while(current != nullptr){
        parent = current;
        if(current->element > data)
            current = &current->LeftChild();
        else 
            current = &current->RightChild();
    }

    if(parent == nullptr) {
        root = newnode;
    } else {
        if (parent->element > data) {
            parent->leftchild = newnode;
            ++size;
        } else { 
            parent->rightchild = newnode;
            ++size;
        }
    }
}  

template<typename Data>
void Insert(Data&& data){
    NodeLnk* newnode = new NodeLnk(std::move(data));

    /* Per sicurezza */
    newnode->leftchild = nullptr;
    newnode->rightchild = nullptr;

    NodeLnk* parent = nullptr;
    NodeLnk* current = root;

    while(current != nullptr){
        parent = current;
        if(current->element > data)
            current = &current->LeftChild();
        else 
            current = &current->RightChild();
    }

    if(parent == nullptr) {
        root = newnode;
    } else {
        if (parent->element > data) {
            parent->leftchild = newnode;
            ++size;
        } else { 
            parent->rightchild = newnode;
            ++size;
        }
    }
}  

template<typename Data>
void BST<Data>::Remove(const Data& data) {

}

template<typename Data>
bool BST<Data>::Exists(const Data& data) const noexcept {
    NodeLnk* temp = root;
    
    while(temp != nullptr) {
        if (temp->element == data) {
            return true;
        } else if (temp->element > data) {
            temp = &temp->LeftChild();
        } else {
            temp = &temp->RightChild();
        }
    } 

    return false;  
}


/*********************** AUXILIARY MEMBER FUNCTIONS ***********************/
template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node) {
    Data elem = node->element;

    /* SE NODE E' OTTENUTO DALLA DETACH, ALLORA OK */
    delete node; // POSSIBILE SEGMENTATION FAULT.
    
    return elem;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
    if (node != nullptr) {
        if (node->leftchild == nullptr) {
            return Skip2Right(node);
        } else if (node->rightchild == nullptr) {
            return Skip2Left(node);
        } else {
            // Nel caso in cui il nodo ha entrambi i figli:
            NodeLnk* detach = DetachMax(node->leftchild);
            std::swap(node->element, detach->element);
            return detach;
        }
    }

    return nullptr;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {
    return Skip2Right( FindPointerToMin(node) );
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {
    return Skip2Left( FindPointerToMax(node) );
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& node) noexcept {
    NodeLnk* sinistro = nullptr;

    if(node != nullptr){
        std::swap(sinistro, node->leftchild);
        std::swap(sinistro, node);
        --size;
    }   

    return sinistro;    
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& node) noexcept {
    NodeLnk* destro = nullptr;

    if(node != nullptr){
        std::swap(destro, node->rightchild);
        std::swap(destro, node);
        --size;
    }   

    return destro;    
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& node) const noexcept {
    /*
        NOTAZIONE DOPPIO PUNTATORE: 
            --> Il primo '*' serve per salvare l'indirizzo della variabile.
            --> Il secondo '*' serve per salvare l'indirizzo del primo puntatore. 
    */
    
    NodeLnk* const* point = &node;
    NodeLnk* curr = node;

    if (curr != nullptr) {
        // Finchè ne ho la possibilità, bisogna scendere a sinistra.
        while (curr->leftchild != nullptr) {
            point = &curr->leftchild;
            curr = curr->leftchild;
        }
    }

    return *point;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& node) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& node) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* curr = node;

    if(curr != nullptr) {
        // Finchè ne ho la possibilità, bisogna scendere a destra.
        while (curr->rightchild != nullptr) {
            point = &curr->rightchild;
            curr = curr->rightchild;
        }
    }

    return *point;
}

template <typename Data>
inline typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, const Data& elem) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, elem));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, const Data& elem) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* curr = node;

    while (curr != nullptr) {
        
        if (curr->element < elem) {
            point = &curr->rightchild;
            curr = curr->rightchild;
        } else if (curr->element > elem) {
            point = &curr->leftchild;
            curr = curr->leftchild;
        } else {
            break;
        }

    }

    return *point;
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& node, const Data& elem) noexcept {
    return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, elem));
}

template <typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(NodeLnk* const& node , const Data& elem) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* const* ptr = nullptr;

    while (true) {
        NodeLnk& current = **point;
        if(current.element < elem) {
            ptr = point;
            if(current.rightchild == nullptr) {
                return ptr;
            } else {
                point = &current.rightchild;
            }
        } else {
            if (current.leftchild == nullptr) {
                return ptr;
            } else {
                if (current.element > elem){
                    point = &current.leftchild;
                } else {
                    return &FindPointerToMax(current.leftchild);
                }
            }
        }
    }
}


template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& node, const Data& data) noexcept {
    return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, data));
}

template<typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, const Data& data) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* const* ptr = nullptr;

    while(true) {
        NodeLnk& current = **point;
        if(current.element > data) {
            ptr = point;
            if(current.leftchild == nullptr){
                return ptr;
            } else {
                point = &current.leftchild;
            }
        } else {
            if(current.rightchild == nullptr) {
                return ptr;
            } else {
                if(current.element < data) {
                    point = &current.rightchild;
                } else {
                    return &FindPointerToMin(current.rightchild);
                }
            }
        }
    }
}

/* ************************************************************************** */

}