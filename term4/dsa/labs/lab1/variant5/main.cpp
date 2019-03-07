#include <functional>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

template <typename T>
class LinkedList
{
  private:
    template <typename N>
    struct Node
    {
        N value;
        Node *next;
        Node *previous;

        Node(N value)
        {
            next = nullptr;
            previous = nullptr;
            this->value = value;
        }
    };

    LinkedList::Node<T> *first, *last;

  public:
    LinkedList() : first{nullptr}, last{nullptr} {}

    void add(T value)
    {
        LinkedList::Node<T> *n = new LinkedList::Node<T>(value);
        if (first == nullptr)
        {
            first = n;
            last = first;
        }
        else
        {
            last->next = n;
            n->previous = last;
            last = n;
        }
    }

    std::size_t get_list_hash()
    {
        std::size_t result_hash = 0;

        if (first == nullptr)
        {
            return result_hash;
        }

        result_hash = std::hash<T>()(first->value);
        for (LinkedList::Node<T> *n = first->next; n; n = n->next)
        {
            result_hash = result_hash ^ (std::hash<T>()(n->value) << 1);
        }

        return result_hash;
    }

    friend std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list)
    {
        os << "LinkedList{";
        for (LinkedList<T>::Node<T> *n = list.first; n; n = n->next)
        {
            os << n->value << (n->next ? ", " : "}");
        }
        return os;
    }
};

int main()
{
    LinkedList<int> equal_list1{}, equal_list2{}, different_list3{};
    for (std::size_t i = 0; i < 7; i++)
    {
        int value = std::rand() % 100;
        equal_list1.add(value);
        equal_list2.add(value);
        different_list3.add(value + 5);
        different_list3.add(value - 5);
    }

    std::cout << equal_list1 << std::endl;
    std::cout << equal_list2 << std::endl;
    std::cout << different_list3 << std::endl;

    if (equal_list1.get_list_hash() == equal_list2.get_list_hash())
    {
        std::cout << "list1 is equal to list2" << std::endl;
    }
    else
    {
        std::cout << "list1 is not equal to list2 => program error" << std::endl;
    }

    if (equal_list1.get_list_hash() != different_list3.get_list_hash())
    {
        std::cout << "list1 is not equal to list3" << std::endl;
    }
    else
    {
        std::cout << "list1 is equal to list3 => program error" << std::endl;
    }

    if (equal_list2.get_list_hash() != different_list3.get_list_hash())
    {
        std::cout << "list2 is not equal to list3" << std::endl;
    }
    else
    {
        std::cout << "list2 is equal to list3 => program error" << std::endl;
    }

    return 0;
}
