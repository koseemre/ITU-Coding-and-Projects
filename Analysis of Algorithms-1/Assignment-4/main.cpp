#include <iostream>
#include <cstring>
#include <fstream>
#define SIZE 10000

using namespace std;

bool black=0;
bool red=1;
bool male=0;
bool female=1;

class Person{
public:
    string name;
    char gender;
    int age;
};
class RedBlackTreeNode{ //Node for holding Person nodes and women and men numbers
public:
    RedBlackTreeNode(string NewName, bool NewGender, int NewAge);
    string Name;
    bool Gender;
    int Age;
    bool color;
    RedBlackTreeNode *right;
    RedBlackTreeNode *left;
    RedBlackTreeNode *parent;
    int womenNum;
    int menNum;
};
RedBlackTreeNode::RedBlackTreeNode(string NewName, bool NewGender, int NewAge){
    Name = NewName;
    Gender = NewGender;
    Age = NewAge;
    color = black;
    right = NULL;
    left = NULL;
    parent = NULL;
    womenNum=0;
    menNum=0;
}
class RedBlackTree{ //Red-Black Tree structure
public:
    RedBlackTree();
    void insertion(RedBlackTreeNode *NewNode);
    void printing();
    void nth_man(int i);
    void nth_woman(int i);
    void counter();

private:
    RedBlackTreeNode *root;
    RedBlackTreeNode *NIL;

    void maintenance(RedBlackTreeNode *NewNode){
        RedBlackTreeNode *temptraverse;

        while (NewNode->parent->color == red){
            if (NewNode->parent == NewNode->parent->parent->left){
                temptraverse = NewNode->parent->parent->right;
                if (temptraverse->color == red){
                    NewNode->parent->color = black;
                    temptraverse->color = black;
                    NewNode->parent->parent->color = red;
                    NewNode = NewNode->parent->parent;
                }
                else{
                    if (NewNode == NewNode->parent->right){
                        NewNode = NewNode->parent;
                        LEFT_ROTATE(NewNode);
                    }
                    NewNode->parent->color = black;
                    NewNode->parent->parent->color = red;
                    RIGHT_ROTATE(NewNode->parent->parent);
                }
            }
            else{
                temptraverse = NewNode->parent->parent->left;
                if (temptraverse->color == red){
                    NewNode->parent->color = black;
                    temptraverse->color = black;
                    NewNode->parent->parent->color = red;
                    NewNode = NewNode->parent->parent;
                }
                else{
                    if (NewNode == NewNode->parent->left){
                        NewNode = NewNode->parent;
                        RIGHT_ROTATE(NewNode);
                    }
                    NewNode->parent->color = black;
                    NewNode->parent->parent->color = red;
                    LEFT_ROTATE(NewNode->parent->parent);
                }
            }
        }
        root->color = black;
    }
    void LEFT_ROTATE(RedBlackTreeNode *newnode){
        RedBlackTreeNode *temptraverse;

        temptraverse = newnode->right;
        newnode->right = temptraverse->left;
        temptraverse->left->parent = newnode;
        temptraverse->parent = newnode->parent;
        if (newnode->parent == NIL)
            root = temptraverse;
        else{
            if (newnode == newnode->parent->left)
                newnode->parent->left = temptraverse;
            else
                newnode->parent->right = temptraverse;
        }
        temptraverse->left = newnode;
        newnode->parent = temptraverse;
    }
    void RIGHT_ROTATE(RedBlackTreeNode *newnode){
        RedBlackTreeNode *temptraverse;

        temptraverse = newnode->left;
        newnode->left = temptraverse->right;
        temptraverse->right->parent = newnode;
        temptraverse->parent = newnode->parent;
        if (newnode->parent == NIL)
            root = temptraverse;
        else{
            if (newnode == newnode->parent->right)
                newnode->parent->right = temptraverse;
            else
                newnode->parent->left = temptraverse;
        }
        temptraverse->right = newnode;
        newnode->parent = temptraverse;
    }
    void printing_node(RedBlackTreeNode* traverse, int depth,char direct){ // direct helps the know node is from left('l') or right('r') child
        if(traverse == NIL){
            return;
        }
        printing_node(traverse->left,++depth,'l');
        for(int i=0;i<depth-1;i++){
            cout<<"   		 ";
        }
        if(direct == 'l' )
            cout<<"/ ";
        else if(depth != 1)
            cout<<"\\";
        if(traverse->color==0){
            if(traverse->Gender==male)
                cout<<"(B) "<<traverse->Name<<"-"<<traverse->Age<<"-M "<<endl;
            else if(traverse->Gender==female)
                cout<<"(B) "<<traverse->Name<<"-"<<traverse->Age<<"-F "<<endl;
        }
        else{
            if(traverse->Gender==male)
                cout<<"(R) "<<traverse->Name<<"-"<<traverse->Age<<"-M "<<endl;
            else if(traverse->Gender==female)
                cout<<"(B) "<<traverse->Name<<"-"<<traverse->Age<<"-F "<<endl;
        }
        depth--;

        printing_node(traverse->right,++depth,'r');
    }
    // Find Nth Man
    RedBlackTreeNode* finding_nth_man(RedBlackTreeNode * traverse, int i){
        int j;
        if(traverse->Gender == 0)
            j = traverse->left->menNum+1;
        else
            j = traverse->left->menNum;

        if(i == j && traverse->Gender == 0)
            return traverse;
        else if (i>j){
            finding_nth_man(traverse->right, i-j);
        }
        else
        {
            finding_nth_man(traverse->left, i);
        }


    }
    // Find Nth Woman
    RedBlackTreeNode* finding_nth_woman(RedBlackTreeNode* traverse, int i){
        int j;
        if(traverse->Gender == 1)
            j = traverse->left->womenNum+1;
        else
            j = traverse->left->womenNum;



        if (i == j && traverse->Gender == 1)
            return traverse;
        else if (i>j)
            finding_nth_woman(traverse->right, i-j);
        else
            finding_nth_woman(traverse->left, i);
    }
    // counts the number of men and women in tree
    void counter_for_man_woman(RedBlackTreeNode *traverse){

        if (traverse->right != NIL)
            counter_for_man_woman(traverse->right);

        if (traverse->left != NIL)
            counter_for_man_woman(traverse->left);

        if (traverse->Gender == male){
            traverse->menNum++;
        }
        else
            traverse->womenNum++;

        if (traverse != root){
            traverse->parent->menNum += traverse->menNum;
            traverse->parent->womenNum += traverse->womenNum;
        }
    }
};

RedBlackTree::RedBlackTree(){
    NIL=new RedBlackTreeNode("NIL",0,0);
    NIL->color=black;
    NIL->left=NIL;
    NIL->right=NIL;
    NIL->parent=NIL;
    root=NIL;
}

//insertion function
void RedBlackTree::insertion(RedBlackTreeNode *newnode){
    RedBlackTreeNode *temptraverse1=root;
    RedBlackTreeNode *temptraverse2=NIL;

    while(temptraverse1 != NIL){
        temptraverse2 = temptraverse1;
        for(int i=0;i<strlen(newnode->Name.c_str()) || i<strlen(temptraverse1->Name.c_str());i++){
            if(newnode->Name[0]<temptraverse1->Name[0]){
                temptraverse1 = temptraverse1->left;
                break;
            }
            else if(newnode->Name[0] == temptraverse1->Name[0]){
                continue;
            }
            else{
                temptraverse1 = temptraverse1->right;
                break;
            }
        }
    }
    newnode->parent=temptraverse2;

    if(temptraverse2 == NIL)
        root = newnode;
    else{
        for(int i=0;i<strlen(newnode->Name.c_str()) || i<strlen(temptraverse2->Name.c_str());i++){
            if(newnode->Name[0] < temptraverse2->Name[0]){
                temptraverse2->left = newnode;
                break;
            }
            else if(newnode->Name[i] == temptraverse2->Name[i]){
                continue;
            }
            else{
                temptraverse2->right = newnode;
                break;
            }
        }
    }
    newnode->color = red;
    newnode->right = NIL;
    newnode->left = NIL;
    maintenance(newnode);
}

void RedBlackTree::printing(){
    printing_node(root, 0,'n');
}

void RedBlackTree::nth_man(int i){
    RedBlackTreeNode* temp=finding_nth_man(root, i);
    cout<<temp->Name;
}

void RedBlackTree::nth_woman(int i){
    RedBlackTreeNode *temp=finding_nth_woman(root, i);
    cout <<temp->Name;
}

void RedBlackTree::counter(){
    counter_for_man_woman(root);
}

int main(int argc, char** argv){
    ifstream fin(argv[1]);
    Person *list=new Person[SIZE];
    int i=0;
    RedBlackTree mytree;

    while(!fin.eof()){
        fin>>list[i].name;
        fin>>list[i].gender;
        fin>>list[i].age;
        i++;
    }
    for(int j=0;j<i;j++){
        RedBlackTreeNode *newnode;
        if(list[j].gender=='M')
            newnode=new RedBlackTreeNode(list[j].name,male,list[j].age);
        else if(list[j].gender=='F')
            newnode=new RedBlackTreeNode(list[j].name,female,list[j].age);
        mytree.insertion(newnode);
    }
    mytree.printing();
    mytree.counter();

    cout << "3nd woman: ";
    mytree.nth_woman(3);
    cout << endl;

    cout << "4nd man: ";
    mytree.nth_man(4);
    cout << endl;



    delete []list;
    fin.close();
    return 0;
}
