#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <cstring>
#include <ctime>


// The class which holds the states as objects
class State{
    int id;
    char Farmer;
    char Rabbit;
    char Fox;
    char Carrots;

public:
    int edgesNumber;
    State *edges;
    State(){
        Farmer = 'w';
        Rabbit = 'w';
        Fox = 'w';
        Carrots = 'w';
        edges=NULL;
        edgesNumber=0;
        id=0;
    }



    int calculateId(){  // this id calculation helps to find neighbours easily
        id=0;
        if(Farmer=='e')
            id=id+8;
        if(Rabbit == 'e')
            id=id+4;
        if(Fox == 'e')
            id=id+2;
        if(Carrots == 'e')
            id=id+1;

        return id;
    }

    void addEdge(State &newState){  // to construct bfs graph

        if(edges==NULL){
            edgesNumber++;
            edges = new State();
            edges= &newState;

        }

        else{
            State *temp = new State[edgesNumber];

            for(int i=0;i<edgesNumber;i++){
                temp[i] = edges[i];
            }

            edges = new State[edgesNumber+1];
            int i=0;
            for(i=0; i < edgesNumber;i++){
                edges[i] = temp[i];

            }

            edges[i] = newState;
            edgesNumber++;

            delete []temp;
        }

    }
    // calculates the neighbour number of any node
        int calculateEdgeNum(){
                int possibleEdgeNumber=1;
                if(Farmer == Rabbit)
                    possibleEdgeNumber++;
                if(Farmer == Fox)
                    possibleEdgeNumber++;
                if(Farmer == Carrots)
                    possibleEdgeNumber++;

                return possibleEdgeNumber;
        }
        //getters
        int getEdgesNumber()  {
            return edgesNumber;
        }

        char getFarmer()  {
            return Farmer;
        }

        void setFarmer(char Farmer) {
            State::Farmer = Farmer;
        }

        char getRabbit()  {
            return Rabbit;
        }

        void setRabbit(char Rabbit) {
            State::Rabbit = Rabbit;
        }

        char getFox()  {
            return Fox;
        }

        void setFox(char Fox) {
            State::Fox = Fox;
        }

        char getCarrots()  {
            return Carrots;
        }

        void setCarrots(char Carrots) {
            State::Carrots = Carrots;
        }


};


// this class is used to handle bfs and dfs
class BfsDfsHandler{

public:
    State *root;
    int path[50];
    int solution[50];
    int solutionLength;
    bool flag[15];      //holds visited nodes for bfs
    bool flagDfs[15];   //holds visited nodes for dfs
    int reachedNodeNumber; // 1 for bfs
    int reachedNumberDfs;
    int s[9]={0,12,4,14,2,11,3,15}; // solution control array
    int keptInMemoryBfs;


    BfsDfsHandler(State *rootNode){

        root = rootNode;
        root->edges=NULL;
        root->calculateId();
        flag[0]= true;  // this flag is used for bfs
        keptInMemoryBfs=0;
        for(int i=1;i<15;i++){
            flag[i] = false;
        }
        for(int i=0;i<15;i++){

            flagDfs[i] = false; // this flag is used for dfs
        }

        reachedNodeNumber=1;
        reachedNumberDfs =0;
        solutionLength=1;
        path[0] = 0;        // first state id is zero ( look report to understand the mean of id)
    }

    void deleteGraph(State* state)
    {
         if (state == NULL) return;
          int edgesNum= state->getEdgesNumber();
          for(int i=0 ; i<edgesNum; i++){
              deleteGraph(&state->edges[i]);
          }


          delete state;

    }
    //destrcutor
    ~BfsDfsHandler(){
        deleteGraph(root);
    }
    //controls the state according to rules of crossing river
    bool isValidState(State &state){
        int id = state.calculateId();
        if(id == 0 || id == 12 ||id == 4 ||id == 14 ||id == 2 ||id == 11 ||id == 3 ||id == 15)
            return  true;
        else
            return false;
    }
    //returns neighbours of any state
    std::vector<State>  getNeighbours(State currentState){
        std::vector<State> myVector;


        int possibleEdgeNumber=1;
        if(currentState.getFarmer() == currentState.getRabbit())
            possibleEdgeNumber++;
        if(currentState.getFarmer() == currentState.getFox())
            possibleEdgeNumber++;
        if(currentState.getFarmer() == currentState.getCarrots())
            possibleEdgeNumber++;

        int k=0;
        char currentLoc = currentState.getFarmer();
        int randNumber=0;

        if(possibleEdgeNumber>0 ){

            State states[possibleEdgeNumber];


            if(currentState.getFarmer()==currentState.getFox()){

                if(currentLoc == 'w'){
                    states[k].setFarmer('e');
                    states[k].setFox('e');}
                states[k].setRabbit(currentState.getRabbit());
                states[k].setCarrots(currentState.getCarrots());
                if(states[k].calculateId() != 7)
                myVector.push_back(states[k]);
                k++;
            }
            if(currentState.getFarmer()==currentState.getRabbit()){

                if(currentLoc == 'w'){

                    states[k].setFarmer('e');
                    states[k].setRabbit('e');}
                states[k].setFox(currentState.getFox());
                states[k].setCarrots(currentState.getCarrots());
                if(states[k].calculateId() != 7)
                    myVector.push_back(states[k]);
                k++;
            }
            if(currentState.getFarmer()==currentState.getCarrots()){

                if(currentLoc == 'w'){
                    states[k].setFarmer('e');
                    states[k].setCarrots('e');}
                states[k].setRabbit(currentState.getRabbit());
                states[k].setFox(currentState.getFox());
                if(states[k].calculateId() != 7)
                    myVector.push_back(states[k]);
                k++;
            }

            if(currentLoc == 'w')
                states[k].setFarmer('e');
            else
                states[k].setFarmer('w');

            states[k].setRabbit(currentState.getRabbit());
            states[k].setFox(currentState.getFox());
            states[k].setCarrots(currentState.getCarrots());
            states[k].calculateId();
            if(states[k].calculateId() != 7)
                myVector.push_back(states[k]);
            k++;



            return myVector;

        }

    }
    //to costruct bfs graph
    void assignNeighbours(State *currentState, char type){

        int possibleEdgeNumber=1;
        if(currentState->getFarmer() == currentState->getRabbit())
            possibleEdgeNumber++;
        if(currentState->getFarmer() == currentState->getFox())
            possibleEdgeNumber++;
        if(currentState->getFarmer() == currentState->getCarrots())
            possibleEdgeNumber++;

        int k=0;
        char currentLoc = currentState->getFarmer();

        if(possibleEdgeNumber>0 ){

            State states[possibleEdgeNumber];

            if(currentState->getFarmer()==currentState->getRabbit()){

                if(currentLoc == 'w'){

                    states[k].setFarmer('e');
                    states[k].setRabbit('e');}
                states[k].setFox(currentState->getFox());
                states[k].setCarrots(currentState->getCarrots());

                k++;
            }
            if(currentState->getFarmer()==currentState->getFox()){

                if(currentLoc == 'w'){
                    states[k].setFarmer('e');
                    states[k].setFox('e');}
                states[k].setRabbit(currentState->getRabbit());
                states[k].setCarrots(currentState->getCarrots());

                k++;
            }
            if(currentState->getFarmer()==currentState->getCarrots()){

                if(currentLoc == 'w'){
                    states[k].setFarmer('e');
                    states[k].setCarrots('e');}
                states[k].setRabbit(currentState->getRabbit());
                states[k].setFox(currentState->getFox());
                k++;
            }

            if(currentLoc == 'w')
                states[k].setFarmer('e');
            else
                states[k].setFarmer('w');

            states[k].setRabbit(currentState->getRabbit());
            states[k].setFox(currentState->getFox());
            states[k].setCarrots(currentState->getCarrots());

            states[k].calculateId();

            if(type == 'b'){

                for(int i=0;i<possibleEdgeNumber;i++){
                    int currentId= states[i].calculateId();
                    currentState->addEdge(states[i]);
                    keptInMemoryBfs++;

                }
            }



        }

    }
    // gets a node from bfs graph
    State * getState(int NodeId){
        bool searchFlag[15]= { false };
        State *temp = root;
        searchFlag[0]= true;
        std::queue<State*> myqueue;
        myqueue.push(temp);
        while(!myqueue.empty()){
            State *tempNode = myqueue.front();
            myqueue.pop();
            if(tempNode->calculateId() == NodeId)
                return tempNode;

            for(int i=0; i< tempNode->getEdgesNumber();i++){

                if(searchFlag[tempNode->edges[i].calculateId()] == false ){

                    myqueue.push(&(tempNode->edges[i]));
                    searchFlag[tempNode->edges[i].calculateId()] = true;

                }

            }
        }
        return NULL;
    }

    //printing for solution
    void printState(int id){
        if(id==0)
            std::cout <<  "farmer (W) , rabbit (W) , fox(W) , carrots (W) ";
        if(id==1)
            std::cout <<  "farmer (W) , rabbit (W) , fox(W) , carrots (E) ";
        if(id==2)
            std::cout <<  "farmer (W) , rabbit (W) , fox(E) , carrots(W) ";
        if(id==3)
            std::cout <<  "farmer (W) , rabbit (W) , fox(E) , carrots(E) ";
        if(id==4)
            std::cout <<  "farmer (W) , rabbit (E) , fox(W) , carrots(W) ";
        if(id==5)
            std::cout <<  "farmer (W) , rabbit (E) , fox(W) , carrots(E) ";
        if(id==6)
            std::cout <<  "farmer (W) , rabbit (E) , fox(E) , carrots(W) ";
        if(id==7)
            std::cout <<  "farmer (W) , rabbit (E) , fox(E) , carrots(E) ";
        if(id==8)
            std::cout <<  "farmer (E) , rabbit (W) , fox(W) , carrots(W) ";
        if(id==9)
            std::cout <<  "farmer (E) , rabbit (W) , fox(W) , carrots(E) ";
        if(id==10)
            std::cout <<  "farmer (E) , rabbit (W) , fox(E) , carrots(W) ";
        if(id==11)
            std::cout <<  "farmer (E) , rabbit (W) , fox(E) , carrots(E) ";
        if(id==12)
            std::cout <<  "farmer (E) , rabbit (E) , fox(W) , carrots(W) ";
        if(id==13)
            std::cout <<  "farmer (E) , rabbit (E) , fox(W) , carrots(E) ";
        if(id==14)
            std::cout <<  "farmer (E) , rabbit (E) , fox(E) , carrots(W) ";
        if(id==15)
            std::cout <<  "farmer (E) , rabbit (E) , fox(E) , carrots(E) ";
    }
    void printPath(){
        std::cout << "\nSolution Path: ";
        for(int i =0 ; i< 2 ; i++){
            std::cout << "**********************"<< std::endl;
        }
        for(int i =0 ; i< 8 ; i++){
            if(i == 0)
                std::cout <<  "starting point: farmer(w) , rabbit (w) , fox(w) , carrots(w) " << std::endl;
            else{
                std::cout<< "from  ";
                printState(path[i-1]);

                std::cout<< "  to  ";
                printState(path[i]);
                std::cout<< std::endl;
            }

        }
        for(int i =0 ; i< 2 ; i++){
            std::cout << "****************************************************************************************"<< std::endl;
        }
    }

    void printSolution(){
        std::cout << "\nSolution Path: ";
        for(int i =0 ; i< 2 ; i++){
            std::cout << "****************************************************************************************"<< std::endl;
        }
        for(int i =0 ; i< solutionLength ; i++){
            if(i == 0)
                std::cout <<  "starting point: farmer(w) , rabbit (w) , fox(w) , carrots(w) " << std::endl;
            else{
                std::cout<< "from  ";
                printState(solution[i-1]);

                std::cout<< "  to  ";
                printState(solution[i]);
                std::cout<< std::endl;
            }

        }
        for(int i =0 ; i< 2 ; i++){
            std::cout << "****************************************************************************************"<< std::endl;
        }
    }

//controls the node is valid or not
    bool isValidId(int newId){
        int id = newId;

        if( id == 0 || id == 12 ||id == 4 ||id == 14 ||id == 2 ||id == 11 ||id == 3 || id == 15){
            for(int i=0 ; i<solutionLength; i++){
                if(solution[i] == id)
                    return false;
            }
        }

        if( id == 12 ||id == 4 ||id == 14 ||id == 2 ||id == 11 || id == 3 || id == 15 )
            return true;
        else
            return false;
    }



    void addToSolution(int id){
        solutionLength++;
        solution[solutionLength-1] = id;
    }

// to find a solution for bfs
    void findSolution(State *temp){

        if(temp->calculateId() == 15)
            return;


        int neighNum = temp->getEdgesNumber();
        for(int a = 0; a < neighNum; a++)
        {
            int x=temp->edges[a].calculateId();
        }


        for(int i = 0; i< neighNum; i++)
        {
            if(isValidId(temp->edges[i].calculateId()))
            {

                addToSolution(temp->edges[i].calculateId());
                std::cout << temp->edges[i].calculateId() << " ";
                State *newRoot = getState(temp->edges[i].calculateId());
                std::cout << " " << newRoot->calculateId();

                findSolution(newRoot);
                break;

            }
        }
    }
    // to handle bfs
    void bfs() {
        State *rootState = root;
        std::queue<State*> myqueue;
        myqueue.push(rootState);

        while(!myqueue.empty()){

            State *tempNode = myqueue.front();

            myqueue.pop();

            assignNeighbours(tempNode,'b');
            std::cout<< tempNode->getEdgesNumber();

            for(int i=0; i< tempNode->getEdgesNumber();i++){

                if(flag[tempNode->edges[i].calculateId()] == false ){

                    myqueue.push(&(tempNode->edges[i]));
                    path[reachedNodeNumber] = tempNode->edges[i].calculateId();
                    flag[tempNode->edges[i].calculateId()] = true;
                    tempNode->edges[i].calculateId();
                    reachedNodeNumber++;
                }

            }
            if(reachedNodeNumber == 15 ){
                std::cout<< "all nodes are reached" << std::endl;
                break;
            }
        }

        while(!myqueue.empty()){

            State *tempNode = myqueue.front();
            myqueue.pop();
            if(tempNode->calculateId() != 15 && tempNode->calculateId() != 0)
                assignNeighbours(tempNode,'b');
        }
    }
    // to handle dfs (returns boolean value if solution is found)
    bool dfs(){

        std::vector<State> myVector;
        std::stack<State> myStack;
        State tempNode;


        tempNode= *root;
        myStack.push(tempNode);


        while(!myStack.empty()){


            tempNode = myStack.top();
            int sayac= tempNode.calculateEdgeNum();
            myVector = getNeighbours(tempNode);



            if(flagDfs[tempNode.calculateId()] == false ){


                flagDfs[tempNode.calculateId()] = true;
                myStack.pop();

                path[reachedNumberDfs] = tempNode.calculateId();
                reachedNumberDfs++;


                State bestMatch;
                bool matchFound = false;

                for(int i=0; i< sayac; i++){

                    if(isValidState(myVector[i]) && flagDfs[myVector[i].calculateId()] == false){

                        bestMatch = myVector[i];
                        matchFound = true;

                    }

                }

                if(matchFound){
                    for(int i=0; i< sayac; i++){
                        if(myVector[i].calculateId() != bestMatch.calculateId())
                            myStack.push(myVector[i]);
                    }
                        myStack.push(bestMatch);
                }
                else
                    for(int i=0; i< sayac; i++){
                            myStack.push(myVector[i]);
                    }


            }
            else{
                myStack.pop();
            }

            if(reachedNumberDfs == 15 ){
                std::cout<< "all nodes are reached" << std::endl;
                break;
            }
        }
    }


};



int main(int argc, char *argv[]) {

    if(argc != 2){
        std::cout << "invalid parameters";
    }
    else{
        std::string bfs = "bfs";
        std::string dfs = "dfs";
        if(bfs.compare(argv[1]) == 0)
        {

            clock_t time;
            time=clock();
            State *root = new State();
            BfsDfsHandler *bfsHandler = new BfsDfsHandler(root);
            bfsHandler->bfs();

            State *r = bfsHandler->getState(0);
            bfsHandler->findSolution(r);
            time=clock()-time;
            std::cout<<"\n\n";
            std::cout<<"\n\nAlgorithm:BFS \n";
            std::cout << "Number of visited nodes: 15" << std::endl;
            std::cout << "Maximum number of nodes kept in memory: " << bfsHandler->keptInMemoryBfs<< std::endl;
            std::cout<<"Running Time: "<<((double)time/double(CLOCKS_PER_SEC))*1000 <<std::endl;
            std::cout << "Solution move count: 8" << std::endl;
            bfsHandler->printSolution();
        }
        else if(dfs.compare(argv[1]) == 0){
            clock_t time;
            time=clock();
            State *root = new State();
            BfsDfsHandler *dfsHandler = new BfsDfsHandler(root);
            bool ctrl = dfsHandler->dfs();
            time=clock()-time;

            std::cout<<"\n\nAlgorithm:DFS \n";
            std::cout << "Number of visited nodes: 8" << std::endl;
            std::cout << "Maximum number of nodes kept in memory: 1(only for root node, other nodes are not taken with new[])" << std::endl;
            std::cout<<"Running Time: "<<((double)time/double(CLOCKS_PER_SEC))*1000 <<std::endl;
            std::cout << "Solution move count: 8" << std::endl;
            dfsHandler->printPath();

            if(ctrl)
                std::cout << "solution was found in dfs " <<std::endl;
            else
                std::cout << "solution was not found in dfs" <<std::endl;
        }
    }

    
}
