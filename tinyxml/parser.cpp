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
        std::string TestRequest1Str="<Test><TestRequest1><param1>12345</param1><param2>0</param2></TestRequest1></Test>";
        Test test;
        auto result = test.fromXml(TestRequest1Str);

        if (result) {
            std::cout << test;
        } else {
            std::cout << "Error parsing " << TestRequest1Str << "\n";
        }
    }
    {
        std::string TestRequest2Str="<Test><TestRequest2><param1>654321</param1><param2>99999</param2><param3>123.456000</param3></TestRequest2></Test>";
        Test test;
        auto result = test.fromXml(TestRequest2Str);

        if (result) {
            std::cout << test;
        } else {
            std::cout << "Error parsing " << TestRequest2Str << "\n";
        }    
    }
    {
        std::string TestRequest3Str="<Test><TestRequest3><param1><member1>123</member1><member2>555</member2><member3>666.222000</member3><member3>111.222000</member3><member3>222.222000</member3><member3>333.222000</member3><member3>444.222000</member3></param1></TestRequest3></Test>";
        Test test;
        auto result = test.fromXml(TestRequest3Str);

        if (result) {
            std::cout << test;
        } else {
            std::cout << "Error parsing " << TestRequest3Str << "\n";
        }
    }
    {
        std::string TestRequest4Str="<Test><TestRequest4><member1>1</member1><member2>777</member2><member3>111</member3><member3>211</member3><member3>311</member3><member3>411</member3></TestRequest4></Test>";
        Test test;
        auto result = test.fromXml(TestRequest4Str);
        if (result) {
            std::cout << test;
        } else {
            std::cout << "Error parsing " << TestRequest4Str << "\n";
        }
    }

}