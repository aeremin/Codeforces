#pragma once

template <class T>
struct Node {
    T data;
    Node<T>* next;
};

template <class T>
class SingleLinkedList {
  public:
    typedef Node<T> NodeType;
    typedef Node<T>* NodePtr;

  public:
    SingleLinkedList() : head(nullptr) {}

    ~SingleLinkedList() {
        auto curr = head;
        while (curr) {
            auto next = curr->next;
            delete curr;
            curr = next;
        }
    }

    bool isEmpty() const { return head == nullptr; }

    NodePtr insert(const T& elt) {
        auto node = new NodeType();
        node->data = elt;
        node->next = head;

        head = node;

        return node;
    }

    // Returns false if no such node found
    bool deleteNode(NodePtr nodePtr) {
        auto curr = head;
        NodePtr prev = nullptr;
        while (curr) {
            if (curr == nodePtr) {
                if (prev) {
                    prev->next = curr->next;
                    delete curr;
                } else {
                    // Deleting head node
                    head = curr->next;
                    delete curr;
                }
                return true;
            }
            prev = curr;
            curr = curr->next;
        }

        return false;
    }

    template <class Callable>
    void forEach(Callable callable) {
        forEachNode([callable](NodePtr node) { callable(node->data); });
    }

    void reverse() {
        NodePtr prevNode = nullptr;
        NodePtr currNode = head;
        while (currNode) {
            auto nextNode = currNode->next;
            currNode->next = prevNode;
            prevNode = currNode;
            currNode = nextNode;
        }
        head = prevNode;
    }

  private:
    template <class Callable>
    void forEachNode(Callable callable) {
        auto currNode = head;
        while (currNode) {
            callable(currNode);
            currNode = currNode->next;
        }
    }

  private:
    NodePtr head;
};
