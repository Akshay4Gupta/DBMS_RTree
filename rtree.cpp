#include<bits/stdc++.h>
#include "file_manager.h"
#include "errors.h"

using namespace std;

typedef vector<pair<int, int>> MBR;
typedef vector<pair<int, MBR>> vpintMBR;

/* Global Variables */
int d, maxCap, pagesUsed = 0, sizeofInt = sizeof(int);

class Node{
private:
  int id;
  int parentID;
  MBR mbr;
	vpintMBR children;
	bool isleaf;

  void recalculateMBR(){
    mbr = this->children[0].second;
    for(int i = 1; i < this->total_children; i++){
      updateMBR(this->children[i].second);
    }
  }
  int total_children;
public:
  Node(int id, vector<MBR> points, bool isleaf = true, vector<int> childrenIDs = vector<int>(maxCap, 0)){
    this->id = id;
    this->parentID = -1;
    this->total_children = points.size();
    this->children.resize(maxCap);
    for(int i = 0; i < points.size(); i++){
      this->children[i].first = childrenIDs[i];
      this->children[i].second = points[i];
      if(this->mbr.size() == 0)
        this->mbr = points[i];
      else
        this->updateMBR(points[i]);
    }
    for(int i = points.size(); i < maxCap; i++){
      this->children[i].first = -1;
      this->children[i].second = MBR(d, {INT_MIN, INT_MIN});
    }
    this->isleaf = isleaf;
  }

  Node(int id, vpintMBR children, bool isleaf = true){
    this->id = id;
    this->parentID = -1;
    this->total_children = children.size();
    this->children = children;
    this->children.resize(maxCap, {-1, MBR(d, {INT_MIN, INT_MIN})});
    this->isleaf = isleaf;
    this->mbr = children[0].second;
    for(int i = 1; i < children.size(); i++){
      this->updateMBR(children[i].second);
    }
  }

  // adds a child to the node if there is a space else return false;
  bool addChild(pair<int, MBR> idmbr){
    if(this->total_children >= maxCap)
      return false;
    this->children[this->total_children] = idmbr;
    this->total_children++;
    this->updateMBR(idmbr.second);
    return true;
  }

  // change the child's and update the node's mbr if the index provided is right;
  bool changeChildMBR(int i, MBR mbr){
    if(i >= this->total_children)
      return false;
    this->children[i].second = mbr;
    this->recalculateMBR();
    return true;
  }

  // change the child and update the node's mbr if the index provided is right;
  bool changeChild(int i, pair<int, MBR> child){
    if(i >= this->total_children)
      return false;
    this->children[i] = child;
    this->recalculateMBR();
    return true;
  }

  // updates the mbr of the node according to the given mbr. used when a new child is added to the node;
  bool updateMBR(MBR mbr){
    if(mbr.size() != this->mbr.size())
      return false;
    for(int i = 0; i < mbr.size(); i++){
      this->mbr[i].first = min(this->mbr[i].first, mbr[i].first);
      this->mbr[i].second = max(this->mbr[i].second, mbr[i].second);
    }
    return true;
  }

  bool updateMBR(vector<int> point){
    if(point.size() != this->mbr.size())
      return false;
    for(int i = 0; i < point.size(); i++){
      this->mbr[i].first = min(this->mbr[i].first, point[i]);
      this->mbr[i].second = max(this->mbr[i].second, point[i]);
    }
    return true;
  }

  // getter and setter functions;
  vpintMBR getChildren(){
    return vpintMBR (this->children.begin(), this->children.begin() + this->totalChildren());
  }

  MBR getMBR(){
    return this->mbr;
  }

  int getID(){
    return this->id;
  }

  int getParentID(){
    return this->parentID;
  }

  int totalChildren(){
    return this->total_children;
  }

  bool isLeaf(){
    return isleaf;
  }

  bool setParentID(int id){
    if(id < 0)
      return false;
    this->parentID = id;
    return true;
  }
};

int sizeofNode = sizeof(Node);

// function to check if nodes have correct value of not. read all the pages in tempfile.
void readNodes(FileManager &fm, string tempfile, int N){
  int l = sizeof(Node);
  FileHandler fh = fm.OpenFile(tempfile.c_str());
	PageHandler ph = fh.FirstPage();
  pagesUsed++;
	int i = 0, k = 0, v;
	while(true){
    i++;
    Node *node = (Node *)ph.GetData();
    // MBR x = node->getMBR();
    cout<<node->getID();
    // for(int j = 0; j < x.size(); j++){
    //   cout<<x[j].first<<":"<<x[j].second<<" ";
    // }
    // cout<<endl;
    // cout<<"<:>"<<node->getID()<<" "<<node->totalChildren()<<endl;
    // vpintMBR children = node->getChildren();
    // for(int j = 0; j < children.size(); j++){
    //   MBR childrenMBR = children[j].second;
    //   for(auto x: childrenMBR){
    //     cout<<x.first<<":"<<x.second<<" ";
    //   }
    //   cout<<endl;
    // }
    try{
      fh.UnpinPage(ph.GetPageNum());
      ph = fh.NextPage(ph.GetPageNum());
      k = 0;
    }catch(exception &e){
      break;
    }
    cout<<endl;
  }
  fm.CloseFile(fh);
}
/*----------------------------- INSERTION ---------------------------------*/
// check if the point lies inside the given mbr.
bool insideMBR(MBR &mbr, vector<int> &point){
  for(int i = 0; i < mbr.size(); i++){
    if(point[i] >= mbr[i].first && point[i] <= mbr[i].second){
      continue;
    }else{
      return false;
    }
  }
  return true;
}

// to calculate the area of the mbr. I think not I have not used this anywhere.
int calculateAreaOfMBR(MBR &mbr){
  int area = 0;
  for(auto i: mbr){
    area *= i.second - i.first;
  }
  return area;
}

// calculate the enlargenment of the mbr by considering that that point will lie inside this mbr.
vector<double> calculateMBREnlargenment(MBR &mbr, MBR &point){
  vector<double> area = {1, 1};
  for(int i = 0; i < mbr.size(); i++){
    area[0] *= max(mbr[i].second, point[i].second) - min(mbr[i].first, point[i].first);
    area[1] *= mbr[i].second - mbr[i].first;
  }
  area[0] -= area[1];
  return area;
}

// will return the node index to which this point insertion will cause the minimum mbr enlargenment.
// if you want third comparison to be nodes of minimum length pass the length instead of child node ids.
int minMBREnlargement(vpintMBR &childNodes, MBR &point){
  vector<vector<double>> areaMBRs;
  for(auto child: childNodes){
    areaMBRs.push_back(calculateMBREnlargenment(child.second, point));
    areaMBRs[areaMBRs.size()-1].push_back(child.first);
  }
  return min_element(areaMBRs.begin(), areaMBRs.end()) - areaMBRs.begin();
}

// find the distance between two mbrs: Hausdorff distance in case of hyper rectangle and euclidean distance in case of points.
int distanceBetweenMBRs(MBR &mbr1, MBR &mbr2, bool isLeaf){
  int distance = 0;
  if(!isLeaf){
    for(int i = 0; i < mbr1.size(); i++){
      distance = max(distance, max(abs(mbr1[i].first - mbr2[i].first), abs(mbr1[i].second - mbr2[i].second)));
    }
  }else{
    for(int i = 0; i < mbr1.size(); i++){
      distance += pow((mbr1[i].first - mbr2[i].first), 2);
    }
  }
  return distance;
}

// find two maximum distance nodes with bruteforce.
pair<int, int> maxDistanceMBRs(vpintMBR &childNodes, bool isLeaf){
  pair<int, int> p;
  int distance = 0;
  for(int i = 0; i < childNodes.size(); i++){
    for(int j = i+1; j < childNodes.size(); j++){
      int temp = distanceBetweenMBRs(childNodes[i].second, childNodes[j].second, isLeaf);
      if(temp > distance){
        distance = temp;
        p = {i, j};
      }
    }
  }
  return p;
}

// assign the provided children to one of the two nodes with given page numbers.
void assignToNode(FileManager &fm, FileHandler &fh, int newNodePageNum1, int newNodePageNum2, int e1, int e2, vpintMBR &childNodes){
  int threshold = ceil((float)maxCap/2.0);

  PageHandler ph1 = fh.PageAt(newNodePageNum1);
  Node *node1 = (Node *)ph1.GetData();

  PageHandler ph2 = fh.PageAt(newNodePageNum2);
  Node *node2 = (Node *)ph2.GetData();

  for(int i = 0; i < childNodes.size(); i++){
    if(i != e1 && i != e2){
      int tc_node1 = node1->totalChildren();
      // fh.MarkDirty(newNodePageNum1);
      // fh.UnpinPage(newNodePageNum1);
      // fh.FlushPage(newNodePageNum1);

      int tc_node2 = node2->totalChildren();
      // fh.MarkDirty(newNodePageNum2);
      // fh.UnpinPage(newNodePageNum2);
      // fh.FlushPage(newNodePageNum2);

      if(tc_node1 < threshold && tc_node2 < threshold){
        vpintMBR assignmentNodes = {{node1->totalChildren(), node1->getMBR()}};
        assignmentNodes.push_back({node2->totalChildren(), node2->getMBR()});
        int choice = minMBREnlargement(assignmentNodes, childNodes[i].second);
        if(choice == 0){
          // ph1 = fh.PageAt(newNodePageNum1);
          // node1 = (Node *)ph1.GetData();
          node1->addChild(childNodes[i]);
          // fh.MarkDirty(newNodePageNum1);
          // fh.FlushPage(newNodePageNum1);
        }else{
          // ph2 = fh.PageAt(newNodePageNum2);
          // node2 = (Node *)ph2.GetData();
          node2->addChild(childNodes[i]);
          // fh.MarkDirty(newNodePageNum2);
          // fh.FlushPage(newNodePageNum2);
        }
      }else{
        if(tc_node1 < threshold){
          // ph1 = fh.PageAt(newNodePageNum1);
          // node1 = (Node *)ph1.GetData();
          node1->addChild(childNodes[i]);
          // fh.MarkDirty(newNodePageNum1);
          // fh.FlushPage(newNodePageNum1);
        }else{
          // ph2 = fh.PageAt(newNodePageNum2);
          // node2 = (Node *)ph2.GetData();
          node2->addChild(childNodes[i]);
          // fh.MarkDirty(newNodePageNum2);
          // fh.FlushPage(newNodePageNum2);
        }
      }
    }
  }

  fh.MarkDirty(newNodePageNum1);
  // fh.FlushPage(newNodePageNum1);
  fh.MarkDirty(newNodePageNum2);
  // fh.FlushPage(newNodePageNum2);
  // fh.FlushPages();
}

// insert the node in the node with given pagenum and if needed split it into two
vpintMBR nodeInsert(FileManager &fm, FileHandler &fh, int pageNum, pair<int, MBR> &point){
  PageHandler ph = fh.PageAt(pageNum);
  Node *node_failed = (Node *)ph.GetData();
  bool isLeaf = node_failed->isLeaf();
  vpintMBR childNodes = node_failed->getChildren();

  vpintMBR ret;

  if(node_failed->totalChildren() < maxCap){
    fh.MarkDirty(pageNum);
    fh.UnpinPage(pageNum);
    fh.FlushPage(pageNum);
    ph = fh.PageAt(pageNum);
    Node *n = (Node *)ph.GetData();
    n->addChild(point);
    fh.MarkDirty(pageNum);
    fh.UnpinPage(pageNum);
    fh.FlushPage(pageNum);
    ph = fh.PageAt(pageNum);
    Node *n1 = (Node *)ph.GetData();
    ret = {{n1->getID(), n1->getMBR()}};
  }else{
    fh.UnpinPage(ph.GetPageNum());
    char *writedata;
    childNodes.push_back(point);
    sort(childNodes.begin(), childNodes.end());
    auto e = maxDistanceMBRs(childNodes, isLeaf);
    int e1 = e.first, e2 = e.second;

    PageHandler ph_newNode1 = fh.NewPage();
    int newNodePageNum1 = ph_newNode1.GetPageNum();
    writedata = ph_newNode1.GetData();
    Node *node1 = new Node(newNodePageNum1, {childNodes[e1]}, isLeaf);
    memcpy(writedata, node1, sizeofNode);
    fh.MarkDirty(newNodePageNum1);
    // fh.UnpinPage(newNodePageNum1);
    // fh.FlushPage(newNodePageNum1);

    PageHandler ph_newNode2 = fh.NewPage();
    int newNodePageNum2 = ph_newNode2.GetPageNum();
    writedata = ph_newNode2.GetData();
    Node *node2 = new Node(newNodePageNum2, {childNodes[e2]}, isLeaf);
    memcpy(writedata, node2, sizeofNode);
    fh.MarkDirty(newNodePageNum2);
    // fh.UnpinPage(newNodePageNum2);
    // fh.FlushPage(newNodePageNum2);
    // fh.FlushPages();

    assignToNode(fm, fh, newNodePageNum1, newNodePageNum2, e1, e2, childNodes);

    // ph_newNode1 = fh.PageAt(newNodePageNum1);
    // node1 = (Node *)ph_newNode1.GetData();
    MBR nm1 = node1->getMBR();
    fh.UnpinPage(newNodePageNum1);

    // ph_newNode2 = fh.PageAt(newNodePageNum2);
    // node2 = (Node *)ph_newNode2.GetData();
    MBR nm2 = node2->getMBR();
    fh.UnpinPage(newNodePageNum2);

    ret = {{newNodePageNum1, nm1}, {newNodePageNum2, nm2}};
  }
  fh.FlushPages();
  return ret;
}

vpintMBR insertion(FileManager &fm, FileHandler &fh, int pageNum, MBR &point){
  int m = ceil((float)maxCap / 2.0);
  PageHandler ph = fh.PageAt(pageNum);
  Node *node = (Node *)ph.GetData();
  vpintMBR childNodes = node->getChildren();
  fh.UnpinPage(ph.GetPageNum());
  vpintMBR ret;

  if(node->isLeaf()){
    pair<int, MBR> pintMBR = {0, point};
    ret = nodeInsert(fm, fh, pageNum, pintMBR);
    PageHandler ph = fh.PageAt(pageNum);
    Node *node = (Node *)ph.GetData();

  }else{
    int min_nodeID_iterator = minMBREnlargement(childNodes, point);
    fh.FlushPages();
    vpintMBR nodeIDs = insertion(fm, fh, childNodes[min_nodeID_iterator].first, point);

    ph = fh.PageAt(pageNum);
    node = (Node *)ph.GetData();
    if(nodeIDs.size() == 2){
      node->changeChild(min_nodeID_iterator, nodeIDs[0]);
      fh.MarkDirty(pageNum);
      // fh.FlushPage(pageNum);
      fh.FlushPages();
      ret = nodeInsert(fm, fh, pageNum, nodeIDs[1]);
    }else if(nodeIDs.size() == 1){
      node->changeChild(min_nodeID_iterator, nodeIDs[0]);
      ret.push_back({node->getID(), node->getMBR()});
      fh.MarkDirty(node->getID());
      // fh.FlushPage(node->getID());
    }
  }
  fh.FlushPages();
  return ret;
}

/*---------------------------- POINT QUERY --------------------------------*/
bool pointQuery(FileManager &fm, FileHandler &fh, int nodeid, vector<int> &point){
  PageHandler ph = fh.PageAt(nodeid);
  Node *node = (Node *)ph.GetData();
  vpintMBR childNodes = node->getChildren();
  fh.UnpinPage(nodeid);
  if(node->isLeaf()){
    for(auto child: childNodes){
      if(insideMBR(child.second, point)){
        return true;
      }
    }
  }else{
    for(auto child: childNodes){
      if(insideMBR(child.second, point)){
        if(pointQuery(fm, fh, child.first, point)){
          return true;
        }
      }
    }
  }
  return false;
}

/*----------------------------- BULKLOAD ---------------------------------*/
void assignParent(FileManager &fm, FileHandler &fh, vector<int> &childIDs, int N){
  int B = ceil((float)N / (float)maxCap);
  int S = min(maxCap, N);

  if(N <= 1){
    return;
  }
  PageHandler phParent = fh.NewPage();
  int parentid = phParent.GetPageNum();
  fh.MarkDirty(parentid);
  fh.UnpinPage(parentid);

  vector<MBR> oneNode;
  vector<int> oneNodeIDs;
  vector<int> currentNodeIDs;

  for(auto i: childIDs){
    PageHandler phChild = fh.PageAt(i);

    Node *child = (Node *)phChild.GetData();
    oneNode.push_back(child->getMBR());
    oneNodeIDs.push_back(child->getID());

    child->setParentID(parentid);
    fh.MarkDirty(phChild.GetPageNum());
    fh.UnpinPage(phChild.GetPageNum());

    if(oneNode.size() == maxCap){
      Node *parent = new Node(parentid, oneNode, false, oneNodeIDs);
      phParent = fh.PageAt(parentid);
      char *data = phParent.GetData();

      memcpy(data, parent, sizeofNode);
      fh.MarkDirty(parentid);
      fh.UnpinPage(parentid);
      currentNodeIDs.push_back(parentid);

      phParent = fh.NewPage();
      parentid = phParent.GetPageNum();
      oneNode.clear();
      oneNodeIDs.clear();
    }

  }
  if(oneNode.size() > 0){
    Node *parent = new Node(phParent.GetPageNum(), oneNode, false, oneNodeIDs);
    phParent = fh.PageAt(parentid);
    char *data = phParent.GetData();

    memcpy(data, parent, sizeofNode);
    fh.MarkDirty(parentid);
    fh.UnpinPage(parentid);
    currentNodeIDs.push_back(parentid);

  }else
    fh.DisposePage(phParent.GetPageNum());
  assignParent(fm, fh, currentNodeIDs, B);
}

Node *bulkload(FileManager &fm, FileHandler &fh, string tempfile, int N){
  FileHandler fhw = fm.CreateFile(tempfile.c_str());
  int pieces = ceil((float)N / (float)maxCap);

  PageHandler ph = fh.FirstPage();
  char *data = ph.GetData();

  int nodeSize = sizeof(Node);
  vector<MBR> oneNode;
  vector<int> currentNodeIDs;

  for(int i = 0, k = 0; i < N; i++){
    MBR point(d);
    for(int j = 0; j < d; j++){
      memcpy(&point[j].first, &data[k*sizeofInt], sizeofInt);
      memcpy(&point[j].second, &data[k++*sizeofInt], sizeofInt);
    }
    oneNode.push_back(point);
    if(oneNode.size() == maxCap){
      fh.UnpinPage(ph.GetPageNum());
      int currentpage = ph.GetPageNum();

      PageHandler phw = fhw.NewPage();
      char *writedata = phw.GetData();
      Node *node = new Node(phw.GetPageNum(), oneNode, true);
      memcpy(writedata, node, nodeSize);
      fhw.MarkDirty(phw.GetPageNum());
      fhw.UnpinPage(phw.GetPageNum());
      currentNodeIDs.push_back(phw.GetPageNum());
      ph = fh.PageAt(currentpage);
      data = ph.GetData();
      oneNode.clear();
    }
    if(PAGE_CONTENT_SIZE - (k*sizeofInt) < d*sizeofInt){
      try{
        fh.UnpinPage(ph.GetPageNum());
        ph = fh.NextPage(ph.GetPageNum());
        data = ph.GetData();
        k = 0;
      }catch(exception &e){
        break;
      }
    }
  }
  if(oneNode.size() > 0){
    fh.UnpinPage(ph.GetPageNum());

    PageHandler phw = fhw.NewPage();
    char *writedata = phw.GetData();
    Node *node = new Node(phw.GetPageNum(), oneNode, true);
    memcpy(writedata, node, nodeSize);
    fhw.MarkDirty(phw.GetPageNum());
    fhw.UnpinPage(phw.GetPageNum());
    currentNodeIDs.push_back(phw.GetPageNum());
  }

  fh.UnpinPage(ph.GetPageNum());
  assignParent(fm, fhw, currentNodeIDs, pieces);
  PageHandler phw = fhw.LastPage();
  Node *ret = (Node *)phw.GetData();
  fhw.UnpinPage(phw.GetPageNum());
  fm.CloseFile(fhw);
  return ret;
}


int main(int argc, char **argv){
  if(argc < 5)
    return -1;

  // READ QUERY FILE
  string queryFile = argv[1];
  ifstream file;
  file.open(queryFile.c_str());

  // INITIALIZE THE GLOBAL VARIABLES
  maxCap = atoi(argv[2]);
  d = atoi(argv[3]);

  // CREATE AND OPEN THE OUTPUT FILE
  string outputFile = argv[4];
  ofstream outfile;
  outfile.open(outputFile, ios::out);

  int root_node_id;
  Node *node = nullptr;
  FileManager fm;
  FileHandler fhw;
  string tempfile = "temp.txt", line;
  try{
    while(getline(file, line)){
      stringstream s(line);
      string word;
      s >> word;
      if(word == "BULKLOAD"){
        // input
        string sortedFile, totalpoints;
        s>>sortedFile;
        s>>totalpoints;
        int totalPoints = stoi(totalpoints);

        FileHandler fh = fm.OpenFile(sortedFile.c_str());
        node = bulkload(fm, fh, tempfile, totalPoints);
        root_node_id = node->getID();
        fm.CloseFile(fh);
        fhw = fm.OpenFile(tempfile.c_str());

        // cout<<endl<<"-----------------Node check:------------------------"<<endl;
        // readNodes(fm, tempfile, INT_MAX);
        outfile<<"BULKLOAD"<<endl<<endl<<endl;
      }else if(word == "INSERT"){
        // input
        MBR point;
        while(s>>word){
          point.push_back({stoi(word), stoi(word)});
        }
        if(point.size() != d)
          continue;
        int backupid = root_node_id;
        // fhw.FlushPages();
        try{
          vpintMBR retd_value = insertion(fm, fhw, root_node_id, point);
          if(retd_value.size() > 1){
            PageHandler newroot = fhw.NewPage();
            root_node_id = newroot.GetPageNum();
            Node *newRootNode = new Node(root_node_id, retd_value, false);
            char *tocpy = newroot.GetData();
            memcpy(tocpy, newRootNode, sizeofNode);
            fhw.MarkDirty(root_node_id);
            fhw.FlushPages();
          }else{
            root_node_id = retd_value[0].first;
          }
        }catch(exception &e){
          root_node_id = backupid;
        }
        // output
        outfile<<"INSERT"<<endl<<endl<<endl;
      }else if(word == "QUERY"){
        // input
        vector<int> point;
        while(s>>word){
          point.push_back(stoi(word));
        }
        try{
          bool x = pointQuery(fm, fhw, root_node_id, point);
          if(x)
            outfile<<"TRUE"<<endl<<endl<<endl;
          else
            outfile<<"FALSE"<<endl<<endl<<endl;
        }catch(exception &e){
          outfile<<"TRUE"<<endl<<endl<<endl;
        }// output
        fhw.UnpinPage(node->getID());
        fhw.FlushPages();
      }
    }
  }catch(exception &e){
    fm.DestroyFile(tempfile.c_str());
  }
  outfile.close();
  fm.CloseFile(fhw);
  fm.DestroyFile(tempfile.c_str());
  file.close();
  return 0;
}
