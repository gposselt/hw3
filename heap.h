#ifndef HEAP_H
#define HEAP_H
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename PComparator = std::less<T> >
class Heap : private std::vector<T> {
public:
    /**
    * @brief Construct a new Heap object
    *
    * @param m ary-ness of heap tree (default to 2)
    * @param c binary predicate function/functor that takes two items
    *          as an argument and returns a bool if the first argument has
    *          priority over the second.
    */
    Heap(int m=2, PComparator c = PComparator());

    /**
    * @brief Destroy the Heap object
    *
    */
    ~Heap();

    /**
    * @brief Push an item to the heap
    *
    * @param item item to heap
    */
    void push(const T& item);

    /**
    * @brief Returns the top (priority) item
    *
    * @return T const& top priority item
    * @throw std::underflow_error if the heap is empty
    */
    T const & top() const;

    /**
    * @brief Remove the top priority item
    *
    * @throw std::underflow_error if the heap is empty
    */
    void pop();

    /// returns true if the heap is empty

    /**
    * @brief Returns true if the heap is empty
    *
    */
    bool empty() const;

    /**
    * @brief Returns size of the heap
    *
    */
    size_t size() const;

    // void print();


private:
    int m;
    PComparator c;

    /// Add whatever helper functions and data members you need below
    std::vector<size_t> getChildren(size_t parentIndex);




};

// Add implementation of member functions here


template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : std::vector<T>() {
    this->m = m;
    this->c = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() = default;

// We will start top() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()){
        // ================================
        // throw the appropriate exception
        // ================================
        throw std::underflow_error("Heap empty");

    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element

    return std::vector<T>::front();

}


template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {

    this->push_back(item);

    size_t index = this->std::vector<T>::size() - 1;

    while (index != 0) {
        //get parent based on m-order
        std::size_t parent_index = (index - 1) / m;

        //store refrences to the current T and the current's parent T
        T& current = this->at(index);
        T& parent = this->at(parent_index);

        //if we're in the right place, break
        if (!c(current, parent))
            break;

        //swap the current and parent
        std::swap(current, parent);

        //update our index
        index = parent_index;


    }
}




// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
    if(empty()){
        // ================================
        // throw the appropriate exception
        // ================================
        throw std::underflow_error("Heap empty");

    }


    //swap first and last nodes in the heap
    std::swap(std::vector<T>::front(), std::vector<T>::back());

    //remove the top node
    std::vector<T>::pop_back();

    size_t lastIndex = 0;


    while (lastIndex < size()) {
        std::vector<size_t> childrenIndices = getChildren(lastIndex);


        //bounds check for children indices
        if (childrenIndices.empty())
            return;

        //if the first child is greater than the size of the heap, return
        if (childrenIndices[0] >= size()) {
            return;
        }

        std::vector<size_t> inBoundsIndices{};

        for (size_t ts : childrenIndices) {
            if (ts < size()) {
                inBoundsIndices.push_back(ts);
            }
        }


        //all of our children are out of bounds
        //therefor we are at the lowest we can be
        //and we are done
        //so we exit :3
        if (inBoundsIndices.empty()) {
            std::cout << "uh oh 1" << std::endl;
            for (size_t ts : childrenIndices) {
                std::cout << ts << " ";
            }
            std::cout << std::endl;
            return;
        }

        //war crimes
        //sort the array with our comparator
        //this guarantees that the smallest item will be at the start of the array
        std::sort(inBoundsIndices.begin(), inBoundsIndices.end(),
            [this](int lhs, int rhs) {
                        return this->c(this->at(lhs), this->at(rhs));
            });

        //get the best child from the sorted array
        size_t bestChild = inBoundsIndices.front();


        if (!c(this->at(lastIndex), this->at(bestChild)))
            std::swap(this->at(lastIndex), this->at(bestChild));

        lastIndex = bestChild;
    }

}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
    return this->std::vector<T>::empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
    return this->std::vector<T>::size();
}

// template <typename T, typename PComparator>
// void Heap<T, PComparator>::print() {
//     for (size_t i = 0; i < this->std::vector<T>::size(); i++) {
//         std::cout << this->at(i) << " ";
//     }
//     std::cout << std::endl;
// }

template <typename T, typename PComparator>
std::vector<size_t> Heap<T, PComparator>::getChildren(size_t parentIndex) {
    std::vector<size_t> childrenIndices{};

    childrenIndices.reserve(this->m);

    for (int i = 0; i < this->m; i++) {
            childrenIndices.push_back(this->m * parentIndex + 1 + i);
    }

    return childrenIndices;
}




#endif

