template<class T> 
struct Node
{
    T data;
    Node<T>* next;
};

template<class T> 
class SingleLinkedList
{
public:
    typedef Node<T>  NodeType;
    typedef Node<T>* NodePtr;

public:
    SingleLinkedList() : head(nullptr) {}

    ~SingleLinkedList()
    {
        auto curr = head;
        while (curr)
        {
            auto next = curr->next;
            delete curr;
            curr = next;
        }
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void insert(const T& elt)
    {
        auto node = new NodeType();
        node->data = elt;
        node->next = head;

        head = node;
    }

    template<class Callable>
    void for_each(Callable callable)
    {
        for_each_node([callable](NodePtr node)
        {
            callable(node->data);
        });
    }

    void reverse()
    {
        NodePtr prevNode = nullptr;
        NodePtr currNode = head;
        while (currNode)
        {
            auto nextNode = currNode->next;
            currNode->next = prevNode;
            prevNode = currNode;
            currNode = nextNode;
        }
        head = prevNode;
    }

private:
    template<class Callable>
    void for_each_node(Callable callable)
    {
        auto currNode = head;
        while (currNode)
        {
            callable(currNode);
            currNode = currNode->next;
        }
    }

private:
    NodePtr head;
};

