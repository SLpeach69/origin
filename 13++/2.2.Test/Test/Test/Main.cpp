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

TEST_CASE("List PushBack and PushFront functions", "[list]")
{
    SECTION("PushBack on empty list")
    {
        List list;
        REQUIRE(list.Empty() == true);

        list.PushBack(42);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
    }

    SECTION("PushFront on empty list")
    {
        List list;
        REQUIRE(list.Empty() == true);

        list.PushFront(100);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
    }

    SECTION("Multiple PushBack operations")
    {
        List list;

        for (int i = 1; i <= 5; i++) {
            list.PushBack(i * 10);
            REQUIRE(list.Size() == i);
        }

        REQUIRE(list.Empty() == false);
        REQUIRE(list.Size() == 5);
    }

    SECTION("Multiple PushFront operations")
    {
        List list;

        for (int i = 1; i <= 5; i++) {
            list.PushFront(i * 10);
            REQUIRE(list.Size() == i);
        }

        REQUIRE(list.Empty() == false);
        REQUIRE(list.Size() == 5);
    }

    SECTION("Mixed PushBack and PushFront operations")
    {
        List list;

        list.PushBack(1);  
        list.PushFront(2); 
        list.PushBack(3);  
        list.PushFront(4); 

        REQUIRE(list.Size() == 4);
        REQUIRE(list.Empty() == false);
    }
};

TEST_CASE("List PopBack and PopFront functions", "[list]")
{
    SECTION("PopBack on empty list should throw")
    {
        List list;
        REQUIRE(list.Empty() == true);

        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("PopFront on empty list should throw")
    {
        List list;
        REQUIRE(list.Empty() == true);

        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("PopBack on single element list")
    {
        List list;
        list.PushBack(42);
        REQUIRE(list.Size() == 1);

        int value = list.PopBack();
        REQUIRE(value == 42);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("PopFront on single element list")
    {
        List list;
        list.PushFront(100);
        REQUIRE(list.Size() == 1);

        int value = list.PopFront();
        REQUIRE(value == 100);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Multiple PopBack operations")
    {
        List list;

        list.PushBack(10);
        list.PushBack(20);
        list.PushBack(30);
        REQUIRE(list.Size() == 3);

        REQUIRE(list.PopBack() == 30);
        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopBack() == 20);
        REQUIRE(list.Size() == 1);

        REQUIRE(list.PopBack() == 10);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Multiple PopFront operations")
    {
        List list;

        list.PushFront(10);
        list.PushFront(20);
        list.PushFront(30);
        REQUIRE(list.Size() == 3);

        REQUIRE(list.PopFront() == 30);
        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopFront() == 20);
        REQUIRE(list.Size() == 1);

        REQUIRE(list.PopFront() == 10);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Mixed PopBack and PopFront operations")
    {
        List list;

        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        list.PushBack(4);
        REQUIRE(list.Size() == 4);

        REQUIRE(list.PopFront() == 1); 
        REQUIRE(list.PopBack() == 4);  
        REQUIRE(list.PopFront() == 2); 
        REQUIRE(list.PopBack() == 3);  

        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }
};

TEST_CASE("Complex scenario: mixed operations", "[list]")
{
    SECTION("Complex usage scenario 1")
    {
        List list;

        list.PushBack(1);
        list.PushFront(2);
        list.PushBack(3);
        list.PushFront(4);
        REQUIRE(list.Size() == 4);

        REQUIRE(list.PopFront() == 4); 
        REQUIRE(list.PopBack() == 3); 

        list.PushBack(5);
        list.PushFront(6);
        REQUIRE(list.Size() == 4);

        REQUIRE(list.PopFront() == 6); 
        REQUIRE(list.PopFront() == 2); 
        REQUIRE(list.PopBack() == 5); 
        REQUIRE(list.PopFront() == 1); 

        REQUIRE(list.Empty() == true);
    }

    SECTION("Complex usage scenario 2 - large operations")
    {
        List list;
        const int operationCount = 100;

        for (int i = 0; i < operationCount; i++) {
            if (i % 2 == 0) {
                list.PushFront(i);
            }
            else {
                list.PushBack(i);
            }
        }
        REQUIRE(list.Size() == operationCount);

        for (int i = 0; i < operationCount / 2; i++) {
            if (i % 2 == 0) {
                list.PopFront();
            }
            else {
                list.PopBack();
            }
        }
        REQUIRE(list.Size() == operationCount / 2);

        for (int i = 0; i < 25; i++) {
            list.PushBack(i + 100);
        }
        REQUIRE(list.Size() == (operationCount / 2 + 25));

        while (!list.Empty()) {
            list.PopBack();
        }

        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);

        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
    }

    SECTION("Complex usage scenario 3 - alternating operations")
    {
        List list;

        list.PushBack(10);    
        list.PushFront(20);   
        REQUIRE(list.PopBack() == 10);   
        list.PushBack(30);    
        list.PushFront(40);   
        REQUIRE(list.PopFront() == 40);  
        list.PushBack(50);    
        REQUIRE(list.PopBack() == 50);    
        list.PushFront(60);   
        REQUIRE(list.PopFront() == 60);   

        REQUIRE(list.Size() == 2);
        REQUIRE(list.PopFront() == 20);
        REQUIRE(list.PopBack() == 30);
        REQUIRE(list.Empty() == true);
    }
};