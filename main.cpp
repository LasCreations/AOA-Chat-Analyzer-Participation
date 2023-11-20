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
  		AnswerNode *nextNode; // Node *nextNode;

	public:
  		AnswerNode() {
    			data = Answer();
    			nextNode = NULL;
  		}

  		AnswerNode(Answer data) {
    			this->data = data;
    			this->nextNode = NULL;
 	 	} 

  		Answer getData() { return data; }

  		void setData(Answer data) { this->data = data; }

  		AnswerNode *getNextNode() { return nextNode; }

  		void setNextNode(AnswerNode *nextNode) { this->nextNode = nextNode; }	
};

class AnswerLinkedList {
	private:
  		AnswerNode *head; 

	public:	
  		AnswerLinkedList() {
    			head = NULL; 
  		}

  		bool IsEmpty() {
    			if (head == NULL)
      				return true;
    			else
      				return false;
  		}

  		void InsertAtFront(Answer data) {
    			AnswerNode *temp = new AnswerNode(data);
    			if (temp != NULL) {
      				if (IsEmpty()) {
        				head = temp;
      				}else {
        				temp->setNextNode(head);
        				head = temp;
      				}
    			}
  		}

  		int CountNode() {
    			AnswerNode *traverse = head;
			int count = 0;
    			while (traverse != NULL) {
      				//traverse->Display();
				count++;
      				traverse = traverse->getNextNode();
    			}
			return count;
  		}
};

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
        			answerList.InsertAtFront(answer);
      			}
    		}
    		inputFile.close();
  	}

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

int main() {
  	vector<Student> *studentVector = new vector<Student>();
  	AnswerLinkedList *answerList = new AnswerLinkedList();

  	readChatFile(*studentVector, "ChatSession.txt"); 
	readAnswerFile(*answerList, "Answer.txt");



	cout << answerList->CountNode() << endl;








  /*
  for (int i = 0; i < studentVector->size(); i++) {
    cout << (*studentVector)[i].getFname() << " " << (*studentVector)[i].getLname() << endl;
    cout << "Chats:" << endl;
    for(int j = 0; j<(*studentVector)[i].getChats().size();j++){
		cout << (*studentVector)[i].getChats()[j].GetTimeStamp() << " " 
			<< (*studentVector)[i].getChats()[j].GetMessage() << endl;
    }
    cout << "\n\n" << endl;
  }*/

  if(isEarlierTime((*studentVector)[1].getChats()[1].GetTimeStamp(),
  (*studentVector)[0].getChats()[0].GetTimeStamp())){
 	cout << "This is earlier" << endl; 
  }else{
  	cout << "This is not earlier" << endl;
  }

  return 0;
}

