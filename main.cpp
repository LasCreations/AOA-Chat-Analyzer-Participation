#include <fstream> 
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Class Definitions
class TimeStamp {
	private:
  		int hour, minute, seconds;

	public:
  		TimeStamp() {}
  		TimeStamp(int hr, int min, int sec) {
    			this->hour = hr;
    			this->minute = min;
    			this->seconds = sec;
  		}

  void setHour(int hr) { this->hour = hr; }

  void setMinute(int min) { this->minute = min; }

  void setSeconds(int sec) { this->seconds = sec; }

  int getHour() { return this->hour; }

  int getMinute() { return this->minute; }

  int getSeconds() { return this->seconds; }
};

class Chat {
private:
  string message;
  TimeStamp timestamp;

public:
  // default constructor
  Chat() {}

  // Primary constructor
  Chat(TimeStamp timestamp, string message) {
    this->timestamp = timestamp;
    this->message = message;
  }

  // Mutators and Accessors
  void SetTimeStamp(TimeStamp timestamp) { this->timestamp = timestamp; }

  TimeStamp GetTimeStamp() { return this->timestamp; }

  void SetMessage(string message) { this->message = message; }

  string GetMessage() { return this->message; }
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

  int getIdNum() { return Idnum; }

  void setIdNum(int IdNum) { this->Idnum = IdNum; }

  string getFname() { return fname; }

  void setFname(string Fname) { this->fname = Fname; }

  string getLname() { return lname; }

  void setLname(string Lname) { this->lname = Lname; }

  float getParticipation() { return participation; }

  void setChat(Chat chat) { this->chat.push_back(chat); }

  vector<Chat> getChats() { return this->chat; }

  void setParticipation(float Participation) {
    this->participation = Participation;
  }
};

class Answer {
private:
  TimeStamp timestamp;
  string ans;

public:
  Answer() {}

  Answer(string Answer, TimeStamp timestamp) {
    this->ans = Answer;
    this->timestamp = timestamp;
  }

  void setAnswer(string Answer) { this->Answer = Answer; }

  void setTimestamp(TimeStamp timestamp) { this->timestamp = timestamp; }

  string getAnswer() { return this->Answer; }

  TimeStamp getTimestamp() { return this->timestamp; }
};

class QuestionNode {
private:
  Question data;
  QuestionNode *nextNode; // Node *nextNode;

public:
  // Implementing the Default Constructor
  QuestionNode() {
    data = Question();
    nextNode = NULL;
  }

  // Implementing the Primary Constructor
  QuestionNode(Question data) {
    this->data = data;
    this->nextNode = NULL;
  }

  // Implementing the copy Constructor
  QuestionNode(QuestionNode *obj) {
    this->data = obj->data;
    this->nextNode = NULL;
  }

  // Implementing the getters and setters
  Question getData() { return data; }

  void setData(Question data) { this->data = data; }

  QuestionNode *getNextNode() { return nextNode; }

  void setNextNode(QuestionNode *nextNode) { this->nextNode = nextNode; }

  void Display() {
    cout << data.getQuestion() << endl;
    cout << data.getAnswer() << endl;
    cout << data.getTimestamp().getHour() << endl;
    cout << data.getTimestamp().getMinute() << endl;
    cout << data.getTimestamp().getSeconds() << endl;
  }
};

class QuestionLinkedList {
private:
  QuestionNode *head; // private Node *head;

public:
  // Implementing the Default Constructor
  QuestionLinkedList() {
    head = NULL; // It is null becasue there is nothing to reference to
                 // becasue the list is empty.
  }

  // Implementing the IsEmpty Method
  bool IsEmpty() {
    if (head == NULL)
      return true;
    else
      return false;
  }

  // Implementing the Insert at Front method
  void InsertAtFront(Question data) {
    QuestionNode *temp = new QuestionNode(data);
    if (temp != NULL) {
      if (IsEmpty()) {
        head = temp;
      } else {
        temp->setNextNode(head);
        head = temp;
      }
    }
  }

  void Display() {
    QuestionNode *traverse = head;
    while (traverse != NULL) {
      traverse->Display();
      traverse = traverse->getNextNode();
    }
  }
};

void readChatFile(vector<Student> &studentVector, string filepath) {
  	ifstream inputFile;           
  	inputFile.open(filepath);     
  	if (!inputFile.is_open()) { 
      	 	cerr << "Failed to open the input file." << endl;
  	}else {
		regex pattern(R"((\d{2}):(\d{2}):(\d{2}) From (\w+ \w+): (.+))");
    		smatch match;
    		string line;
   		while (getline(inputFile, line)) {
      			// Try to match the regular expression
      			if (std::regex_match(line, match, pattern)) {
        			Chat chat;
       		 		Student student;
        		
				chat.SetTimeStamp(TimeStamp(stoi(match[1]), stoi(match[2]), stoi(match[3])));
        			student.setFname(match[4]);
        			chat.SetMessage(match[5]);

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

void readQuestionAnswerFile(vector<Student> &studentVector, string filepath){

}

int main() {
  // Declare vectors for student and chat
  vector<Student> *studentVector = new vector<Student>();

  // Declare a linked list for the questions
  QuestionLinkedList *questionsList = new QuestionLinkedList();

  readChatFile(*studentVector, "ChatSession.txt"); 
  
  
  for (int i = 0; i < studentVector->size(); i++) {
    cout << (*studentVector)[i].getFname() << " " << (*studentVector)[i].getLname() << endl;
    cout << "Chats:" << endl;
    for(int j = 0; j<(*studentVector)[i].getChats().size();j++){
    	cout<< (*studentVector)[i].getChats()[j].GetTimeStamp().getHour() << ":" << 
		(*studentVector)[i].getChats()[j].GetTimeStamp().getMinute() <<":" <<
		(*studentVector)[i].getChats()[j].GetTimeStamp().getSeconds()
	      << " " << (*studentVector)[i].getChats()[j].GetMessage() << endl;
    }
    cout << "\n\n" << endl;
  }
  return 0;
}

