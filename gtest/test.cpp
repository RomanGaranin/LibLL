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

	//ASSERT_EQ(Stub.node.next, (NODE*)&Stub);
	//ASSERT_EQ(Stub.node.prev, (NODE*)&Stub);

	ASSERT_EQ(test_list, f);
	ASSERT_NE(test_list, (NODE*)&Stub);	
	ASSERT_EQ(test_list->next, test_list);
	ASSERT_EQ(test_list->prev, test_list);
}

TEST(LinkedList, ConnectSecond)
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

int main(int argc, char **argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

