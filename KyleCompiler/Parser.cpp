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
        if(thread != nullptr) thread -> child[2] = Association_parse();

        // match ';'
        if(que.front().ID != FEN) { std::cout << "syntax error: fenhao" << std::endl; return nullptr; }
        else que.pop();
    }


    // match end
    if(que.front().ID != END) { std::cout << que.front().opt_str << " syntax error: end" << std::endl; return nullptr; }
    else que.pop();

    // match identifier
    if(que.front().ID != IDENTIFIER_STATEMACHINE) { std::cout << que.front().opt_str << "syntax error: identifier" << std::endl; return nullptr; }
    else que.pop();

    // match fen
    if(que.front().ID == FEN) que.pop();
    else {std::cout << "syntax error: ThreadSpec Fenhao at the end of the file." << std::endl; return nullptr;}

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

    treeNode *flowSpec_root = new treeNode();

    // match none
    if(que.front().ID == NONE) {
        que.pop();
        if(que.front().ID == FEN) que.pop();
        else {std::cout << "syntax error: FlowSpec none fenhao" << std::endl; return nullptr;}
        flowSpec_root -> data = "FlowSpec None";
    }

    // 匹配 FlowSourceSpec, FlowSinkSpec, FlowPathSpec前面公共部分
    // match identifier
    if(que.front().ID == IDENTIFIER_STATEMACHINE) {
        treeNode *identifier1 = new treeNode();
        identifier1 -> data = que.front().opt_str;
        flowSpec_root -> child[0] = identifier1;
        que.pop();
    }
    else {std::cout << "syntax error: FlowSpec identifier" << std::endl; return nullptr;}

    // match mao
    if(que.front().ID == MAO) que.pop();
    else {std::cout << "syntax error: FlowSpec mao" << std::endl; return nullptr;}

    // match flow
    if(que.front().ID == FLOW) que.pop();
    else {std::cout << "syntax error: FlowSpec mao" << std::endl; return nullptr;}

    // source, sink or path
    if(que.front().ID == SOURCE) {

        flowSpec_root -> data = "Flow Source";

        que.pop();

        // match identifier
        if(que.front().ID == IDENTIFIER_STATEMACHINE) {
            treeNode *identifier2 = new treeNode();
            identifier2 -> data = que.front().opt_str;
            flowSpec_root -> child[1] = identifier2;
            que.pop();
        }

        flowSpec_root -> child[2] = FlowSourceSpec_parse();
    }
    else if(que.front().ID == SINK) {

        flowSpec_root -> data = "Flow Sink";

        que.pop();

        // match identifier
        if(que.front().ID == IDENTIFIER_STATEMACHINE) {
            treeNode *identifer2 = new treeNode();
            identifer2 -> data = que.front().opt_str;
            flowSpec_root -> child[1] = identifer2;
            que.pop();
        }

        flowSpec_root -> child[2] = FlowSinkSpec_parse();
    }
    else if(que.front().ID == PATH) {

        flowSpec_root -> data = "Flow Path";

        que.pop();

        // match identifier
        if(que.front().ID == IDENTIFIER_STATEMACHINE) {
            treeNode *identifier2 = new treeNode();
            identifier2 -> data = que.front().opt_str;
            flowSpec_root -> child[1] = identifier2;
            que.pop();
        }

        flowSpec_root -> child[2] = FlowPathSpec_parse();
    }
    else {
        std::cout << "syntax error: FlowSpec the keyword isn't in the set of (source, sink and path)" << std::endl;
        return nullptr;
    }

    return flowSpec_root;
}

/**
    Association 语法规则
*/
treeNode * Parser::Association_parse()
{
    treeNode *association_root = new treeNode();

    // match identifier
    if(que.front().ID != IDENTIFIER_STATEMACHINE) {
        // match none
        if(que.front().ID == NONE) {
            association_root -> data = "None";
            que.pop();
        }
        return association_root;
    }
    else {
        treeNode *identifier1 = new treeNode();
        identifier1 -> data = que.front().opt_str;
        association_root -> child[0] = identifier1;
        que.pop();

        // match :: (可有可无
        if(que.front().ID == TWO_MAO) {
            treeNode *two_mao1 = new treeNode();
            two_mao1 -> data = que.front().opt_str;
            association_root -> child[1] = two_mao1;
            que.pop();

            // match identifier
            if(que.front().ID == IDENTIFIER_STATEMACHINE) {
                treeNode *identifier2 = new treeNode();
                identifier2 -> data = que.front().opt_str;
                association_root -> child[2] = identifier2;
                que.pop();
            }
            else {std::cout << "syntax error: Association identifier::^identifier^" << std::endl; return nullptr;}
        }
    }

    // match splitter
    if(association_root != nullptr) association_root -> child[3] = Splitter_parse();

    // 尝试匹配 constant (可有可无
    if(que.front().ID == CONSTANT) que.pop();

    // match access
    if(que.front().ID == ACCESS) que.pop();
    else {std::cout << "syntax error: access" << std::endl; return nullptr;} // 因为前面部分已经匹配成功了，所以当此处无法
                                                                        // 进行匹配的时候语法分析错误

    // match decimal
    if(que.front().ID == DECIMAL_STATEMACHINE) {
        treeNode *decimal = new treeNode();
        decimal -> data = que.front().opt_str;
        association_root -> child[4] = decimal;
        que.pop();
    }
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
    else {
        treeNode *identifier1 = new treeNode();
        identifier1 -> data = que.front().opt_str;
        portSpec_root -> child[0] = identifier1;
        que.pop();
    }

    // match :
    if(que.front().ID != MAO) {std::cout << que.front().opt_str << "syntax error: portSpec :" << std::endl; return nullptr;}
    else que.pop();

    // IOtype 语法规则
    if(portSpec_root != nullptr) portSpec_root -> child[1] = IOtype_parse();

    //std::cout << "portspec----------------------------------------" << std::endl;

    // PortType 语法规则
    if(portSpec_root != nullptr) portSpec_root -> child[2] = PortType_parse();

    int i = 3; // 标记child下标
    // association 语法规则
    while(que.front().ID == LEFT_HUA_KH) {
        que.pop();
        if(portSpec_root != nullptr) portSpec_root -> child[i++] = Association_parse();
        if(que.front().ID == RIGHT_HUA_KH) que.pop();
        else {std::cout << "syntax error: association" << std::endl; return nullptr;}
    }

    // match ;
    if(que.front().ID == FEN) que.pop();
    else {std::cout << "syntax error: PortSpec fenhao" << std::endl; return nullptr;}

    return portSpec_root;

}

/**
    parameterspec
*/
treeNode * Parser::ParameterSpec_parse()
{
    treeNode *parameterSpec_root = new treeNode();
    parameterSpec_root -> data = "ParameterSpec";

    // match identifier
    if(que.front().ID == IDENTIFIER_STATEMACHINE) {
        treeNode *identifier1 = new treeNode();
        identifier1 -> data = que.front().opt_str;
        parameterSpec_root -> child[0] = identifier1;
        que.pop();
    }

    // match :
    if(que.front().ID == MAO) que.pop();

    // IOtype 语法规则
    if(parameterSpec_root != nullptr) parameterSpec_root -> child[1] = IOtype_parse();

    // match parameter
    if(que.front().ID == PARAMETER) que.pop();

    // 尝试进行reference匹配
    treeNode *ref = Reference_parse();
    if(ref != nullptr) {
        if(parameterSpec_root != nullptr) parameterSpec_root -> child[2] = ref;
    }


    int i = 3;
    while(que.front().ID == LEFT_HUA_KH) {
        que.pop();
        if(parameterSpec_root != nullptr) parameterSpec_root -> child[i++] = Association_parse();
        if(que.front().ID == RIGHT_HUA_KH) que.pop();
        else {std::cout << "syntax error: parameter association" << std::endl; return nullptr;}
    }

    return parameterSpec_root;
}


/**
    IOtype
*/
treeNode * Parser::IOtype_parse()
{
    treeNode *iotype_root = new treeNode();

    //std::cout << "iotype--------------------------------" << std::endl;
    // match in
    if(que.front().ID == IN) {
        que.pop();
        // match out
        if(que.front().ID == OUT) {
            iotype_root -> data = "IOType => IN OUT";
            que.pop();
        }
        else {
            iotype_root -> data = "IOType => IN";
        }
    }

    // match out
    else if(que.front().ID == OUT) {
        iotype_root -> data = "IOType => OUT";
        que.pop();
    }
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
    porttype_root -> data = "PortType";

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
        else if(que.front().ID == PORT) {
            treeNode *event_port = new treeNode();
            event_port -> data = "Event Port";
            porttype_root -> child[2] = event_port;
            que.pop();
        }
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
/*treeNode * Parser::Reference_parse()
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
}*/


/**
    PackageName
*/
//treeNode * Parser::PackageName_parse()
treeNode * Parser::Reference_parse()
{
    treeNode *packagename_root = new treeNode();
    packagename_root -> data = "PackageName";

    int id1 = que.front().ID;
    std::string str1 = que.front().opt_str;
    que.pop();
    int id2 = que.front().ID;
    std::string str2 = que.front().opt_str;
    que.pop();

    int i = 0;
    while(id1 == IDENTIFIER_STATEMACHINE && id2 == TWO_MAO) {
        treeNode *identifier1 = new treeNode();
        treeNode *mao = new treeNode();

        identifier1 -> data = str1;
        mao -> data = str2;

        packagename_root -> child[i] = identifier1;
        packagename_root -> child[i+1] = mao;

        i = i + 2;

        id1 = que.front().ID;
        if(id1 == IDENTIFIER_STATEMACHINE) package_identifier_cnt++;
        que.pop();
        id2 = que.front().ID;
        if(id2 == TWO_MAO) {que.pop(); package_identifier_cnt--;}
    }

    /*while(que.front().ID == IDENTIFIER_STATEMACHINE) {
        que.pop();
        if(que.front().ID == TWO_MAO) que.pop();
        else {std::cout << que.front().opt_str << "syntax error: packagename two mao" << std::endl; return nullptr;}
    }*/

    // match identifier
    // 多于1个identifier
    //std::cout << "cnt => " << cnt << std::endl;
    if(package_identifier_cnt == 1) package_identifier_cnt = 0; // match identifer
    else {std::cout << "syntax error: reference identifer" << std::endl; return nullptr;}

    return packagename_root;
}


/**
    FlowSourceSpec
*/
treeNode * Parser::FlowSourceSpec_parse()
{

    treeNode *flowsourcespec_root = new treeNode();

    int i = 0;
    while(que.front().ID == LEFT_HUA_KH) {
        que.pop();
        if(flowsourcespec_root != nullptr) flowsourcespec_root = Association_parse();
        if(que.front().ID == RIGHT_HUA_KH) que.pop();
        else {std::cout << "syntax error: flowsourcespec association" << std::endl; return nullptr;}
    }

    // match fen
    if(que.front().ID == FEN) que.pop();
    else {std::cout << "syntax error: FlowSourceSpec fenhao in the last location." << std::endl; return nullptr;}

    return flowsourcespec_root;
}


/**
    FlowSinkSpec
*/
treeNode * Parser::FlowSinkSpec_parse()
{
    treeNode *flowsinkspec_root = new treeNode();

    int i = 0;
    while(que.front().ID == LEFT_HUA_KH) {
        que.pop();
        if(flowsinkspec_root != nullptr) flowsinkspec_root = Association_parse();
        if(que.front().ID == RIGHT_HUA_KH) que.pop();
        else {std::cout << "syntax error: flowsinkspec association" << std::endl; return nullptr;}
    }

    // match fen
    if(que.front().ID == FEN) que.pop();
    else {std::cout << "syntax error: FlowSinkSpec fenhao in the last location." << std::endl; return nullptr;}

    return flowsinkspec_root;
}


/**
    FlowPathSpec
*/
treeNode * Parser::FlowPathSpec_parse()
{
    treeNode *flowpathspec_root = new treeNode();

    // match ->
    if(que.front().ID == MISE_GREARER) que.pop();
    else {std::cout << "syntax error: flowpathspec ->" << std::endl; return nullptr;}

    // match identifer
    if(que.front().ID == IDENTIFIER_STATEMACHINE) {
        flowpathspec_root -> data = que.front().opt_str;
        que.pop();
    }
    else {std::cout << que.front().opt_str << "syntax error: flowpathspec identifier" << std::endl; return nullptr;}

    // match fen
    if(que.front().ID == FEN) que.pop();
    else {std::cout << "syntax error: FlowPathSpec fenhao in the last location." << std::endl; return nullptr;}

    return flowpathspec_root;
}


/**
    splitter
*/
treeNode * Parser::Splitter_parse()
{
    treeNode *splitter_root = new treeNode();

    // match =>
    if(que.front().ID == EQUAL_GREATER) {
        splitter_root -> data = que.front().opt_str;
        que.pop();
    }

    // match +=>
    else if(que.front().ID == PLUS_EQUAL_GREATER) {
        splitter_root -> data = que.front().opt_str;
        que.pop();
    }

    else {std::cout << "syntax error: splitter" << std::endl; return nullptr;}

    return splitter_root;
}


/**
    先序遍历打印语法树
*/
void Parser::print_parser_tree(treeNode *root)
{
    int flag = 0;
    int sons = 0; // 计算当前节点子节点数量
    std::cout << root -> data << " " << std::endl;
    //std::cout << "======sons======" << std::endl;
    for(int i = 0; i < MAXCHILD; i++) {
        // MAXCHILD个子节点是否均为空节点
        if(root -> child[i] != nullptr) {
            sons++;
            flag = 1;
            //std::cout << root -> child[i] -> data << std::endl;
            print_parser_tree(root -> child[i]);
        }
    }
    std::cout << root -> data << "的子节点数量： " << sons << std::endl;
    // 子节点均为空，将该节点的值打印出来，否则继续递归
    if(!flag) {
        //std::cout << "******grandson*******" << std::endl;
        return;
    }
    return;
}



/**
    语法分析器
*/
treeNode* Parser::parser_solve()
{
    //std::cout << que.size() << std:: endl;
    treeNode *root = new treeNode(); // 森林共父亲节点
    root -> data = "ROOT";
    int i = 0;
    int cnt = 0;
    while(!que.empty()) {
        cnt++;
        std::cout << "==============================Parser " << cnt << "================================" << std::endl;
        std::cout << "Queue size: " << que.size() << "\n" << std::endl;
        treeNode * tmp = Threadspec_parse();
        if(tmp == nullptr) return nullptr;
        root -> child[i++] = tmp;
    }
    return root;
}
