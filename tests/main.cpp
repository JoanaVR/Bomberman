#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>



int main(int argc, char **argv){
  
  ::testing::GTEST_FLAG(print_time) = 1;

  //::testing::GTEST_FLAG(filter) = "bson_*";
 
  //::testing::GTEST_FLAG(filter) =
  //"mongodb_profile."
  //"serialization_deserialization";
 

  //::testing::GTEST_FLAG(filter) = "sql_fill_test_db.init";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
