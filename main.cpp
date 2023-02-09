#include <iostream>
#include <vector>
#include <stdexcept>

//bubble sort in desc order
void sort(std::vector<std::pair<int,int>>& v){
  for(unsigned int i=0; i<v.size()-1; i++){
    for(unsigned int j=0; j<v.size()-i-1; j++){
      if(v[j].second < v[j+1].second){
        std::pair<int, int> temp(v[j].first, v[j].second);
        v[j].first = v[j+1].first;
        v[j].second = v[j+1].second;
        v[j+1].first = temp.first;
        v[j+1].second = temp.second;
      }
    }
  }
}

//sort in asc order
void sortVector(std::vector<int>& v){
  for(unsigned int i=0; i<v.size()-1; i++){
    for(unsigned int j=0; j<v.size()-i-1; j++){
      if(v[j] > v[j+1]){
        int temp = v[j];
        v[j] = v[j+1];
        v[j+1] = temp;
      }
    }
  }
}

void sortMatrix(std::vector<std::pair<int, std::vector<int>>>& v){
  for(unsigned int i=0; i<v.size()-1; i++){
    for(unsigned int j=0; j<v.size()-i-1; j++){
      if(v[j].first > v[j+1].first){
        std::pair<int, std::vector<int>> temp(v[j].first, v[j].second);
        v[j].first = v[j+1].first;
        v[j].second = v[j+1].second;
        v[j+1].first = temp.first;
        v[j+1].second = temp.second;        
      }
    }
  }
  for(unsigned int i=0; i<v.size(); i++){
    if(!v[i].second.empty()){
      sortVector(v[i].second);
    }
  }
}


int search(std::vector<std::pair<int, std::vector<int>>>& v, int elem){
  for(unsigned int i=0; i<v.size(); i++){
    if(v[i].first == elem){
      return i;
    }
  }
  return -1;
}

std::vector<std::pair<int, std::vector<int>>> havelHakimiHelper(std::vector<std::pair<int,int>>& v){
  std::vector<std::pair<int, std::vector<int>>> output;
  std::vector<std::pair<int, std::vector<int>>> emptyOutput;
  std::vector<int> empVector; // create an empty vector
  
  //Uncomment if you want to see the steps
/* for(unsigned int i=0; i<v.size(); i++){
    std::cout << v[i].second << " ";
  }
  std::cout << "\n"; */
  
  if(v.size() == 1){
    if(v[0].second == 0){
      output.push_back(std::pair<int, std::vector<int>>(v[0].first,empVector));
    }
    return output; //returns an empty vector if the sequence is not graphic
  }
  sort(v);
  int vsize = v.size(); //casting to an int as not to cause any comparison issues
  if(v[0].second > (vsize-1)){
    return emptyOutput; //returns an empty vector if the sequence is not graphic
  }
  std::vector<std::pair<int,int>> newV;
  std::vector<int> indexes;
  for(unsigned int i=1; i<v.size(); i++){
    if(i <= v[0].second){
      newV.push_back(std::pair<int,int>(v[i].first, v[i].second-1));
      indexes.push_back(v[i].first);
    }
    else{
      newV.push_back(std::pair<int,int>(v[i].first, v[i].second));
    }
  }
  output = havelHakimiHelper(newV);
  if(output.empty()){
    return emptyOutput;
  }
  output.push_back(std::pair<int, std::vector<int>>(v[0].first, indexes));
  for(unsigned int i=0; i<indexes.size(); i++){
    output[search(output,indexes[i])].second.push_back(v[0].first);
  }
  return output;
}

std::vector<std::pair<int, std::vector<int>>> havelHakimi(std::vector<int>& v){
  std::vector<std::pair<int,int>> outputVector;
  for(unsigned int i=0; i<v.size(); i++){
    outputVector.push_back(std::pair<int,int>(i+1, v[i]));
  }
  return havelHakimiHelper(outputVector);
}

int main() {
  std::cout << "Enter the numbers of nodes in this graph: ";
  int n;
  std::cin >> n;
  std::cout << "Enter the degree sequence, seperated by spaces." << std::endl;
  std::vector<int> input;
  for(int i=0; i<n; i++){
    int k;
    std::cin >> k;
    input.push_back(k);
  }
  std::vector<std::pair<int, std::vector<int>>> output = havelHakimi(input);
  if(!output.empty()){
    sortMatrix(output);
  }
  for(unsigned int i=0; i<output.size(); i++){
    std::cout << output[i].first << ": ";
    for(unsigned int j=0; j<output[i].second.size(); j++){
      std::cout << output[i].second[j] << " ";
    }
    if(output[i].second.size() == 0){
      std::cout << "Empty";
    }
    std::cout << "\n";
  }
  if(output.size() == 0){
    std::cout << "This degree sequence is not graphic. \n";
  }
}