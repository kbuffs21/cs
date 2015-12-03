// FILE: BSTreeBag.cxx
// TEMPLATE CLASS IMPLEMENTED: BSTreeBag<ItemType> (see BSTreeBag.h for documentation)
// INVARIANT of the ADT:
//   root_ptr is the root pointer of a binary search tree that contains the
//   BSTreeBag's items.

#include <cassert>
#include <cstdlib>


namespace bst2270
{
    template <class ItemType>
	void bst_remove_max(binary_tree_node<ItemType>*& root_ptr, ItemType& removed)
	// Precondition: root_ptr is a root pointer of a non-empty binary 
	// search tree.
	// Postcondition: The largest item in the binary search tree has been
	// removed, and root_ptr now points to the root of the new (smaller) 
	// binary search tree. The reference parameter, removed, has been set 
	// to a copy of the removed item.
	{
		if( root_ptr->right() == nullptr )//no right child
		{
			binary_tree_node<ItemType>* old_root_ptr = root_ptr;
			root_ptr = root_ptr->left();//copy left child to root ptr's address
			removed = root_ptr->data();
			delete old_root_ptr;
		}
		else//has right child,recurse
		{
			bst_remove_max(root_ptr->right(), removed);
		}
	}

    template <class ItemType>
	bool bst_remove(binary_tree_node<ItemType>*& root_ptr, const ItemType& target)
	// Precondition: root_ptr is a root pointer of a binary search tree 
	// or may be nullptr for an empty tree).
	// Postcondition: If target was in the tree, then one copy of target
	// has been removed, and root_ptr now points to the root of the new 
	// (smaller) binary search tree. In this case the function returns true.
	// If target was not in the tree, then the tree is unchanged (and the
	// function returns false).
	{
		if( root_ptr == nullptr )
		{
			return false;
		}
		else if( root_ptr->data() > target )
		{
			return bst_remove(root_ptr->left(), target);
		}
		else if( root_ptr->data() < target ) 
		{
			return bst_remove(root_ptr->right(), target);
		}
		else//targer is found at root ptr's data
		{
			if( root_ptr->left() == nullptr )//root ptr has no left child
			{
				binary_tree_node<ItemType>* old_root_ptr = root_ptr;
				root_ptr = root_ptr->right();// replace with right child
				delete old_root_ptr;// no leaks		
			}
			else//root ptr has left child
			{
				bst_remove_max(root_ptr->left(), root_ptr->data());
			}
			return true;
		}
	}
	
    template <class ItemType>
	unsigned int bst_remove_all
	(binary_tree_node<ItemType>*& root_ptr, const ItemType& target)
	// Precondition: root_ptr is a root pointer of a binary search tree 
	// or may be nullptr for an empty tree).
	// Postcondition: All copies of target have been removed from the tree
	// has been removed, and root_ptr now points to the root of the new 
	// (smaller) binary search tree. The return value tells how many copies
	// of the target were removed.
	{
		if( root_ptr == nullptr )
		{
			return 0;
		}
		else if( root_ptr->data() > target )
		{
			return bst_remove_all(root_ptr->left(), target);
		}
		else if( root_ptr->data() < target ) 
		{
			return bst_remove_all(root_ptr->right(), target);
		}
		else//target found at rootptr data
		{
			if( root_ptr->left() == nullptr )
			{
				binary_tree_node<ItemType>* old_root_ptr = root_ptr;
				root_ptr = root_ptr->right();// replace with right child
				delete old_root_ptr;// no leaks		
			}
			else
			{
				bst_remove_all(root_ptr->left(), root_ptr->data());
			}
			return 1 +  bst_remove_all(root_ptr, target);
		}
	}

    template <class ItemType>//default constructor
	BSTreeBag<ItemType>::BSTreeBag()
	{
		root_ptr = nullptr;
	}
	
    template <class ItemType>//copy constructor
	BSTreeBag<ItemType>::BSTreeBag(const BSTreeBag<ItemType>& source)
	// Library facilities used: bintree.h
	{
		root_ptr = tree_copy(source.root_ptr);
	}

    template <class ItemType>//destructor
	BSTreeBag<ItemType>::~BSTreeBag( )
	// Header file used: bintree.h
	{
		tree_clear(root_ptr);
	}

    template <class ItemType>//returns how many nodes in tree
	unsigned int BSTreeBag<ItemType>::size( ) const
	// Header file used: bintree.h
	{
		return tree_size(root_ptr);
	}

    template <class ItemType>//insert new nodes into BST
	void BSTreeBag<ItemType>::insert(const ItemType& entry)
	// Header file used: bintree.h
	{
		if( root_ptr == nullptr )
		{
			root_ptr = new binary_tree_node<ItemType>(entry);
		}
		else
		{
			bool done = false;
			binary_tree_node<ItemType>* cursor = root_ptr;
			while(!done)
			if(cursor->data() >= entry )//data goes to left subtree
			{
				if( cursor->left() == nullptr )//if left child is empty
				{
					cursor->left() = new binary_tree_node<ItemType>(entry);
					done = true;				
				}
				else
				{
					cursor = cursor->left();
				}
			}
			else//data goes to right subtree
			{
				if( cursor->right() == nullptr )//if right child is empty
				{
					cursor->right() = new binary_tree_node<ItemType>(entry);
					done = true;	
				}
				else
				{
					cursor = cursor->right();
				}
			}
			
		}
		
	}

    template <class ItemType>
	unsigned int BSTreeBag<ItemType>::count(const ItemType& target) const
	{
		unsigned int answer = 0;
		binary_tree_node<ItemType>* cursor = root_ptr;
		while(cursor != nullptr)
		{
			if( cursor->data() == target )
			{
				answer++;	
				cursor = cursor->left();		
			}
			else if( cursor->data() >= target )
			{
				cursor = cursor->left();
			}
			else
			{
				cursor = cursor->right();
			}
		}
		return answer;
	}

    template <class ItemType>
	unsigned int BSTreeBag<ItemType>::erase(const ItemType& target)
	{
		return bst_remove_all(root_ptr, target);
	}

    template <class ItemType>
	bool BSTreeBag<ItemType>::erase_one(const ItemType& target)
	{
		return bst_remove(root_ptr, target);
	}

    template <class ItemType>//assignment operator
	void BSTreeBag<ItemType>::operator =(const BSTreeBag<ItemType>& source)
    {
		if (this == &source)
		    return;
		tree_clear(root_ptr);
		root_ptr = tree_copy(source.root_ptr);
	}

    template <class ItemType>
	void BSTreeBag<ItemType>::operator +=(const BSTreeBag<ItemType>& addend)
	{
		if (root_ptr == addend.root_ptr)
		{
			BSTreeBag<ItemType> copy = addend;
			insert_all(copy.root_ptr);
		}
		else
			insert_all(addend.root_ptr);
	}

	template <class ItemType>
	BSTreeBag<ItemType> operator +(const BSTreeBag<ItemType>& b1, const BSTreeBag<ItemType>& b2)
	{
		BSTreeBag<ItemType> answer = b1;
		answer += b2;
		return answer;
	}

    template <class ItemType>
	void BSTreeBag<ItemType>::insert_all(binary_tree_node<ItemType>* addroot_ptr)
        // Precondition: addroot_ptr is the root pointer of a binary search tree that
        // is separate for the binary search tree of the BSTreeBag that activated this
        // method.
        // Postcondition: All the items from the addroot_ptr's binary search tree
        // have been added to the binary search tree of the BSTreeBag that activated this
        // method.
	{
		if (addroot_ptr != nullptr)
		{
			insert(addroot_ptr->data( ));
			insert_all(addroot_ptr->left( ));
			insert_all(addroot_ptr->right( ));
		}
	}
	
}
