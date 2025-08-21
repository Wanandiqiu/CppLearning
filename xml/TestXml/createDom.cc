#include <iostream>
#include "tinyxml2.h"

using namespace tinyxml2;
using std::endl;
using std::endl;

// 创建一个xml文档
// 其实就是序列化与反序列化

void test()
{
    XMLDocument doc;      
    XMLElement *root = doc.NewElement("order");
    doc.InsertEndChild(root);

    
    XMLElement *goodsNode = doc.NewElement("Goods");
    goodsNode->SetAttribute("ID" , 1);
    root->LinkEndChild(goodsNode);

    XMLElement *priceNode = doc.NewElement("price");
    priceNode->SetText("6999");
    goodsNode->LinkEndChild(priceNode);

    XMLElement *brandNode = doc.NewElement("brand");
    brandNode->SetText("HUAWEI");
    goodsNode->LinkEndChild(brandNode);


    XMLElement *goodsNode1 = doc.NewElement("Goods");
    goodsNode1->SetAttribute("ID" , 2);
    root->LinkEndChild(goodsNode1);

    XMLElement *priceNode1 = doc.NewElement("price");
    priceNode1->SetText("10999");
    goodsNode1->LinkEndChild(priceNode1);

    XMLElement *brandNode1 = doc.NewElement("brand");
    brandNode1->SetText("MacBook");
    goodsNode1->LinkEndChild(brandNode1);


    doc.SaveFile("order.xml");

}

int main()
{
    test();

    return 0;
}

