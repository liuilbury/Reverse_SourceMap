//
// Created by liulizhang on 2020/5/28.
//

#include "gtest/gtest.h"
#include "rev_SourceMap.h"
class test_revMap : public ::testing::Test {
 public:
  rev_SourceMap test;
  bool check(Res A,Res B){
#ifdef DEBUG
	std::cout<<A.to_string()<<" "<<B.to_string()<<std::endl;
#endif
	return A.row == B.row && A.col == B.col && A.sources == B.sources;
  }
};
TEST_F(test_revMap, source_map_dev) {
  test.run("C:\\Users\\liulizhang\\CLionProjects\\Reverse-SourceMap\\Test\\tests\\testMap\\dev\\source-map\\bundle.js.map");
  EXPECT_TRUE(check(test.find(87,10),(Res{83,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(84,18),(Res{83,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(20,30),(Res{19,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(115,50),(Res{3,49,"webpack:///./src/index.js"})));
  EXPECT_TRUE(check(test.find(99,5),(Res{4,9,"webpack:///./src/hello.js"})));
}

TEST_F(test_revMap, cheap_module_source_map_dev) {
  test.run("C:\\Users\\liulizhang\\CLionProjects\\Reverse-SourceMap\\Test\\tests\\testMap\\dev\\cheap-module-source-map\\bundle.js.map");
  EXPECT_TRUE(check(test.find(87,10),(Res{83,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(84,18),(Res{83,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(20,30),(Res{19,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(115,50),(Res{3,1,"webpack:///./src/index.js"})));
  EXPECT_TRUE(check(test.find(99,5),(Res{4,1,"webpack:///./src/hello.js"})));
}


TEST_F(test_revMap, source_map_prod) {
  test.run("C:\\Users\\liulizhang\\CLionProjects\\Reverse-SourceMap\\Test\\tests\\testMap\\prod\\source-map\\bundle.js.map");
  //EXPECT_TRUE(check(test.find(1,911),(Res{1,911,"bundle.js"})));
  EXPECT_TRUE(check(test.find(1,902),(Res{83,10,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(1,110),(Res{19,22,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(1,983),(Res{3,49,"webpack:///./src/index.js"})));
  EXPECT_TRUE(check(test.find(1,1080),(Res{4,16,"webpack:///./src/hello.js"})));
}

/*TEST_F(test_revMap, cheap_modluesource_map_prod) {
  test.run("C:\\Users\\liulizhang\\CLionProjects\\Reverse-SourceMap\\Test\\tests\\testMap\\prod\\cheap-module-source-map\\bundle.js.map");
  EXPECT_TRUE(check(test.find(1,911),(Res{1,911,"bundle.js"})));
  EXPECT_TRUE(check(test.find(1,902),(Res{83,10,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(1,110),(Res{19,22,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(1,983),(Res{3,49,"webpack:///./src/index.js"})));
  EXPECT_TRUE(check(test.find(1,1080),(Res{4,16,"webpack:///./src/hello.js"})));
}*/
