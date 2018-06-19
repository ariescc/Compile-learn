/**
    语法分析
*/

#include "resource.h"
#include "TreeNode.h"

class Parser {
public:
    // 将词法分析得到的vector转为queue
    std::queue<WordAnalyse_Result> que;
    int package_identifier_cnt = 0; // packageName 最后多余的identifer个数，即最后一个::后面identifer的个数
                                // 作为全局变量，使reference和package均能访问到此变量的值
    int indent = 0; // 格式化输出空格数

    Parser(); // 构造函数

    treeNode *parser_solve(); // 语法分析，输出为语法分析树根节点

    void init(std::vector<WordAnalyse_Result> v); // 初始化词法队列
    bool Match(int id); // 匹配终结符，为终结符创建一个树节点并返回

    void print_parser_tree(treeNode *root, int cnt); // 中序遍历打印语法树

    void rescover_queue(std::queue<std::string> tmp, std::queue<std::string> global_que, int flag);

    // =========================================================================================================
    // 语法规则
    treeNode *Threadspec_parse(); // Threadspec
    treeNode *FeatureSpec_parse(); // FeatureSpec
    treeNode *FlowSpec_parse(); // FlowSpec
    treeNode *Association_parse(); // Association
    treeNode *PortSpec_parse();
    treeNode *ParameterSpec_parse();
    treeNode *IOtype_parse();
    treeNode *PortType_parse();
    treeNode *Reference_parse();
    treeNode *PackageName_parse();
    treeNode *FlowSourceSpec_parse();
    treeNode *FlowSinkSpec_parse();
    treeNode *FlowPathSpec_parse();
    treeNode *Splitter_parse();
};
