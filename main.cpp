#include <fstream> 
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Chat {
	private:
  		string message;
  		string timestamp;

	public:
  		Chat() {}

  		Chat(string timestamp, string message) {
    			this->timestamp = timestamp;
    			this->message = message;
  		}	

  		void SetTimeStamp(string timestamp) { 
			this->timestamp = timestamp; 
		}

  		string GetTimeStamp() {
		       	return this->timestamp; 
		}

 	 	void SetMessage(string message) { 
			this->message = message; 
		}

  		string GetMessage() {
		       	return this->message; 
		}
};

class Student {
	private:
  		int Idnum;
  		string fname;
  		string lname;
  		float participation;
  		vector<Chat> chat;

	public:
  		Student() {}
  		Student(int IdNum, string Fname, string Lname, float Participation){
    			this->Idnum = IdNum;
    			this->fname = Fname;
    			this->lname = Lname;
    			this->participation = Participation;
  		}

  		int getIdNum() {
		   	return Idnum; 
		}

  		void setIdNum(int IdNum) {
		       	this->Idnum = IdNum; 
		}

  		string getFname() {
		       	return fname; 
		}

  		void setFname(string Fname) {
		       	this->fname = Fname; 
		}

  		string getLname() {
		       	return lname; 
		}

  		void setLname(string Lname) {
		       	this->lname = Lname; 
		}

  		float getParticipation() {
		       	return participation; 
		}

  		void setChat(Chat chat) {
		       	this->chat.push_back(chat); 
		}

  		vector<Chat> getChats() {
		       	return this->chat; 
		}

  		void setParticipation(float Participation) {
    			this->participation = Participation;
  		}
};

class Answer {
	private:
  		string timestamp;
  		string ans;

	public:
  		Answer() {}

  		Answer(string Answer, string timestamp) {
   	 		this->ans = Answer;
    			this->timestamp = timestamp;
  		}

  		void setAnswer(string Answer) { 
			this->ans = Answer; 
		}

  		void setTimestamp(string timestamp) {
		       	this->timestamp = timestamp; 
		}

  		string getAnswer() {
		       	return this->ans; 
		}

  		string getTimestamp() {
		       	return this->timestamp; 
		}
};

class AnswerNode {
	private:
  		Answer data;
  		AnswerNode *nextNode, *previousNode; // Node *nextNode;

	public:
  		AnswerNode() {
    			data = Answer();
    			nextNode = NULL;
			previousNode = NULL;
  		}

  		AnswerNode(Answer data) {
    			this->data = data;
    			this->nextNode = NULL;
			this->previousNode = NULL;
 	 	} 

  		Answer getData() { return data; }

  		void setData(Answer data) { this->data = data; }

  		AnswerNode *getNextNode() { return nextNode; }

  		void setNextNode(AnswerNode *nextNode) { this->nextNode = nextNode; }	
		
		AnswerNode *getPreviousNode(){return previousNode;}
		
		void setPreviousNode(AnswerNode *previousnode){previousNode = previousnode;}
};

class AnswerLinkedList {
	private:
		AnswerNode *Head, *Tail;
	public:
		AnswerLinkedList(){
			Head = NULL;
			Tail = NULL;
		}

		AnswerLinkedList(AnswerNode *head, AnswerNode *tail){
			Head = head;
			Tail = tail;
		}

		AnswerNode *GetHead() const{
			return Head;
		}
		
		AnswerNode *GetTail(){
			return Tail;
		}

		void InsertAtFront(Answer dataToInsert){
			AnswerNode *temp = new AnswerNode(dataToInsert);
			if(temp!=NULL){
				if(IsEmpty()){
					Head = temp;
					Tail = temp;
				}else{
					temp->setNextNode(Head);
					Head->setPreviousNode(temp);
					Head = temp;
				}	
			}
		}
			
		void InsertAtBack(Answer dataToInsert){
			AnswerNode *temp = new AnswerNode(dataToInsert);
			if(temp!=NULL){
				if(IsEmpty()){
					Head = temp;
					Tail = temp;
				}else{
					Tail->setNextNode(temp);
					temp->setPreviousNode(Tail);
					Tail = temp;
				}	
			}
		}
	
		int CountNodes(){
			AnswerNode *temp = new AnswerNode; //Create a new node
			int count=0;
			temp = Head;
			while(temp!=NULL){
				count++;
				temp = temp->getNextNode();
			}
			return count;
		}
		
		bool IsEmpty(){
			if(Head==NULL)return true;
			else return false;
		}
};


//Function Declaration 
void readChatFile(vector<Student>&, string);
void readAnswerFile(AnswerLinkedList&, string);
bool isEarlierTime(const string&, const string&);
vector<string> Tokenizer(const string&);

/*
void traverseList(const AnswerLinkedList& answerList, vector<Student>& studentVector){
	
	//Runs all student
	for (int i = 0; i < studentVector.size(); i++) {
      		//cout << (*studentVector)[i].getFname() << " " << (*studentVector)[i].getLname() << endl;
      		//cout << "Chats:" << endl;
		//Runs all student chat
      		for(int j = 0; j<studentVector[i].getChats().size();j++){
			//compare the time stamp of a answer with the students response
      			for(AnswerNode* traverse = answerList.getHead(); traverse != NULL; traverse = traverse->getNextNode()){
				if(isEarlierTime(traverse->getData().getTimestamp(),studentVector[i].getChats()[j].GetTimeStamp())
					&& isEarlierTime(studentVector[i].getChats()[j].GetTimeStamp(),
					       	traverse->getNextNode()->getData().getTimestamp())){
					cout << "jnrei" << endl;	
				}
			}
		}
    		//cout << "\n\n" << endl;
  	}		
}*/


void traverseList(const AnswerLinkedList& answerList, vector<Student>& studentVector){
/*
for (int i = 0; i < studentVector.size(); i++) {
        for (int j = 0; j < studentVector[i].getChats().size(); j++) {
            // Ensure that getHead() is not returning nullptr
            AnswerNode* traverse = answerList.getHead();
            while (traverse != nullptr) {
                // Ensure that getNextNode() is not returning nullptr
                if (traverse->getNextNode() != nullptr &&
                    isEarlierTime(traverse->getData().getTimestamp(), studentVector[i].getChats()[j].GetTimeStamp()) &&
                    isEarlierTime(studentVector[i].getChats()[j].GetTimeStamp(), traverse->getNextNode()->getData().getTimestamp())) {
                    cout << "jnrei" << endl;
                }
                traverse = traverse->getNextNode();
            }
        }
   }*/
	/*
	AnswerNode* traverse = answerList.GetHead();
	while(traverse != NULL){
		cout << traverse->getData().getTimestamp() << endl;
		traverse = traverse->getNextNode();
	}*/

	
	//Runs all student
	for (int i = 0; i < studentVector.size(); i++) {
      		cout << studentVector[i].getFname() << " " << studentVector[i].getLname() << endl;
      		cout << "Chats: \n" << endl;
		
		//Runs all student chat
      		for(int j = 0; j<studentVector[i].getChats().size();j++){	
			//compare the time stamp of a answer with the students response
			AnswerNode* traverse = answerList.GetHead();
			while(traverse != NULL){
				if(traverse->getNextNode() != NULL && 
					isEarlierTime(traverse->getData().getTimestamp(),
					studentVector[i].getChats()[j].GetTimeStamp()) &&
			       		isEarlierTime(studentVector[i].getChats()[j].GetTimeStamp(),
					traverse->getNextNode()->getData().getTimestamp())){
					//vector<string> answerVector = ; 
					//vector<string> chatVector = ;	
					//cout << "jnrei" << endl;
					cout <<"Student Message: " <<  studentVector[i].getChats()[j].GetMessage() << endl;	
					cout <<"Student Message TimeStamp: " << studentVector[i].getChats()[j].GetTimeStamp() << endl;	
					cout << "Answer TimeStamp: " << traverse->getData().getTimestamp()<< endl;	
					cout << "Answer : " << traverse->getData().getAnswer()<< endl;	
					cout << "\n\n" << endl;
				
				}
				traverse = traverse->getNextNode();
			}
		}
    		//cout << "\n\n" << endl;
  	}	
}

int main() {
  	vector<Student> *studentVector = new vector<Student>();
  	AnswerLinkedList *answerList = new AnswerLinkedList();

  	readChatFile(*studentVector, "ChatSession.txt"); 
	readAnswerFile(*answerList, "Answer.txt");
	
	traverseList(*answerList,*studentVector);
	
	//answerList->traverseList();  
	
  	return EXIT_SUCCESS;
}

// Function to check if time1 is earlier than time2
bool isEarlierTime(const string& time1, const string& time2) {
    	// Helper function to convert time in "hh:mm:ss" format to seconds
    	auto parseTime = [](const string& time) {
        	int hours, minutes, seconds;
        	sscanf(time.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);
        	return hours * 3600 + minutes * 60 + seconds;
    	};

    	// Convert time1 and time2 to time points (moments in time)
    	auto timePoint1 = system_clock::now() + seconds(parseTime(time1));
    	auto timePoint2 = system_clock::now() + seconds(parseTime(time2));

    	// Compare the time points
    	return timePoint1 < timePoint2;
}

vector<string> Tokenizer(const string& input) {
	regex wordPattern("\\b(\\w+)\\b");
    	sregex_token_iterator iter(input.begin(), input.end(), wordPattern, 1);
    	sregex_token_iterator end;
    	vector<std::string> result(iter, end);
    	return result;
}

void readChatFile(vector<Student> &studentVector, string filepath) {
  	ifstream inputFile;           
  	inputFile.open(filepath);     
  	if (!inputFile.is_open()) { 
      	 	cerr << "Failed to open the input file." << endl;
  	}else {
		regex pattern(R"((\d{2}:\d{2}:\d{2}) From (\w+ \w+): (.+))");
    		smatch match;
    		string line;
   		while (getline(inputFile, line)) {
      			// Try to match the regular expression
      			if (std::regex_match(line, match, pattern)) {
        			Chat chat;
       		 		Student student;
        		
				chat.SetTimeStamp(match[1]);
        			student.setFname(match[2]);
        			chat.SetMessage(match[3]);
        			// Split the full name into first name and last name
        			size_t spacePos = student.getFname().find(' ');
        			if (spacePos != std::string::npos) {
          				student.setLname(student.getFname().substr(spacePos + 1));
          				student.setFname(student.getFname().erase(spacePos));
        			}	
				student.setParticipation(0.0);
				student.setChat(chat);
				
				bool found = false;	
				for(int i = 0; i<studentVector.size();i++){
					if(student.getFname()==studentVector[i].getFname() && 
						student.getLname()==studentVector[i].getLname()){
						found = true;
						studentVector[i].setChat(chat);	
					}
				}
				if(!found){
        				studentVector.push_back(student);
				}
      			}
    		}
    		inputFile.close();
  	}
}

void readAnswerFile(AnswerLinkedList &answerList, string filepath){
		ifstream inputFile;           
  		inputFile.open(filepath);     
  		if (!inputFile.is_open()) { 
      	 		cerr << "Failed to open the input file." << endl;
  		}else {
			regex pattern(R"((\d{2}:\d{2}:\d{2})\s(.+))");
    			smatch match;
    			string line;
   			while (getline(inputFile, line)) {
      			if (std::regex_match(line, match, pattern)) {
        			Answer answer;	
				answer.setTimestamp(match[1]);
				answer.setAnswer(match[2]);
				if(answerList.IsEmpty()){
        				answerList.InsertAtFront(answer);
				}else{
        				answerList.InsertAtBack(answer);
				}
      			}
    		}
    		inputFile.close();
  	}

}
