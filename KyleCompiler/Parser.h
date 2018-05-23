/**
    语法分析
*/

#include "resource.h"
#include "TreeNode.h"

class Parser {
public:
    // 将词法分析得到的vector转为queue
    std::queue<WordAnalyse_Result> que;

    Parser(); // 构造函数

    treeNode *parser_solve(); // 语法分析，输出为语法分析树根节点

    void init(std::vector<WordAnalyse_Result> v); // 初始化词法队列

    bool Match(int id); // 匹配终结符，为终结符创建一个树节点并返回

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
