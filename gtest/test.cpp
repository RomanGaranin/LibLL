#include <gtest/gtest.h>

#include "LibLL.h"

TEST(LinkedList, Creaete)
{
	mCREATE_LIST(test_list, test_tmp);
	ASSERT_EQ(test_list, (NODE*)&Stub);
       	ASSERT_EQ(test_list->next, test_list);
	ASSERT_EQ(test_list->prev, test_list);	
}

TEST(LinkedList, ConnectOne)
{
	NODE first;
	NODE* f = &first;
	mINIT_NODE(f);
	mCREATE_LIST(test_list, test_tmp);

	LL_Connect(&test_list, f, &test_tmp);
	
	ASSERT_EQ(test_list, f);
	ASSERT_NE(test_list, (NODE*)&Stub);	
	ASSERT_EQ(test_list->next, test_list);
	ASSERT_EQ(test_list->prev, test_list);
}

TEST(LinkedList, ConnectFirstSecond)
{
	NODE first;
	NODE second;
	NODE* f = &first;
	NODE* s = &second;
	mINIT_NODE(f);
	mCREATE_LIST(test_list, test_tmp);

	LL_Connect(&test_list, f, &test_tmp);
	LL_Connect(&test_list, s, &test_tmp);

	ASSERT_NE(test_list, (NODE*)&Stub);

	ASSERT_EQ(test_list, f);

	ASSERT_EQ(test_list->next, s);
	ASSERT_EQ(test_list->prev, s);
	ASSERT_EQ(test_list, f);
	ASSERT_EQ(f->next, s);
	ASSERT_EQ(f->prev, s);
	ASSERT_EQ(s->next, f);
	ASSERT_EQ(s->prev, f);
}

TEST(LinkedList, ThreeNodesDinamicaly)
{
	NODE* f = (NODE*)malloc(sizeof(NODE));
	NODE* s = (NODE*)malloc(sizeof(NODE));
	NODE* t = (NODE*)malloc(sizeof(NODE));
	
	mCREATE_LIST(test_list, test_tmp);

	LL_Connect(&test_list, f, &test_tmp);
	LL_Connect(&test_list, s, &test_tmp);
	LL_Connect(&test_list, t, &test_tmp);

	ASSERT_EQ(f->prev, t);
	ASSERT_EQ(t->next, f);

	ASSERT_EQ(f->next, s);
	ASSERT_EQ(t->prev, s);

	ASSERT_EQ(s->next, t);
	ASSERT_EQ(s->prev, f);
	
	LL_Disconnect(&test_list, f, &test_tmp);
	LL_Disconnect(&test_list, s, &test_tmp);
	LL_Disconnect(&test_list, t, &test_tmp);

	ASSERT_EQ(f->next, f);
	ASSERT_EQ(f->prev, f);

	ASSERT_EQ(s->next, s);
	ASSERT_EQ(s->prev, s);

	ASSERT_EQ(t->next, t);
	ASSERT_EQ(t->prev, t);


	ASSERT_EQ(test_list, (NODE*)&Stub);


	free(f);free(s);free(t);
}

TEST(LinkedList, Insertion)
{
	NODE* f = (NODE*)malloc(sizeof(NODE));
	NODE* s = (NODE*)malloc(sizeof(NODE));
	NODE* t = (NODE*)malloc(sizeof(NODE));
	
	mCREATE_LIST(test_list, test_tmp);

	LL_Connect(&test_list, f, &test_tmp);
	LL_Connect(&test_list, s, &test_tmp);

	LL_Insert(f, t, &test_tmp);

	ASSERT_EQ(t->next, s);
	ASSERT_EQ(t->prev, f);

	ASSERT_EQ(f->prev, s);
	ASSERT_EQ(s->next, f);

	ASSERT_EQ(t->next, s);
	ASSERT_EQ(t->prev, f);
	
	LL_Disconnect(&test_list, f, &test_tmp);
	LL_Disconnect(&test_list, s, &test_tmp);
	LL_Disconnect(&test_list, t, &test_tmp);

	ASSERT_EQ(f->next, f);
	ASSERT_EQ(f->prev, f);

	ASSERT_EQ(s->next, s);
	ASSERT_EQ(s->prev, s);

	ASSERT_EQ(t->next, t);
	ASSERT_EQ(t->prev, t);

	ASSERT_EQ(test_list, (NODE*)&Stub);

	free(f);free(s);free(t);
}
