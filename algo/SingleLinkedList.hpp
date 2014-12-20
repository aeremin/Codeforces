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
    SingleLinkedList() : head(nullptr) {}

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void insert(const T& elt)
    {
        auto node = new Node<T>();
        node->data = elt;
        node->next = head;

        head = node;
    }

    template<class Callable>
    void for_each(Callable callable)
    {
        for_each_node([callable](Node<T>* node)
        {
            callable(node->data);
        });
    }

    void reverse()
    {
        Node<T>* prevNode = nullptr;
        Node<T>* currNode = head;
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
    Node<T>* head;
};

