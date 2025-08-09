#include <iostream>//basic IO
#include <cmath>//for mathemical functions
#include <iomanip>
#include <fstream>//file handling
#include <string>//string handling and getline
#include <filesystem>//to create folders
#include <cstdio>//for remove/delete function to delete the file from directory 

using namespace std;
namespace fs = std::filesystem;

//FUNCTION PROTOYPES 
int start();
int CreatingProfile();
bool login();
void DeleteProfile();
void ViewProfile();
bool UpdateProfile();
bool Exit();
int choices(int choice);
bool ConfirmDelete(const string& Name);
bool verify(const string& username, const string& pass);
void LowerCase(string& str);
bool ValidPassword(const string& password);
bool ValidPhoneNumber(const string& phoneNumber);
bool CheckUsername(const string& Name);
bool ValidCnic(const string& CNIC);
bool isEmpty(const string& data);
void removeSpaceFromUsername(string& UserName);
int backup(const string& name);
int SaveData(const string& Name, const string data);

int TotalEnergyConsumption();
void inverter(double& invertercost, double& invertercapacity, double& reqpower);
double battery(double& reqpower);
double wiring();
int panelsrequired();
void savings();
void tips();

//making totalconsumption variable global
double totalconsumption = 0.0;

string name, username, pass, password;//global variables of login or signup username and password 

//int main()
//{
//	start();
//}


//starting point aka main menu function
int start()
{
	cout << "=========================================" << endl;
	cout << "||                                     ||" << endl;
	cout << "||              MAIN MENU              ||" << endl;
	cout << "||                                     ||" << endl;
	cout << "=========================================" << endl;
	cout << "Option 1: Create New Profile" << endl;
	cout << "Option 2: View All Profiles" << endl;
	//cout << "Option 3: Update Profile" << endl;
	cout << "Option 3: Delete Profile" << endl;
	cout << "Option 4: Calculate Energy Consumption & Required Panels" << endl;
	cout << "Option 5: Exit" << endl;
	cout << "\n------------------------------------------" << endl << endl;

	int choice;
	do
	{
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore(9999, '\n');
		cin.clear(); //clears the new line buffer entered by cin
		if (cin.fail() || choice > 5 || choice < 1)
		{
			cin.clear();
			cin.ignore(999999, '\n');
			cout << "Invalid input" << endl;
		}
	} while (cin.fail() || choice > 5 || choice < 1);

	if (choices(choice) == 1)
		start();//starts application again
	else
		return 0;
}


//functions handling choices of main menu
int choices(int choice)
{
	if (choice == 1)
	{
		CreatingProfile();
		return 1;
	}
	else if (choice == 2)
	{
		ViewProfile();
		return 1;
	}
	//else if (choice == 3)
	//{
	//	UpdateProfile();
	//	return 1;
	//}
	else if (choice == 3)
	{
		DeleteProfile();
		return 1;
	}
	else if (choice == 4)
	{
		TotalEnergyConsumption();
	}
	else if (choice == 5)

	{
		if (Exit)
			return 0;
		else
			return 1;
	}
}


//function for creating new profile and adding information
int CreatingProfile()
{
	if (!fs::exists("User_Profiles"))
		fs::create_directory("User_Profiles");
	if (!fs::exists("Backup_Profiles"))
		fs::create_directory("Backup_Profiles");
	string  number, email, address, cnic;

	cout << "\n------------------------------------------" << endl << endl;
	cout << ">>>>>>>> LETS CREATE YOUR PROFILE <<<<<<<" << endl << endl;

	do
	{
		cout << "Enter username: ";
		getline(cin, username);
		removeSpaceFromUsername(username);
		LowerCase(username);
	} while (CheckUsername(username) || isEmpty(username));

	do
	{
		cout << "Enter email account: ";
		getline(cin, email);
	} while (isEmpty(email));

	do
	{
		cout << "Enter telephone or cellphone number: ";
		getline(cin, number);
	} while (isEmpty(number) || !ValidPhoneNumber(number));

	do
	{
		cout << "Enter CNIC: ";
		getline(cin, cnic);
	} while (isEmpty(cnic) || !ValidCnic(cnic));

	do
	{
		cout << "Enter address: ";
		getline(cin, address);
	} while (isEmpty(address));

	do
	{
		cout << "Enter your password: ";
		getline(cin, password);
	} while (isEmpty(password) || !ValidPassword(password));

	string a = "-----------PERSONAL DATA-----------\n\n";
	string data = a + "Username: " + username + "\nPassword: " + password + "\nCNIC: " + cnic + "\nEmail: " + email + "\nContact Number: " + number + "\nAddress: " + address;

	if (SaveData(username, data) != 0)
	{
		cout << "\nAN ERROR OCCURED! TRY AGAIN!" << endl;
		CreatingProfile();
	}
	cout << "\n\nYour profile has been created successfully" << endl << endl << endl;
	return 0;
}


//checks if string is empty 
bool isEmpty(const string& data)
{
	if (data.empty())
	{
		cout << "\n------------------------------------------" << endl << endl;
		cout << "String can not be empty!" << endl;
		return true;
	}

	return false;
}


//removes spaces from username
void removeSpaceFromUsername(string& UserName)
{
	int index = 0;
	for (int i = 0; UserName[i] != '\0'; i++)
		if (UserName[i] != ' ')
			UserName[index++] = UserName[i];

	UserName[index] = '\0';
}

//converts string to lowercase
void LowerCase(string& str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
}


//function to check if username already exists while creating new profile
bool CheckUsername(const string& Name)
{
	string filepath = "User_Profiles/" + Name + ".txt";
	if (fs::exists(filepath))//checks if the file of username exists
	{
		cout << "\n------------------------------------------" << endl << endl;
		cout << "Username Already exists! Try Another Username!" << endl;
		return true;
	}
	return false;
}

//function to validate if number has only digits and their count is 11
bool ValidPhoneNumber(const string& phoneNumber)
{
	int Count = 0;
	for (int i = 0; phoneNumber[i] != '\0'; ++i)
		if (phoneNumber[i] >= '0' && phoneNumber[i] <= '9')
			Count++;
		else
		{
			cout << "\n------------------------------------------" << endl << endl;
			cout << "Enter a valid phone number" << endl;
			return false;
		}

	if (Count == 11)
		return true;
	else
	{
		cout << "\n------------------------------------------" << endl << endl;
		cout << "Enter a valid phone number" << endl;
		return false;
	}
}


//function to validate cnic
bool ValidCnic(const string& CNIC)
{
	int Count = 0;
	for (int i = 0; CNIC[i] != '\0'; ++i)
		if (CNIC[i] >= '0' && CNIC[i] <= '9')
			Count++;
		else
		{
			cout << "\n------------------------------------------" << endl << endl;
			cout << "Enter a valid CNIC number" << endl;
			return false;
		}

	if (Count == 13)
		return true;
	else
	{
		cout << "\n------------------------------------------" << endl << endl;
		cout << "Enter a valid CNIC number" << endl;
		return false;
	}
}


// Function to validate the password and check its strength
bool ValidPassword(const string& password)
{
	bool hasLetter = false, hasDigit = false, hasSpecialChar = false;
	bool hasUpperCase = false, hasLowerCase = false;
	int length = 0;


	for (int i = 0; password[i] != '\0'; ++i)
	{
		length++;

		// Check for uppercase letter
		if (password[i] >= 'A' && password[i] <= 'Z')
			hasUpperCase = true;


		// Check for lowercase letter
		if (password[i] >= 'a' && password[i] <= 'z')
			hasLowerCase = true;


		// Check for digit
		if (password[i] >= '0' && password[i] <= '9')
			hasDigit = true;


		// Check for special character
		if ((password[i] >= '!' && password[i] <= '/') || (password[i] >= ':' && password[i] <= '@') ||
			(password[i] >= '[' && password[i] <= '`') || (password[i] >= '{' && password[i] <= '~'))
			hasSpecialChar = true;

	}

	// If the password length is less than 8, it's invalid
	if (length < 8)
	{
		cout << "Password should be at least 8 characters long.\n";
		return false;
	}

	if (!hasUpperCase || !hasLowerCase || !hasDigit || !hasSpecialChar)
	{
		cout << "Password must contain at least one uppercase letter, one lowercase letter, one digit, and one special character.\n";
		return false;
	}

	// determines password strength
	if (length > 15)
		cout << "Password strength: Strong\n";
	else if (length >= 10 && length < 15)
		cout << "Password strength: Moderate\n";
	else if (length >= 8 && length < 10)
		cout << "Password strength: Weak\n";

	return true;
}


//function for login 
bool login()
{
	int count = 0;
	char choice;
	cout << "\n------------------------------------------" << endl << endl;
	cout << ">>>>>>>>>>>>>>>>> LOGIN <<<<<<<<<<<<<<<<<<" << endl;
	do
	{
		do
		{
			cout << "Enter username: ";
			getline(cin, name);
		} while (isEmpty(name));

		do
		{
			cout << "Enter password: ";
			getline(cin, pass);
		} while (isEmpty(pass));

		removeSpaceFromUsername(name);
		LowerCase(name);
		++count;
		if (count == 3)
		{
			cout << "\n\nToo many failed login attempts! Make sure you already have an account registered.Taking you back to the menu";
			cout << "\n------------------------------------------" << endl << endl;
			return false;
		}
	} while (!verify(name, pass));
	cout << "\n------------------------------------------" << endl << endl;
	cout << "LOGIN SUCCESSFUL" << endl;
	return true;
}


///function to verify if username and password are correct while login
bool verify(const string& name, const string& pass)
{
	string line;
	string filepath = "User_Profiles/" + name + ".txt";
	if (!fs::exists(filepath))//checks if the file of username exists

	{
		cout << "Username Does Not Exists" << endl;
		return false;
	}

	ifstream file(filepath);
	while (getline(file, line))
	{
		// initialize i = 10  skip the first "Password: " part (10 characters)
		int i = 10;

		// Start extracting password from the file after the "Password: " part
		string storedPass;
		while (i < line.length() && line[i] != '\n')
		{
			storedPass += line[i];
			i++;
		}

		if (storedPass == pass)
		{
			file.close();
			return true; // Password matches
		}
	}
}


//function to view user profile 
void ViewProfile()
{
	if (login())
	{
		string data;
		char choice;
		string filepath = "User_Profiles/" + name + ".txt";
		ifstream file(filepath);

		if (!file)
			cout << "error opening file" << endl;

		cout << "------------------------------------------" << endl << endl;
		cout << ">>>>>>>>> VIEWING PROFILE DATA <<<<<<<<<" << endl << endl;
		while (getline(file, data))//reading data from user file and printing it 
			cout << data << endl;
		file.close();
		cout << "\n------------------------------------------" << endl << endl;
		return;
	}
	else
		return;
}


//function to update user profile
bool UpdateProfile()
{
	ViewProfile();
	int choice;
	cout << "------------------------------------------" << endl << endl;
	cout << ">>>>>>>>> UPDATE PROFILE DATA <<<<<<<<<" << endl << endl;
	cout << "What do you want to update? " << endl;
	return 0;
}


//function that deletes user profile
void DeleteProfile()
{
	if (login())
	{
		cout << "------------------------------------------" << endl << endl;
		cout << ">>>>>>>>>> DELETE PROFILE DATA <<<<<<<<<<" << endl << endl;

		if ((ConfirmDelete(name))) //confirming to delete
		{
			string filepath = "User_Profiles/" + name + ".txt";
			if (fs::exists(filepath))
			{
				if (remove(filepath.c_str()) == 0)
				{
					cout << "PROFILE DELETED SUCCESSFULLY!" << endl;
					return;
				}
				else
				{
					cout << "ERROR DELETING FILE.IT MIGHT NOT EXIST OR MIGHT BE CORRUPTED" << endl;
					return;
				}
			}
			else
				cout << "\nFILE NOT FOUND" << endl;

		}
		else
			return;
	}
	else
		return;
}


//function that confirms if the user wants to delete his profile
bool ConfirmDelete(const string& Name)
{
	char arr[81] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
					'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '=', '<', '>', '?', '/', '|' };

	cout << "\n------------------------------------------" << endl << endl;
	cout << "Enter Following Captcha to delete your profile: ";
	string input;
	for (int attempts = 0; attempts < 3; ++attempts)
	{
		string captcha = "";
		for (int i = 0; i < 6; i++)
			captcha += arr[rand() % 81];
		cout << captcha << endl;
		getline(cin, input);
		if (input == captcha)
		{
			cout << "CAPTCHA successful.\n";
			return true;
		}

		cout << "CAPTCHA verification failed. Please try again.\n";
	}

	cout << "Too many failed attempts. Returning to the main menu.\n";
	return false;
}



//function that creates a backup of user profile
int backup(const string& name)
{
	string data;
	//reading from user file 
	ifstream file1("User_Profiles/" + name + ".txt");
	if (!file1)
	{
		cout << "error opening file" << endl;
		return 1;
	}
	ofstream file2("Backup_Profiles/" + name + "_backup.txt", ios::app);
	if (!file2)
	{
		cout << "error opening file" << endl;
		return 1;
	}
	while (getline(file1, data))//gets input line by line 
		//copying user data into backup file
		file2 << data << endl;
	file2.close();
	file1.close();
	return 0;
}


//a single function that does all the file handling
//it stores all the data of every user in a file with their respective username
int SaveData(const string& name, const string data)
{
	//create a file with the name of user ;
	ofstream file("User_Profiles/" + name + ".txt", ios::app);
	if (!file)
	{
		cout << "error opening file" << endl;
		return 1;
	}
	//writing into the file
	file << data << endl;
	file.close();
	backup(name);
	return 0;
}

bool Exit()
{
	int select;
	cout << "ARE YOU SURE YOU WANT TO EXIT" << endl;
	cout << "---> Enter '1' for yes " << endl;
	cout << "---> Enter '2' for no " << endl;
	do
	{
		cin >> select;
		cin.ignore(1000, '\n');//clears the new line buffer entered by cin
		if (select != 1 && select != 2)
			cout << "INVALID INPUT! ENTER AGAIN" << endl;
	} while (select != 1 && select != 2);

	if (select == 1)
		return true;
	else
		return false;
}

// contains calculations for inverter, called in panelsrequired function
void inverter(double& inverterprice, double& invertercapacity, double& reqpower)
{
	char companychoice, inverterchoice;
	string companyname[4] = { "Tesla", "Inverex", "Fronus", "Solis" }, invertertype;
	double addcharges[4] = { 1.2, 1.15, 1.1, 1.05 }; //brand charges
	double price[4] = { 0 };
	long baseprice = 0;

	cout << "\n\************************************************************\n";
	cout << "***********   WELCOME TO SOLAR PANEL ESTIMATOR   ***********\n";
	cout << "************************************************************\n\n";

	invertercapacity = static_cast<long>(reqpower + 1);
	cout << "Based on energy consumption, the capacity of inverter is: " << invertercapacity;


	cout << "\n>>>>>>>>>>>>>>>>>>> INVERTER TYPE <<<<<<<<<<<<<<<<<<<<\n\n";
	cout << "Select an inverter type:\n\n";
	cout << "1. Offgrid (Base Price: 35000 PKR)\n";
	cout << "2. Ongrid  (Base Price: 42500 PKR)\n";
	cout << "3. Hybrid  (Base Price: 52500 PKR)\n\n";

	do {
		cout << "Enter choice (1-3): ";
		cin >> inverterchoice;

		if (cin.fail() || (inverterchoice != '1' && inverterchoice != '2' && inverterchoice != '3')) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Enter again: " << endl;
		}
	} while (cin.fail() || (inverterchoice != '1' && inverterchoice != '2' && inverterchoice != '3'));

	if (inverterchoice == '1')
	{
		baseprice = 35000;
		invertertype = "Off grid";
	}

	else if (inverterchoice == '2')
	{
		baseprice = 42500;
		invertertype = "On grid";
	}

	else
	{
		baseprice = 52500;
		invertertype = "Hybrid";
	}

	cout << "\n>>>>>>>>>>>>>>>>>>> INVERTER COMPANY <<<<<<<<<<<<<<<<<<<<\n";

	for (int i = 0; i < 4; i++)
	{
		price[i] = baseprice * invertercapacity * addcharges[i];
	}

	cout << "---------------------------------------------------------------------------" << endl;
	cout << "Options   Company Name   Inverter Type   Capacity (KW)   Price (PKR) \n";
	cout << "---------------------------------------------------------------------------" << endl;

	cout << fixed << setprecision(1);

	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ")\t   "
			<< companyname[i] << "\t   "
			<< invertertype << "\t    "
			<< invertercapacity << "\t\t  "
			<< price[i] << "\n";
	}

	do {
		cout << "\nEnter your choice (1-4): ";
		cin >> companychoice;

		if (cin.fail() || companychoice != '1' && companychoice != '2' && companychoice != '3' && companychoice != '4')
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Enter again: " << endl;
		}

	} while (cin.fail() || companychoice != '1' && companychoice != '2' && companychoice != '3' && companychoice != '4');

	inverterprice = price[companychoice - '1'];

	cout << "Price of selected inverter is: " << inverterprice << " PKR\n";

}


// contains calculations for battery, called in panelsrequired function
double battery(double& reqpower)
{
	int choice;
	string companyname[3] = { "Inverex", "Osaka", "Exide" }, batterytype;
	double addcharges[3] = { 1.3, 1.2, 1.1 };                      // brand charges w.r.t to repute and quality
	double price[4] = { 0 };
	double batterycapacity[5] = { 100, 160, 190, 220, 290 };
	double baseprice[5] = { 25000, 35000, 40000, 45000, 55000 };     //price w.r.t capacity
	double selectedcapacity, batteryvoltage = 12, batteryprice;
	long numofbattery;

	cout << "Select required capacity of battery: \n\n";
	for (int i = 0; i < 5; i++)
		cout << i + 1 << ") " << batterycapacity[i] << " AH \n";

	do {
		cout << "\nEnter your choice (1-5): ";
		cin >> choice;

		if (cin.fail() || choice < 1 || choice > 5) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Enter again: " << endl;
		}
	} while (cin.fail() || choice < 1 || choice > 5);

	//storing selected capacity
	selectedcapacity = batterycapacity[choice - 1];

	double totalcapacity = (reqpower * 1000) / batteryvoltage;       //converting req power to watts
	numofbattery = (totalcapacity / selectedcapacity) + 1;

	for (int i = 0; i < 3; i++) {
		price[i] = baseprice[choice - 1] * addcharges[i];
	}

	cout << "\n>>>>>>>>>>>>>>>>>>> BATTERY COMPANY <<<<<<<<<<<<<<<<<<<<\n";
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Options   Company Name   Capacity (Ah)   Voltage (V)   Batteries Needed   Price (PKR)\n";
	cout << "---------------------------------------------------------------------------------------" << endl;

	cout << fixed << setprecision(1);

	for (int i = 0; i < 3; i++) {
		cout << i + 1 << ")\t   "
			<< companyname[i] << "\t   "
			<< selectedcapacity << "\t  "
			<< batteryvoltage << "\t\t  "
			<< numofbattery << "\t\t  "
			<< price[i] << "\n";
	}

	do {
		cout << "\nEnter your choice (1-3): ";
		cin >> choice;

		if (cin.fail() || choice < 1 || choice > 3) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Enter again: " << endl;
		}
	} while (cin.fail() || choice < 1 || choice > 3);

	batteryprice = price[choice - 1] * numofbattery;
	cout << "Price of " << numofbattery << " batteries is: " << batteryprice << " PKR\n";

	return batteryprice;
}

// contains calculations for wiring, called in panelsrequired function
double wiring()
{
	double wirelength, wireprice, structureprice;
	string wiretype[2] = { "Copper", "Aluminium" };
	double pricepermetre[2] = { 480, 250 };
	int wirechoice;

	do {
		cout << "Enter required length of DC cable (in metres): ";
		cin >> wirelength;

		if (cin.fail() || wirelength <= 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input, enter again: \n";
		}

	} while (cin.fail() || wirelength <= 0);

	cout << "\n--------------------------------------------------------------\n";
	cout << "Options   Wire Type   Price Per Metre (pkr)   Total Price\n";
	cout << "--------------------------------------------------------------\n";

	for (int i = 0; i < 2; i++)
	{
		cout << i + 1 << ")\t   "
			<< wiretype[i] << "\t   "
			<< pricepermetre[i] << "\t\t "
			<< pricepermetre[i] * wirelength << "\n";
	}

	do {
		cout << "\nEnter your choice (1-2): ";
		cin >> wirechoice;

		if (cin.fail() || (wirechoice < 1 || wirechoice > 2))
		{
			cin.ignore();
			cin.clear(1000, '\n');
			cout << "Wrong input, enter again\n";
		}
	} while (cin.fail() || (wirechoice < 1 || wirechoice > 2));

	wireprice = pricepermetre[wirechoice - 1] * wirelength;
	cout << "Price of selected DC cable is " << wireprice << " PKR";

	return wireprice;
}

//takes input about info of all appliances 
int TotalEnergyConsumption()
{
	long numAppliances, numRooms;
	double housesize;

	cout << "========================================================= \n";
	cout << "|            Energy Consumption of Appliances           |\n";
	cout << "========================================================= \n";

	fstream file;
	file.open("consumption.txt", ios::out);

	if (!file) {
		cout << "Error opening the file!" << endl;
		return 1;
	}

	// Input house size with validation
	do {
		cout << "Enter house size (in marlas): ";
		cin >> housesize;

		if (cin.fail() || housesize <= 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a positive number for house size.\n";
		}
	} while (cin.fail() || housesize <= 0);

	// Input number of rooms with validation
	do {
		cout << "Enter number of rooms: ";
		cin >> numRooms;

		if (cin.fail() || numRooms <= 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Enter a positive integer for the number of rooms.\n";
		}
	} while (cin.fail() || numRooms <= 0);

	file << "Number of rooms: " << numRooms << endl;

	// Menu choice for whole house or selected appliances
	char choice;
	do {
		cout << "Do you want to:\n";
		cout << "1. Run the whole house on solar\n";
		cout << "2. Run selected appliances on solar\n\n";
		cout << "Enter your choice (1 or 2): ";
		cin >> choice;

		if (choice != '1' && choice != '2') {
			cout << "Invalid choice. Please enter 1 or 2.\n";
		}
	} while (choice != '1' && choice != '2');
	cout << "\n";

	// Case 1: Whole house energy consumption
	if (choice == '1') {
		double units;

		do {
			cout << "Enter your average monthly bill units (kWh): ";
			cin >> units;

			if (cin.fail() || units <= 0) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please enter a positive value for bill units.\n";
			}
		} while (cin.fail() || units <= 0);

		totalconsumption = units / 30.0;

		cout << "To run your whole house on solar:\n";
	}

	// Case 2: Selected appliances
	else if (choice == '2') {
		string appliancename[14] = { "Tube Light", "Energy Saver", "LED Bulb", "Fan", "TV",
									 "Washing Machine", "Freezer", "Refrigerator", "Computer",
									 "Water Pump", "Iron", "Microwave Oven", "Split AC", "Inverter AC" };

		double consumption[14] = { 40.0, 25.0, 7.0, 100.0, 250.0, 800.0, 350.0,
								350.0, 250.0, 700.0, 1000.0, 1200.0, 3500.0, 2000.0 };

		int appliancequantity[14] = { 0 };
		double dailyuse[14] = { 0.0 };
		char additionchoice;

		for (int i = 0; i < 14; i++) {
			do {
				cout << appliancename[i] << " (" << consumption[i] << "W):\n";
				cout << "Enter quantity (0 or greater): ";
				cin >> appliancequantity[i];

				if (cin.fail() || appliancequantity[i] < 0) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input. Please enter 0 or a positive number.\n";
				}
			} while (cin.fail() || appliancequantity[i] < 0);

			do {
				cout << "Enter average hours of usage per day: ";
				cin >> dailyuse[i];

				if (cin.fail() || dailyuse[i] < 0 || dailyuse[i] > 24) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input. Please enter 0 or a positive number for hours.\n";
				}
			} while (cin.fail() || dailyuse[i] < 0);

			totalconsumption += (consumption[i] * appliancequantity[i] * dailyuse[i]);
		}

		// Additional appliances handling
		do {
			cout << "\nDo you have any additional appliances? (1 for Yes, 0 for No): ";
			cin >> additionchoice;

			if (additionchoice == '1') {
				double additionalconsumption;
				int additionalquantity;
				double additionalusage;

				do {
					cout << "Enter the Energy Consumption of additional appliance: ";
					cin >> additionalconsumption;

					if (cin.fail() || additionalconsumption <= 0) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid input. Enter a positive value for consumption.\n";
					}
				} while (cin.fail() || additionalconsumption <= 0);

				do {
					cout << "Enter quantity of this appliance: ";
					cin >> additionalquantity;

					if (cin.fail() || additionalquantity <= 0) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid input. Enter a positive integer for quantity.\n";
					}
				} while (cin.fail() || additionalquantity <= 0);

				do {
					cout << "Enter average hours of usage per day of this appliance: ";
					cin >> additionalusage;

					if (cin.fail() || additionalusage < 0) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid input. Enter a positive value for hours.\n";
					}
				} while (cin.fail() || additionalusage < 0);

				totalconsumption += (additionalconsumption * additionalquantity * additionalusage);
			}
			else if (additionchoice != '0') {
				cout << "Invalid choice. Please enter 1 for Yes or 0 for No.\n";
			}
		} while (additionchoice != '0');

		// Convert total consumption to kWh and display
		totalconsumption /= 1000;
	}


	cout << "Daily Energy consumption (in kWh) is " << totalconsumption << endl;
	file << endl << "Total Energy Consumption (in kWh) is: " << totalconsumption << endl;

	file.close();

	panelsrequired();

	return 0;
}

//calculates number of panels required and also calculates total price including inverter, battery, wiring etc 
int panelsrequired()
{
	char paneltypechoice, paneltype, doping, invertchoice, batterychoice, wiringchoice, structurechoice;
	int panelchoice;
	long numofpanels[8], priceperwatt, installprice = 50000;
	double effeciency = 0, sunhours, reqpower = 0, priceperpanel[8], totalprice;
	double panelpower[8] = { 150, 200, 250, 300, 350, 400, 450, 500 };

	fstream file;
	file.open("panelsrequired.txt", ios::out);

	if (!file) {
		cout << "Error opening the file!" << endl;
		return 1;
	}

	cout << "\n=========================================================\n";
	cout << "|              WELCOME TO SOLAR PANEL ESTIMATOR            |";
	cout << "\n=========================================================\n";

	cout << "\n<<<<<<<<<<<<<<<<< PANEL TYPE <<<<<<<<<<<<<<<<<\n\n";
	cout << "Option 1  : N-Type & Single Glass \n";
	cout << "Price     : 28 PKR per Watt \n";
	cout << "Efficiency: 22.85 %\n";
	cout << "--------------------------------\n\n";

	cout << "Option 2  : N-Type & Double Glass \n";
	cout << "Price     : 31 PKR per Watt \n";
	cout << "Efficiency: 23.97 %\n";
	cout << "-----------------------------------\n\n";


	cout << "Option 3  : P-Type & Single Glass \n";
	cout << "Price     : 26 PKR per Watt \n";
	cout << "Efficiency: 22.9 %\n";
	cout << "------------------------------------\n\n";

	cout << "Option 4  : P-Type & Double Glass \n";
	cout << "Price     : 29 PKR per Watt \n";
	cout << "Efficiency: 21.8 %\n";
	cout << "-------------------------------------\n";

	do
	{
		cout << "Enter your choice (1-4): ";
		cin >> paneltypechoice;

		if (cin.fail() || paneltypechoice != '1' && paneltypechoice != '2' && paneltypechoice != '3' && paneltypechoice != '4')
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Enter again: " << endl;
		}

	} while (cin.fail() || paneltypechoice != '1' && paneltypechoice != '2' && paneltypechoice != '3' && paneltypechoice != '4');

	if (paneltypechoice == '1')
	{
		doping = 'N';
		paneltype = 'S';
		effeciency = (22.85 / 100);
		priceperwatt = 28;
	}

	else if (paneltypechoice == '2')
	{
		doping = 'N';
		paneltype = 'D';
		effeciency = (23.97 / 100);
		priceperwatt = 31;
	}

	else if (paneltypechoice == '3')
	{
		doping = 'P';
		paneltype = 'S';
		effeciency = (21.8 / 100);
		priceperwatt = 26;
	}

	else if (paneltypechoice == '4')
	{
		doping = 'P';
		paneltype = 'D';
		effeciency = (22.9 / 100);
		priceperwatt = 29;
	}

	cout << "\nEnter average sunlight hours:";
	do
	{
		cin >> sunhours;

		if (cin.fail() || (sunhours <= 0 || sunhours > 24))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Enter again: " << endl;
		}
	} while (cin.fail() || (sunhours <= 0 || sunhours > 24));
	cout << "\n";


	//calculating number of panels
	reqpower = totalconsumption / sunhours;  // reqpower is in kwh as totalconsumption is also in kwh
	cout << fixed << setprecision(1);
	cout << "Required Power of Solar System is: " << reqpower << " Kilo watts \n";

	for (int i = 0; i < 8; i++)
	{
		// calculating price of one panel
		priceperpanel[i] = priceperwatt * panelpower[i];

		panelpower[i] = panelpower[i] / 1000; // converting into kw

		//numofpanels = (reqpower) / panelpower;
		numofpanels[i] = static_cast<int>(reqpower / panelpower[i] + 0.99);
	}

	cout << "------------------------------------------------------------------------------  " << endl;
	cout << "Options   Panel Power (watts)   Price Per Panel (pkr)   Panels Required" << endl;
	cout << "------------------------------------------------------------------------------  " << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << i + 1 << ")\t  "
			<< panelpower[i] * 1000 << "\t\t\t"
			<< priceperpanel[i] << "\t\t\t"
			<< numofpanels[i] << endl;
	}

	do {
		cout << "\nEnter your choice (1-8): ";
		cin >> panelchoice;

		if (cin.fail() || panelchoice < 1 || panelchoice > 8)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Enter again: " << endl;
		}

	} while (cin.fail() || panelchoice < 1 || panelchoice > 8);

	//calculating total price
	totalprice = priceperpanel[panelchoice - 1] * numofpanels[panelchoice - 1];
	cout << "\nTotal price of " << numofpanels[panelchoice - 1] << " panels is: " << totalprice << " PKR" << endl;


	// asking user for inverter
	do
	{
		cout << "\nDo you also want inverter(Y/N)? ";
		cin >> invertchoice;

		if (cin.fail() || (invertchoice != 'Y' && invertchoice != 'y' && invertchoice != 'N' && invertchoice != 'n'))
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: \n";
		}

	} while (cin.fail() || (invertchoice != 'Y' && invertchoice != 'y' && invertchoice != 'N' && invertchoice != 'n'));

	double inverterprice = 0, invertercapacity = 1; // initializing variables passed to func

	if (invertchoice == 'Y' || invertchoice == 'y')
		inverter(inverterprice, invertercapacity, reqpower); //calling inverter function


	// asking user for battery
	do
	{
		cout << "\nDo you also want battery(Y/N)? ";
		cin >> batterychoice;

		if (cin.fail() || (batterychoice != 'Y' && batterychoice != 'y' && batterychoice != 'N' && batterychoice != 'n'))
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: \n";
		}

	} while (cin.fail() || (batterychoice != 'Y' && batterychoice != 'y' && batterychoice != 'N' && batterychoice != 'n'));

	double batteryprice = 0;
	if (batterychoice == 'Y' || batterychoice == 'y')
		batteryprice = battery(reqpower);                    //calling battery function


	//asking for wiring
	do
	{
		cout << "\nDo you also want DC cable(Y/N)? ";
		cin >> wiringchoice;

		if (cin.fail() || (wiringchoice != 'Y' && wiringchoice != 'y' && wiringchoice != 'N' && wiringchoice != 'n'))
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: \n";
		}

	} while (cin.fail() || (wiringchoice != 'Y' && wiringchoice != 'y' && wiringchoice != 'N' && wiringchoice != 'n'));

	double wireprice = 0;
	if (wiringchoice == 'Y' || wiringchoice == 'y')
		wireprice = wiring();                             //calling wiring function


	//asking for structure
	do
	{
		cout << "\n\nDo you also want structure for panels(Y/N)? ";
		cin >> structurechoice;

		if (cin.fail() || (structurechoice != 'Y' && structurechoice != 'y' && structurechoice != 'N' && structurechoice != 'n'))
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: \n";
		}

	} while (cin.fail() || (structurechoice != 'Y' && structurechoice != 'y' && structurechoice != 'N' && structurechoice != 'n'));

	double structureprice = 0;
	if (structurechoice == 'Y' || structurechoice == 'y')
	{
		structureprice = 3 * reqpower * 1000;    // multiply price of structure per panel with total panels 
		cout << "Price of structure is (3 pkr per watt): " << structureprice << " PKR\n\n";
	}

	totalprice = totalprice + batteryprice + inverterprice + structureprice; //updated total price
	cout << "Total price is: " << totalprice << " PKR\n\n\n";



	//APPLYING FILE HANDLING
	file << "*********** Solar Panel Estimation Results ***********\n";
	file << "Doping Type: " << (doping == 'P' ? "P-type" : "N-type") << endl;
	file << "Panel Type: " << (paneltype == 'S' ? "Single Glass" : "Double Glass") << endl;
	file << "Efficiency: " << effeciency * 100 << " %\n";
	file << "Number of Panels: " << numofpanels[panelchoice - 1] << endl;

	if (invertchoice == 'y' || invertchoice == 'Y')
	{
		file << "Inverter Capacity (in kwh): " << invertercapacity << endl;
		file << "Inverter Price (in PKR): " << inverterprice << endl;
	}

	file << "Installment and Maintainence Price: " << structureprice << endl;
	file << "Total Cost: " << totalprice << " PKR\n";

	//closing the file
	file.close();

	char savechoice;

	cout << "Do you want to calculate your Solar Panel savings (y/n): ";
	cin >> savechoice;

	if (savechoice == 'y' || savechoice == 'Y')
		savings();

	else
		tips(); 

}

// calculates savings over lifespan of panel
void savings()
{
	long numofpanels, lifespan;
	double initialefficiency, sunhours = 1, monthlysaving, yearlysaving, totalmonthlysaving = 0, totalyearlysaving = 0;
	double degrad_rate = 0, sum = 0, totalsavings = 0, efficiency, panelpower;
	double energyrate = 35.50; //taken from website of lesco(rate of one unit)

	cout << "\n=========================================================\n";
	cout << "|           WELCOME TO SOLAR PANEL SAVING ESTIMATOR       |";
	cout << "\n=========================================================\n\n";



	do
	{
		cout << "Enter number of panels: ";
		cin >> numofpanels;

		if (cin.fail() || numofpanels <= 0)
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: " << endl;
		}
	} while (cin.fail() || numofpanels <= 0);

	do {
		cout << "Enter power of one panel (in watts): ";
		cin >> panelpower;

		if (cin.fail() || panelpower <= 0)
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: " << endl;
		}
	} while (cin.fail() || panelpower <= 0);

	do {
		cout << "Enter average sunlight hours daily: ";
		cin >> sunhours;

		if (cin.fail() || (sunhours > 24 || sunhours <= 0))
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: " << endl;
		}
	} while (cin.fail() || (sunhours > 24 || sunhours <= 0));

	do
	{
		cout << "Enter degradation rate (0.05% - 2%): ";
		cin >> degrad_rate;

		if (cin.fail() || degrad_rate <= 0 || degrad_rate >= 100)
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: " << endl;
		}
	} while (cin.fail() || degrad_rate <= 0 || degrad_rate >= 100);

	do {
		cout << "Enter lifespan (warranty) of panel (in years): ";
		cin >> lifespan;

		if (cin.fail() || lifespan <= 0)
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: " << endl;
		}
	} while (cin.fail() || lifespan <= 0);

	do
	{
		cout << "Enter efficiency of panel: ";
		cin >> initialefficiency;

		if (cin.fail() || (initialefficiency <= 0 || initialefficiency >= 100))
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input, enter again: " << endl;
		}
	} while (cin.fail() || (initialefficiency <= 0 || initialefficiency >= 100));

	int year;

	for (year = 1; year <= lifespan; year++)
	{
		efficiency = (initialefficiency / 100) * pow(1 - (degrad_rate / 100), year - 1);
		// it is the effeciency which degrades over the year using formula: initialefficiency * (1-degradation rate) ^ (year-1)

		// monthlysaving = num of panels * power of 1 panel * sunlight hours * efficiency * energyrate(rate of 1 kwh)
		monthlysaving = numofpanels * (panelpower / 1000) * sunhours * efficiency * 30 * energyrate;
		yearlysaving = monthlysaving * 12;

		totalmonthlysaving += monthlysaving;
		totalyearlysaving += yearlysaving;
		totalsavings = totalsavings + yearlysaving;
	}

	cout << "\n-----------------------------------------------------------------------\n";
	cout << "Average monthly savings are: " << totalmonthlysaving / lifespan << " PKR\n";
	cout << "Average yearly savings are: " << totalyearlysaving / lifespan << " PKR\n";
	cout << "Estimated saving over " << lifespan << " is:" << totalsavings << " PKR\n";
	cout << "-----------------------------------------------------------------------\n";

	tips();
}

// gives tips and recommendations
void tips()
{
	cout << "=========================================================================\n";
	cout << "|                               SOLAR TIPS                              |\n";
	cout << "=========================================================================\n";
	cout << "|  1. PANEL PLACEMENT                                                   |\n";
	cout << "|     - Ensure panels are placed in a location with maximum             |\n";
	cout << "|       sun exposure.                                                   |\n";
	cout << "|     - Panels should face south (in the northern hemisphere)           |\n";
	cout << "|       and north (in the southern hemisphere).                         |\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "|  2. PANEL ORIENTATION                                                 |\n";
	cout << "|     - Panels should be tilted at an angle matching your               |\n";
	cout << "|       geographical location.                                          |\n";
	cout << "|     - In winter, increase tilt angle by 10 degree.                    |\n";
	cout << "|     - In summer, decrease tilt angle by 10 degree.                    |\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "|  3. USAGE OF BATTERY                                                  |\n";
	cout << "|     - Consider installing solar batteries to store excess energy.     |\n";
	cout << "|     - Use stored energy during cloudy days.                           |\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "|  4. REGULAR CLEANING                                                  |\n";
	cout << "|     - Clean panels regularly to increase efficiency.                  |\n";
	cout << "|     - Remove dirt, dust, or snow to prevent energy loss.              |\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "|  5. REMOVE SHADES                                                     |\n";
	cout << "|     - Check for shading from trees, buildings, or other obstacles.    |\n";
	cout << "|     - Remove obstacles to ensure full sunlight exposure.              |\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "|  6. USE ENERGY-EFFICIENT APPLIANCES                                   |\n";
	cout << "|     - Use energy-efficient appliances (e.g., LED lights, efficient    |\n";
	cout << "|       air conditioning).                                              |\n";
	cout << "|     - Reduce energy use to maximize solar benefits.                   |\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "|  7. SOLAR AGE                                                         |\n";
	cout << "|     - Older systems degrade over time, reducing output.               |\n";
	cout << "|     - Inspect and replace degraded panels or components as needed.    |\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "|  8. RESOURCES                                                         |\n";
	cout << "|     - For more information visit Solar Energy Industries              |\n";
	cout << "|       Association website (seia.org).                                 |\n";
	cout << "|     - You can also visit www.skyelectric.com to learn about solar     |\n";
	cout << "|       energy.                                                         |\n";
	cout << "=========================================================================\n";
	cout << "|                FOLLOW THESE TIPS TO MAXIMIZE EFFICIENCY               |\n";
	cout << "=========================================================================\n";
}

int main()
{
	start();

}