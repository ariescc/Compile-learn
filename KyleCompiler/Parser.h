/**
    �﷨����
*/

#include "resource.h"
#include "TreeNode.h"

class Parser {
public:
    // ���ʷ������õ���vectorתΪqueue
    std::queue<WordAnalyse_Result> que;
    int package_identifier_cnt = 0; // packageName �������identifer�����������һ��::����identifer�ĸ���
                                // ��Ϊȫ�ֱ�����ʹreference��package���ܷ��ʵ��˱�����ֵ
    int indent = 0; // ��ʽ������ո���

    Parser(); // ���캯��

    treeNode *parser_solve(); // �﷨���������Ϊ�﷨���������ڵ�

    void init(std::vector<WordAnalyse_Result> v); // ��ʼ���ʷ�����
    bool Match(int id); // ƥ���ս����Ϊ�ս������һ�����ڵ㲢����

    void print_parser_tree(treeNode *root, int cnt); // ���������ӡ�﷨��

    void rescover_queue(std::queue<std::string> tmp, std::queue<std::string> global_que, int flag);

    // =========================================================================================================
    // �﷨����
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
