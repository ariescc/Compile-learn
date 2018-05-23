#include "Parser.h"

Parser::Parser() {}

void Parser::init(std::vector<WordAnalyse_Result> v)
{
    for(int i = 0; i < v.size(); i++) {
        que.push(v[i]);
    }
    //std::cout << que.size() << std::endl;
}

/**
    匹配终结符，构建子树
*/
bool Parser::Match(int id)
{

}


/**
    ThreadSpec 语法规则
*/
treeNode * Parser::Threadspec_parse()
{

    //std::cout << "==================threadspec start=====================" << std::endl;

    // create root node of "thread"
    treeNode *thread = new treeNode();
    thread -> data = "threadSpec";

    // match thread
    if(que.front().ID != THREAD) { std::cout << "syntax error: thread" << std::endl; return nullptr; }
    else que.pop();

    // match identifier
    if(que.front().ID != IDENTIFIER_STATEMACHINE) { std::cout << "syntax error: identifier" << std::endl; return nullptr; }
    else que.pop();


    // if-match features
    if(que.front().ID == FEATURES) {
        que.pop();
        if(thread != nullptr) thread -> child[0] = FeatureSpec_parse();
    }


    // if-match flows
    if(que.front().ID == FLOWS) {
        que.pop();
        if(thread != nullptr) thread -> child[1] = FlowSpec_parse();
    }

    //std::cout << "th1----------------------------------------" << std::endl;


    // if-match properties
    if(que.front().ID == PROPERTIES) {
        que.pop();
        if(thread != nullptr) thread -> child[3] = Association_parse();

        // match ';'
        if(que.front().ID != FEN) { std::cout << "syntax error: fenhao" << std::endl; return nullptr; }
        else que.pop();
    }


    // match end
    if(que.front().ID != END) { std::cout << "syntax error: end" << std::endl; return nullptr; }

    // match identifier
    if(que.front().ID != IDENTIFIER_STATEMACHINE) { std::cout << "syntax error: identifier" << std::endl; return nullptr; }

    //std::cout << "==================threadspec end=====================" << std::endl;

    return thread;
}

/**
    FeatureSpec 语法规则
*/
treeNode * Parser::FeatureSpec_parse()
{
    //std::cout << "==================feature start========================" << std::endl;

    // create root node of "featureSpec"
    treeNode *features_root = new treeNode();
    features_root -> data = "FeatureSpec";

    // PortSpec 语法规则
    treeNode *portSpec_node = PortSpec_parse();
    if(portSpec_node != nullptr) return (features_root -> child[0] = portSpec_node);

    // ParamterSpec 语法规则
    treeNode *parameterSpec_node = ParameterSpec_parse();
    if(parameterSpec_node != nullptr) return (features_root -> child[0] = parameterSpec_node);

    // match "none"
    if(que.front().ID != NONE) { std::cout << "syntax error: FeatureSpec" << std::endl; return nullptr; }
    else que.pop();

    // match ';'
    if(que.front().ID != FEN) { std::cout << "syntax error: FeatureSpec" << std::endl; return nullptr; }
    else que.pop();

    //std::cout << "==================feature start========================" << std::endl;

    return features_root;
}

/**
    FlowSpec 语法规则
*/
treeNode * Parser::FlowSpec_parse()
{
    // 尝试 FlowSourceSpec
    treeNode *fsource = FlowSourceSpec_parse();
    if(fsource != nullptr) return fsource;

    // 尝试 FlowSinkSpec
    treeNode *fsink = FlowSinkSpec_parse();
    if(fsink != nullptr) return fsink;

    // 尝试 FlowPathSpec
    treeNode *fpath = FlowPathSpec_parse();
    if(fpath != nullptr) return fpath;

    // match none
    if(que.front().ID != NONE) {std::cout << "syntax error: FlowSpec none" << std::endl; return nullptr;}
    else que.pop();

    // match ;
    if(que.front().ID != FEN) {std::cout << "syntax error: FlowSpec fen" << std::endl; return nullptr;}
    else que.pop();

    treeNode *flowspec_root = new treeNode();
    flowspec_root -> data = "FlowSpec";

    return flowspec_root;
}

/**
    Association 语法规则
*/
treeNode * Parser::Association_parse()
{
    treeNode *association_root = new treeNode();
    association_root -> data = "Association";

    // match identifier
    if(que.front().ID != IDENTIFIER_STATEMACHINE) {
        // match none
        if(que.front().ID == NONE) que.pop();
        return association_root;
    }
    else que.pop();

    // match :: (可有可无
    if(que.front().ID == TWO_MAO) que.pop();

    // match splitter
    if(association_root != nullptr) association_root -> child[0] = Splitter_parse();

    // 尝试匹配 constant (可有可无
    if(que.front().ID == CONSTANT) que.pop();

    // match access
    if(que.front().ID == ACCESS) que.pop();
    else {std::cout << "syntax error: access" << std::endl; return nullptr;} // 因为前面部分已经匹配成功了，所以当此处无法
                                                                        // 进行匹配的时候语法分析错误

    // match decimal
    if(que.front().ID == DECIMAL_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: decimal" << std::endl; return nullptr;} // 因为前面部分已经匹配成功了，所以当此处无法
                                                                        // 进行匹配的时候语法分析错误

    return association_root;
}


/**
    portSpec
*/
treeNode * Parser::PortSpec_parse()
{
    //std::cout << "======================PortSpec start===============================" << std::endl;

    treeNode *portSpec_root = new treeNode();
    portSpec_root -> data = "PortSpec";

    // match identifier
    if(que.front().ID != IDENTIFIER_STATEMACHINE) { std::cout << "syntax error: portSpec identifier" << std::endl; return nullptr; }
    else que.pop();

    // match :
    if(que.front().ID != MAO) {std::cout << que.front().opt_str << "syntax error: portSpec :" << std::endl; return nullptr;}
    else que.pop();

    // IOtype 语法规则
    if(portSpec_root != nullptr) portSpec_root -> child[0] = IOtype_parse();

    //std::cout << "portspec----------------------------------------" << std::endl;

    // PortType 语法规则
    if(portSpec_root != nullptr) portSpec_root -> child[1] = PortType_parse();

    int i = 2; // 标记child下标
    // association 语法规则
    while(que.front().ID == LEFT_HUA_KH) {
        que.pop();
        if(portSpec_root != nullptr) portSpec_root -> child[i++] = Association_parse();
        if(que.front().ID == RIGHT_HUA_KH) que.pop();
        else {std::cout << "syntax error: association" << std::endl; return nullptr;}
    }

    return portSpec_root;

}

/**
    parameterspec
*/
treeNode * Parser::ParameterSpec_parse()
{
    treeNode *parameterSpec_root = new treeNode();
    parameterSpec_root -> data = "parameterSpec";

    // match identifier
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();

    // match :
    if(que.front().ID == MAO) que.pop();

    // IOtype 语法规则
    if(parameterSpec_root != nullptr) parameterSpec_root -> child[0] = IOtype_parse();

    // match parameter
    if(que.front().ID == PARAMETER) que.pop();

    // 尝试进行reference匹配
    treeNode *ref = Reference_parse();
    if(ref != nullptr) {
        if(parameterSpec_root != nullptr) parameterSpec_root -> child[1] = ref;
    }


    int i = 2;
    while(que.front().ID == LEFT_HUA_KH) {
        que.pop();
        if(parameterSpec_root != nullptr) parameterSpec_root -> child[i++] = Association_parse();
        if(que.front().ID == RIGHT_HUA_KH) que.pop();
        else {std::cout << "syntax error: parameter association" << std::endl; return nullptr;}
    }

    return parameterSpec_root;
}


/**
    语法分析器
*/
treeNode* Parser::parser_solve()
{
    treeNode * root = Threadspec_parse();
    return root;
}


/**
    IOtype
*/
treeNode * Parser::IOtype_parse()
{
    treeNode *iotype_root = new treeNode();
    iotype_root -> data = "IOtype";

    //std::cout << "iotype--------------------------------" << std::endl;
    // match in
    if(que.front().ID == IN) {
        que.pop();
        // match out
        if(que.front().ID == OUT) que.pop();
    }

    // match out
    else if(que.front().ID == OUT) que.pop();
    else {
            std::cout << que.front().opt_str << " syntax error: IOtype" << std::endl;
            return nullptr;
    }

    return iotype_root;
}

/**
    PortType
*/
treeNode * Parser::PortType_parse()
{
    treeNode *porttype_root = new treeNode();
    porttype_root -> data = "porttype";

    // match data
    if(que.front().ID == DATA) {
        que.pop();
        // match port
        if(que.front().ID == PORT) {
            que.pop();
            // reference 语法规则
            if(porttype_root != nullptr) porttype_root -> child[0] = Reference_parse();
        }
        else {std::cout << "syntax error: portType data port" << std::endl; return nullptr;}
    }

    // match event
    else if(que.front().ID == EVENT) {
        que.pop();
        // match data
        if(que.front().ID == DATA) {
            que.pop();
            // match port
            if(que.front().ID == PORT) {
                que.pop();
                if(porttype_root != nullptr) porttype_root -> child[1] = Reference_parse();
            }
        }
        else if(que.front().ID == PORT) que.pop();
        else {std::cout << "syntax error: porttype event " << std::endl; return nullptr;}
    }
    else {
        std::cout << "syntax error: PortType" << std::endl;
        return nullptr;
    }

    return porttype_root;
}


/**
    Reference
*/
treeNode * Parser::Reference_parse()
{
    treeNode *reference_root = new treeNode();
    reference_root -> data = "Reference";

    // 尝试匹配 PackageName
    treeNode *pn = PackageName_parse();
    if(pn != nullptr) {
        if(reference_root != nullptr) reference_root -> child[0] = pn;
        // match ::
        if(que.front().ID == TWO_MAO) que.pop();
        else {std::cout << que.front().opt_str << "syntax error: reference two_mao" << std::endl; return nullptr;}
    }

    // match identifier
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: reference identifier" << std::endl; return nullptr;}

    return reference_root;
}


/**
    PackageName
*/
treeNode * Parser::PackageName_parse()
{
    treeNode *packagename_root = new treeNode();
    packagename_root -> data = "PackageName";

    int cnt = 0;

    int id1 = que.front().ID;
    que.pop();
    int id2 = que.front().ID;
    que.pop();

    while(id1 == IDENTIFIER_STATEMACHINE && id2 == TWO_MAO) {
        id1 = que.front().ID;
        if(id1 == IDENTIFIER_STATEMACHINE) cnt++;
        que.pop();
        id2 = que.front().ID;
        if(id2 == TWO_MAO) que.pop();
    }

    /*while(que.front().ID == IDENTIFIER_STATEMACHINE) {
        que.pop();
        if(que.front().ID == TWO_MAO) que.pop();
        else {std::cout << que.front().opt_str << "syntax error: packagename two mao" << std::endl; return nullptr;}
    }*/

    // match identifier
    // 多于1个identifier
    if(cnt > 1) {std::cout << que.front().opt_str << "syntax error: packagename identifier" << std::endl; return nullptr;}
    else if(cnt == 1) cnt = 0; // match identifier

    return packagename_root;
}


/**
    FlowSourceSpec
*/
treeNode * Parser::FlowSourceSpec_parse()
{

    treeNode *flowsourcespec_root = new treeNode();
    flowsourcespec_root -> data = "FlowSourceSpec";

    // match identifier
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: identifier" << std::endl; return nullptr;}

    // match :
    if(que.front().ID == MAO) que.pop();
    else {std::cout << "syntax error: mao" << std::endl; return nullptr;}

    // match flow
    if(que.front().ID == FLOW) que.pop();
    else {std::cout << "syntax error: flow" << std::endl; return nullptr;}

    // match source
    if(que.front().ID == SOURCE) que.pop();
    else {std::cout << "syntax error: source" << std::endl; return nullptr;}

    // match identifier
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: identifer" << std::endl; return nullptr;}

    int i = 0;
    while(que.front().ID == LEFT_HUA_KH) {
        que.pop();
        if(flowsourcespec_root != nullptr) flowsourcespec_root -> child[i++] = Association_parse();
        if(que.front().ID == RIGHT_HUA_KH) que.pop();
        else {std::cout << "syntax error: flowsourcespec association" << std::endl; return nullptr;}
    }

    return flowsourcespec_root;
}

/**
    FlowSinkSpec
*/
treeNode * Parser::FlowSinkSpec_parse()
{
    treeNode *flowsinkspec_root = new treeNode();
    flowsinkspec_root -> data = "FlowSinkSpec";

    // match identifer
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: flowsinkspec identifier" << std::endl; return nullptr;}

    // match :
    if(que.front().ID == MAO) que.pop();
    else {std::cout << "syntax error: flowsinkspec mao" << std::endl; return nullptr;}

    // match flow
    if(que.front().ID == FLOW) que.pop();
    else {std::cout << "syntax error: flowsinkspec flow" << std::endl; return nullptr;}

    // match source
    if(que.front().ID == SOURCE) que.pop();
    else {std::cout << "syntax error: flowsinkspec source" << std::endl; return nullptr;}

    // match identifer
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: flowsinkspec identifier" << std::endl; return nullptr;}

    int i = 0;
    while(que.front().ID == LEFT_HUA_KH) {
        que.pop();
        if(flowsinkspec_root != nullptr) flowsinkspec_root -> child[i++] = Association_parse();
        if(que.front().ID == RIGHT_HUA_KH) que.pop();
        else {std::cout << "syntax error: flowsinkspec association" << std::endl; return nullptr;}
    }

    return flowsinkspec_root;
}

/**
    FlowPathSpec
*/
treeNode * Parser::FlowPathSpec_parse()
{
    // match identifer
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: flowpathspec identifier" << std::endl; return nullptr;}

    // match :
    if(que.front().ID == MAO) que.pop();
    else {std::cout << "syntax error: flowpathspec mao" << std::endl; return nullptr;}

    // match flow
    if(que.front().ID == FLOW) que.pop();
    else {std::cout << "syntax error: flowpathspec flow" << std::endl; return nullptr;}

    // match path
    if(que.front().ID == PATH) que.pop();
    else {std::cout << "syntax error: flowpathspec path" << std::endl; return nullptr;}

    // match identifer
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: flowpathspec identifier" << std::endl; return nullptr;}

    // match ->
    if(que.front().ID == MISE_GREARER) que.pop();
    else {std::cout << "syntax error: flowpathspec ->" << std::endl; return nullptr;}

    // match identifer
    if(que.front().ID == IDENTIFIER_STATEMACHINE) que.pop();
    else {std::cout << "syntax error: flowpathspec identifier" << std::endl; return nullptr;}

    treeNode *flowpathspec_root = new treeNode();
    flowpathspec_root -> data = "flowpathspec";

    return flowpathspec_root;
}


/**
    splitter
*/
treeNode * Parser::Splitter_parse()
{
    // match =>
    if(que.front().ID == EQUAL_GREATER) que.pop();

    // match +=>
    else if(que.front().ID == PLUS_EQUAL_GREATER) que.pop();

    else {std::cout << "syntax error: splitter" << std::endl; return nullptr;}

    treeNode *spitter_root = new treeNode();
    spitter_root -> data = "spitter";

    return spitter_root;
}
