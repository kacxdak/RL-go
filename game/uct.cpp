#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

#include "main.h"
#include "node.h"
#include "uct.h"

//UCT
UCT::UCT(int bsize, bool dbg) {
	debug = dbg;
	if(debug) cout<<"Init tree"<<endl;
	boardsize = bsize;
	size = 0;
	//Start with empty board
	Item empty;
	empty.group = 0;
	empty.val = 0;
	empty.visit = false;
	Item** currboard;
	currboard = new Item*[boardsize];
	for(int i=0;i<boardsize;i++) {
		currboard[i] = new Item[boardsize];
		for(int j=0;j<boardsize;j++)
			currboard[i][j] = empty;
	}
	root = new Node(size++, currboard, boardsize);
	root->setDebug(debug);
	Node *next = new Node(size++, currboard, boardsize);
	next->setDebug(debug);
	next->addConnect(root, Coor(-1,-1));
	root->addConnect(next, Coor(-1,-1));
	if(debug) cout<<"Finished Init tree"<<endl;
}

// Public Functions
Node* UCT::insert(Node* prev, Item** currBoard, Coor move) {
//	Node *prev = search(prevBoard);
//	int rotate = prev->Compare(prevBoard);
	if(debug) cout<<"Inserting Node to "<<prev->id<<"\t"<<move.x<<", "<<move.y<<endl<<"\tCurrent size: "<<size<<endl;
	Node *next = new Node(size++, currBoard, boardsize);
	Node *nextpt2 = new Node(size++, currBoard, boardsize);
	next->setDebug(debug);
	nextpt2->setDebug(debug);
	next->addConnect(nextpt2, Coor(-1,-1));
	nextpt2->addConnect(next, Coor(-1,-1));
	if(!prev->addConnect(next, move)) {
		cout<<"\n\nInserting with  tree did not connect"<<endl;
		//dump data
		exit(0);
	}
	if(debug) cout<<" New size: "<<size<<endl;
	return next;
}

Node* UCT::Search(Item** board) {
	queue<Node *> searchlist;
	searchlist.push(root);
	vector<int> idlist (1, root->id);
	while(!searchlist.empty()) {
		Node* curr = searchlist.front();
		if(curr->Compare(board) != -1)
			return curr;
		for( int i = 0; i < 82; i++ ) {
			Node* next = curr->Select(i);
			if(next != NULL) {
				if( find(idlist.begin(), idlist.end(), next->id) != idlist.end() ) {
					searchlist.push(next);
					idlist.push_back(next->id);
				}
			}
		}
		searchlist.pop();
	}
	return NULL;
}

void UCT::UCT_output(){
	ofstream myfile; 
	myfile.open("UCT_Tree");
	myfile<<size<<endl;
	myfile<<boardsize<<endl;
	UCT_Write(root,myfile);
}

void UCT::UCT_Write(Node* current, ofstream myfile){
	if (current == NULL)
		return;
	int i, j;
	for (i=0; i<boardsize; i++) {
		for (j=0; j<boardsize; j++){
			myfile << current->board[i][j];
			if (j==boardsize-1)
				myfile<<endl;
		}
	}
	myfile << current->visit<<endl;
	myfile << current->id<<endl;
	for (i=0; i<=boardsize*boardsize;i++){
		myfile << current->visit<<endl;
		myfile <<amafvisit<<endl;
		myfile <<value<<endl;
		myfile <<amafvalue<<endl;
		if (next==NULL)
			myfile<<-1<<endl;
		else
			myfile<<current
	



	

//Private Functions
