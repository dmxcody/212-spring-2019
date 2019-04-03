#ifndef __LIST__H__
#define __LIST__H__

#ifndef NULL
#define NULL 0x00
#endif

class Node {
    private:
        int data;
        Node *next;
    public:
        Node(int v);
        ~Node();

    friend class List;
};

class List {
    private:
        Node *head;
        Node *tail;

    public:
        List();
        ~List();

        void prepend(int v);
};

#endif