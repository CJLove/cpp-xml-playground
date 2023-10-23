#include <tinyxml.h>
#include <unistd.h>
#include <string>
#include <cstdint>
#include "messages.h"



int main(int argc, char**argv)
{
    int c = 0;
    bool compact = false;
    while ((c = getopt(argc,argv,"c?")) != EOF)
    {
        switch (c) {
        case 'c':
            compact = true;
            break;
        case '?':
            std::cerr << "Usage\nbuilder [-c]\n";
            return 1;
        }
    }

    {
        Test test;
        test.m_active = Test::Request1;
        test.m_request1.m_param1 = 12345;
        test.m_request1.m_param2 = false;

        std::cout << "TestRequest1:\n" << test.toXml(compact) << "\n";
    }
    {
        Test test;
        test.m_active = Test::Request2;
        test.m_request2.m_param1 = 654321;
        test.m_request2.m_param2 = 99999;
        test.m_request2.m_param3 = 123.456;

        std::cout << "TestRequest2:\n" << test.toXml(compact) << "\n";
    }
    {
        Test test;
        test.m_active = Test::Request3;
        test.m_request3.m_param1.m_member1 = 123;
        test.m_request3.m_param1.m_member2 = 555;
        test.m_request3.m_param1.m_member3[0] = 666.222;
        test.m_request3.m_param1.m_member3[1] = 111.222;
        test.m_request3.m_param1.m_member3[2] = 222.222;
        test.m_request3.m_param1.m_member3[3] = 333.222;
        test.m_request3.m_param1.m_member3[4] = 444.222;

        std::cout << "TestRequest3:\n" << test.toXml(compact) << "\n";

    }
    {
        Test test;
        test.m_active = Test::Request4;
        test.m_request4.m_member1 = true;
        test.m_request4.m_member2 = 777;
        test.m_request4.m_member3[0] = 111;
        test.m_request4.m_member3[1] = 211;
        test.m_request4.m_member3[2] = 311;
        test.m_request4.m_member3[3] = 411;

        std::cout << "TestRequest4:\n" << test.toXml(compact) << "\n";
    }
#if 0
    TiXmlDocument doc;
    TiXmlDeclaration *decl = new TiXmlDeclaration( "1.0", "", "");
    TiXmlElement *msg = new TiXmlElement("Msg");
    TiXmlElement *testReq = new TiXmlElement("TestRequest1");
    TiXmlElement *param1 = new TiXmlElement("param1");
    TiXmlText *p1Text = new TiXmlText("12345");
    param1->LinkEndChild(p1Text);
    TiXmlElement *param2 = new TiXmlElement("param2");
    TiXmlText *p2Text = new TiXmlText("true");
    param2->LinkEndChild(p2Text);
    doc.LinkEndChild(decl);
    doc.LinkEndChild(msg);
    msg->LinkEndChild(testReq);
    testReq->LinkEndChild(param1);
    testReq->LinkEndChild(param2);
    doc.Print();
#endif
}