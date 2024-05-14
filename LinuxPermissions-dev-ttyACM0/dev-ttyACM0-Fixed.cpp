#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
	string User;
	cout << endl << "User: ";
	cin >> User;
	
	string OS;
	cout << endl << "Choose your OS: " << endl;
	cout << endl << "1. Debian-based" << endl << "2. Arch-based" << endl << "[1, 2] > ";
	cin >> OS;

	while (OS != "1" && OS != "2") {
		cout << endl << "Error ! choose 1 or 2:" << endl;
		cout << "> ";
		cin >> OS;
	}

	string Cmd;

	if (OS == "1") {
		Cmd = "sudo usermod -a -G dialout " + User;
	}
	else if (OS == "2") {
		Cmd = "sudo usermod -a -G uucp " + User;
	}

	const string Command = Cmd;

	system(Command.c_str());
	system("sudo chmod +x /dev/ttyACM0");
	cout << endl << "Done." << endl;

	system("sleep 1");

	cout << endl << "Log Out and Log Back In:" << endl;
	cout << endl << "\t After adding your user to the group, log out and then log back in for the changes to take effect." << endl;
	cout << endl << "Verify Port Name:" << endl;
	cout << endl << "\t Double-check that the port in the Arduino IDE (Tools > Port) matches the actual port where your Arduino is connected." << endl; 
	cout << endl << "\t (usually /dev/ttyACM0 for Arduino boards)." << endl;
	cout << endl << "Timing and Reset:" << endl;
	cout << endl << "\t Sometimes, timing matters during the upload process." << endl;
	cout << endl << "\t Press the reset button on your Arduino board and immediately click the upload button in the Arduino IDE." << endl;
	cout << endl << "\t Experiment with the timing to find the right moment." << endl;

	return 0;
}
