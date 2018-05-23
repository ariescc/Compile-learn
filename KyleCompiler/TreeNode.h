/**
    语法分析树的节点
*/

#define MAXCHILD 50

struct treeNode {
    struct treeNode *child[MAXCHILD]; // 定义子节点
    struct treeNode *brother; // 兄弟节点指针

    std::string data;

    int line_no; // 行号
};
