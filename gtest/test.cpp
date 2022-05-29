#include <gtest/gtest.h>

#include "LibLL.h"

TEST(LinkedList, Creaete)
{
  ASSERT_EQ(2, 2);
}

int main(int argc, char **argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
