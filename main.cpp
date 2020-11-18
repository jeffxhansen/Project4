
#include <iostream>
#include <fstream>
#include <sstream>

#include "Lexer.h"
#include "DatalogProgram.h"

//#include "Relation.h" // FIXME: Remove this
//#include "Database.h"
#include "Interpreter.h"

using namespace std;

void testing() {
    Tuple tuple2("Trevor", "Austin");
    Tuple tuple3("Spencer", "Jacob");
    Tuple tuple1("Jeff", "Ryan");

    Header header1("T", "B");

    Relation relation("Roomates", header1);
    relation.addTuple(tuple1);
    relation.addTuple(tuple2);
    relation.addTuple(tuple3);

    Relation relation2("Age", Header("Name", "Age"));
    relation2.addTuple(Tuple("Jeff", "22"));
    relation2.addTuple(Tuple("Ryan", "20"));
    relation2.addTuple(Tuple("Trevor", "21"));
    relation2.addTuple(Tuple("Jacob", "21"));
    relation2.addTuple(Tuple("Austin", "21"));
    relation2.addTuple(Tuple("Spencer", "22"));

    Relation relation3("Numbers", Header("A", "B", "C"));
    relation3.addTuple(Tuple("1", "2", "3"));
    relation3.addTuple(Tuple("2", "4", "6"));
    relation3.addTuple(Tuple("4", "8", "12"));

    Database database;
    database.addRelation(relation);
    database.addRelation(relation2);

    cout << relation2.toString() << endl;

    cout << "Rename" << endl;
    vector<string> input;
    input.push_back("Num1");
    input.push_back("Num2");
    cout << relation2.rename(input).toString() << endl;


    cout << relation3.toString() << endl;

    cout << "Rename" << endl;
    input.clear();
    input.push_back("1");
    input.push_back("2");
    input.push_back("3");
    cout << relation3.rename(input).toString() << endl;

    cout << "Project" << endl;
    vector<int> indices;
    indices.push_back(1);
    indices.push_back(2);
    cout << relation3.project(indices).toString() << endl;

    Relation relation4("Numbers", Header("A", "B", "C"));
    relation4.addTuple(Tuple("1", "2", "1"));
    relation4.addTuple(Tuple("2", "2", "3"));
    relation4.addTuple(Tuple("3", "2", "1"));
    relation4.addTuple(Tuple("2", "3", "1"));

    cout << "Select" << endl;
    cout << relation4.selectColVal(0, "1").toString() << endl;

    /* set<Tuple> testSet;

    cout << "Testing the set of tuples" << endl;
    testSet.insert(tuple1);
    testSet.insert(tuple2);
    testSet.insert(tuple3);

    for (Tuple t : testSet) {
        cout << t.toString() << endl;
    }*/

    /*cout << "Tuple1: " << tuple1.toString() << endl;
    cout << "Tuple2: " << tuple2.toString() << endl;
    cout << "Tuple2: " << tuple3.toString() << endl;

    if (tuple1 < tuple2) cout << "tuple1 is smaller" << endl;
    if (tuple2 < tuple1) cout << "tuple2 is smaller" << endl;*/

    /*cout << "Testing the Relation class constructor and such" << endl;

    cout << relation.toString() << endl;

    cout << relation2.toString() << endl;

    cout << "----" << endl;
    cout << database.toString() << endl;*/
}

int main(int argc, char* argv[])
{
    Lexer lexer(argv[1]);
    lexer.run();
    // lexer.printTokens();
    // cout << endl;

    DatalogProgram datalog(lexer.Tokens());
    datalog.parse();

    Interpreter interpreter(datalog);
    interpreter.interpret();

    interpreter.test();

}
