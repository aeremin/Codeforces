#pragma once
#include <utility>
#include <assert.h>

template<typename T>
class CyclicDoubleLinkedList;

template<typename T>
struct Node
{
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    CyclicDoubleLinkedList<T> childs;
    bool marked = false;

    T data;

    Node(const T& val) : data(val) {};
};

template<typename T>
class CyclicDoubleLinkedList
{
public:
    typedef Node<typename T> NodeType;
    
    CyclicDoubleLinkedList() : head_(nullptr), size_(0) {}

    ~CyclicDoubleLinkedList()
    {
        NodeType* curr = nullptr;
        while (curr = head())
        {
            extractNode(curr);
            delete curr;
        }
    }

    NodeType* head() const
    {
        return head_;
    }

    int size() const
    {
        return size_;
    }

    void insertNodeAfter(NodeType* insertAfter, NodeType* nodeToInsert)
    {
        nodeToInsert->right = insertAfter->right;
        nodeToInsert->left = insertAfter;
        nodeToInsert->right->left = nodeToInsert;
        nodeToInsert->left->right = nodeToInsert;

        size_++;
    }

    void insertNode(NodeType* nodeToInsert)
    {
        if (!head())
        {
            head_ = nodeToInsert;
            head_->left = head_;
            head_->right = head_;
            size_++;
        }
        else
        {
            insertNodeAfter(head(), nodeToInsert);
        }
    }

    void extractNode(NodeType* nodeToExtract)
    {
        size_--;

        if (nodeToExtract == head_)
        {
            if (head_->right == head_)
            {
                head_ = nullptr;
                return;
            }
            else
                head_ = head_->left;
        }
        nodeToExtract->left->right = nodeToExtract->right;
        nodeToExtract->right->left = nodeToExtract->left;
    }

    void mergeOtherList(CyclicDoubleLinkedList<T>& other)
    {
        std::swap(head_->left, other.head_->left);
        other.head = nullptr;
        size_ += other.size_;
        other.size_ = 0;
    }

    template<class Callable>
    void forEachNode(Callable callable)
    {
        auto currNode = head();
        for (int i = 0; i < size(); ++i)
        {
            callable(currNode);
            currNode = currNode->right;
        }
    }
    
private:
    NodeType* head_;
    int size_;
};

template<typename T>
class FibonacciHeap
{
public:
    typedef Node<typename T> NodeType;

    FibonacciHeap() : minNode_(nullptr), size_(0) {}

    bool isEmpty() const
    {
        assert((topLevel_.size() == 0) == (minNode_ == nullptr));
        return (topLevel_.size() == 0);
    }
    
    NodeType* push(const T& data)
    {
        auto newNode = new NodeType(data);
        updateMin_(newNode);
        topLevel_.insertNode(newNode);
        size_++;
        return newNode;
    }

    const T& getMin() const
    {
        assert(minNode_);
        return minNode_->data;
    }

    void popMin()
    {
        auto nodeToRemove = minNode_;
        assert(nodeToRemove);
        bubbleUpChilds_(nodeToRemove);
        topLevel_.extractNode(nodeToRemove);

        minNode_ = nullptr;
        if (nodeToRemove != nodeToRemove->right)
            consolidate_();

        delete nodeToRemove;
        size_--;
    }

    void decreaseValue(NodeType* node, const T& value)
    {
        assert(value <= node->data);
        node->data = value;
        auto parent = node->parent;
        if (parent && (node->data > parent->data))
        {
            cut_(node, parent);
            cascadingCut_(parent);
        }
        
        updateMin_(node);
    }

    void remove(NodeType* node)
    {
        decreaseValue(node, std::numeric_limits<T>::min());
        popMin();
    }

    void mergeOther(FibonacciHeap<T>& other)
    {
        topLevel_.mergeOtherList(other.topLevel_);
        size_ += other.size_;
        if (!minNode_ || (other.minNode_ && other.minNode_->data < minNode_->data))
            minNode_ = other.minNode_;
    }

private:
    void bubbleUpChilds_(NodeType* node)
    {
        assert(node->parent == nullptr);
        NodeType* currChild = nullptr;
        while (currChild = node->childs.head())
        {
            node->childs.extractNode(currChild);
            currChild->parent = nullptr;
            topLevel_.insertNode(currChild);
        }
    }

    void consolidate_()
    {
        int maxDegree = 2 * (int) (log(size_) + 1);
        std::vector<NodeType*> nodeOfDegree(maxDegree, nullptr);
        int nodesToProcess = topLevel_.size();
        auto currNode = topLevel_.head();
        for (int i = 0; i < nodesToProcess; ++i)
        {
            auto nextNode = currNode->right;
            
            while (auto sameSizeNode = nodeOfDegree[currNode->childs.size()])
            {
                if (currNode->data >= sameSizeNode->data)
                    std::swap(currNode, sameSizeNode);
                nodeOfDegree[currNode->childs.size()] = nullptr;
                makeChildOf_(currNode, sameSizeNode);               
            }
            nodeOfDegree[currNode->childs.size()] = currNode;
            currNode = nextNode;
        }

        topLevel_.forEachNode([&](NodeType* node) {updateMin_(node); });
    }

    void makeChildOf_(NodeType* parent, NodeType* child)
    {
        topLevel_.extractNode(child);
        parent->childs.insertNode(child);
        child->parent = parent;
        child->marked = false;
    }

    void cut_(NodeType* child, NodeType* parent)
    {
        parent->childs.extractNode(child);
        child->parent = nullptr;
        topLevel_.insertNode(child);
        child->marked = false;
    }

    void cascadingCut_(NodeType* node)
    {
        auto parent = node->parent;
        if (parent)
        {
            if (parent->marked)
            {
                cut_(node, parent);
                cascadingCut_(parent);
            }
            else
                parent->marked = true;
        }
    }
    
    void updateMin_(NodeType* candidate)
    {
        if (!minNode_ || candidate->data < minNode_->data)
            minNode_ = candidate;
    }

    bool validateMinProperty_(NodeType* node)
    {
        NodeType* child = node->childs.head();
        
        node->childs.forEachNode([&](NodeType* child)
        {
            assert(child->data >= node->data);
            validateMinProperty_(child);
        });
        return true;
    }

    void validateTopLevelHaveNoParents_()
    {
        topLevel_.forEachNode([&](NodeType* node)
        {
            assert(child->parent = nullptr);
        });
    }

private:
    CyclicDoubleLinkedList<T> topLevel_;
    NodeType* minNode_;
    int size_;
};

template<typename T>
std::ostream& operator<<(std::ostream& outStream, Node<T>& node)
{
    outStream << node.data << " {";
    node.childs.forEachNode([&](Node<T>* node)
    {
        outStream << *node << " ";
    });
    outStream << " }";
    return outStream;
}