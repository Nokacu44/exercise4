
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data> // Must extend BinaryTreeLnk<Data>
class BST : virtual public DictionaryContainer<Data>, 
            virtual public BinaryTreeLnk<Data> {
private:

protected:
  using typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:
  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&); // A bst obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST& bst) : BinaryTreeLnk<Data>(bst) {};

  // Move constructor
  BST(BST&& bst) noexcept : BinaryTreeLnk<Data>(std::move(bst)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&);

  // Move assignment
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BST&) const noexcept;
  inline bool operator!=(const BST&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& Min() const;  // (concrete function must throw std::length_error when empty)
  virtual Data MinNRemove();        // (concrete function must throw std::length_error when empty)
  virtual void RemoveMin();         // (concrete function must throw std::length_error when empty)

  virtual const Data& Max() const; // (concrete function must throw std::length_error when empty)
  virtual Data MaxNRemove();       // (concrete function must throw std::length_error when empty)
  virtual void RemoveMax();        // (concrete function must throw std::length_error when empty)

  virtual const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data&);       // (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data&);        // (concrete function must throw std::length_error when not found)

  virtual const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data&);       // (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data&);        // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual void Insert(const Data&) override;     // Override DictionaryContainer member (Copy of the value)
  virtual void Insert(Data&&) override;          // Override DictionaryContainer member (Move of the value)
  virtual void Remove(const Data&) override;     // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

protected:

  // Auxiliary member functions

  virtual Data DataNDelete(NodeLnk*);
  
  virtual NodeLnk* Detach(NodeLnk*&) noexcept;
  
  virtual NodeLnk* DetachMin(NodeLnk*&) noexcept;
  virtual NodeLnk* DetachMax(NodeLnk*&) noexcept;

  virtual NodeLnk* Skip2Left(NodeLnk*&) noexcept;
  virtual NodeLnk* Skip2Right(NodeLnk*&) noexcept;

  virtual NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept; // Both mutable & unmutable versions.
  virtual NodeLnk* const& FindPointerToMin(NodeLnk* const&) const noexcept;
  
  virtual NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept; // Both mutable & unmutable versions.
  virtual NodeLnk* const& FindPointerToMax(NodeLnk* const&) const noexcept; 

  virtual NodeLnk*& FindPointerTo(NodeLnk*&, const Data&) noexcept; // Both mutable & unmutable versions
  virtual NodeLnk* const& FindPointerTo(NodeLnk* const&, const Data&) const noexcept;

  virtual NodeLnk** FindPointerToPredecessor(NodeLnk*&, const Data&) noexcept; // Both mutable & unmutable versions
  virtual NodeLnk* const* FindPointerToPredecessor(NodeLnk* const&, const Data&) const noexcept;
  virtual NodeLnk** FindPointerToSuccessor(NodeLnk*&, const Data&) noexcept;   // Both mutable & unmutable versions
  virtual NodeLnk* const* FindPointerToSuccessor(NodeLnk* const&, const Data&) const noexcept;
};

/* ************************************************************************** */

}

#include "bst.cpp"
#endif