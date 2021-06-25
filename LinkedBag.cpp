/** ADT bag: Link-based implementation.*/
#include "LinkedBag.h"
#include "Node.h"



template<class ItemType>
LinkedBag<ItemType>::LinkedBag(): itemCount(0), headPtr(nullptr){}

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag){
    itemCount = aBag.itemCount;
    Node<ItemType>* origChainPtr = aBag.headPtr;

    if(origChainPtr == nullptr)
        headPtr = nullptr;
    else
    {
        headPtr = new Node<ItemType>();
        headPtr->setItem(origChainPtr->getItem());

        Node<ItemType>* newChainPtr = headPtr;
        origChainPtr = origChainPtr->getNext();

        while(origChainPtr != nullptr)
        {

            ItemType nextItem = origChainPtr->getItem();

            origChainPtr = origChainPtr->getNext();

            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

            newChainPtr->setNext(newNodePtr);

            newChainPtr = newChainPtr->getNext();
        }
        newChainPtr->setNext(nullptr);
    }
}

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag(){}

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
    return this->itemCount;
}

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
    return (this->itemCount == 0);
}

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& anEntry)
{
    Node<ItemType>* nextNodePtr = new Node<ItemType>(anEntry, this->headPtr);
    this->headPtr = nextNodePtr;
    itemCount++;
    return true;
}


template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType &anEntry) {
    Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
    if(canRemoveItem)
    {
        entryNodePtr->setItem(headPtr->getItem());

        Node<ItemType>* nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();

        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;

        itemCount--;
    }

    return canRemoveItem;
}

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
    while(headPtr != nullptr) {
        Node<ItemType> *nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
    }
    itemCount = 0;


}

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType &anEntry) const {
    int frequency = 0;
    int counter = 0;
    Node<ItemType>* curPtr = headPtr;
    while((curPtr != nullptr) && (counter < itemCount))
    {
    if(anEntry == curPtr->getItem())
    {
        frequency++;
    }
    counter++;
    curPtr = curPtr->getNext();

    }

    return frequency;
}

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType &anEntry) const {
    return (getPointerTo(anEntry) != nullptr);
}

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
    vector<ItemType> bagContents;
    Node<ItemType>* curPtr = headPtr;
    int counter = 0;
    while((curPtr!= nullptr) && (counter < itemCount))
    {
        bagContents.push_back(curPtr->getItem());
        curPtr = curPtr->getNext();
        counter++;
    }
    return bagContents;

}




template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType &target) const {
    bool found = false;
    Node<ItemType>* curPtr = headPtr;
    while(!found && (curPtr != nullptr)) {
        if(target == curPtr->getItem())
            found = true;
        else
            curPtr = curPtr->getNext();
    }
    return curPtr;
}
