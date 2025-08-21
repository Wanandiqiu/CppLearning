#include "tinyxml2.h"
#include <iostream>

using namespace tinyxml2;
using std::cout;
using std::endl;

void test1(){
    // 创建文档对象
    XMLDocument doc;
    // 创建根节点
    XMLElement * root = doc.NewElement("Persons");
    // 将根节点添加到文档对象中 文档对象跟根节点建立联系
    doc.InsertEndChild(root);
    // 创建子节点
    XMLElement * personNode = doc.NewElement("Person");
    personNode->SetAttribute("ID",1);
    // 添加子节点
    root->LinkEndChild(personNode);
    // 为PersonNode添加子节点
    // name节点
    XMLElement * nameNode = doc.NewElement("name");
    nameNode->SetText("周星星");
    // age节点
    XMLElement * ageNode = doc.NewElement("age");
    ageNode->SetText("20");
    personNode->LinkEndChild(nameNode);
    personNode->LinkEndChild(ageNode);
    // 保存
    doc.SaveFile("person.xml");
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}

