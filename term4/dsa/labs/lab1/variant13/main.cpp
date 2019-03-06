#include <stdexcept>
#include <iostream>

struct ListObject
{
    std::string name;
    std::size_t code;
};

std::ostream &operator<<(std::ostream &os, const struct ListObject &obj)
{
    os << "ListObject{name: '" << obj.name << "', code: " << obj.code << "}";
    return os;
}

class LinkedList
{
  private:
    struct Node
    {
        ListObject value;
        Node *next;
        Node *previous;

        Node(ListObject value)
        {
            next = nullptr;
            previous = nullptr;
            this->value = value;
        }
    };

    LinkedList::Node *first, *last;

  public:
    LinkedList() : first{nullptr}, last{nullptr} {}

    void add(ListObject value)
    {
        LinkedList::Node *n = new LinkedList::Node(value);
        if (first == nullptr)
        {
            first = n;
            last = first;
        }
        else
        {
            LinkedList::Node *current;
            for (current = first; current; current = current->next)
            {
                if (current->value.name == n->value.name)
                {
                    return;
                }
            }

            for (current = first; current; current = current->next)
            {
                if (current->value.code > n->value.code)
                {
                    if (current->previous)
                    {
                        if (current->previous->value.code < n->value.code)
                        {
                            current->previous->next = n;
                            n->previous = current->previous;
                            current->previous = n;
                            n->next = current;
                            return;
                        }
                    }
                    else
                    {
                        first = n;
                        n->next = current;
                        current->previous = n;
                        return;
                    }
                }
                else if (current->value.code < n->value.code)
                {
                    if (current->next)
                    {
                        if (current->next->value.code > n->value.code)
                        {
                            current->next->previous = n;
                            n->next = current->next;
                            current->next = n;
                            n->previous = current;
                            return;
                        }
                    }
                    else
                    {
                        last = n;
                        current->next = n;
                        n->previous = current;
                        return;
                    }
                }
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const LinkedList &list)
    {
        os << "LinkedList{";
        for (LinkedList::Node *n = list.first; n; n = n->next)
        {
            os << n->value << (n->next ? ", " : "}");
        }
        return os;
    }
};

int main()
{
    LinkedList list{};
    for (int i = 0; i < 5; i++)
    {
        ListObject obj = ListObject{};
        obj.code = 5 - i;
        obj.name = "object #" + std::to_string(obj.code);
        list.add(obj);
        list.add(obj);
    }
    ListObject obj = ListObject{};
    obj.code = 7;
    obj.name = "object #7";
    list.add(obj);
    obj.code = 6;
    obj.name = "object #6";
    list.add(obj);

    std::cout << list << std::endl;

    return 0;
}
