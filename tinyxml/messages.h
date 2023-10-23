#include <tinyxml.h>
#include <iostream>

struct TestRequest1 {
    uint32_t m_param1;
    bool m_param2;

    void toXml(TiXmlElement &parent)
    {
        TiXmlElement request("TestRequest1");

        TiXmlElement param1("param1");
        TiXmlText param1Val(std::to_string(m_param1));
        param1.InsertEndChild(param1Val);
        request.InsertEndChild(param1);

        TiXmlElement param2("param2");
        TiXmlText param2Val(std::to_string(m_param2));
        param2.InsertEndChild(param2Val);
        request.InsertEndChild(param2);

        parent.InsertEndChild(request);
    }

    bool fromXml(TiXmlElement &parent)
    {
        TiXmlElement *elt = parent.FirstChildElement();
        if (elt) {
            while (elt) {
                if (elt->ValueStr().compare("param1") == 0) {
                    m_param1 = std::stoul(elt->GetText());
                } else if (elt->ValueStr().compare("param2") == 0) {
                    m_param2 = std::stoul(elt->GetText());
                } else {
                    return false;
                }

                elt = elt->NextSiblingElement();
            }
        }
        return true;
    }
};

std::ostream &operator<<(std::ostream &os, const TestRequest1 &tr1)
{
    os << "param1 " << tr1.m_param1 << " param2 " << tr1.m_param2 << "\n";
    return os;
}

struct TestRequest2 {
    int32_t m_param1;
    int32_t m_param2;
    double m_param3;
    
    void toXml(TiXmlElement &parent)
    {
        TiXmlElement request("TestRequest2");
        TiXmlElement param1("param1");
        TiXmlText param1Val(std::to_string(m_param1));
        param1.InsertEndChild(param1Val);
        request.InsertEndChild(param1);        

        TiXmlElement param2("param2");
        TiXmlText param2Val(std::to_string(m_param2));
        param2.InsertEndChild(param2Val);
        request.InsertEndChild(param2);        

        TiXmlElement param3("param3");
        TiXmlText param3Val(std::to_string(m_param3));
        param3.InsertEndChild(param3Val);
        request.InsertEndChild(param3);        

        parent.InsertEndChild(request);
    }

    bool fromXml(TiXmlElement &parent)
    {
        TiXmlElement *elt = parent.FirstChildElement();
        if (elt) {
            while (elt) {
                if (elt->ValueStr().compare("param1") == 0) {
                    m_param1 = std::stol(elt->GetText());
                } else if (elt->ValueStr().compare("param2") == 0) {
                    m_param2 = std::stol(elt->GetText());
                } else if (elt->ValueStr().compare("param3") == 0) {
                    m_param3 = std::stod(elt->GetText());
                } else {
                    return false;
                }

                elt = elt->NextSiblingElement();
            }
        }
        return true;
    }
};

std::ostream &operator<<(std::ostream &os, const TestRequest2 &tr2)
{
    os << "param1 " << tr2.m_param1 << " param2 " << tr2.m_param2 << " param3 " << tr2.m_param3 << "\n";
    return os;
}

struct TestStruct {
    int32_t m_member1;
    int32_t m_member2;
    double m_member3[5];

    void toXml(TiXmlElement &parent)
    {
        //TiXmlElement elt("TestStruct");
        TiXmlElement member1("member1");
        TiXmlText member1Val(std::to_string(m_member1));
        member1.InsertEndChild(member1Val);
        parent.InsertEndChild(member1);

        TiXmlElement member2("member2");
        TiXmlText member2Val(std::to_string(m_member2));
        member2.InsertEndChild(member2Val);
        parent.InsertEndChild(member2);

        for (int i = 0; i < 5; i++) {
            TiXmlElement member3("member3");
            TiXmlText member3Val(std::to_string(m_member3[i]));
            member3.InsertEndChild(member3Val);
            parent.InsertEndChild(member3);
        }

        //parent.InsertEndChild(elt);
    }

    bool fromXml(TiXmlElement &parent)
    {
        TiXmlElement *elt = parent.FirstChildElement();
        if (elt) {
            uint32_t count = 0;
            while (elt) {
                if (elt->ValueStr().compare("member1") == 0) {
                    m_member1 = std::stol(elt->GetText());
                } else if (elt->ValueStr().compare("member2") == 0) {
                    m_member2 = std::stol(elt->GetText());
                } else if (elt->ValueStr().compare("member3") == 0) {
                    m_member3[count++] = std::stod(elt->GetText());
                } else {
                    std::cerr << "Error looking at " << elt->ValueStr() << "\n";
                    return false;
                }

                elt = elt->NextSiblingElement();
            }
        }
        return true;
    }
};

std::ostream &operator << (std::ostream &os, const TestStruct &ts)
{
    os << " m_member1 " << ts.m_member1 << " m_member2 " << ts.m_member2;
    for (int i = 0; i < 5; i++) {
        os << " m_member3[" << i << "] " << ts.m_member3[i];
    }
    return os;
}

struct TestRequest3 {
    TestStruct m_param1;

    void toXml(TiXmlElement &parent)
    {
        TiXmlElement request("TestRequest3");
        TiXmlElement param1("param1");

        m_param1.toXml(param1);

        request.InsertEndChild(param1);

        parent.InsertEndChild(request);
    }

    bool fromXml(TiXmlElement &parent)
    {
        TiXmlElement *elt = parent.FirstChildElement();
        if (elt) {
            while (elt) {
                if (elt->ValueStr().compare("param1") == 0) {
                    m_param1.fromXml(*elt);
                } else {
                    std::cerr << "Error looking at " << elt->ValueStr() << "\n";

                    return false;
                }

                elt = elt->NextSiblingElement();
            }
        }
        return true;
    }
};

std::ostream &operator << (std::ostream &os, const TestRequest3 &tr3)
{
    os << " param1 " << tr3.m_param1 << "\n";
    return os;
}

struct TestRequest4 {
    bool m_member1;
    int32_t m_member2;
    int32_t m_member3[4];

    TestRequest4()
    {}

    void toXml(TiXmlElement &parent)
    {
        TiXmlElement request4("TestRequest4");
        TiXmlElement member1("member1");
        TiXmlText member1Val(std::to_string(m_member1));
        member1.InsertEndChild(member1Val);
        request4.InsertEndChild(member1);

        TiXmlElement member2("member2");
        TiXmlText member2Val(std::to_string(m_member2));
        member2.InsertEndChild(member2Val);
        request4.InsertEndChild(member2);

        for (int i = 0; i < 4; i++) {
            TiXmlElement member3("member3");
            TiXmlText member3Val(std::to_string(m_member3[i]));
            member3.InsertEndChild(member3Val);
            request4.InsertEndChild(member3);
        }

        parent.InsertEndChild(request4);

    }

    bool fromXml(TiXmlElement &parent)
    {
        TiXmlElement *elt = parent.FirstChildElement();
        if (elt) {
            uint32_t count = 0;
            while (elt) {
                if (elt->ValueStr().compare("member1") == 0) {
                    m_member1 = std::stol(elt->GetText());
                } else if (elt->ValueStr().compare("member2") == 0) {
                    m_member2 = std::stol(elt->GetText());
                } else if (elt->ValueStr().compare("member3") == 0) {
                    m_member3[count++] = std::stol(elt->GetText());
                } else {
                    std::cerr << "Error looking at " << elt->ValueStr() << "\n";
                    return false;
                }

                elt = elt->NextSiblingElement();
            }
        }
        return true;
    }
};

std::ostream &operator<< (std::ostream &os, const TestRequest4 &tr4)
{
    os << "member1 " << tr4.m_member1 << " member2 " << tr4.m_member2;
    for (int i = 0; i < 4; i++) {
        os << " member3[" << i << "] " << tr4.m_member3[i];
    }
    os << "\n";
    return os;
}

struct Test {
    enum RequestType { Request1, Request2, Request3, Request4 };
    TestRequest1 m_request1;
    TestRequest2 m_request2;
    TestRequest3 m_request3;
    TestRequest4 m_request4;
    RequestType m_active;
    TiXmlDocument m_document;
    TiXmlElement m_root;

    Test():
        m_active(Request1),
        m_root("Test")
    {
    }

    std::string toXml(bool compact = true) {
        switch(m_active) {
        case Request1:
            m_request1.toXml(m_root);
            break;
        case Request2:
            m_request2.toXml(m_root);
            break;
        case Request3:
            m_request3.toXml(m_root);
            break;
        case Request4:
            m_request4.toXml(m_root);
            break;
        }
        m_document.InsertEndChild(m_root);
        TiXmlPrinter printer;
        if (compact) printer.SetStreamPrinting();
        m_document.Accept(&printer);
        return printer.Str();
    }

    bool fromXml(const std::string &xmlStr) {
        TiXmlDocument doc;
        doc.Parse(xmlStr.c_str());
        TiXmlElement *root = doc.RootElement();
        TiXmlElement *child = root->FirstChildElement();
        if (child) {
            if (child->ValueStr().compare("TestRequest1") == 0) {
                m_active = Request1;
                return m_request1.fromXml(*child);

            } else if (child->ValueStr().compare("TestRequest2") == 0) {
                m_active = Request2;
                return m_request2.fromXml(*child);
            } else if (child->ValueStr().compare("TestRequest3") == 0) {
                m_active = Request3;
                return m_request3.fromXml(*child);
            } else if (child->ValueStr().compare("TestRequest4") == 0) {
                m_active = Request4;
                return m_request4.fromXml(*child);
            }
        }
        return false;
    }
};

std::ostream &operator<<(std::ostream &os, const Test &test)
{
    switch (test.m_active) {
        case Test::Request1:
            os << "TestRequest1 " << test.m_request1;
            break;
        case Test::Request2:
            os << "TestRequest2 " << test.m_request2;
            break;
        case Test::Request3:
            os << "TestRequest3 " << test.m_request3;
            break;
        case Test::Request4:
            os << "TestRequest4 " << test.m_request4;
            break;
    }
    return os;
}