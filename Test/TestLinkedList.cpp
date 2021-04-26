extern "C" {
	#include "../LinkedList/Inc/Node.h"
	#include "../LinkedList/Src/Node.c"
}

NODE *TestList = (NODE*)&Stub;
NODE *TestTmp = (NODE *)&Stub;

TEST(TestCase0, TestName) {
  EXPECT_EQ(TestList, TestTmp);
  EXPECT_EQ((NODE*)&Stub, TestTmp);
  EXPECT_EQ(TestList, (NODE*)&Stub);
}

mCREATE_LIST(TestList1, ListTmp1)

TEST(TestCase01, TestName) {
  EXPECT_EQ(TestList, TestTmp);
  EXPECT_EQ((NODE *)&Stub, TestTmp);
  EXPECT_EQ(TestList, (NODE *)&Stub);
}

TEST(TestCase1, TestName) {
  NODE *node = (NODE *)malloc(sizeof(NODE));
  Node_Connect(&TestList, node, &TestTmp);
  EXPECT_EQ(TestList, node);
  EXPECT_EQ(node->next, node);
  EXPECT_EQ(node->prev, node);

  Node_Disconnect(&TestList, node, &TestTmp);

  EXPECT_NE(TestList, node);

  EXPECT_EQ(node->next, node);
  EXPECT_EQ(node->prev, node);

  EXPECT_EQ(TestList, TestTmp);
  EXPECT_EQ((NODE *)&Stub, TestTmp);
  EXPECT_EQ(TestList, (NODE *)&Stub);

  free(node);
  //EXPECT_TRUE(true);
}

TEST(TestCase2, TestName) {
  NODE *node1 = (NODE *)malloc(sizeof(NODE));
  NODE *node2 = (NODE *)malloc(sizeof(NODE));
  Node_Connect(&TestList, node1, &TestTmp);
  Node_Connect(&TestList, node2, &TestTmp);
  EXPECT_EQ(TestList, node1);
  EXPECT_EQ(node1->next, node2);
  EXPECT_EQ(node1->prev, node2);
  EXPECT_EQ(node2->next, node1);
  EXPECT_EQ(node2->prev, node1);

  Node_Disconnect(&TestList, node1, &TestTmp);
 
  EXPECT_EQ(node1->next, node1);
  EXPECT_EQ(node1->prev, node1);

  EXPECT_EQ(TestList, node2);
  EXPECT_EQ(node2->next, node2);
  EXPECT_EQ(node2->prev, node2);

  Node_Disconnect(&TestList, node2, &TestTmp);

  EXPECT_NE(TestList, node2);

  EXPECT_EQ(node2->next, node2);
  EXPECT_EQ(node2->prev, node2);

  EXPECT_EQ(TestList, TestTmp);
  EXPECT_EQ((NODE *)&Stub, TestTmp);
  EXPECT_EQ(TestList, (NODE *)&Stub);

  Node_Disconnect(&TestList, node1, &TestTmp);

  free(node1);
  free(node2);
}

TEST(TestCase3, TestName) {
  NODE *node1 = (NODE *)malloc(sizeof(NODE));
  NODE *node2 = (NODE *)malloc(sizeof(NODE));
  NODE *node3 = (NODE *)malloc(sizeof(NODE));
  NODE *node4 = (NODE *)malloc(sizeof(NODE));
  if (NULL == node1) {
    return;
  }
  if (NULL == node2) {
    return;
  }
  if (NULL == node3) {
    return;
  }
  if (NULL == node4) {
    return;
  }
  mINIT_NODE(node1)
  mINIT_NODE(node2)
  mINIT_NODE(node3)
  mINIT_NODE(node4)

  Node_Connect(&TestList, node1, &TestTmp);
  Node_Connect(&TestList, node2, &TestTmp);
  Node_Connect(&TestList, node3, &TestTmp);
  Node_Insert(node2, node4, &TestTmp);

  EXPECT_EQ(node2->next, node4);
  EXPECT_EQ(node4->prev, node2);
  EXPECT_EQ(node4->next, node3);
  EXPECT_EQ(node3->prev, node4);

  Node_Disconnect(&TestList, node2, &TestTmp);
  EXPECT_EQ(node1->next, node4);
  EXPECT_EQ(node4->prev, node1);

  Node_Disconnect(&TestList, node1, &TestTmp);
  Node_Disconnect(&TestList, node3, &TestTmp);
  Node_Disconnect(&TestList, node4, &TestTmp);

  EXPECT_EQ(node1->next, node1);

  free(node1);
  free(node2);
  free(node3);
  free(node4);

  EXPECT_EQ(TestList, TestTmp);
  EXPECT_EQ((NODE *)&Stub, TestTmp);
  EXPECT_EQ(TestList, (NODE *)&Stub);

}