SRCS:=  $(wildcard Class/*.cpp Br_tree/*.cpp Avl_tree/*.cpp ThreadPool/*.cpp STL/*.cpp *.cpp)
INCS := Br_tree Avl_tree ThreadPool STL
#Avl_tree/*.cpp Br_tree/*.cpp
SRCS_NODIR:= $(notdir $(SRCS))
OBJS:= $(patsubst %.cpp,%.o,$(SRCS))
#./AVL_tree ./Br_tree
LIBS:= -lpthread -lssl
CXX = g++

#-l指定链接需要的库,.a/.so,编译器查找动态连接库时有隐含的命名规则，即在给出的名字前面加上lib，后面加上.a/.so来确定库的名称
#-shared:指定生成动态链接库.so, -static:指定生成静态链接库.a
#-w	关闭编译时的警告 -Wall生成所有警告信息
CXXFLAGS = -g -w -Wall -Wextra -std=c++11 -O3 -fopenmp
INCFLAGS := $(patsubst %,-I%,$(INCS))

all: test_run

test_run:$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

#-c ：只激活预处理、编译和汇编,也就是把程序做成目标文件(.o文件)。
#不带-c选项，-o会直接生成可执行文件，出现找不到main错误
$(OBJS):%.o:%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

.PHONY:clean
clean:
	rm -rf $(OBJS)
	rm -rf test_run
