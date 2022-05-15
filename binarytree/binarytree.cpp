// #include "..."

namespace lasd {

/* ************************************************************************** */

/************************ NODE MEMBER PROPERTIES *************************/
// OPERATORE== PER NODE
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node_to_compare) const noexcept {
    if(node_to_compare.Element() == this->Element()) {
        bool thisDx = this->HasRightChild();
        bool thisSx = this->HasLeftChild();

        bool node_to_compare_dx = node_to_compare.HasRightChild();
        bool node_to_compare_sx = node_to_compare.HasLeftChild();

        bool right = (thisDx == node_to_compare_dx); 
        bool left  = (thisSx == node_to_compare_sx);

        if (right && left) {
            if(thisSx && thisDx) {
                return ( (node_to_compare.LeftChild() == this->LeftChild()) && (node_to_compare.RightChild() == this->RightChild()));
            } else if(thisDx) {
                return (node_to_compare.RightChild() == this->RightChild());
            } else if(thisSx) {
                return (node_to_compare.LeftChild() == this->LeftChild());
            } else {
                return true;
            }
        }
    }

    return false;
}

template <typename Data>
inline bool BinaryTree<Data>::Node::operator!=(const Node& node_to_compare) const noexcept { return !(*this == node_to_compare); }

/************************ BINARY TREE *************************/
// BINARY TREE COMPARISON OPERATORS
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt_to_compare) const noexcept {
    if(size == bt_to_compare.size){
        if(size != 0) {
            return ( this->Root() == bt_to_compare.Root() );
        } else {
            return true;
        }
    } else {
        return false;
    }
}

template <typename Data>
inline bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt_to_compare) const noexcept { return !(*this == bt_to_compare); }

// MAP FUNCTIONS
template <typename Data>
inline void BinaryTree<Data>::Map(MapFunctor funct, void* par) {
    if(size != 0)
        MapPreOrder(funct, par);
}

template<typename Data>
inline void BinaryTree<Data>::MapPreOrder(MapFunctor funct, void* par) {
    if(size != 0)
        MapPreOrder(funct, par, &(this->Root()));
}

template<typename Data>
inline void BinaryTree<Data>::MapPostOrder(MapFunctor funct, void* par) {
    if(size != 0)
        MapPostOrder(funct, par, &(this->Root()));
}

template<typename Data>
inline void BinaryTree<Data>::MapInOrder(MapFunctor funct, void* par) {
    if(size != 0)
        MapInOrder(funct, par, &(this->Root()));
}

template<typename Data>
inline void BinaryTree<Data>::MapBreadth(MapFunctor funct, void* par) {
    if(size != 0)
        MapBreadth(funct, par, &(this->Root()));
}

// FOLD FUNCTIONS
template <typename Data>
inline void BinaryTree<Data>::Fold(FoldFunctor funct, const void* par, void* accum) const {
    if(size != 0)
        FoldPreOrder(funct, par, accum, &(this->Root()));
}

template<typename Data>
inline void BinaryTree<Data>::FoldPreOrder(FoldFunctor funct, const void* par, void* accum) const {
    if(size != 0)
        FoldPreOrder(funct, par, accum, &(this->Root()));
}

template<typename Data>
inline void BinaryTree<Data>::FoldPostOrder(FoldFunctor funct, const void* par, void* accum) const {
    if(size != 0)
        FoldPostOrder(funct, par, accum, &(this->Root()));
}

template<typename Data>
inline void BinaryTree<Data>::FoldInOrder(FoldFunctor funct, const void* par, void* accum) const {
    if(size != 0)
        FoldInOrder(funct, par, accum, &(this->Root()));
}

template<typename Data>
inline void BinaryTree<Data>::FoldBreadth(FoldFunctor funct, const void* par, void* accum) const {
    if(size != 0)
        FoldBreadth(funct, par, accum, &(this->Root()));
}

// AUXILIARY BINARY TREE MEMBER FUNCTIONS
template<typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor funct, void* par, Node* node) {
    /*
        La MapPreOrder è applicata nel seguente modo: partendo dalla radice, viene applicata la visita 
        (e la relativa funzione) al nodo e poi ai suoi sottoalberi sinistro e destro. 
        Lo stesso identico concetto è applicato anche per la FoldPreOrder. 
    */
    if(node != nullptr) {
        funct(node->Element(), par);

        if(node->HasLeftChild())
            MapPreOrder(funct, par, &(node->LeftChild())); 

        if(node->HasRightChild())
            MapPreOrder(funct, par, &(node->RightChild()));
    }
}

template<typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor funct, void* par, Node* node) {
    /*
        La MapPostOrder è applicata nel seguente modo: viene applicata la visita (e la relativa funzione) 
        ai sottoalberi sinistro e destro e poi, solo dopo al nodo.
        Lo stesso identico concetto è applicato anche per la FoldPostOrder. 
    */
    if(node != nullptr) {
        if(node->HasLeftChild())
            MapPostOrder(funct, par, &(node->LeftChild()));

        if(node->HasRightChild())
            MapPostOrder(funct, par, &(node->RightChild()));
        
        funct(node->Element(), par);
    }
}

template<typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor funct, void* par, Node* node) {
    /*
        La MapInOrder è applicata nel seguente modo: prima si applica la visita (e la relativa funzione)
        al sottoalbero di sinistra, poi al nodo e poi al sottoalbero di destra.  
        Lo stesso identico concetto è applicato anche per la FoldInOrder. 
    */
    if(node != nullptr) {
        if(node->HasLeftChild()) 
            MapInOrder(funct, par, &(node->LeftChild())); 

        funct(node->Element(), par);
        
        if(node->HasRightChild())
            MapInOrder(funct, par, &(node->RightChild()));
    }
}

template<typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor funct, void* par, Node* node) {
    lasd::QueueLst<Node*> queue;
    queue.Enqueue(node);
    Node* temp;

    // ALGORITMO DI VISITA IN AMPIEZZA TRAMITE QUEUELST
    while(!(queue.Empty())) {
        temp = queue.HeadNDequeue();
        funct(temp->Element(), par);

        if(temp->HasLeftChild()) 
            queue.Enqueue(&(temp->LeftChild()));

        if(temp->HasRightChild())
            queue.Enqueue(&(temp->RightChild()));
    }
}

template<typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor funct, const void* par, void* accum, Node* node) const {
    if(node != nullptr) {
        funct(node->Element(), par, accum);

        if(node->HasLeftChild())
            FoldPreOrder(funct, par, accum, &(node->LeftChild())); 

        if(node->HasRightChild())
            FoldPreOrder(funct, par, accum, &(node->RightChild()));
    }
}

template<typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor funct, const void* par, void* accum, Node* node) const {
    if(node != nullptr) {
        if(node->HasLeftChild())
            FoldPostOrder(funct, par, accum, &(node->LeftChild())); 

        if(node->HasRightChild())
            FoldPostOrder(funct, par, accum, &(node->RightChild()));
        
        funct(node->Element(), par, accum);
    }
}

template<typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor funct, const void* par, void* accum, Node* node) const {
    if(node != nullptr) {
        if(node->HasLeftChild()) 
            FoldInOrder(funct, par, accum, &(node->LeftChild())); 

        funct(node->Element(), par, accum);
        
        if(node->HasRightChild())
            FoldInOrder(funct, par, accum, &(node->RightChild()));
    }
}

template<typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor funct, const void* par, void* accum, Node* node) const {
    lasd::QueueLst<Node*> queue;
    queue.Enqueue(node);
    Node* temp;

    while(!(queue.Empty())) {
        temp = queue.HeadNDequeue();
        funct(temp->Element(), par, accum);

        if(temp->HasLeftChild()) 
            queue.Enqueue(&(temp->LeftChild()));

        if(temp->HasRightChild())
            queue.Enqueue(&(temp->RightChild()));
    }
}

/************************ BTPreOrderIterator *************************/
// COSTRUTTORI
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {
    if (bt.Size() != 0) {
        root = &(bt.Root());
        current = root;
    }
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& bt_pre_iterator) { 
    root = bt_pre_iterator.root;
    current = bt_pre_iterator.current;
    stack = bt_pre_iterator.stack;
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& bt_pre_iterator) noexcept {
    std::swap(root, bt_pre_iterator.root);;
    std::swap(current, bt_pre_iterator.current);
    std::swap(stack, bt_pre_iterator.stack); // stack = std::move(bt_pre_iterator.stack);
}

// DISTRUTTORE
// template<typename Data>
// BTPreOrderIterator<Data>::~BTPreOrderIterator() {
//     /*
//         Attenzione! : se invece di porre semplicemente a nullptr root e current effettui la delete dei riferimenti,
//         quello che accade è segmentation fault!
//         Quello che accadrebbe è l'eliminazione ricorsiva partendo dalla root di TUTTI i nodi.
//         !! Non è nel concetto dell'iteratore fare questo lavoro. !!

//         Questa cosa vale per tutti gli altri iteratori!
//     */
//     stack.Clear();
//     root = nullptr;
//     current = nullptr;
// }

template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& bt) {
    BTPreOrderIterator<Data>* temp = new BTPreOrderIterator<Data>(bt);
    std::swap(*bt, *this);
    delete temp;
    return *this;
}

template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(current, bt.current);
    std::swap(stack, bt.stack); // stack = std::move(bt.stack);
    return *this;
}

// COMPARISON OPERATORS 
template<typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& bt) const noexcept {
    if( (current != bt.current) || (stack != bt.stack) ) return false; 

    return true;
}

template<typename Data>
inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& bt) const noexcept { return !(*this == bt); }

template<typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Attenzione: stato BTPreOrderIterator: terminated !");

    return current->Element();
}

// FUNZIONE DI TERMINAZIONE
template<typename Data>
inline bool BTPreOrderIterator<Data>::Terminated() const noexcept{ return (current == nullptr); }

template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if(Terminated()) {
        throw std::out_of_range("Attenzione: stato BTPreOrderIterator: terminated !");
    } else {
        /*
            Dovendo scendere a sinistra, è necessario salvare nello stack prima i figli destri!
            Come faresti a risalire l'albero altrimenti?
        */
        if(current->HasRightChild())
            stack.Push(&(current->RightChild()));
    
        if(current->HasLeftChild())
            stack.Push(&(current->LeftChild()));

        if(stack.Empty()) 
            current = nullptr;
        else
            current = stack.TopNPop();
    
        return *this;
    }
}

template<typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
    /*
        La Reset() deve solo effettuare la Clear() e far si che 
        il puntatore al nodo corrente (current) riparta dalla root!
        Non bisogna cancellare la struttura!
    */
    current = root;
    stack.Clear();
}

/************************************** BTPostOrderIterator **************************************/
template<typename Data>
void BTPostOrderIterator<Data>::getMostLeftLeaf() {
    if( !Terminated() ) {
        while (current->HasLeftChild()) {
            stack.Push(current);
            current = &(current->LeftChild());
        }

        if(current->HasRightChild()) {
            stack.Push(current);
            current = &(current->RightChild());
            getMostLeftLeaf();
        }
    }
}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {
    if (bt.Size() != 0) {
        root = &(bt.Root());
        current = root; 
        getMostLeftLeaf();
        last = current; // last deve essere il riferimento alla MostLeftLeaf.
    } 
}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& bt){
    root = bt.root;
    current = bt.current;
    last = bt.last;
    stack = bt.stack;
}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(current, bt.current); 
    std::swap(last, bt.last);
    std::swap(stack, bt.stack); // stack = std::move(bt.stack);
}

// template<typename Data>
// BTPostOrderIterator<Data>::~BTPostOrderIterator() {
//     stack.Clear();
//     root = nullptr;
//     current = nullptr;
//     last = nullptr;
// }

template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& bt) {
    BTPostOrderIterator<Data>* temp = new BTPostOrderIterator<Data>(bt); 
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(current, bt.current); 
    std::swap(last, bt.last);
    std::swap(stack, bt.stack); // stack = std::move(bt.stack);
    return *this;
}

template<typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator& bt) const noexcept {
    if( (current != bt.current) || (last != bt.last) || (stack != bt.stack) )
        return false; 

    return true;
}

template<typename Data>
inline bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator& bt) const noexcept { return !(*this == bt); }

template<typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Attenzione: stato BTPostOrderIterator = terminated !");

    return current->Element();
}

template<typename Data>
inline bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (current == nullptr);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Attenzione: stato BTPostOrderIterator: terminated !");

    if(stack.Empty()) {
        current = nullptr; 
        last = nullptr;
    } else {
        current = stack.TopNPop();
        /*
            Se current ha figlio destro e non è == last, lo salviamo nello stack ed andiamo a destra.
            Bisogna però far si che current (ri) punti all MostLeftLeaf. 
        */
        if(current->HasRightChild() && !(&(current->RightChild()) == last)) {
            stack.Push(current);
            current = &(current->RightChild()); 
            getMostLeftLeaf();
        }
    }
    last = current; 
    return *this;
}

template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
    current = root;
    stack.Clear();
    getMostLeftLeaf();
    last = current;
}

/************************************** BTInOrderIterator **************************************/
template<typename Data>
void BTInOrderIterator<Data>::getMostLeftNode() {
    // Nodo alla più estrema sinistra.
    if(current != nullptr) {
        if(current->HasLeftChild()) {
            stack.Push(current); 
            current = &(current->LeftChild());
            getMostLeftNode();
        }
    }
}

// COSTRUTTORI E DISTRUTTORE
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {
    if(bt.Size() != 0) {
        root = &(bt.Root()); 
        current = root;
        /*
            current, partendo dalla radice deve arrivare al nodo alla più estrema sinistra.
        */
        getMostLeftNode();
    }
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& bt) {
    root = bt.root;
    current = bt.current; 
    stack = bt.stack;
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(current, bt.current); 
    std::swap(stack, bt.stack); // stack = std::move(bt.stack);
}

// template<typename Data>
// BTInOrderIterator<Data>::~BTInOrderIterator() { 
//     stack.Clear();
//     root = nullptr;
//     current = nullptr;   
// }

// OPERATORI DI ASSEGNAZIONE
template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& bt) {
    BTInOrderIterator<Data>* temp = new BTInOrderIterator<Data>(bt); 
    std::swap(*temp, *this);
    delete temp;
    return *this;
}

template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(current, bt.current); 
    std::swap(stack, bt.stack); // stack = std::move(bt.stack);
    return *this;
}

// OPERATORI DI CONFRONTO
template<typename Data>
inline bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& bt) const noexcept {
    if( (current != bt.current) || (stack != bt.stack) )
        return false; 

    return true;
}

template<typename Data>
inline bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& bt) const noexcept { return !(*this == bt); }

// OVERRIDE METODO PER: operator*
template<typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Attenzione: stato BTInOrderIterator terminated !");

    return current->Element();
}

template<typename Data>
inline bool BTInOrderIterator<Data>::Terminated() const noexcept { return (current == nullptr); }

template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Attenzione: stato BTInOrderIterator: terminated !");

    if(current->HasRightChild()) {
        current = &(current->RightChild()); 
        getMostLeftNode();
    } else {
        if(stack.Empty()) 
            current = nullptr; 
        else
            current = stack.TopNPop(); 
    }
    return *this;
}

template<typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
    current = root;
    stack.Clear(); 
    getMostLeftNode();
}

/************************************** BTBreadthIterator **************************************/
// COSTRUTTORI E DISTRUTTORE
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
    if(bt.Size() != 0) {
        root = &(bt.Root()); 
        current = root;
    }
}

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& bt) {
    root = bt.root;
    current = bt.current;  
    queue = bt.queue;
}

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(current, bt.current);  
    std::swap(queue, bt.queue); // queue = std::move(bt.queue);
}

// template<typename Data>
// BTBreadthIterator<Data>::~BTBreadthIterator() {
//     queue.Clear();
//     root = nullptr;
//     current = nullptr;
// }

// OPERATORI DI ASSEGNAMENTO
template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& bt) {
    BTBreadthIterator<Data>* temp = new BTBreadthIterator<Data>(bt); 
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(current, bt.current);  
    std::swap(queue, bt.queue); // queue = std::move(bt.queue);
    return *this;
}

// OPERATORI DI CONFRONTO
template<typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& bt) const noexcept {
    if(current != bt.current || queue != bt.queue)
        return false;
    
    return true;
}

template<typename Data>
inline bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& bt) const noexcept {
    return !(*this == bt);
}

template<typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Attenzione: stato BTBreadthIterator: terminated !");

    return current->Element();
}

template<typename Data>
inline bool BTBreadthIterator<Data>::Terminated() const noexcept{ return (current == nullptr); }

template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Attenzione: stato BTBreadthIterator terminated !");

    if(current->HasLeftChild()) {
        queue.Enqueue(&(current->LeftChild()));
    }
    
    if(current->HasRightChild()) {
        queue.Enqueue(&(current->RightChild()));
    }

    if(queue.Empty())
        current = nullptr; 
    else 
        current = queue.HeadNDequeue();

    return *this;
}

template<typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
    current = root; 
    queue.Clear();
}

/* ************************************************************************** */

}