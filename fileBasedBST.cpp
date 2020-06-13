#include <bits/stdc++.h>
using namespace std;

class HDDNode
{
private:
  string key;
  string value;
  HDDNode *left;
  HDDNode *right;

public:
  HDDNode(string key, string value)
  {
    this->key = key;
    this->value = value;
    left = nullptr;
    right = nullptr;

    thread writeKeyVal(&HDDNode::writeToFile, this);
    writeKeyVal.join();
  }

  HDDNode(string key)
  {
    string filename = key + ".txt";
    fstream i(filename, ios::in | ios::out);
    string line;
    vector<string> lines;
    while (i)
    {
      getline(i, line);
      lines.push_back(line);
    }
    i.close();
    this->key = lines[0], this->value = lines[1];
    this->left = (lines[2] == "NULL") ? nullptr : new HDDNode(lines[2]);
    this->right = (lines[3] == "NULL") ? nullptr : new HDDNode(lines[3]);
  }

  string getKey() { return this->key; }
  string getValue() { return this->value; }
  HDDNode *getLeftNode() { return this->left; }
  HDDNode *getRightNode() { return this->right; }

  void setLeftNode(HDDNode *node)
  {
    this->left = node;

    thread writeLeftNode(&HDDNode::writeToFile, this);
    writeLeftNode.join();
  }

  void setRightNode(HDDNode *node)
  {
    this->right = node;

    thread writeRightNode(&HDDNode::writeToFile, this);
    writeRightNode.join();
  }

  void writeToFile()
  {
    string filename = key + ".txt";
    fstream o(filename, ios::in | ios::out | ios::trunc);
    string leftNode = left ? left->getKey() : "NULL";
    string rightNode = right ? right->getKey() : "NULL";
    string data = key + "\n" + value + "\n" + leftNode + "\n" + rightNode;
    o << data << endl;
    o.close();
  }
};

class BST
{
public:
  HDDNode *root;

  BST()
  {
    ifstream rt("root.txt");
    string line;
    if (rt)
    {
      getline(rt, line);
      this->root = line.empty() ? nullptr : new HDDNode(line);
    }
    else
    {
      this->root = nullptr;
    }
  }

  bool rootExists() { return this->root != nullptr; }

  void insert(HDDNode *node, string key, string value)
  {
    if (!node)
    {
      this->root = new HDDNode(key, value);
      fstream writeRoot("root.txt", ios::out | ios::in);
      writeRoot << this->root->getKey() << " "
                << this->root->getValue() << endl;
      writeRoot.close();
      return;
    }
    if (value > node->getValue())
    {
      if (!node->getRightNode())
        node->setRightNode(new HDDNode(key, value));
      else
        insert(node->getRightNode(), key, value);
    }
    else
    {
      if (!node->getLeftNode())
        node->setLeftNode(new HDDNode(key, value));
      else
        insert(node->getLeftNode(), key, value);
    }
  }

  string search(HDDNode *node, string key)
  {
    if (!node)
      return "";
    if (node->getKey() == key)
      return node->getValue();
    string l = search(node->getLeftNode(), key);
    return (!l.empty()) ? l : search(node->getRightNode(), key);
  }

  void put(string key, string value) { insert(root, key, value); }
  string get(string key) { return search(root, key); }
};

int main()
{
  BST *bst = new BST();
  int choice;
  string key, value;
  while (1)
  {
  start:
    cout << "Enter your choice: (1. Enter data 2. Find Data 3. Quit)\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
      int numNodes;
      cout << "Enter number of nodes to be inserted into BST:\n";
      cin >> numNodes;
      while (numNodes--)
      {
        cout << "Enter key and value:\n";
        cin >> key >> value;
        if ((!(bst->get(key)).empty()))
          cout << "Key already exists!\n";
        else
          bst->put(key, value);
      }
      break;
    case 2:
      if (!(bst->rootExists()))
      {
        cout << "Tree is null, Enter data first!\n";
        break;
      }
      cout << "Enter key to search for:\n";
      cin >> key;
      value = bst->get(key);
      if (!value.empty())
        cout << "Value for " << key << " is " << value << "\n";
      else
        cout << "Key not found!\n";
      break;
    case 3:
      exit(1);
      break;
    default:
      cout << "Invalid choice! Enter again\n";
      goto start;
      break;
    }
  }
  return 0;
}