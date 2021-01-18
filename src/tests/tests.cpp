#include "../graph.h"
#include <iostream>
#include "../catch/catch.hpp"

    /*
    Path function signatures:
    
    findPathBfs(std::string from, std::string to);
    findPathIddfs(std::string from, std::string to, int max_depth);
    findPathLandmark(std::string from, std::string to, std::string through);
    Call functions to find paths. Verify path length as well as the actual path output.
    The function getLastFoundPath() will return a vector of strings with node id's representing the last-found path.
    */

TEST_CASE("Creation and simple BFS") {
    Graph g;
    
    g.create_graph("../test_dataset.txt");
    g.setFeatPath("../test_feats.txt");
    g.setFeatNamesPath("../test_featnames.txt");
    
    REQUIRE(g.nodes_.find("1") != g.nodes_.end());
    
    g.findPathBfs("1", "6"); //1->2->6

    std::vector<std::string> path = g.getLastFoundPath();

    assert(path.size() == 3);

    REQUIRE(path[0] == "6");
    REQUIRE(path[1] == "2");
    REQUIRE(path[2] == "1");
    
    
    g.findPathBfs("1", "5");

    std::vector<std::string> path2 = g.getLastFoundPath(); 


    assert(path2.size() == 5);

    REQUIRE(path2[0] == "5");
    REQUIRE(path2[1] == "4");
    REQUIRE(path2[2] == "3");
    REQUIRE(path2[3] == "2");
    REQUIRE(path2[4] == "1");
    
}


TEST_CASE("Creation and backwards BFS") {
    Graph g;

    g.create_graph("../test_dataset.txt");
    g.setFeatPath("../test_feats.txt");
    g.setFeatNamesPath("../test_featnames.txt");

    REQUIRE(g.nodes_.find("3") != g.nodes_.end());

    g.findPathBfs("3", "1");

    std::vector<std::string> path = g.getLastFoundPath(); //3->4->1

    assert(path.size() == 3);

    REQUIRE(path[0] == "1");
    REQUIRE(path[1] == "4");
    REQUIRE(path[2] == "3");
  
    
}

TEST_CASE("Creation and Simple Landmark") {
    Graph g; 

    g.create_graph("../test_dataset.txt");
    g.setFeatPath("../test_feats.txt");
    g.setFeatNamesPath("../test_featnames.txt");


    REQUIRE(g.nodes_.find("1") != g.nodes_.end());


    g.findPathLandmark("1", "6", "2"); //Find path from 1 to 6 through 2

    std::vector<std::string> path = g.getLastFoundPath(); //1->2->6


    assert(path.size() == 3);


    REQUIRE(path[0] == "6");
    REQUIRE(path[1] == "2");
    REQUIRE(path[2] == "1");  
    
}

TEST_CASE("Creation and Backwards Landmark") {
    Graph g; 

    g.create_graph("../test_dataset.txt");
    g.setFeatPath("../test_feats.txt");
    g.setFeatNamesPath("../test_featnames.txt");


    REQUIRE(g.nodes_.find("4") != g.nodes_.end());


    g.findPathLandmark("4", "2", "1"); //Find path from 4 to 2 through 1

    std::vector<std::string> path = g.getLastFoundPath(); //4->1->2

    assert(path.size() == 3);

    REQUIRE(path[0] == "2");
    REQUIRE(path[1] == "1");
    REQUIRE(path[2] == "4"); 

}

TEST_CASE("Creation and Simple IDDFS (short path)") {
    Graph g; 

    g.create_graph("../test_dataset.txt");
    g.setFeatPath("../test_feats.txt");
    g.setFeatNamesPath("../test_featnames.txt");


    REQUIRE(g.nodes_.find("1") != g.nodes_.end());


    g.findPathIddfs("1", "3", 3); //Find pat from 1 to 3 given max depth of 3

    std::vector<std::string> path = g.getLastFoundPath(); //1->2->3


    assert(path.size() == 3);

    REQUIRE(path[0] == "3");  
    REQUIRE(path[1] == "2");
    REQUIRE(path[2] == "1");
}

TEST_CASE("Creation and IDDFS (longer path)") {
    Graph g; 

    g.create_graph("../test_dataset.txt");
    g.setFeatPath("../test_feats.txt");
    g.setFeatNamesPath("../test_featnames.txt");

    REQUIRE(g.nodes_.find("1") != g.nodes_.end());

    g.findPathIddfs("1", "5", 5); //Find path from 1 to 5 given max depth of 5

    std::vector<std::string> path = g.getLastFoundPath(); //1->2->3->4->5


    assert(path.size() == 5);

    REQUIRE(path[0] == "5");  
    REQUIRE(path[1] == "4");
    REQUIRE(path[2] == "3");
    REQUIRE(path[3] == "2");  
    REQUIRE(path[4] == "1");

}

TEST_CASE("Creation and IDDFS (backwards path)") {
    Graph g; 

    g.create_graph("../test_dataset.txt");
    g.setFeatPath("../test_feats.txt");
    g.setFeatNamesPath("../test_featnames.txt");

    REQUIRE(g.nodes_.find("3") != g.nodes_.end());

    g.findPathIddfs("3", "2", 4); //Find path from 3 to 2 given max depth of 4

    std::vector<std::string> path = g.getLastFoundPath(); //3->4->1->2

    assert(path.size() == 4);

    REQUIRE(path[0] == "2");  
    REQUIRE(path[1] == "1");
    REQUIRE(path[2] == "4");
    REQUIRE(path[3] == "3");  

}









