/**
    �﷨�������Ľڵ�
*/

#define MAXCHILD 5

struct treeNode {
    struct treeNode *child[MAXCHILD]; // �����ӽڵ�
    struct treeNode *brother; // �ֵܽڵ�ָ��

    std::string data;

    int line_no; // �к�
};
