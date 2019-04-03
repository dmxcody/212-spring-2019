#include "list.h"

Node::Node(int v) {
    data = v;
    next = NULL;
}

Node::~Node() {
}

List::List() {
    head = NULL;
    tail = NULL;
}

List::~List() {
    // TODO later
    Node *aux;
    while (head != NULL) {
        aux = head;
        head = head->next;
        delete aux;
    }
}

void List::prepend(int v) {
    // TODO now
    Node *p = new Node(v);
    // case 0: empty list
    if (head == NULL) {
        head = p;
        tail = p;
    // case 1: non-empty list
    } else {
        p->next = head;
        head = p;
    }
}