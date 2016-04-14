#include "buffer.h"
#include <gtest/gtest.h>


class BUFFER_INIT : public testing::Test{
public:
/*
    BUFFER_CREATE(buffer,50);
  virtual void SetUp(){
    buffer_clear(&buffer)
  }
  virtual void TearDown(){
  }
*/
};

TEST_F(BUFFER_INIT, macro_init){
  BUFFER_CREATE(buffer_1,10);
  ASSERT_EQ(10,buffer_1.capacity);
  ASSERT_EQ(0,buffer_1.mounted);
  ASSERT_EQ(1,buffer_1.info);
  ASSERT_EQ(0,buffer_1._entry);
  ASSERT_EQ(0,buffer_1._exit);
}

TEST_F(BUFFER_INIT, function_init){
  uint8_t circuit_buffer[20]
  buffer_init(buffer_2,circuit_buffer,20);
  ASSERT_EQ(10,buffer_1.capacity);
  ASSERT_EQ(0,buffer_1.mounted);
  ASSERT_EQ(1,buffer_1.info);
  ASSERT_EQ(0,buffer_1._entry);
  ASSERT_EQ(0,buffer_1._exit);
}
