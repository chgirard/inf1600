#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include "../Article.h"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class ArticleTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ArticleTest);
    CPPUNIT_TEST(testgetters);
    CPPUNIT_TEST(trouverArticle);
    CPPUNIT_TEST(trouverArticle2);
    CPPUNIT_TEST_SUITE_END();
    
public:
    void setUp(void);
    void tearDown(void);
    
protected:
    void testgetters(void);
    void trouverArticle(void);
    void trouverArticle2(void);
    
private:
    
    Article *art;
};

// ------------------------ IMPLEMENTATION ------------------------

void ArticleTest::testgetters(void)
{
    string name = art->getName();
    string auteur = art->getAuteur();
    string editeurName = art->getEditeurName();
    string editeurCodePostal = art->getEditeurCodePostal();
    string editeurAddress = art->getEditeurAddress();
    
    if (name == "nameTest"
        && auteur == "auteurTest"
        && editeurName == "editeurNameTest"
        && editeurCodePostal == "editeurCodePostalTest"
        && editeurAddress == "editeurAddressTest") {
        CPPUNIT_ASSERT(true);
    } else {
        CPPUNIT_ASSERT(false);
    }
    
}

void ArticleTest::trouverArticle(void)
{
    Article * a = art->trouverArticle ("../DB.txt", "test");
    if (a == NULL) {
        CPPUNIT_ASSERT(true);
    } else {
        CPPUNIT_ASSERT(false);
    }
}


void ArticleTest::trouverArticle2(void)
{
    Article * a = art->trouverArticle ("../DB.txt", "nameTest");
    if (a != NULL) {
        CPPUNIT_ASSERT(true);
    } else {
        CPPUNIT_ASSERT(false);
    }
}

void ArticleTest::setUp(void)
{
    art = new Article("nameTest",
                      "auteurTest",
                      "editeurNameTest",
                      "editeurCodePostalTest",
                      "editeurAddressTest");
}

void ArticleTest::tearDown(void)
{
    delete art;
}