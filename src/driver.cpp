#include "driver.h"

void Driver::graphProgram()
{
    //----------------------------------------
    bool hasCustomFeats = false;
    bool hasCustomSet = false;
    std::string filepath = "../gplus_appended.txt";
    std::cout << "                               __" << std::endl;
    std::cout << "                             .d$$b" << std::endl;
    std::cout << "                           .' TO$;\\" << std::endl;
    std::cout << "                          /  : TP._;" << std::endl;
    std::cout << "                         / _.;  :Tb|" << std::endl;
    std::cout << "                        /   /   ;j$j" << std::endl;
    std::cout << "                    _.-\"       d$$$$" << std::endl;
    std::cout << "                  .' ..       d$$$$;" << std::endl;
    std::cout << "                 /  /P'      d$$$$P. |\\" << std::endl;
    std::cout << "                /   \"      .d$$$P' |\\^\"l" << std::endl;
    std::cout << "              .'           `T$P^\"\"\"\"\"  :" << std::endl;
    std::cout << "          ._.'      _.'                ;" << std::endl;
    std::cout << "       `-.-\".-'-' ._.       _.-\"    .-\"" << std::endl;
    std::cout << "     `.-\" _____  ._              .-\"" << std::endl;
    std::cout << "    -(.g$$$$$$$b.              .'" << std::endl;
    std::cout << "      ""^^T$$$P^)            .(:" << std::endl;
    std::cout << "        _/  -\"  /.'         /:/;" << std::endl;
    std::cout << "     ._.'-'`-'  \")/         /;/;" << std::endl;
    std::cout << "  `-.-\"..--\"\"   \" /         /  ;" << std::endl;
    std::cout << " .-\" ..--\"\"        -'          :" << std::endl;
    std::cout << " ..--\"\"--.-\"         (\\      .-(\\" << std::endl;
    std::cout << "   ..--\"\"              `-\\(\\/;`" << std::endl;
    std::cout << "     _.                      :" << std::endl;
    std::cout << "                             ;`-" << std::endl;
    std::cout << "                            :\\" << std::endl;


    std::cout << "Welcome to Networker! Enter the path to your dataset or type \'default\' to use a Google+ network" << std::endl;
    std::cin >> filepath;
    hasCustomSet = true;
    if (filepath == "default") {
        filepath = "../gplus_appended.txt";
        hasCustomSet = false;
    }
    std::ifstream myFile;
    myFile.open(filepath);
    while (!myFile.good()) {
        std::cout << "Please enter a valid filepath, or enter \'default\'" << std::endl;
        std::cin >> filepath;
        if (filepath == "default") {
            hasCustomSet = false;
            filepath = "../gplus_appended.txt";
        }
        myFile.open(filepath);
        if (myFile.good())
            break;
    }
    myFile.close();
    //------------------------------------ filepath to dataset

    //------------------------------------
    Graph g;
    std::cout << "Creating your graph..." << std::endl;
    g.create_graph(filepath);
    std::cout << "Graph created!" << std::endl;
    //----------------------------------- create graph

    //----------------------------------- feats (node id to name filepath setup)
    std::string featpath = "../feats.txt";
    std::string featnamepath = "../featnames.txt";

    if (filepath != "../gplus_appended.txt") {
        featpath = "";
        featnamepath = "";
        std::cout << "Please enter your features file filepath." << std::endl;
        std::cin >> featpath;
        if (featpath != "none") {
            hasCustomFeats = true;
            myFile.open(featpath);
            while (!myFile.good()) {
                std::cout << "Please enter a valid filepath, or enter \'none\'" << std::endl;
                std::cin >> featpath;
                if (featpath == "none") {
                    featpath = "../feats.txt";
                    hasCustomFeats = false;
                }
                myFile.open(featpath);
                if (myFile.good())
                    break;
            }
            myFile.close();
            std::cout << "Please enter your feature names file filepath." << std::endl;
            std::cin >> featnamepath;
            myFile.open(featnamepath);
            while (!myFile.good()) {
                std::cout << "Please enter a valid filepath, or enter \'none\'" << std::endl;
                std::cin >> featnamepath;
                if (featnamepath == "none") {
                    featnamepath = "../feats.txt";
                    hasCustomFeats = false;
                }
                myFile.open(featnamepath);
                if (myFile.good())
                    break;
            }
            myFile.close();
        }
        else {
            featpath = "../feats.txt";
            featnamepath = "../featnames.txt";
        }
    } /*  ADD WHILE LOOPS TO ENSURE CORRECT FILEPATHS */
    g.setFeatPath(featpath);
    g.setFeatNamesPath(featnamepath);

    //---------------------------------------

    //-------------------------------------- picking people
    std::string from;
    std::string to;

    if ((!hasCustomFeats && !hasCustomSet) || (hasCustomFeats && hasCustomSet)) {

        std::cout << "Please enter a name to start from" << std::endl;
        std::cin >> from;
        std::cout << "Please enter a name to end at" << std::endl;
        std::cin >> to;

        //std::ifstream featNameFile;
        myFile.open(featnamepath);
        std::string line;
        int line_num = 0;
        bool found_from = false;
        bool found_to = false;

        if (myFile.is_open()) {
            while (getline(myFile, line)) {
                if (line.find("name") != std::string::npos) { //at names section

                    if (line.find(from) != std::string::npos && !found_from) { //found name
                        std::cout << "parsing " << from << " into a node id..." << std::endl;
                        //search featnames file
                        std::ifstream featFile;
                        featFile.open(featpath);
                        std::string featLine;
                        int index = (g.getIdLen() + 1) + (2 * line_num); //CHECK THIS
                        if (featFile.is_open()) {
                            while (getline(featFile, featLine)) {
                                if (featLine[index] == '1') {
                                    std::cout << from << "'s id is ";
                                    from = featLine.substr(0, g.getIdLen());
                                    std::cout << from << std::endl;
                                    found_from = true;
                                    break;
                                }
                            }
                        }
                        featFile.close();
                    }

                    if (line.find(to) != std::string::npos && !found_to) { //found name
                        //search featnames file
                        //index of 1 is id_len + 2*line_num
                        std::cout << "parsing " << to << " into a node id..." << std::endl;
                        std::ifstream featFile;
                        featFile.open(featpath);
                        std::string featLine;
                        int index = (g.getIdLen() + 1) + (2 * line_num);
                        ;
                        if (featFile.is_open()) {
                            while (getline(featFile, featLine)) {
                                if (featLine[index] == '1') {
                                    std::cout << to << "'s id is ";
                                    to = featLine.substr(0, g.getIdLen());
                                    std::cout << to << std::endl;
                                    found_to = true;
                                    break;
                                }
                            }
                        }
                        featFile.close();
                    }
                }
                line_num++;
            }
        }

        if (from.length() != (unsigned long)g.getIdLen()) {
            std::cout << "Coulnd't parse " << from << ", using default value" << std::endl;
            from = "116374117927631468606";
        }
        if (to.length() != (unsigned long)g.getIdLen()) {
            std::cout << "Coulnd't parse " << to << ", using default value" << std::endl;
            to = "116374117927631468606";
        }
    }
    else {
        std::cout << "No features found, please enter a Node Id to start from" << std::endl;
        std::cin >> from;
        std::cout << "No features found, please enter a Node Id to end at" << std::endl;
        std::cin >> to;
    }

    //-------------------------------------

    std::cout << "I'm finding the path between these people... please specify a max distance for me to search in." << std::endl;
    int lim;
    std::cin >> lim;
    if (g.findPathIddfs(from, to, lim)) {
        std::cout << "Path exists within " << lim << " nodes!\n";
        if ((!hasCustomFeats && !hasCustomSet) || (hasCustomFeats && hasCustomSet)) {
            g.printLastFoundPathNames();
        }
        else {
            g.printLastFoundPathId();
        }
    }
    else {
        std::cout << "Path does not exist within" << lim << " nodes...\n";
    }
 
}