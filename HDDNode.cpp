#include <bits/stdc++.h>
// #include <unistd.h>

using namespace std;

// string pwd()
// {
//   char buff[FILENAME_MAX];
//   getcwd(buff, FILENAME_MAX);
//   string current_working_dir(buff);
//   return current_working_dir;
// }

void writeToFile(string filename, string name, string score)
{
  ofstream myfile(filename, ios::app);
  myfile << name << " " << score << endl;
  myfile.close();
}

string readFromFile(string filename)
{
  ifstream obj(filename);
  string line;
  string res;
  while (getline(obj, line))
  {
    res += line + "\n";
  }
  obj.close();
  return res;
}

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
    this->left = nullptr;
    this->right = nullptr;

    writeToFile("xyz.txt", this->key, this->value);
  }

  HDDNode(string key)
  {
    string contents = readFromFile("xyz.txt");
  }
};

int main()
{
  string name, score;
  cout << "Enter name and score:\n";
  cin >> name >> score;
  HDDNode *root = new HDDNode(name, score);
  cout << "Wrote to file\n";

  string contents = readFromFile("xyz.txt");
  cout << "Read from file\n";
  cout << contents;
  return 0;
}