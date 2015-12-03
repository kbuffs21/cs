
#include <cstddef>

template <class ItemType>
int ArrayBag<ItemType>::getCapacity( ) const
{
	return DEFAULT_CAPACITY;
}

template <class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newItem)
{
	if (itemCount < DEFAULT_CAPACITY)
		{		
			items[itemCount++] = newItem;//iC++ instead of ++iC	
			if (isFull()) 
				return false;
			else 
				return true;
		}
	else
		return false;
}

template <class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}

template <class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return itemCount == 0;// bag cannot only be full or empty
}

template <class ItemType>
bool ArrayBag<ItemType>::isFull() const
{
	return (itemCount == DEFAULT_CAPACITY);	
}

template <class ItemType>
ArrayBag<ItemType>::ArrayBag()
{
	itemCount = 0;//found missing code with dbg
}

template <class ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount = 0;
}

template <class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anItem)
{
	int k;
	if (itemCount == 0) //add another'='
		return false;
	for (k = 0; k < itemCount; ++k)	//remove ';'
		if (items[k] == anItem)
		{
			if (k < itemCount - 1)//add '-1'
			{
				items[k] = items[itemCount-1];//add '1'
				itemCount--;
				return true;
			}
		}
		 
	return false;
}

template <class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anItem) const
{
	int k = 0;
	while (k < itemCount)//strictly less than	
	{
		if (anItem == items[k])//remove ';'	
		{
			return true;
		}
		
		k++;//add k++
	}
	return false;
}

template <class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anItem) const
{
	int freq = 0;
	if (contains(anItem) == false) 	
		return 0;
	int k = 0; 
	while (itemCount > k);		
		if (items[k] == anItem)
		{
			freq++;
		}
	return freq;
}

template <class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	for (int k = 0; k < itemCount; ++k)
		bagContents.push_back(items[k]);
	return bagContents;
}
