#include <iostream>
#include <vector>

using namespace std;

class Node {

    private:
    
        int         data;
    
        Node*       son;
    
        Node*       brother;
    
    public:
    
        Node(int newdata){
        
            data    =   newdata;
        
            son     =   NULL;
        
            brother =   NULL;
        }
    
        void AddSon(Node newson){
        
            son     =   &newson;
        }
    
        void AddBrother(Node newbrother){
            
            brother =   &newbrother;
        }
    
        Node* AskSon(){
        
            return son;
        }
    
        Node* AskBrother(){
            
            return brother;
        }
    
        ostream& operator << (ostream& os){
       
            return os<<data;
        }
};


class Tree {
    
    private:
    
        Node* origin;
    
        std::vector<Node> Numeration;
    
        std::vector<Node> Container;
    
        void AddRoute(int newdata){
            
            Node neworigin(newdata);
            
            neworigin.AddSon(*origin);
            
            origin     =    &neworigin;

            Numeration.push_back(neworigin);
        }
    
        void AddSon(int newdata, Node father){
        
            Node newson(newdata);
        
            father.AddSon(newson);
        
            Numeration.push_back(newson);
        }
    
        void AddBrother(int newdata, Node brother){
        
            Node newbrother(newdata);
        
            brother.AddBrother(newbrother);
        
            Numeration.push_back(newbrother);
        }
    
    public:
    
        Tree(Node neworigin){
        
            origin     =    &neworigin;
            
            Numeration.push_back(neworigin);
        }
    
        void Strait(Node self){
            
            Container.push_back(self);
            
            if (self.AskSon()!=NULL){
                
                Container.push_back(*(self.AskSon()));
                
                Strait(*(self.AskSon()));
            }
            
            if (self.AskBrother()!=NULL){
                
                Container.push_back(*(self.AskBrother()));
                
                Strait(*(self.AskBrother()));
            }
        }
    
        Node SearchBrother(Node oldnode){
            
            if (oldnode.AskBrother()!=NULL){
                
                SearchBrother(*(oldnode.AskBrother()));
            }
            
            return oldnode;
        }
    
        void Add(int newdata, int number){
        
            Strait(*origin);
        
            Node newnode(newdata);
        
            if (Container.at(number).AskSon()==NULL) {
           
                Container.at(number).AddSon(newnode);
            
            } else {
            
                SearchBrother(*(Container.at(number).AskSon())).AddBrother(newnode);
            }
        
        }
    
        void ShowTree(){
            
            for(int i=0; i<Container.size(); i++){
                
                cout<<i+1<<":"<<&Container.at(i);
            }
        }
    
    //void Simmentric();
    //void Reverse();
};

void Add(Tree TheTree){
    
    int         data,
                number;
    
    cout<< "Enter the number of the element you want the son to be added";
    
    cin>>number;
    
    cout<< "Enter the value of the new element";
    
    cin>>data;
    
    TheTree.Add(data, number);
}

int main(int argc, const char * argv[])
{
    Node origin(1);
    Tree MyTree(origin);
    MyTree.Add(2, 0);
    MyTree.Add(3, 0);
    MyTree.Add(4, 1);
    MyTree.ShowTree();
    
    return 0;
}

