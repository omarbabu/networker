#pragma once
#include <unordered_map>
#include <vector>
#include <string>
/**
 * Class for manipulating and intepreting data from datasets.
 * Correct dataset format is required, and enforced in the create_graph function
 * This implementation works for directed graphs, we need to check whether it works properly for undirected grpahs.
 * Our example dataset consists of over 13 million edges.
 * */
class Graph {
private:
    int id_len_ = 21; //set default to gplus_combined size
    bool id_counted_ = false;
    std::unordered_map<std::string, std::string> path_;
    std::string last_from;
    std::string last_to;
    bool depthLimitSearch(std::string from, std::string to, int limit);
    int shortest_path_dist;
    std::string featspath = "../feats.txt";
    std::string featnamespath = "../featnames.txt";

public:
    class Node {
    public:
        std::string id;
        bool visited;
        std::vector<std::string> adjacent; //storing id's rather than Node objs for space efficiency
    }; //Node class
    void printLastFoundPathId();
    void printLastFoundPathNames();
    std::unordered_map<std::string, Node> nodes_;
    void create_graph(std::string filename);
    void findPathBfs(std::string from, std::string to, bool landmark = false);
    bool findPathIddfs(std::string from, std::string to, int max_depth);
    void findPathLandmark(std::string from, std::string to, std::string through);
    int getShortestPathDist();
    int getIdLen();
    void setFeatPath(std::string path);
    void setFeatNamesPath(std::string path);
    std::vector<std::string> getLastFoundPath();
};
