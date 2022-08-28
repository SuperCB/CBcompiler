#pragma once
#include <map>
using u32 = unsigned int;

enum class OpType {
    Add = 0,
    Sub,
    Mul,
    Div,
    Mod,
    Lt,
    Le,
    Ge,
    Gt,
    Eq,
    Ne,
    And,
    Or
};

template<class Node>
class ilist {
public:

    Node *head;
    Node *tail;

    ilist():head(nullptr),tail(nullptr) {  }
    // insert newNode before insertBefore
    void insertBefore(Node *newNode, Node *insertBefore) {
        newNode->prev = insertBefore->prev;
        newNode->next = insertBefore;
        if (insertBefore->prev) {
            insertBefore->prev->next = newNode;
        }
        insertBefore->prev = newNode;

        if (head == insertBefore) {
            head = newNode;
        }
    }

    // insert newNode after insertAfter
    void insertAfter(Node *newNode, Node *insertAfter) {
        newNode->prev = insertAfter;
        newNode->next = insertAfter->next;
        if (insertAfter->next) {
            insertAfter->next->prev = newNode;
        }
        insertAfter->next = newNode;

        if (tail == insertAfter) {
            tail = newNode;
        }
    }

    // insert newNode at the end of ilist
    void insertAtEnd(Node *newNode) {
        newNode->prev = tail;
        newNode->next = nullptr;

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // insert newNode at the begin of ilist
    void insertAtBegin(Node *newNode) {
        newNode->prev = nullptr;
        newNode->next = head;

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            head = newNode;
        }
    }

    // remove node from ilist
    void remove(Node *node) {
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
    }
};

template<typename D, typename B>
bool isa(const B *b) {
    if constexpr (std::is_base_of_v<D, B>) {
        return true;
    } else {
        static_assert(std::is_base_of_v<B, D>);
        return D::classof(b);
    }
}

template<typename D, typename B>
const D *dyn_cast(const B *b) {
    return isa<D>(b) ? static_cast<const D *>(b) : nullptr;
}

template<typename D, typename B>
D *dyn_cast(B *b) {
    return isa<D>(b) ? static_cast<D *>(b) : nullptr;
}

template<typename D, typename B>
const D *dyn_cast_nullable(const B *b) {
    return b && isa<D>(b) ? static_cast<const D *>(b) : nullptr;
}

template<typename D, typename B>
D *dyn_cast_nullable(B *b) {
    return b && isa<D>(b) ? static_cast<D *>(b) : nullptr;
}

// 是否是两个相反的比较运算符，即 l <a> r 是否等于 r <b> l
//inline bool isrev(Op a, Op b) {
//    return (a == Lt && b == Gt) || (a == Gt && b == Lt) || (a == Le && b == Ge) || (a == Ge && b == Le);
//}
// namespace op

template<class T>
class IndexMapper {
    std::map<T *, u32> mapping;
    u32 index_max = 0;
public:
    u32 alloc() { return index_max++; }

    u32 get(T *t) {
        auto [it, inserted] = mapping.insert({t, index_max});
        index_max += inserted;
        return it->second;
    }
};