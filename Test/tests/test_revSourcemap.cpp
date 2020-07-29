//
// Created by liulizhang on 2020/5/28.
//

#include "gtest/gtest.h"
#include "RevSourceMap.h"
class test_revMap : public ::testing::Test {
 public:
  RevSourceMap test;
  bool check(Res A,Res B){
#ifdef DEBUG
	std::cout<<A.to_string()<<" "<<B.to_string()<<std::endl;
#endif
	return A.row == B.row && A.col == B.col && A.sources == B.sources;
  }
};
TEST_F(test_revMap, source_map_dev) {
  test.runFile("Test/tests/testMap/dev/source-map/bundle.js.map");
  EXPECT_TRUE(check(test.find(87,10),(Res{83,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(84,18),(Res{83,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(20,30),(Res{19,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(115,50),(Res{3,49,"webpack:///./src/index.js"})));
  EXPECT_TRUE(check(test.find(99,5),(Res{4,9,"webpack:///./src/hello.js"})));
}

TEST_F(test_revMap, cheap_module_source_map_dev) {
  test.runFile("Test/tests/testMap/dev/cheap-module-source-map/bundle.js.map");
  EXPECT_TRUE(check(test.find(87,10),(Res{83,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(84,18),(Res{83,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(20,30),(Res{19,1,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(115,50),(Res{3,1,"webpack:///./src/index.js"})));
  EXPECT_TRUE(check(test.find(99,5),(Res{4,1,"webpack:///./src/hello.js"})));
}


TEST_F(test_revMap, source_map_prod) {
  test.runFile("Test/tests/testMap/prod/source-map/bundle.js.map");
  //EXPECT_TRUE(check(test.find(1,911),(Res{1,911,"bundle.js"})));
  EXPECT_TRUE(check(test.find(1,902),(Res{83,10,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(1,110),(Res{19,22,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(1,983),(Res{3,49,"webpack:///./src/index.js"})));
  EXPECT_TRUE(check(test.find(1,1080),(Res{4,16,"webpack:///./src/hello.js"})));
}

TEST_F(test_revMap, pixui_test) {
	test.runFile("Test/tests/testMap/dev/pixui_test/main.js.map");
	EXPECT_TRUE(check(test.find(1,78460),(Res{64,39,"webpack:///E:/work_git/reactH5/pandora/html/src/pandora/radio/pages/MainPanel.tsx"})));
	EXPECT_TRUE(check(test.find(1,58515),(Res{195,36,"webpack:///E:/work_git/reactH5/pandora/html/src/pandora/radio/pages/HomeContent.tsx"})));
	EXPECT_TRUE(check(test.find(1,57925),(Res{103,45,"webpack:///E:/work_git/reactH5/pandora/html/src/pandora/radio/pages/HomeContent.tsx"})));
	EXPECT_TRUE(check(test.find(1,28457),(Res{154,40,"webpack:///E:/work_git/reactH5/pandora/html/src/pandora/radio/js/frame/pandora_sdk_adapter.js"})));
}

/*TEST_F(test_revMap, cheap_modluesource_map_prod) {
  test.run("Test/tests/testMap/prod/cheap-module-source-map/bundle.js.map");
  EXPECT_TRUE(check(test.find(1,911),(Res{1,911,"bundle.js"})));
  EXPECT_TRUE(check(test.find(1,902),(Res{83,10,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(1,110),(Res{19,22,"webpack:///webpack/bootstrap"})));
  EXPECT_TRUE(check(test.find(1,983),(Res{3,49,"webpack:///./src/index.js"})));
  EXPECT_TRUE(check(test.find(1,1080),(Res{4,16,"webpack:///./src/hello.js"})));
}*/
