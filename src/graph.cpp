#include "graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>    // std::reverse

using namespace std;

void Graph::create_graph(std::string filename = "../gplus_appended.txt")
{
    std::ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()) {
        //std::string::size_type sz;
        std::string line;
        while (getline(myfile, line)) {
            if (line.empty() || line[0] == '#') { //account for empty lines
                continue;
            }
            else {
                if (!id_counted_) {
                    for (unsigned long i = 0; i < line.length(); i++) {
                        if (line[i] == ' ') {
                            id_len_ = i; //update in case other datasets are used
                            id_counted_ = true;
                            break;
                        }
                        if (i + 1 == line.length()) {
                            //ensure datset is in combined format, like the one we're using
                            std::cout << "Please ensure your dataset is in a combined format, with the left column being the 'from' node, and right column being the 'to' node." << std::endl;
                        }
                    }
                } //counted the correct node id length
                std::string id;
                std::string adj_id;
                if (line.length() < (unsigned long)id_len_) { //account for nodes with no adjacent nodes
                    for (int i = 0; i < id_len_; i++) {
                        id += line[i];
                    }
                }
                else {
                    for (int i = 0; i < id_len_; i++) {
                        id += line[i];
                        adj_id += line[id_len_ + i + 1];
                    }
                }
                //long long id = std::stoll(id_str);    //convert string to long
                //long long adj_id = std::stoll(adj_node_str);
                //64 bytes per node x 150000 nodes = 9.15527 gb of memory, need to optimize when using actual dataset
                //using string for id, 1 byte per char x 150000 nodex = 21*150*1000 = 3gb. Might trim dataset.

                if (nodes_.find(id) == nodes_.end()) {
                    Node n;
                    n.id = id;
                    n.adjacent.push_back(adj_id);
                    nodes_.insert(std::make_pair(id, n));
                }
                else {
                    nodes_[id].adjacent.push_back(adj_id);
                }
            }
        }
    }
}

//  FINDING NAMES:
//     It'll be too timely and costly to parse all nodes into names and occupations.
//     Instead, we'll ask for user input on names, then search the features file for that name.
//     If more than one individual exists with the name, we will display a small list of the first x people with the name.
//     From there, user selects, and we find path using Node id's as usual.
//     After finding the path, we will also search the feature files for the people in the path to display people names rather than node id.

void Graph::findPathBfs(std::string from, std::string to, bool landmark)
{

    if (!path_.empty() && !landmark) {
        for (auto id : path_) {
            if (nodes_.find(id.first) != nodes_.end()) {
                nodes_[id.first].visited = false;
            }
            if (nodes_.find(id.second) != nodes_.end()) {
                nodes_[id.second].visited = false;
            }
        }
        path_.clear();
    }

    // if (nodes_[from].visited) {
    //     std::cout << "YIKES" << std::endl;
    // }
    last_from = from;
    last_to = to;
    std::queue<std::string> q;
    std::unordered_map<std::string, std::string> prev; //maybe change to string and node
    q.push(from);
    nodes_[from].visited = true;
    while (!q.empty()) {
        std::string curr_id = q.front();
        q.pop();
        for (auto adj_node_id : nodes_[curr_id].adjacent) {
            if (!nodes_[adj_node_id].visited) {
                nodes_[adj_node_id].visited = true;
                q.push(adj_node_id);
                prev[adj_node_id] = curr_id;
                if (adj_node_id == to) {
                    break;
                }
            }
        }
    }
    path_ = prev;
}

void Graph::printLastFoundPathId()
{
    std::vector<std::string> path;
    for (std::string i = last_to; i != ""; i = path_[i]) {
        path.push_back(i);
        if (i == last_from) {
            break; // NEED TO OPTIMIZE
        }
    }
    shortest_path_dist = path.size();
    if (path.at(path.size() - 1) == last_from) {
        // PRINT PATH
        std::cout << "\n _____________________________ PATH ___________________________________\n\n";
        int i = 0;
        for (auto it = path.begin(); it != path.end(); ++it) {
            i++;
            if (it + 1 != path.end()) {
                std::cout << *it << "  -->  ";
            }
            else {
                std::cout << *it;
            }
            if (i > 2500000) {
                std::cout << "Path is ridiculously large, or infinite loop has occurred" << std::endl;
            }
        }
        std::cout << "\n";
    }
    else {
        std::cout << "No path was found." << std::endl;
    }
}

bool Graph::findPathIddfs(std::string from, std::string to, int depth_lim)
{
    last_from = from;
    last_to = to;
    path_.clear();
    for (int i = 0; i <= depth_lim; i++) {
        if (depthLimitSearch(from, to, i)) {
            return true;
        }
    }
    return false;
}

bool Graph::depthLimitSearch(std::string from, std::string to, int limit)
{
    if (from == to) {
        return true;
    }
    if (limit <= 0)
        return false;

    for (auto adj_id : nodes_[from].adjacent) {
        if (depthLimitSearch(adj_id, to, limit - 1)) {
            path_.insert(std::make_pair(adj_id, from));
            return true;
            //insert into path here??
        }
    }
    return false;
}

int Graph::getShortestPathDist()
{
    return shortest_path_dist;
}

int Graph::getIdLen()
{
    return id_len_;
}

void Graph::printLastFoundPathNames()
{
    std::vector<std::string> path;
    for (std::string i = last_to; i != ""; i = path_[i]) {
        path.push_back(i);
        if (i == last_from) {
            break; // NEED TO OPTIMIZE
        }
    }
    if (!(path.at(path.size() - 1) == last_from || path.at(path.size() - 1) == last_to)) {
        std::cout << "No path found" << std::endl;
        return;
    }

    std::cout << "\n _____________________________ PATH ___________________________________\n\n";

    // ALL OF THIS TO CONVERT NODE ID'S INTO NAMES .. :0
    std::vector<std::string> name_path;
    std::ifstream feats;
    std::ifstream featnames;
    std::string line;
    std::string featline;
    feats.open(featspath); //search feature file for node id
    bool found_all = false; //accunt for cases where a node id is 0 or 1, which results in unnecessary loops
    if (feats.is_open()) {
        for (auto id : path) { //FOR EACH ID IN PATH (this part works, tested heavily)
            if (found_all)
                break;
            if (!feats.is_open()) {
                feats.open(featspath);
            }

            while (getline(feats, line) && !found_all) { //find where names start
                if (line.find(id) != std::string::npos) { //found id

                    for (unsigned long i = id_len_ + 1; i < line.size(); i += 2) { //go through all 1's and 0's
                        if (line[i] == '1') { //found an attribute for an id in path
                            featnames.open(featnamespath);
                            if (featnames.is_open()) {

                                unsigned long j = 0;
                                while (getline(featnames, featline) && !found_all) { //go through all featnames
                                    if (j == (i - (id_len_ + 1)) / 2) { //check correct placement of 1 in featnames match
                                        if (featline.find("name") != std::string::npos) { //check that the attribute is in fact a name
                                            name_path.push_back(featline.substr(featline.find("name") + 5, featline.length()));
                                            std::cout << featline.substr(featline.find("name") + 5, featline.length()) << std::endl;
                                            if (name_path.size() == path.size()) {
                                                //std::cout << "found all" << std::endl;
                                                found_all = true;
                                                std::cout << "\n";
                                            }
                                            else {
                                                for (unsigned long k = 0; k < name_path.size(); k++) {
                                                    std::cout << "  ";
                                                } if (name_path.size() + 1 < path.size()) {
                                                    std::cout << "|__";
                                                }
                                            }
                                        }
                                    }
                                    j++;

                                } //go through all featnames
                            }
                            featnames.close();
                        } //found attribute for id

                    } //go through all 1's and 0's

                } //found id
            }
            feats.close();
        }
    }

    feats.close();

    // OLD PRINTING, FOR SOME REASON GIVING INCONSISTENT RESULTS. SCRAPPED.
    // std::cout << "\n _____________________________ PATH ___________________________________\n\n";

    // for (auto name : name_path) {
    //   std::cout << name << "   ";
    // }

    // int i = 0;
    // for (auto it = name_path.begin(); it != name_path.end(); ++it) {
    //   i++;
    //   if (it + 1 != name_path.end()) {
    //     std::cout << *it << "  -->  ";
    //   } else {
    //     std::cout << *it;
    //   }
    //   if (i > 2500000) {
    //     std::cout << "Path is ridiculously large, or infinite loop has occurred" << std::endl;
    //   }
    // }
    std::cout << "\n";
}

void Graph::setFeatPath(std::string path)
{
    featspath = path;
}
void Graph::setFeatNamesPath(std::string path)
{
    featnamespath = path;
}

//landmark -- A to B through C
// BFS from C to A and C to B
//gives shortest path from C to A and B
//combine these paths
void Graph::findPathLandmark(std::string from, std::string to, std::string through)
{
    last_from = from;
    last_to = to;
    findPathBfs(from, through);
    std::vector<std::string> landpath;
    for (std::string i = last_to; i != ""; i = path_[i]) {
        landpath.push_back(i);
        if (i == last_from) {
            break; // NEED TO OPTIMIZE
        }
    }
    std::reverse(landpath.begin(), landpath.end());

    findPathBfs(through, to, true);
    std::vector<std::string> secondlandpath;

    for (std::string i = last_to; i != ""; i = path_[i]) {
        secondlandpath.push_back(i);
        if (i == last_from) {
            break; // NEED TO OPTIMIZE
        }
    }
    std::reverse(secondlandpath.begin(), secondlandpath.end());

    for (auto elem : secondlandpath) landpath.push_back(elem);
    std::reverse(landpath.begin(), landpath.end());

    path_.clear();
    for (unsigned long i = 1; i < landpath.size(); i++) {
        path_.insert(std::make_pair(landpath.at(i - 1), landpath.at(i)));
    }
    last_from = from;
    last_to = to;
}

std::vector<std::string> Graph::getLastFoundPath() {
    std::vector<std::string> path;
    for (std::string i = last_to; i != ""; i = path_[i]) {
         path.push_back(i);
         if (i == last_from) {
             break; // NEED TO OPTIMIZE
         }
    }
    return path;
}
