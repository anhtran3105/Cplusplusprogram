#include <iostream>
#include <jni.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Animal { //class animal here, i will be doing a vector of class.
   public:
      void SetupAnimal(string animal_data) {
			track_number = animal_data.substr(0,6);
//			cout << animal_data << endl;
			animal_name = animal_data.substr(6,15);
			animal_type = animal_data.substr(21, 15);
			animal_subtype = animal_data.substr(36, 15);
			eggs = stoi(animal_data.substr(51,1));
			nurse = stoi(animal_data.substr(53, 1));
      }

      string GetTrack() { return track_number; }
      string GetName() { return animal_name; }
      string GetType() { return animal_type; }
      string GetSubtype() { return animal_subtype; }
      int GetEggs() { return eggs ; }
      int GetNurse() { return nurse ; }

   private:
      string track_number, animal_name, animal_type, animal_subtype;
      int eggs, nurse;
};

vector<Animal> animalList;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void AddAnimal()
{
     /*
            TODO: Write proper code to add an animal to your vector (or array)
     */
	Animal currAnimal;
	string userInput,userInput2, userRes;
	userRes = "";
	userInput = "";

	cout << "Track number: " << endl;
	getline(cin, userInput);
    for (int i = userInput.length(); i < 6; i++) {
        userInput = "0" + userInput;
    }
    userRes = userRes + userInput;

    cout << "Enter Animal Name: " << endl;
    getline(cin, userInput);
    for (int i = userInput.length(); i < 15; i++) {
        userInput = userInput + " ";
    }
    userRes = userRes + userInput;

    cout << "Enter Animal Type: " << endl;
    getline(cin, userInput);
    for (int i = userInput.length(); i < 15; i++) {
        userInput = userInput + " ";
    }
    userRes = userRes + userInput;

    cout << "Enter Animal Subtype: " << endl;
   	getline(cin, userInput);
    for (int i = userInput.length(); i < 15; i++) {
        userInput = userInput + " ";
    }
    userRes = userRes + userInput;

    cout << "Enter Number of Eggs: " << endl;
    getline(cin, userInput);
    for (int i = userInput.length(); i < 2; i++) {
        userInput = userInput + " ";
    }
    userRes = userRes + userInput;

    cout << "Enter 1 if Nursing, 0 if not: " << endl;
    getline(cin, userInput);
    userRes = userRes + userInput;


    currAnimal.SetupAnimal(userRes);
    animalList.push_back(currAnimal);
}

void RemoveAnimal()
{
     /*
            TODO: Write proper code to remove an animal from your vector (or array. Remmber to re-allocate proper size if using array)
     */
	string userInput;
	cout << "Track number: " << endl;
	getline(cin, userInput);
    for (int i = userInput.length(); i < 6; i++) {
        userInput = "0" + userInput;
    }
    int j;
    for (j = 0; j < animalList.size();j++) {
    	if (animalList.at(j).GetTrack() == userInput) {
//    		animalList.erase(j); // can't user this function for some reason.
    		cout << "Position " << j << endl;
    		break;
    	}
    }
    //this is basically to remove the specific element of vector since the erase function is not working.
    vector<Animal> temp_AnimalList;
    int i = 0;
    while (i < animalList.size()) {
    	if (i != j) {
    		temp_AnimalList.push_back(animalList.at(i));
    	}
    	i++;
    }
    animalList = temp_AnimalList; // re-assign the main list.
}

void LoadDataFromFile()
{
     /*
            TODO: Write proper code to load data from input file (generated using JNI) into vector/array.
     */
	string data;
	ifstream myfile;
	int i = 0;
	vector<Animal> temporary_animalList;
	Animal currAnimal;
	myfile.open ("zoodata.txt");
	getline(myfile, data);
	while (data.length() != 0) {
		i++;
//		cout << data << endl;
		currAnimal.SetupAnimal(data);
		temporary_animalList.push_back(currAnimal);
		getline(myfile, data);
	}
	myfile.close();
	animalList = temporary_animalList;


}

void DisplayAnimalData() {
	//print out the data in column
	cout << "Track#         Name           Type           Sub-type       Eggs      Nursing   " << endl;

	for (int i = 0; i < animalList.size(); i++) {
		cout << animalList.at(i).GetTrack() << "         ";
		cout << animalList.at(i).GetName();
		cout << animalList.at(i).GetType();
		cout << animalList.at(i).GetSubtype();
		cout << animalList.at(i).GetEggs() << "         ";
		cout << animalList.at(i).GetNurse() << endl;
	}

}

void SaveDataToFile() //to write file in the same format as I read it.
{
     /*
            TODO: Write proper code to store vector/array to file.
     */
	  ofstream myfile;
	  myfile.open ("zoodata.txt");

	  for (int i = 0; i < animalList.size(); i++) {
		  myfile << animalList.at(i).GetTrack();
		  myfile << animalList.at(i).GetName();
		  myfile << animalList.at(i).GetType();
		  myfile << animalList.at(i).GetSubtype();
		  myfile << animalList.at(i).GetEggs() << " ";
		  myfile << animalList.at(i).GetNurse() << "\n";
	  }
	  myfile.close();
}

void DisplayMenu()
{
     /*
            TODO: write proper code to display menu to user to select from
     */

//	A user menu which displays the following options:
	cout << "Welcome to the Zoo program!!! Please select one of the following option " << endl;
	cout << "1: Load Animal Data" << endl;
	cout << "2: Generate Data" <<endl;
	cout << "3: Display Animal Data" <<endl;
	cout << "4: Add Record" << endl;
	cout << "5: Delete Record" << endl;
	cout << "6. Save Animal Data" << endl;
	cout << "7.Show menu again" << endl;
	cout << "8. Exit the program" << endl;

}




int main()
{
//
//	GenerateData();
//	LoadDataFromFile();
//	cout << animalList.size() << endl;
//	RemoveAnimal();
//	cout << animalList.size() << endl;
//	cout << animalList.at(0).GetTrack() << endl;
//	cout << animalList.at(2).GetTrack() << endl;
//	AddAnimal();
//	cout << animalList.at(1).GetTrack() << endl;
//	SaveDataToFile();

	string userAns; // this is for every user input.
	DisplayMenu();

	while (userAns != "8") {
		getline(cin, userAns);
		if (userAns == "1") { //load data from zoodata.txt
			LoadDataFromFile();
			cout << "Your data has been loaded, please select option 3 to show your data"<< endl;
			cout << "Press 7 to see menu again" <<endl;
		} else if (userAns == "2") { //generate new data
			GenerateData();
			cout << "After generating data, make sure you load it then display data"<< endl;
			cout << "Press 7 to see menu again" <<endl;
		} else if (userAns == "3") { //display data by column
			DisplayAnimalData();
		} else if (userAns == "4") { // add animal to the vector list.
			AddAnimal();
			cout << "Make sure you save your data. Load it then display to see full data" << endl;
			cout << "Press 7 to see menu again" <<endl;
		} else if (userAns == "5") { //remove an animal by track number
			RemoveAnimal();
			cout << "Make sure you save your data. Load it then display to see full data" << endl;
			cout << "Press 7 to see menu again" <<endl;
		} else if (userAns == "6") { //write new data to zoodata.txt
			SaveDataToFile();
		} else if (userAns == "7") { //dsplay menu again
			DisplayMenu();
		} else if (userAns == "8") { //exit the program
			break;
		} else {
			cout << "please enter a valid input" << endl;
			getline(cin, userAns);
		}
	}

	// just prompt user that the program is done
	cout << "Program exit. Thank you for using our program." << endl;
	return 1;
}
