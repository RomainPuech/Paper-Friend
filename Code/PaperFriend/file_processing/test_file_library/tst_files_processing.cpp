#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class files_processing : public QObject
{
    Q_OBJECT

public:
    files_processing();
    ~files_processing();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

files_processing::files_processing()
{

}

files_processing::~files_processing()
{

}

void files_processing::initTestCase()
{
    Entry test_entry;
}

void files_processing::cleanupTestCase()
{

}

void files_processing::test_case1()
{
    save_entry (test_entry);
}

QTEST_MAIN(files_processing)


#include "tst_files_processing.moc"
