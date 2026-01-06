#ifndef STRING_H
#define STRING_H

typedef struct Node{
    struct Node* nextchar;
    char nowchar;
}Node;

typedef struct String{
    Node* start;
    int length;
} String;

#endif