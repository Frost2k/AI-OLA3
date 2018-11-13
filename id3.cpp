#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <math.h>
#include<iostream>

using namespace std;

struct BstNode
{
    int data;
    BstNode* left;
    BstNode* right;
};

BstNode* GetNewNode(int data)
{
    BstNode* newNode = new BstNode();
    newNode -> data = data;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}


vector<vector<int> > sort_attributes(vector<vector<double> > data);
int main(int argc, char* argv[]) {

  int numFeatures;
  ifstream trainingInput;
  ifstream testingInput;

  vector<vector<double> > data;
  vector<vector<int> > indices;
  string line;
  double value;

  numFeatures = atoi(argv[1]);
  trainingInput.open(argv[2]);
  testingInput.open(argv[3]);
  
  getline(trainingInput,line);
  stringstream parsed(line);
  
  // Prep vectors...
  while (!parsed.eof()) {
    parsed >> value;
    data.push_back(vector<double>());
  }
  
  while (!trainingInput.eof()) {
    stringstream parsed(line);
    for (int i = 0; i < data.size(); i++) {
      parsed >> value;
      data[i].push_back(value);
    }
    getline(trainingInput,line);
  }

  // This is the important stuff...
  indices = sort_attributes(data);

  // Apply permutation for specific column
  for (int k = 0; k < data.size(); k++) {
    cout << "Sorting by " << k << "th column..." << endl;
    for (int j = 0; j < data[0].size(); j++) {
      for (int i = 0; i < data.size(); i++) {
	cout << data[i][indices[k][j]] << " ";
      }
      cout << endl;
    }
  }

  return 0;


}

// Attribute sorting
vector<vector<int> > sort_attributes(vector<vector<double> > data) {
  vector<vector<int> > indices;
  vector<double> *ptr;
  indices.resize(data.size());
  for (int x = 0; x < indices.size(); x++) {
    indices[x].resize(data[x].size());
    iota(indices[x].begin(),indices[x].end(),0);
    ptr = &(data[x]);
    sort(indices[x].begin(),indices[x].end(),
	 [&](size_t i, size_t j){ return (*ptr)[i] < (*ptr)[j]; });
  }
  return indices;
}
