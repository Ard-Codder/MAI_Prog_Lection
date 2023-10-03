#pragma once
#include <iostream>
#include <optional>

template <typename DataType>
class List {
private:
    struct Node {
        Node* next;
        DataType data;
    } *head;
public:
    List();
    List(List&& other); // move constructor
    ~List();
    void InsertNode(DataType newData, int position);
    void RemoveNode(int position);
    std::optional<DataType&> GetElement(size_t position);
    void PrintList();
};

template <typename DataType>
List<DataType>::List() : head(nullptr) {}

template <typename DataType>
List<DataType>::List(List&& other) : head(other.head) {
    other.head = nullptr;
}

template <typename DataType>
List<DataType>::~List() {
    Node* cur = head;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
}

template <typename DataType>
void List<DataType>::InsertNode(DataType newData, int position) {
    Node* newNode = new Node{ nullptr, newData };
    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* cur = head;
        int curPosition = 0;
        while (cur != nullptr && curPosition < position - 1) {
            cur = cur->next;
            curPosition++;
        }
        if (cur != nullptr) {
            newNode->next = cur->next;
            cur->next = newNode;
        } else {
            delete newNode; // position is out of bounds
        }
    }
}

template <typename DataType>
void List<DataType>::RemoveNode(int position) {
    if (position == 0 && head != nullptr) {
        Node* toRemove = head;
        head = head->next;
        delete toRemove;
    } else {
        Node* cur = head;
        int curPosition = 0;
        while (cur != nullptr && curPosition < position - 1) {
            cur = cur->next;
            curPosition++;
        }
        if (cur != nullptr && cur->next != nullptr) {
            Node* toRemove = cur->next;
            cur->next = toRemove->next;
            delete toRemove;
        }
    }
}

template <typename DataType>
std::optional<DataType&> List<DataType>::GetElement(size_t position) {
    Node* cur = head; 
    size_t curPosition = 0;
    while (cur != nullptr && curPosition < position) {
        cur = cur->next;
        curPosition++;
    }
    if (cur != nullptr) {
        return cur->data;
    }
    return {};
}

template <typename DataType>
void List<DataType>::PrintList() {
    Node* cur = head;
    while (cur != nullptr) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}
