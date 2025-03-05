//
// Created by gamma on 3/4/2025.
//

#include "heap.h"

int main(int argc, char* argv[]){
    Heap<int> heap{};

    heap.push(1);

    heap.push(2);

    heap.push(3);


    heap.push(5);
    heap.push(7);

    heap.push(8);
    heap.push(6);


    heap.push(4);

    // heap.print();

    heap.pop();

    // heap.print();
}