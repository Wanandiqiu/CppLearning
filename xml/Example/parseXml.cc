#include "tinyxml2.h"
#include <iostream>

using namespace tinyxml2;
using std::cout;
using std::endl;
using std::string;

// 解析xml
void test1(){
    XMLDocument doc;

    doc.LoadFile("person.xml");
    XMLElement * root = doc.RootElement();
    if(!root){
        return;
    }
    XMLElement * personNode = root->FirstChildElement();
    int id = personNode->IntAttribute("ID");
    XMLElement * nameNode = personNode->FirstChildElement("name");
    string name = nameNode->GetText();
    XMLElement * ageNode = personNode->FirstChildElement("age");
    string age = ageNode->GetText();
    int ageValue = std::stoi(age); 
    cout << "person id: " << id << endl;
    cout << "name : " << name << endl;
    cout << "age : " << ageValue << endl;
}

void test2(){
    XMLDocument doc;

    doc.LoadFile("person.xml");
    XMLElement * root = doc.RootElement();
    if(!root){
        return;
    }
    XMLElement * personNode = root->FirstChildElement("Person");
    while (personNode)
    {
        int id = personNode->IntAttribute("ID");
        XMLElement * nameNode = personNode->FirstChildElement("name");
        string name = nameNode->GetText();
        XMLElement * ageNode = personNode->FirstChildElement("age");
        string age = ageNode->GetText();
        int ageValue = std::stoi(age); 
        cout << "person id: " << id << endl;
        cout << "name : " << name << endl;
        cout << "age : " << ageValue << endl;
        // 数据封装 -->Person对象
        // vector<Person> v; 
        // Person p(id, name, ageValue);
        // v.push_back(p);
        // 找下一个Person节点
        personNode = personNode->NextSiblingElement("Person");
    }
    
 
}
int main(int argc, char *argv[])
{
    // test1();
    test2();
    return 0;
}

