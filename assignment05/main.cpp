/// @brief Assignment 5
/// Calculates minimum number of cameras needed for a building of N rooms 

#include "binTree.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

///---------------------------------------
/// func: preOrder()
/// @param binTreeIterator root
/// preorder traversal of the tree (debugging)
///---------------------------------------
void preOrder(binTree<visibilityType>::binTreeIterator it);

///---------------------------------------
/// func: correctedStr()
/// @param string
/// @return corrected string
/// removes '.' and extraneous characters from read in inputs
///---------------------------------------
std::string correctedStr(std::string input);

///---------------------------------------
/// func: traverse()
/// @param binTreeIterator
/// @param binTreeIterator
/// sets up the cameras - to be called in main
///---------------------------------------
void traverse(binTree<visibilityType>::binTreeIterator it, 
            binTree<visibilityType>::binTreeIterator root);

///---------------------------------------
/// func: payload()
/// @param binTreeIterator
/// @param binTreeIterator
/// @return boolean values for 'this' node
/// checks child's boolean values, returns parent's boolean values
///---------------------------------------
visibilityType payload(binTree<visibilityType>::binTreeIterator it, 
            binTree<visibilityType>::binTreeIterator root);

///---------------------------------------
/// func: countCameras()
/// @param binTreeIterator
/// @return amount of cameras in tree
/// post order traversal to count cameras
///---------------------------------------
int countCameras(binTree<visibilityType>::binTreeIterator it);

///---------------------------------------
/// main-entry point
///---------------------------------------
int main(int argc, char* argv[])
{
    int status = 0;

    if (argc != 2) {

        status = 1;

    }else {

        std::ifstream inFile;
        std::vector<visibilityType> nums;
        std::stringstream ss;
        std::string input;
        int cases;
        int id;
        int cams;

        binTree<visibilityType> t0;
        std::vector<binTree<visibilityType>::binTreeIterator> nodes;

        inFile.open(argv[1]);

        // Read # of Cases
        std::getline(inFile, input, '\n');

        ss << input;
        ss >> cases;
        for (int i = 0; i < cases; i++) {
            
            ss.clear();
            nums.clear();
            nodes.clear();

            //read next line
            std::getline(inFile, input, '\n');
            input = correctedStr(input);
            ss << input;
            while (!ss.eof()) {
                
                visibilityType node;
                ss >> node.id;

                node.camera = false;
                node.seen = false;
    
                nums.push_back(node);
            }
            // build tree, with id's in vector
            t0.buildTree(nums);

            // place cameras
            traverse(t0.rootIterator(), t0.rootIterator());

            // count cameras
            cams = countCameras(t0.rootIterator());
            std::cout << "Case " << (i + 1) << ":  " << cams << " cameras needed" << '\n';
        }
        inFile.close();
        ss.clear();
        nums.clear();
        nodes.clear();
    }

    return status;
}

void preOrder(binTree<visibilityType>::binTreeIterator it)
{
    if (it != nullptr)
    {
        auto node = *it;
        std::cout << "[" << node.id << " camera: " << ((*it).camera? "yes" : "no") << "] ";
        preOrder(it.leftChild());
        preOrder(it.rightChild());
    }
}

std::string correctedStr(std::string input)
{
    for (int i = 0; i < input.length(); i++) {
        if (!(input[i] >= '0' && input[i] <= '9') && (input[i] != ' ' && input[i] != '-'))
        {
            input.erase(i , 1);
        }
    }

    return input;
}

void traverse(binTree<visibilityType>::binTreeIterator it, 
            binTree<visibilityType>::binTreeIterator root)
{
    // this sets the visibilityType vars
    // post order traversal
    // lets get to leaves first before anything else
    if (it != nullptr) {

        traverse(it.leftChild(), root);
        traverse(it.rightChild(), root);

        // if a leaf is found, mark em as seen but no camera
        if (it.leftChild() == nullptr && it.rightChild() == nullptr) {

            (*it).seen = true;
            // corner case where theres only 1 node in the tree
            if ((*it).id == (*root).id) {

                (*it).camera = true;

            }else {

                (*it).camera = false;

            }

        // if not dealing with a leaf
        }else {
            // check children
            auto settings = payload(it, root);

            // set the parents booleans based off children's
            (*it).camera = settings.camera;
            (*it).seen = settings.seen;

        }

    }
}

visibilityType payload(binTree<visibilityType>::binTreeIterator it, 
            binTree<visibilityType>::binTreeIterator root)
{
    visibilityType warhead;

    warhead.camera = false;
    warhead.seen = false;

    auto lchild = it.leftChild();
    auto rchild = it.rightChild();

    if (lchild != nullptr && rchild != nullptr) {
        
        // if children are seen but have no camera
        if (((*lchild).seen && !(*lchild).camera) && ((*rchild).seen && !(*rchild).camera)) {

            warhead.camera = true;
            warhead.seen = true;

        // if one child has no camera
        }else if ( (!(*lchild).camera != !(*rchild).camera) ) {

            warhead.camera = true;
            warhead.seen = true;

            // change which side that has no camera to seen
            if (!(*lchild).camera) {

                (*lchild).seen = true;

            }else if (!(*rchild).camera) {

                (*rchild).seen = true;

            }

        // if both children have cameras
        }else if (((*lchild).seen && (*lchild).camera) && ((*rchild).seen && (*rchild).camera)) {

            warhead.seen = true;

        }

    }else {

        // only left side is valid
        if (rchild == nullptr) {

            // if left side has camera
            if ((*lchild).camera) {

                warhead.seen = true;

            }else {

                warhead.seen = true;
                warhead.camera = true;

            }
                

        }

        // only right side is valid
        if (lchild == nullptr) {

            if ((*rchild).camera) {

                warhead.seen = true;

            }else {

                warhead.seen = true;
                warhead.camera = true;

            }
                
        }

    }

    return warhead;
}

int countCameras(binTree<visibilityType>::binTreeIterator it)
{
    if (it == nullptr) {
        return 0;
    }

    return countCameras(it.leftChild()) + countCameras(it.rightChild()) + ((*it).camera? 1 : 0);
}
