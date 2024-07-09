Linked List Library
============
## Статус:
[![CodeFactor](https://www.codefactor.io/repository/github/owlsurf/libll/badge)](https://www.codefactor.io/repository/github/owlsurf/libll)
[![CMakeGoogletest](https://github.com/OwlSurf/LibLL/actions/workflows/cmake.yml/badge.svg)](https://github.com/OwlSurf/LibLL/actions/workflows/cmake.yml)
## Краткое описание:

Библиотека для создания связных списков и управления ими.

[Документация](https://owlsurf.github.io/LibLL/)

## Содержание:
* [Добавление узла в конец связного списка.](https://owlsurf.github.io/LibLL/LibLL_8c.html#a8274f49f06aa1cf53309da647eb4b06f)
* [Вставка узла в связный спмсок.](https://owlsurf.github.io/LibLL/LibLL_8c.html#a0d58c85ad363abb9b05062ab5e48c1cf)
* [Отключение узла из связного списка.](https://owlsurf.github.io/LibLL/LibLL_8c.html#a4dace3d699f8e0e8eccc721ef5b64c21)
* [Отключение первого узла от связного списка.](https://owlsurf.github.io/LibLL/LibLL_8c.html#a6a39a1c6328eb13c0c6166fb13d1e43c)
* [Перемещение узла из одного связного списка в конец другого.](https://owlsurf.github.io/LibLL/LibLL_8c.html#a87970dc9c75edeeab8ac03eb63452baf)
* [Перемещение узла из одного связного списка в другой.](https://owlsurf.github.io/LibLL/LibLL_8c.html#a84a82de5aa962aa5de7c2239dff19a16)
* [Поиск узла в связном списко.](https://owlsurf.github.io/LibLL/LibLL_8c.html#ab9dbdec177ff191a766d28a90e2d9ba4)
* [Перебор листа.](https://owlsurf.github.io/LibLL/LibLL_8c.html#a22eddbec2ce1ca0eac1d7385558044e6)
* [Удаление листа](https://owlsurf.github.io/LibLL/LibLL_8c.html#a2659814c359a3f001fdc7701e5515bbb) Только для листов созданных динамически.

Внимание: 
Добавление -не ознаяает создание узла в памяти.Пользователю необходимо создать узел перед добавлением.
Отключение  - Не означает удаление узла из памяти.

## Термины и определения:

## Описание:
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
## How to build tests.
For tests [googletest framework](https://github.com/google/googletest) uses. 	

Needed environment:
- cmake;
- gcc;
- g++;
- libgtest-dev;

For build tests type:

    cmake -S gtest/ -B gtest/build 
    cmake --build gtest/build
    make -C gtest/build/

For Run test type:

    cd gtest/build/; ctest; cd ../../
    or 
    ./gtest/build/runtests

## How to use(sketch): 
1) Create your own data type based on node type. Wherein the node type should be in the head of created data type.

Example:
```C
typedef struct obj {
    NODE node;         
    uint16_t id;       
    void (*action)();
} OBJ;
```
2) Create a pointer to your linked list. It should point to stub node defined in library.
3) Create a temporary pointer. It will use for safe management of linked list.

You can use mCREATE_LIST macro.

Example: 
```C
    mCREATE_LIST(ObjList, ObjListTmp);
```
It will create two initialised pointers:
```C
   	NODE* ObjList = (NODE*)&Stub;
	NODE* ObjListTmp = (NODE*)&Stub;
```

4) Create a nodes using data type you created for your linked list.

Example: 
```C
OBJ * obj1 = malloc(sizeof(OBJ));
obj1->id  = 1;
obj1->action = some_real_function1;

OBJ * obj2 = malloc(sizeof(OBJ));
obj2->id  = 2;
obj2->action = some_real_function2;
```

5) Manage linked list using the library, before any manipulation cast your data types to node data type.

Example:
```C
LL_Connect(&ObjList, (NODE*)obj1, &ObjListTmp);
LL_Connect(&ObjList, (NODE*)obj2, &ObjListTmp);

NODE* node = Objlist;
do {
	ObjListTmp = node->next;
	node->action();
	node = ObjListTmp;
    } while ((ObjListTmp != ObjList));

LL_Disconnect(&ObjList, (NODE*)obj1, &ObjListTmp);
LL_Disconnect(&ObjList, (NODE*)obj2, &ObjListTmp);

free(obj1);
free(obj2);
```
