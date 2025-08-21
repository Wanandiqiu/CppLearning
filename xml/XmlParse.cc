#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

using namespace std;
using namespace tinyxml2;
using std::string;
using std::vector;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

// 思路: 解析 XML 文件 将内容先存入 vector 中，然后写入文件 pagelib.txt

class RssReader
{
public:
    RssReader() = default;

    void parseRss();

    void dump(const string &filename); // 输出

private:
    vector<RssItem> _rss;
};

// 去除 HTML 标签
string removeHTMLTags(const string &input)
{
    std::regex tagRegex("<[^>]*>");
    return regex_replace(input, tagRegex, "");
}

string decodeHTMLEntities(const string &input)
{
    unordered_map<string, string> entityMap = {
        {"&lt;", "<"},
        {"&gt;", ">"},
        {"&amp;", "&"},
        {"&quot;", "\""},
        {"&#39;", "'"},
        {"&#8211;", "–"}, // en dash
        {"&#8212;", "—"}, // em dash
        {"&#8220;", "“"}, // left double quotation mark
        {"&#8221;", "”"}, // right double quotation mark
        {"&#8216;", "‘"}, // left single quotation mark
        {"&#8217;", "’"}  // right single quotation mark
    };

    string result = input;
    for (const auto &[entity, charRep] : entityMap)
    {
        size_t pos = 0;
        while ((pos = result.find(entity, pos)) != string::npos)
        {
            result.replace(pos, entity.length(), charRep);
            pos += charRep.length(); // 避免重复替换
        }
    }
    return result;
}

void RssReader::parseRss()
{
    XMLDocument doc;
    RssItem item;

    if (doc.LoadFile("coolshell.xml") != XML_SUCCESS)
    {
        std::cout << "Error loading XML file." << std::endl;
        return;
    }

    XMLElement *targetElement = doc.RootElement()->FirstChildElement("channel")->FirstChildElement("item");
    if (!targetElement)
    {
        std::cout << "target <title> not found." << std::endl;
        return;
    }

    while (targetElement)
    {
        XMLElement *titleNode = targetElement->FirstChildElement("title");
        if (!titleNode)
        {
            std::cout << "target <title> not found." << std::endl;
            return;
        }
        const char *title = titleNode->GetText(); // 获取到title中的内容
        string titleStr = removeHTMLTags(decodeHTMLEntities(title));

        XMLElement *LinkNode = targetElement->FirstChildElement("link");
        if (!LinkNode)
        {
            std::cout << "target <link> not found." << std::endl;
            return;
        }
        const char *link = LinkNode->GetText(); // 获取到link中的内容
        string linkStr = removeHTMLTags(decodeHTMLEntities(link));

        XMLElement *descriptionNode = targetElement->FirstChildElement("description");
        if (!descriptionNode)
        {
            std::cout << "target <description> not found." << std::endl;
            return;
        }
        const char *description = descriptionNode->GetText(); // 获取到description中的内容
        string descriptionStr = removeHTMLTags(decodeHTMLEntities(description));

        XMLElement *contentNode = targetElement->FirstChildElement("content:encoded");
        if (!contentNode)
        {
            std::cout << "target <content:encoded> not found." << std::endl;
            return;
        }
        const char *content = contentNode->GetText(); // 获取到content:encoded中的内容
        string contentStr = removeHTMLTags(decodeHTMLEntities(content));

        // 包装RssItem
        item.title = titleStr;
        item.link = linkStr;
        item.description = descriptionStr;
        item.content = contentStr;

        // 插入到vector中
        _rss.push_back(item);

        targetElement = targetElement->NextSiblingElement("item");
    }
}

void RssReader::dump(const string &filename)
{
    // std::ofstream ofs(filename);
    // if (!ofs.is_open())
    // {
    //     std::cout << "Error opening file." << std::endl;
    //     return;
    // }

    XMLDocument doc;
    XMLElement *root = doc.NewElement("doc");
    doc.InsertFirstChild(root);
    int id = 0;

    for (const auto &item : _rss)
    {
        XMLElement *docid = doc.NewElement("docid");
        docid->SetText(++id);
        root->LinkEndChild(docid);

        XMLElement *title = doc.NewElement("title");
        title->SetText(item.title.c_str());
        root->LinkEndChild(title);


        XMLElement *link = doc.NewElement("link");
        link->SetText(item.link.c_str());
        root->LinkEndChild(link);

        XMLElement *description = doc.NewElement("description");
        description->SetText(item.description.c_str());
        root->LinkEndChild(description);

        XMLElement *content = doc.NewElement("content");
        // 使用CDATA段来避免XML实体编码
        XMLText *textNode = doc.NewText(item.content.c_str());
        textNode->SetCData(true);
        content->InsertFirstChild(textNode);
        root->LinkEndChild(content);
    }

    doc.SaveFile(filename.c_str());

    std::cout << "save success" << std::endl;
}

int testRoot()
{
    XMLDocument doc;
    if (doc.LoadFile("coolshell.xml") != XML_SUCCESS)
    {
        std::cout << "Error loading XML file." << std::endl;
        return -1;
    }

    XMLElement *rss = doc.FirstChildElement("rss");
    if (!rss)
    {
        std::cout << "<rss> not found" << std::endl;
        return -1;
    }

    std::cout << "Found Element: " << rss->Name() << std::endl;

    std::cout << "...." << std::endl;
    const char *text = rss->GetText(); // 没有名字

    std::cout << text << std::endl;

    return 0;
}

int testTag()
{
    XMLDocument doc;
    if (doc.LoadFile("coolshell.xml") != XML_SUCCESS)
    {
        std::cout << "Error loading XML file." << std::endl;
        return -1;
    }

    XMLElement *targetElement = doc.RootElement()->FirstChildElement("channel")->FirstChildElement("title");

    if (!targetElement)
    {
        std::cout << "target <title> not found." << std::endl;
        return -1;
    }

    std::cout << "Found Element: " << targetElement->Name() << std::endl;

    const char *text = targetElement->GetText(); // 有内容

    std::cout << text << std::endl;

    return 0;
}

void testMultiNode()
{
    XMLDocument doc;
    RssItem item;

    if (doc.LoadFile("coolshell.xml") != XML_SUCCESS)
    {
        std::cout << "Error loading XML file." << std::endl;
        return;
    }

    XMLElement *targetElement = doc.RootElement()->FirstChildElement("channel")->FirstChildElement("item");
    if (!targetElement)
    {
        std::cout << "target <title> not found." << std::endl;
        return;
    }

    XMLElement *titleNode = targetElement->FirstChildElement("title");
    const char *title = titleNode->GetText(); // 获取到title中的内容

    std::cout << title << std::endl;

    XMLElement *LinkNode = targetElement->FirstChildElement("link");
    const char *link = LinkNode->GetText(); // 获取到link中的内容

    std::cout << link << std::endl;

    XMLElement *descriptionNode = targetElement->FirstChildElement("description");
    const char *description = descriptionNode->GetText(); // 获取到description中的内容

    std::cout << description << std::endl;

    // 还得获得item的内容
    std::cout << "Item...." << std::endl;

    XMLElement *contentNode = targetElement->FirstChildElement("content:encoded");
    const char *content = contentNode->GetText(); // 获取到content:encoded中的内容

    std::cout << content << std::endl;
}

// cool.xml 转为 pagelib.txt
void testCoolToPageLib()
{
    ifstream ifs("cool.xml");
    if (!ifs.is_open())
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    ofstream ofs("pagelib.txt");
    if (!ofs.is_open())
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    string line;
    while (getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    ifs.close();
    ofs.close();

    std::cout << "save success" << std::endl;
}

void testStorage()
{
    XMLDocument doc;
    RssItem item;

    if (doc.LoadFile("coolshell.xml") != XML_SUCCESS)
    {
        std::cout << "Error loading XML file." << std::endl;
        return;
    }

    XMLElement *targetElement = doc.RootElement()->FirstChildElement("channel")->FirstChildElement("item");
    if (!targetElement)
    {
        std::cout << "target <item> not found." << std::endl;
        return;
    }

    vector<RssItem> items; // 存储所有的item
    while (targetElement)
    {

        XMLElement *titleNode = targetElement->FirstChildElement("title");
        const char *title = titleNode->GetText(); // 获取到title中的内容
        string titleStr = removeHTMLTags(decodeHTMLEntities(title));

        // std::cout << title << std::endl;

        XMLElement *LinkNode = targetElement->FirstChildElement("link");
        const char *link = LinkNode->GetText(); // 获取到link中的内容
        string linkStr = removeHTMLTags(decodeHTMLEntities(link));

        // std::cout << link << std::endl;

        XMLElement *descriptionNode = targetElement->FirstChildElement("description");
        const char *description = descriptionNode->GetText(); // 获取到description中的内容
        string descriptionStr = removeHTMLTags(decodeHTMLEntities(description));

        // std::cout << description << std::endl;

        XMLElement *contentNode = targetElement->FirstChildElement("content:encoded");
        const char *content = contentNode->GetText(); // 获取到content:encoded中的内容
        string contentStr = removeHTMLTags(decodeHTMLEntities(content));

        item.title = titleStr;
        item.link = linkStr;
        item.description = descriptionStr;
        item.content = contentStr;

        items.push_back(item);

        targetElement = targetElement->NextSiblingElement("item");
    }
#if 0
    for (auto item : items)
    {
        std::cout << item.title << std::endl;
        std::cout << item.link << std::endl;
        std::cout << item.description << std::endl;
    }
#endif
    // 创建输出 XML
    int ID = 0;
    XMLDocument doc1;
    XMLElement *root = doc1.NewElement("doc");
    doc1.InsertFirstChild(root);

    for (int i = 0; i < items.size(); i++)
    {
        XMLElement *docid = doc1.NewElement("docid");
        docid->SetText(++ID);
        root->LinkEndChild(docid);

        XMLElement *Title = doc1.NewElement("title");
        Title->SetText(items[i].title.c_str());
        root->LinkEndChild(Title);

        XMLElement *Link = doc1.NewElement("link");
        Link->SetText(items[i].link.c_str());
        root->LinkEndChild(Link);

        XMLElement *Description = doc1.NewElement("description");
        Description->SetText(items[i].description.c_str());
        root->LinkEndChild(Description);

        XMLElement *Content = doc1.NewElement("content");
        // 使用CDATA段来避免XML实体编码
        XMLText *textNode = doc1.NewText(items[i].content.c_str());
        textNode->SetCData(true);
        Content->InsertFirstChild(textNode);
        root->LinkEndChild(Content);
    }

    doc1.SaveFile("cool.xml");

    std::cout << "save success" << std::endl;

    testCoolToPageLib();
}


// 辅助函数：安全获取文本
const char *GetValue(XMLElement *elem, const char *name)
{
    XMLElement *node = elem->FirstChildElement(name);
    return (node && node->GetText()) ? node->GetText() : "";
}

// 辅助函数：添加元素
void AddElement(XMLDocument &doc, XMLElement *parent, const char *name, const char *value)
{
    XMLElement *elem = doc.NewElement(name);
    elem->SetText(value ? value : "");
    parent->LinkEndChild(elem);
}

void testStorage2()
{
    XMLDocument doc;
    if (doc.LoadFile("coolshell.xml") != XML_SUCCESS)
    {
        std::cout << "Error loading XML file." << std::endl;
        return;
    }

    XMLElement *channel = doc.RootElement()->FirstChildElement("channel");
    if (!channel)
    {
        std::cout << "<channel> not found." << std::endl;
        return;
    }

    XMLElement *item = channel->FirstChildElement("item");
    if (!item)
    {
        std::cout << "<item> not found." << std::endl;
        return;
    }

    // 安全获取字段
    const char *title = GetValue(item, "title");
    const char *link = GetValue(item, "link");
    const char *description = GetValue(item, "description"); // 可能为空
    const char *content = GetValue(item, "content:encoded");

    std::cout << "Item processed." << std::endl;

    // 创建新文档
    XMLDocument doc1;
    XMLElement *root = doc1.NewElement("doc");
    doc1.InsertFirstChild(root);

    XMLElement *docid = doc1.NewElement("docid");
    docid->SetAttribute("id", 1);
    root->LinkEndChild(docid);

    AddElement(doc1, root, "title", title);
    AddElement(doc1, root, "link", link);
    AddElement(doc1, root, "description", description);

    // 使用 CDATA 保存 content，避免转义
    XMLElement *contentElem = doc1.NewElement("content");
    if (content && strlen(content) > 0)
    {
        XMLText *textNode = doc1.NewText(content);
        textNode->SetCData(true); // ✅ 关键：使用 CDATA
        contentElem->InsertFirstChild(textNode);
    }
    root->LinkEndChild(contentElem);

    // 保存
    if (doc1.SaveFile("shell.xml") == XML_SUCCESS)
    {
        std::cout << "save success" << std::endl;
    }
    else
    {
        std::cout << "save failed!" << std::endl;
    }
}

int main()
{

    // testTag();
    // testMultiNode();

    // testStorage();

    RssReader reader;
    reader.parseRss();
    reader.dump("pagelib.txt");

    // testStorage2();

    return 0;
}