#define CATCH_CONFIG_MAIN
#include "../catch/catch_amalgamated.hpp"
#include <iostream>
#include <stdexcept>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};

class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("List Basic Functions", "[list]")
{
    SECTION("Empty on fresh list")
    {
        List list;
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    SECTION("Empty after adding and removing elements")
    {
        List list;

        list.PushBack(42);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.Size() == 1);

        list.PopBack();
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);

        list.PushFront(100);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.Size() == 1);

        list.PopFront();
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    SECTION("Clear function - empty list")
    {
        List list;

        REQUIRE_NOTHROW(list.Clear());
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);

        list.PushBack(10);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
    }

    SECTION("Clear function - list with elements")
    {
        List list;

        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        list.PushFront(0);
        REQUIRE(list.Size() == 4);
        REQUIRE(list.Empty() == false);

        REQUIRE_NOTHROW(list.Clear());
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);

        list.PushBack(100);
        list.PushFront(200);
        REQUIRE(list.Size() == 2);
        REQUIRE(list.Empty() == false);
    }

    SECTION("Clear function - mixed operations")
    {
        List list;

        for (int i = 0; i < 10; ++i) {
            if (i % 2 == 0) {
                list.PushBack(i);
            }
            else {
                list.PushFront(i);
            }
        }
        REQUIRE(list.Size() == 10);

        list.Clear();
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);

        for (int i = 0; i < 5; ++i) {
            list.PushBack(i * 10);
        }
        REQUIRE(list.Size() == 5);
    }

    SECTION("Size function with multiple operations")
    {
        List list;

        REQUIRE(list.Size() == 0);

        for (int i = 1; i <= 5; ++i) {
            list.PushBack(i);
            REQUIRE(list.Size() == i);
        }

        for (int i = 6; i <= 10; ++i) {
            list.PushFront(i);
            REQUIRE(list.Size() == i);
        }

        for (int i = 10; i > 0; --i) {
            list.PopBack();
            REQUIRE(list.Size() == i - 1);
        }

        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    SECTION("Size function with large number of elements")
    {
        List list;
        const int largeSize = 1000;

        for (int i = 0; i < largeSize; ++i) {
            if (i % 3 == 0) {
                list.PushFront(i);
            }
            else {
                list.PushBack(i);
            }
        }

        REQUIRE(list.Size() == largeSize);
        REQUIRE(list.Empty() == false);

        list.Clear();
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Empty and Size after exception handling")
    {
        List list;

        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);

        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);

        list.PushBack(42);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);

        list.PopBack();
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);

        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
    }
};