Linked List Library
============
## Status:
[![CodeFactor](https://www.codefactor.io/repository/github/romangaranin/libll/badge)](https://www.codefactor.io/repository/github/romangaranin/libll)
## Brief:
The project is in progress ...

A basic linked list designed for creating more complex linked lists.

https://romangaranin.github.io/LibLL/

## Contents:
* Connecting node to the end of the linked list.
* Inserting node to the linked list.
* Disconnecting node from the linked list.
* Disconnecting the first node from the linked list.
* Replace node from one linked list to the end of another linked list.
* Replace node from one linked list to another linked list (Disconnect from source list and insert to destination list).
* Find node in the list.
* Foreach list.
* Print List to standart output.
* Removing List (freeing memory).

NOTES: 
Connecting - doesn't mean creating the node in memory. User have to create the node befor connecting.
Disconneting - doesn't mean deleting the node from memory.

## Terms and definitions:

## Description:
This is a simple library for creating and managing a linked lists written in C.

The main element of linked list - node. The node is just a struct that contains two pointers only:

- "next" - pointer to the next node.
- "prev" - pointer to the previous node.

Implementatoin of this library assumes:
- node can be created statically and dynamically;
- Nodes can exists independently from any lists; 
- Independent node have to point to itself by both pointers;
- The list is closed. It means that the "next" pointer of the last node points to the first node of the list,  and the "prev" pointer of the first node points to the last node of the list;
- Each list have its own pointer that point to the first element of list;
- Each list have its temporary pointer for safe management;
- If the list is empty its pointer will point to a stub node. A stub node implemented by this library; 
## How to use(sketch): 
1) Create your own data type based on node type. Wherein the node type should be in the head of created data type.
2) Create a pointer to your linked. It should point to stub node defined in library.
3) Create a temporary pointer. It will use for safe management of linked list.
4) Create a nodes using data type you created for your linked list.
5) Manage linked list using the library, before any manipulation cast your data types to node data type.








