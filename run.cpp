/*
Analysis of Algorithms - CIT3003
Group Project
Description : Creating an program to evaluate student engagement in online class chats and assign a participation grade
Authors:
 Lascelle McKenzie - 2104113
 Mellicia Rowe - 2101716
 Jhimani Henry - 1701021
 Ramon Johnston - 2008317
 * */


//standard-defined files
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <cstring>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>


//remove the use of std:: and std::chrono:: on defined functions
using namespace std;
using namespace std::chrono;

//Chat class
class Chat {
	//Private Attributes
	private:
  		string message;
  		string timestamp;
	//public methods	
	public:
  		Chat() {} //default constructor
	
		//primary constructor
  		Chat(string timestamp, string message) {
    			this->timestamp = timestamp;
    			this->message = message;
  		}	

		//Accessors and Mutators
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

//Student class
class Student {
	private: //Private Attributes
  		string fname;
  		string lname;
  		float participation;
  		vector<Chat> chat;
	//public methods
	public:
  		Student() {} //default constructor
		//primary constructor
  		Student(string Fname, string Lname, float Participation){
    			this->fname = Fname;
    			this->lname = Lname;
    			this->participation = Participation;
  		}	
		
		//accessors and mutators
  		string getFname() const{
		       	return fname; 
		}

  		void setFname(string Fname) {
		       	this->fname = Fname; 
		}

  		string getLname() const{
		       	return lname; 
		}

  		void setLname(string Lname) {
		       	this->lname = Lname; 
		}

  		float getParticipation() const{
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

//Answer Class
class Answer {
	//Private Attributes
	private:
  		string timestamp;
  		string ans;
	//Public Methods
	public:
  		Answer() {} //default constructor

		//Primary Constructor
  		Answer(string Answer, string timestamp) {
   	 		this->ans = Answer;
    			this->timestamp = timestamp;
  		}

		//Accessors and Mutators
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

//Creating a Node to Store Answers to put in doubly linked list
class AnswerNode {
	//Private Attributes
	private:
  		Answer data;
  		AnswerNode *nextNode, *previousNode; // AnswerNode *nextNode and previousNode to link nodes

	//Public Methods
	public:
  		AnswerNode() {
    			data = Answer();
    			nextNode = NULL;
			previousNode = NULL;
  		}	
		//Primary Constructor
  		AnswerNode(Answer data) {
    			this->data = data;
    			this->nextNode = NULL;
			this->previousNode = NULL;
 	 	} 

		//Accessors and Mutators
  		Answer getData() { return data; }

  		void setData(Answer data) { this->data = data; }

  		AnswerNode *getNextNode() { return nextNode; }

  		void setNextNode(AnswerNode *nextNode) { this->nextNode = nextNode; }	
		
		AnswerNode *getPreviousNode(){return previousNode;}
		
		void setPreviousNode(AnswerNode *previousnode){previousNode = previousnode;}
};

//Doubly linked list for storing nodes
class AnswerLinkedList {
	private:
		AnswerNode *Head, *Tail;
	public:
		//Methods
		//Default constructor
		AnswerLinkedList(){
			Head = NULL;
			Tail = NULL;
		}
		//Primary constructor
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
			AnswerNode *temp = new AnswerNode(dataToInsert); //Store node in a temp node 
			if(temp!=NULL){  //Check if nothing is in the node
				if(IsEmpty()){ //If the list is empty
					Head = temp;
					Tail = temp;
				}else{ //If the list is not empty
					temp->setNextNode(Head);
					Head->setPreviousNode(temp);
					Head = temp;
				}	
			}
		}
			
		//Insert at back
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
	
		//Count the amount of nodes in the list currently
		int CountNodes() const{
			AnswerNode *temp = new AnswerNode; //Create a new node
			int count=0;
			temp = Head;
			while(temp!=NULL){
				count++;
				temp = temp->getNextNode();
			}
			return count;
		}
		
		//Check it the list is empty
		bool IsEmpty(){
			if(Head==NULL)return true;
			else return false;
		}
};



class MyApp : public wxApp{
	public:
    		virtual bool OnInit();
};

class MyFrame : public wxFrame{
	public:
    		MyFrame();

	private:
    		enum{
        		ID_OpenChatFile = wxID_HIGHEST + 1,
        		ID_OpenAnswerFile,
        		ID_Generate,
    		};

    		void OnOpenChatFile(wxCommandEvent& event);
    		void OnOpenAnswerFile(wxCommandEvent& event);
    		void OnGenerate(wxCommandEvent& event);
		void ProcessFiles();	
		void readChatFile(vector<Student> &studentVector, wxString chatFilePath);
    		void readAnswerFile(AnswerLinkedList &answerList, wxString answerFilePath);
		bool isEarlierTime(const string&, const string&); 
		vector<string> Tokenizer(const string&);
		void analyzeChats(const AnswerLinkedList& answerList, vector<Student>& studentVector);
		void GenerateParticipationFile(vector<Student>& studentVector);

		wxString chatFilePath;
    		wxString answerFilePath;
		vector<Student> *studentVector = new vector<Student>(); ///Declare a vector pointer of Students
  		AnswerLinkedList *answerList = new AnswerLinkedList(); 

    		wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(ID_OpenChatFile, MyFrame::OnOpenChatFile)
    EVT_BUTTON(ID_OpenAnswerFile, MyFrame::OnOpenAnswerFile)
    EVT_BUTTON(ID_Generate, MyFrame::OnGenerate)
wxEND_EVENT_TABLE()

bool MyApp::OnInit(){
    	MyFrame *frame = new MyFrame();
    	frame->Show(true);
    	return true;
}

MyFrame::MyFrame(): wxFrame(nullptr, wxID_ANY, "Chat Analyzer", wxDefaultPosition, wxSize(400, 300)){
    	wxPanel *panel = new wxPanel(this, wxID_ANY);

    	wxButton *openChatButton = new wxButton(panel, ID_OpenChatFile, "Open Chat File", wxPoint(10, 10), wxDefaultSize);
    	wxButton *openAnswerButton = new wxButton(panel, ID_OpenAnswerFile, "Open Answer File", wxPoint(10, 50), wxDefaultSize);
    	wxButton *generateButton = new wxButton(panel, ID_Generate, "Generate", wxPoint(10, 90), wxDefaultSize);
}

void MyFrame::OnOpenChatFile(wxCommandEvent& event){
    	wxFileDialog openFileDialog(this, _("Open Chat File"), "", "",
                                "Text files (*.txt)|*.txt|All files (*.*)|*.*",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    	if (openFileDialog.ShowModal() == wxID_CANCEL){
       	 	return;
    	}

    	chatFilePath = openFileDialog.GetPath();
    	wxMessageBox("Selected chat file: " + chatFilePath, "File Selected", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnOpenAnswerFile(wxCommandEvent& event){
    	wxFileDialog openFileDialog(this, _("Open Answer File"), "", "",
                                "Text files (*.txt)|*.txt|All files (*.*)|*.*",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    	if (openFileDialog.ShowModal() == wxID_CANCEL){
        	return;
    	}

    	answerFilePath = openFileDialog.GetPath();
    	wxMessageBox("Selected answer file: " + answerFilePath, "File Selected", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnGenerate(wxCommandEvent& event){
	if (!chatFilePath.empty() && !answerFilePath.empty()) {
        	ProcessFiles();
    	} else {
        	wxMessageBox("Please open both chat and answer files before generating.", "Error", wxOK | wxICON_ERROR);
    	}
}

void MyFrame::ProcessFiles() {
    	wxMessageBox("Processing files...", "Information", wxOK | wxICON_INFORMATION);
	readChatFile(*studentVector, chatFilePath);
	readAnswerFile(*answerList, answerFilePath);
	analyzeChats(*answerList,*studentVector);
	
	
	GenerateParticipationFile(*studentVector);
    	wxMessageBox("Participation File Generated", "Information", wxOK | wxICON_INFORMATION);
}



void MyFrame::GenerateParticipationFile(vector<Student>& studentVector){

	try {
    		// Open the file for writing
    		std::ofstream outputFile("StudentsParticipation.txt");

    		// Check if the file is opened successfully
    		if (!outputFile.is_open()) {
        		throw std::runtime_error("Error opening file");
    		}

    		// Write each item in the vector to the file
    		for (const auto& student : studentVector) {
        		outputFile << student.getFname() << " " << student.getLname()
			       	<< " " << student.getParticipation() << "%" << "\n";
    		}

    		// Close the file
    		outputFile.close();
	} catch (const std::exception& e) {
    		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void MyFrame::readChatFile(vector<Student> &studentVector, wxString chatFilePath) {
  	ifstream inputFile;  // Create a file stream
	inputFile.open(chatFilePath);  // Open file
	try {
    		if (!inputFile.is_open()) {
        		throw std::runtime_error("Failed to open the input file.");
    		}else {
        		regex pattern(R"((\d{2}:\d{2}:\d{2}) From (\w+ \w+): (.+))"); // Create a pattern
        		smatch match;
        		string line;

        		while (getline(inputFile, line)) {
            			try {
                			// Try to match the regular expression
                			if (std::regex_match(line, match, pattern)) {
                    				Chat chat;
                    				Student student;

                    				// Store based on how the scan splits the string
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

                    				for (int i = 0; i < studentVector.size(); i++) {
                        				if (student.getFname() == studentVector[i].getFname() &&
                            					student.getLname() == studentVector[i].getLname()) {
                            					found = true;
                            					studentVector[i].setChat(chat);
                        				}
                    				}

                    				if (!found) {
                        				studentVector.push_back(student);
                    				}
                			}
            			} catch (const std::exception& e) {
                			// Handle regex matching exception
                			cerr << "Regex matching exception: " << e.what() << endl;
                			// You may choose to continue processing or return from the function
            			}
        		}
        		inputFile.close();
    			}		
	} catch (const std::exception& e) {
    		// Handle file opening exception
    		cerr << "File opening exception: " << e.what() << endl;
    		// You may choose to continue processing or return from the function
	}
}

void MyFrame::readAnswerFile(AnswerLinkedList &answerList, wxString answerFilePath){
	
	ifstream inputFile;
	inputFile.open(answerFilePath);

	try {
    		if (!inputFile.is_open()) {
        		throw std::runtime_error("Failed to open the input file.");
    		} else {
        		regex pattern(R"((\d{2}:\d{2}:\d{2})\s(.+))");
        		smatch match;
        		string line;

        		while (getline(inputFile, line)) {
            			try {
                			if (std::regex_match(line, match, pattern)) {
                    				Answer answer;
                    				answer.setTimestamp(match[1]);
                    				answer.setAnswer(match[2]);

                    				if (answerList.IsEmpty()) {
                        				answerList.InsertAtFront(answer);
                    				} else {
                        				answerList.InsertAtBack(answer);
                    				}
                			}
            			} catch (const std::exception& e) {
                			// Handle regex matching exception
                			cerr << "Regex matching exception: " << e.what() << endl;
                			// You may choose to continue processing or return from the function
            			}
        		}

        		inputFile.close();
    		}
	} catch (const std::exception& e) {
    		// Handle file opening exception
    		cerr << "File opening exception: " << e.what() << endl;
    		// You may choose to continue processing or return from the function
	}
}

// Function to check if time1 is earlier than time2
bool MyFrame::isEarlierTime(const string& time1, const string& time2) {
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

vector<string> MyFrame::Tokenizer(const string& input) {
	regex wordPattern("\\b(\\w+)\\b"); //create a pattern to remove non word characters
    	sregex_token_iterator iter(input.begin(), input.end(), wordPattern, 1); //iterate through sentence
    	sregex_token_iterator end; //Stop search
    	vector<std::string> result(iter, end); //Store each token into vector  
    	return result; //return vector
}

void MyFrame::analyzeChats(const AnswerLinkedList& answerList, vector<Student>& studentVector){
	
	float answerCount = answerList.CountNodes() * 2; //stored the answer count which will be used as the denominator in the
							 //calculations of the user participation grade

	//Runs all student
	for (int i = 0; i < studentVector.size(); i++) {
		float matchCount = 0; //Declare match count as int and set it to 0
		float participation  = 0.0;  //declare participation as float and set it to 0.0
      		cout << studentVector[i].getFname() << " " << studentVector[i].getLname() << endl; //This shows the current student
												   //being analyzed
		//Runs all chat for that student
      		for(int j = 0; j<studentVector[i].getChats().size();j++){	
			//compare the time stamp of a answer with the students response
			AnswerNode* traverse = answerList.GetHead(); //gets the first answer in the linked list
			while(traverse != NULL){ //while the node is not empty
				//This if statement is used to check if the user/student chat timestamp 
				//is later than the answer timestamp and also eariler than the next answer timestamp
				//to ensure the chat is within the range in which the question was asked
				//and it also check to see if the next node would be null
				if(traverse->getNextNode() != NULL && 
						isEarlierTime(traverse->getData().getTimestamp(),
						studentVector[i].getChats()[j].GetTimeStamp()) &&
			       			isEarlierTime(studentVector[i].getChats()[j].GetTimeStamp(),
						traverse->getNextNode()->getData().getTimestamp())){	
					//Store tokenized strings into vectors
					vector<string> answerVector = Tokenizer(traverse->getData().getAnswer()); 
					vector<string> chatVector =  Tokenizer(studentVector[i].getChats()[j].GetMessage());	
    					
					//Sort the strings for the chat in ascending order by lenght of the string	
					std::sort(chatVector.begin(), chatVector.end(), 
						[](const std::string& a, const std::string& b) {
        						return a.length() < b.length();
    					});

					//Outputs the message of the student and the answer for the given question
					cout <<"Student Message: " <<  studentVector[i].getChats()[j].GetMessage() << endl;	
					cout << "Answer : " << traverse->getData().getAnswer()<< endl;	
    					
					//Scans through the string vector of the answer
					for (const auto& answer : answerVector) {
						//Implenting binary search
    						int low = 0; //declare low as 0
    						int high = chatVector.size() - 1; //declare high as -1 of the size of the chat vector

						//while loop to keep track of the search
    						while (low <= high) {
							//initaialize mid
        						int mid = low + (high - low) / 2;

							//if the chat lenght and the answer lenght is the same then
        						if (chatVector[mid].length() == answer.length()) {
            							// Check for exact string match when lengths are equal
            							if (strcasecmp(answer.c_str(), chatVector[mid].c_str()) == 0) {
                							cout << "FOUND MATCH" << endl;
                							cout << chatVector[mid] << endl;
									matchCount++;
                							break;  // Break out of the loop once a match is found
            							} else {
                						// Adjust the search range based on the comparison result
                							if (strcasecmp(answer.c_str(), chatVector[mid].c_str()) < 0) {
                    								high = mid - 1;  // Search in the left half
                							} else {
                    								low = mid + 1;   // Search in the right half
                							}
            							}
        						} else if (chatVector[mid].length() < answer.length()) {
            							low = mid + 1;  // Search in the right half
        						} else {
            							high = mid - 1;  // Search in the left half
        						}
    						}
					}
					cout << "\n" << endl;				
				}
				traverse = traverse->getNextNode(); //Go to the next answer in the list
			}		
		}	
			//Calculate participation grade
			participation = (static_cast<float>(matchCount) / answerCount) * 100;
			//Set participation grade for that student
			studentVector[i].setParticipation(participation);
			//Output user data
			cout << studentVector[i].getFname() << " "  << studentVector[i].getLname()<< endl;
			cout << studentVector[i].getParticipation() << endl;
    			cout << "\n" << endl;
  	}
}

wxIMPLEMENT_APP(MyApp);
