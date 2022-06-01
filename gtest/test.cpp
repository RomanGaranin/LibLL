#include <gtest/gtest.h>

#include "LibLL.h"

TEST(ListCreate, CreaeteWithMacro)
{
	mCREATE_LIST(test_list, test_tmp);
	ASSERT_EQ(test_list, (NODE*)&Stub);
       	ASSERT_EQ(test_list->next, test_list);
	ASSERT_EQ(test_list->prev, test_list);	
}

TEST(Connect, OneStaticNode)
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

TEST(Connect, TwoStaticNodes)
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

TEST(Connect, ThreeDynamicNodes)
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

TEST(InsertOneDynamicNode, InsertBeetwenDynamicTwo)
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

TEST(InsertTwoDynamicNodes, InsertBeetwenToDynamicNodes)
{
	NODE* first = (NODE*)malloc(sizeof(NODE));
	NODE* second = (NODE*)malloc(sizeof(NODE));

	NODE* third = (NODE*)malloc(sizeof(NODE));
	NODE* fours = (NODE*)malloc(sizeof(NODE));

	mCREATE_LIST(test_list1, test_tmp);

	LL_Connect(&test_list1, first, &test_tmp);
	LL_Connect(&test_list1, second, &test_tmp);

	LL_Insert(first, third, &test_tmp);
	LL_Insert(third, fours, &test_tmp);
	
	ASSERT_EQ(first->next, third);
	ASSERT_EQ(third->prev, first);
	ASSERT_EQ(third->next, fours);
	ASSERT_EQ(fours->prev, third);
	ASSERT_EQ(fours->next, second);
	ASSERT_EQ(second->prev, fours);

	ASSERT_EQ(first->prev, second);
	ASSERT_EQ(second->next, first);

	free(first);free(second);free(third);free(fours);
}
