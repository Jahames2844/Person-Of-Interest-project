#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <cctype>
#include <csignal>

volatile std::sig_atomic_t abortRequested = 0;

void handleAbort(int) {
	std::_Exit(0);
}

void setGreekTimeZone() {
#ifdef _WIN32
	_putenv_s("TZ", "EET-2EEST,M3.5.0/3,M10.5.0/4");
	_tzset();
#else
	setenv("TZ", "EET-2EEST,M3.5.0/3,M10.5.0/4", 1);
	tzset();
#endif
}

std::string toUpper(const std::string &str) {
	std::string upperStr = str;
	std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
	[](unsigned char c) {
		return std::toupper(c);
	});
	return upperStr;
}

void typeEffect(const std::string &text, int delayMs = 40) {
	for (char c : text) {
		if (abortRequested) {
			break;
		}
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
	}
	std::cout << std::endl;
}

std::string getTimestamp() {
	std::time_t now = std::time(nullptr);
	char buf[20];
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return buf;
}

void scanningAnimation(int cycles = 3) {
	for (int i = 0; i < cycles; i++) {
		if (abortRequested) {
			return;
		}

		std::cout << "\r[SCANNING";
		for (int j = 0; j < 3; j++) {
			if (abortRequested) {
				std::cout << std::endl;
				return;
			}
			std::cout << "." << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
		std::cout << "]   ";
	}
	std::cout << std::endl;
}

void randomSurveillanceMessage() {
	const std::vector<std::string> messages = {
		"[CAMERA 12] SUBJECT IDENTIFIED",
		"[CAMERA 4] UNKNOWN INDIVIDUAL DETECTED",
		"[AUDIO FEED] CONVERSATION FLAGGED",
		"[GPS TRACK] TARGET LOCATION UPDATED",
		"[DATABASE] RECORDS ACCESSED",
		"[FACIAL RECOGNITION] MATCH FOUND"
	};
	typeEffect(messages[rand() % messages.size()]);
}

void faceScan() {
	typeEffect("[INITIATING FACE SCAN]");
	for (int progress = 0; progress <= 100; progress += 10) {
		if (abortRequested) {
			return;
		}
		std::cout << "\rSCAN PROGRESS: " << progress << "%" << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	if (!abortRequested) {
		std::cout << "\n[SCAN COMPLETE] MATCH FOUND" << std::endl;
	}
}

void saveLastName(const std::string &lastName) {
	std::ofstream file("lastName.txt");
	if (file) {
		file << lastName;
	}
}

std::string loadLastName() {
	std::ifstream file("lastName.txt");
	std::string name;
	if (file) {
		std::getline(file, name);
	}
	return name;
}

void systemStatus() {
	typeEffect("[SYSTEM STATUS]");
	typeEffect("CPU LOAD: 23%");
	typeEffect("MEMORY USAGE: 45%");
	typeEffect("UPTIME: 12 DAYS 4 HOURS 32 MINUTES");
}

struct PersonRecord {
	std::string name;
	std::vector<std::string> aliases;
	std::string status;
	std::string exteriorAddress;
	std::string arrestRecord;
	std::string precinct;
	std::string agency;
};

const std::vector<PersonRecord> &personDatabase() {
	static const std::vector<PersonRecord> people = {
		{"THE MACHINE", {"MACHINE"}, "OPERATIONAL", "", "", "", ""},
		{	"HAROLD FINCH", {"FINCH", "HAROLD WREN"}, "ALIVE",
			"160 Lexington Ave., Manhattan; 5 Beekman St., Manhattan", "", "", ""
		},
		{	"JOHN REESE",
			{"REESE", "JOHN RILEY", "THE MAN IN THE SUIT"},
			"ALIVE", "214 Lafayette Street, Manhattan",
			"RIKERS ISLAND: ARRESTED; RELEASED", "", "CIA; NYPD"
		},
		{	"ROOT", {"SAMANTHA GROVES", "CAROLINE TURING"},
			"ALIVE", "", "", "", ""
		},
		{"SAMEEN SHAW", {"SHAW"}, "ALIVE", "", "", "", ""},
		{	"LIONEL FUSCO", {"FUSCO"}, "ALIVE", "", "",
			"NYPD 8TH PRECINCT; FORMERLY 51ST PRECINCT", "NYPD"
		},
		{	"JOSS CARTER", {"CARTER"}, "DECEASED",
			"141 East 95th Street, Manhattan", "", "NYPD 8TH PRECINCT", "NYPD"
		},
		{"ZOE MORGAN", {"ZOE"}, "ALIVE", "", "", "", ""},
		{"LEON TAO", {"LEON"}, "ALIVE", "", "", "", ""},
		{"GRACE HENDRICKS", {"GRACE"}, "ALIVE", "", "", "", ""},
		{"CALEB PHIPPS", {"CALEB"}, "ALIVE", "", "", "", ""},
		{	"CARL ELIAS", {"ELIAS"}, "DECEASED", "",
			"RIKERS ISLAND: HELD PENDING TRIAL; LATER TRANSFERRED", "", ""
		},
		{"CONTROL", {"ALICIA CORWIN"}, "DECEASED", "", "", "", ""},
		{"ANTHONY MARCONI", {"SCARFACE"}, "DECEASED", "", "", "", ""},
		{"ALONZO QUINN", {"QUINN"}, "DECEASED", "", "", "", "NYPD"},
		{	"PATRICK SIMMONS",
			{"SIMMONS", "OFFICER SIMMONS", "ROBERT MACTIERNAN"},
			"ALIVE", "", "", "NYPD 20TH PRECINCT", "NYPD"
		},
		{	"JAMES STILLS", {"STILLS"}, "DECEASED", "", "",
			"FORMERLY NYPD 51ST PRECINCT", "NYPD"
		},
		{	"MARK SNOW", {"SNOW", "CIA AGENT SNOW"}, "DECEASED",
			"", "", "", "CIA"
		},
		{	"NICHOLAS DONNELLY",
			{"NICK DONNELLY", "AGENT DONNELLY", "FBI AGENT DONNELLY"},
			"DECEASED", "", "", "", "FBI"
		},
		{"DANIEL CASEY", {"CASEY", "NSA ANALYST CASEY"}, "ALIVE", "", "", "", ""},
		{	"SENATOR ROSS GARRISON",
			{"ROSS GARRISON", "SENATOR GARRISON"}, "ALIVE", "", "", "", ""
		},
		{"BYRON", {}, "ALIVE", "", "RIKERS ISLAND: INCARCERATED", "", ""},
		{	"WAYNE PACKER", {"PACKER"}, "ALIVE", "",
			"RIKERS ISLAND: INCARCERATED", "", ""
		},
		{	"CHARLES MACAVOY", {"MACAVOY"}, "ALIVE", "",
			"RIKERS ISLAND: INCARCERATED", "", ""
		},
		{	"BRIAN KELLY", {"KELLY"}, "DECEASED", "",
			"RIKERS ISLAND: FOUND DEAD IN HIS CELL", "", ""
		},
		{	"HERSH", {}, "ALIVE", "",
			"RIKERS ISLAND: INCARCERATED; RELEASED", "", ""
		},
		{	"LOUIS AZARELLO", {"AZARELLO"}, "ALIVE", "",
			"RIKERS ISLAND: INCARCERATED", "", ""
		},
		{	"LASZLO YOGOROV", {"LASZLO"}, "ALIVE", "",
			"RIKERS ISLAND: INCARCERATED", "", ""
		},
		{"NATHAN INGRAM", {"INGRAM", "N.I."}, "DECEASED", "", "", "", ""},
		{"RICK DILLINGER", {"DILLINGER"}, "DECEASED", "", "", "", ""},
		{"CAL BEECHER", {"BEECHER"}, "DECEASED", "", "", "", "NYPD"},
		{"BILL SZYMANSKI", {"SZYMANSKI"}, "DECEASED", "", "", "", "NYPD"},
		{	"BRIAN MOSS", {"AGENT MOSS", "SPECIAL AGENT MOSS"},
			"ALIVE", "", "", "", "FBI"
		},
		{	"KARA STANTON", {"STANTON", "AGENT STANTON"},
			"DECEASED", "", "", "", "CIA"
		},
		{	"TYRELL EVANS", {"EVANS", "AGENT EVANS"},
			"DECEASED", "", "", "", "CIA"
		}
	};

	return people;
}

void threatAssessment() {
	std::string subject;
	typeEffect("[THREAT ASSESSMENT]");
	std::cout << "ENTER SUBJECT NAME OR ALIAS: ";
	std::getline(std::cin, subject);

	if (abortRequested) {
		return;
	}

	std::string query = toUpper(subject);

	for (const PersonRecord &person : personDatabase()) {
		bool matches = query == person.name ||
		               std::find(person.aliases.begin(), person.aliases.end(), query)
		               != person.aliases.end();

		if (!matches) {
			continue;
		}

		typeEffect("SUBJECT: " + person.name);
		typeEffect("[STATUS] " + person.status);

		if (!person.agency.empty()) {
			typeEffect("AGENCY: " + person.agency);
		}
		if (!person.precinct.empty()) {
			typeEffect("PRECINCT: " + person.precinct);
		}
		if (!person.arrestRecord.empty()) {
			typeEffect("ARREST RECORD: " + person.arrestRecord);
		}

		const std::vector<std::string> levels = {"LOW", "MEDIUM", "HIGH"};
		typeEffect("[THREAT LEVEL]: " + levels[rand() % levels.size()]);
		return;
	}

	typeEffect("[NOT IN DATABASE]");
}

void printPersonRecord(const PersonRecord &person, int delayMs = 40) {
	typeEffect(person.name, delayMs);
	if (person.status == "DECEASED") {
		typeEffect("[STATUS] DECEASED", delayMs);
	}
}

void trackSubject() {
	std::string subject;
	typeEffect("[TRACKING SUBJECT]");
	std::cout << "ENTER SUBJECT NAME OR ALL: ";
	std::getline(std::cin, subject);

	if (abortRequested) {
		return;
	}

	std::string name = toUpper(subject);

	if (name == "ALL") {
		for (const PersonRecord &person : personDatabase()) {
			printPersonRecord(person, 0);
		}
		return;
	}

	for (const PersonRecord &person : personDatabase()) {
		bool matches = name == person.name ||
		               std::find(person.aliases.begin(), person.aliases.end(), name)
		               != person.aliases.end();

		if (matches) {
			printPersonRecord(person);
			return;
		}
	}

	typeEffect("[NOT IN DATABASE]");
}

void knownPersons() {
	typeEffect("[KNOWN PERSONS]");

	for (const PersonRecord &person : personDatabase()) {
		typeEffect(person.name + ": " + person.status);
	}
}

void knownAliases() {
	typeEffect("[ALIASES]");

	for (const PersonRecord &person : personDatabase()) {
		std::string entry = person.name + ": ";

		if (person.aliases.empty()) {
			entry += "[NONE]";
		} else {
			for (std::size_t i = 0; i < person.aliases.size(); i++) {
				if (i > 0) {
					entry += ", ";
				}
				entry += person.aliases[i];
			}
		}

		typeEffect(entry);
	}
}

void knownOfficers(const std::string &agencyFilter = "") {
	typeEffect("[KNOWN OFFICERS]");

	for (const PersonRecord &person : personDatabase()) {
		if (person.agency.empty()) {
			continue;
		}
		if (!agencyFilter.empty() &&
		        person.agency.find(agencyFilter) == std::string::npos) {
			continue;
		}

		std::string entry = person.name + ": " + person.status +
		                    " | AGENCY: " + person.agency;

		if (!person.aliases.empty()) {
			entry += " | ALIASES: ";
			for (std::size_t i = 0; i < person.aliases.size(); i++) {
				if (i > 0) {
					entry += ", ";
				}
				entry += person.aliases[i];
			}
		}

		typeEffect(entry);
	}
}

void rikersArrestRecords() {
	typeEffect("[RIKERS ISLAND ARREST RECORDS]");
	typeEffect("CARL ELIAS: HELD PENDING TRIAL; LATER TRANSFERRED");
	typeEffect("JOHN REESE: HELD AFTER FBI ARREST; RELEASED");
	typeEffect("BYRON: INCARCERATED");
	typeEffect("WAYNE PACKER: INCARCERATED");
	typeEffect("CHARLES MACAVOY: INCARCERATED");
	typeEffect("BRIAN KELLY: FOUND DEAD IN HIS CELL");
	typeEffect("HERSH: INCARCERATED; RELEASED");
	typeEffect("LOUIS AZARELLO: INCARCERATED");
	typeEffect("LASZLO YOGOROV: INCARCERATED");
}

void precinctArrestRecords() {
	typeEffect("[PRECINCT ARREST RECORDS]");
	typeEffect("NYPD 8TH PRECINCT: JOHN REESE - APPREHENDED AND PROCESSED; RELEASED");
	typeEffect("NYPD 8TH PRECINCT: PATRICK SIMMONS - ARRESTED BY LIONEL FUSCO");
}

void generateCase() {
	int randomNum = rand() % 9000 + 1000;
	typeEffect("[NEW CASE GENERATED] CASE-2026-" + std::to_string(randomNum));
}

void relevantPerson() {
	const std::vector<std::string> names = {
		"ALEX MORGAN", "JAMIE PARK", "TAYLOR REED",
		"CASEY BLAKE", "RILEY QUINN"
	};

	int nameIndex = rand() % names.size();
	int numberSuffix = rand() % 100;

	std::string phoneNumber = "212-555-01";
	if (numberSuffix < 10) {
		phoneNumber += "0";
	}
	phoneNumber += std::to_string(numberSuffix);

	typeEffect("[RELEVANT PERSON IDENTIFIED]");
	typeEffect("NAME: " + names[nameIndex]);
	typeEffect("PHONE: " + phoneNumber);
}

void socialGraph() {
	typeEffect("[SOCIAL GRAPH]");
	typeEffect("SUBJECT -> CONTACT-" + std::to_string(rand() % 900 + 100));
	typeEffect("CONTACT-" + std::to_string(rand() % 900 + 100) +
	           " -> CONTACT-" + std::to_string(rand() % 900 + 100));
}

void machineStatus() {
	typeEffect("[MACHINE STATUS]");
	typeEffect("MODE: OPERATIONAL");
	typeEffect("THREAT ANALYSIS: ACTIVE");
	typeEffect("DECISION: AWAITING INPUT");
}

void predictOutcome() {
	const std::vector<std::string> outcomes = {
		"OBSERVE",
		"NO ACTION",
		"INTERVENTION REQUIRED"
	};
	typeEffect("[PREDICTION]: " + outcomes[rand() % outcomes.size()]);
}

void caseFile() {
	int caseNumber = rand() % 9000 + 1000;
	const std::vector<std::string> statuses = {
		"ACTIVE",
		"UNDER REVIEW",
		"PENDING"
	};

	typeEffect("[CASE FILE]");
	typeEffect("CASE ID: CASE-2026-" + std::to_string(caseNumber));
	typeEffect("STATUS: " + statuses[rand() % statuses.size()]);
	typeEffect("LAST UPDATED: " + getTimestamp());
}

void assetStatus() {
	const std::vector<std::string> statuses = {
		"ACTIVE",
		"STANDING BY",
		"IN TRANSIT",
		"OFFLINE"
	};

	typeEffect("[ASSET STATUS]");
	typeEffect("ASSET 01: " + statuses[rand() % statuses.size()]);
	typeEffect("ASSET 02: " + statuses[rand() % statuses.size()]);
	typeEffect("ASSET 03: " + statuses[rand() % statuses.size()]);
}

void threatProfile() {
	const std::vector<std::string> classifications = {
		"PERSON OF INTEREST",
		"POTENTIAL WITNESS",
		"UNKNOWN ASSOCIATE",
		"HIGH PRIORITY"
	};
	const std::vector<std::string> riskLevels = {
		"LOW",
		"MODERATE",
		"ELEVATED",
		"HIGH"
	};

	typeEffect("[THREAT PROFILE]");
	typeEffect("CLASSIFICATION: " +
	           classifications[rand() % classifications.size()]);
	typeEffect("RISK LEVEL: " + riskLevels[rand() % riskLevels.size()]);
}

void patternAnalysis() {
	int probability = rand() % 41 + 60;
	typeEffect("[PATTERN ANALYSIS]");
	typeEffect("BEHAVIORAL PATTERN: RECOGNIZED");
	typeEffect("CORRELATION: " + std::to_string(probability) + "%");
	typeEffect("RECOMMENDATION: CONTINUE OBSERVATION");
}

void activeCases() {
	const std::vector<std::string> statuses = {
		"ACTIVE",
		"UNDER REVIEW",
		"PENDING"
	};

	typeEffect("[ACTIVE CASES]");
	for (int i = 0; i < 3; i++) {
		int caseNumber = rand() % 9000 + 1000;
		std::string status = statuses[rand() % statuses.size()];
		typeEffect("CASE-2026-" + std::to_string(caseNumber) + ": " + status);
	}
}

void surveillanceStatus() {
	typeEffect("[SURVEILLANCE STATUS]");
	typeEffect("CAMERA NETWORK: OPERATIONAL");
	typeEffect("AUDIO FEED: ACTIVE");
	typeEffect("FACIAL RECOGNITION: STANDING BY");
	typeEffect("LOCATION TRACKING: ACTIVE");
}

void listCommands() {
	typeEffect("[AVAILABLE COMMANDS]");
	std::cout << "WHAT IS MY LAST NAME?\n"
	          << "FACE SCAN\n"
	          << "THREAT ASSESSMENT\n"
	          << "THREAT PROFILE\n"
	          << "PATTERN ANALYSIS\n"
	          << "SYSTEM STATUS\n"
	          << "TRACK SUBJECT\n"
	          << "GENERATE CASE\n"
	          << "CASE FILE\n"
	          << "ACTIVE CASES\n"
	          << "RELEVANT PERSON\n"
	          << "SOCIAL GRAPH\n"
	          << "ASSET STATUS\n"
	          << "MACHINE STATUS\n"
	          << "PREDICT OUTCOME\n"
	          << "SURVEILLANCE STATUS\n"
	          << "KNOWN PERSONS\n"
	          << "ALIASES\n"
	          << "KNOWN OFFICERS\n"
	          << "NYPD OFFICERS\n"
	          << "CIA PERSONNEL\n"
	          << "FBI PERSONNEL\n"
	          << "RIKERS ARREST RECORDS\n"
	          << "PRECINCT ARREST RECORDS\n"
	          << "ADMINS\n"
	          << "ANALOG INTERFACE\n"
	          << "PROJECTED ADMIN\n"
	          << "NETWORK SCAN\n"
	          << "CLEAR\n"
	          << "HELP\n"
	          << "MEOW\n"
	          << "ABORT\n"
	          << "SHRED/KERNEL.STOP\n"
	          << "EXIT\n";
}

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void networkScan() {
	typeEffect("[INITIATING NETWORK SCAN]");
	for (int i = 0; i < 5; i++) {
		if (abortRequested) {
			return;
		}
		std::cout << "[SCANNING IP] 192.168.0." << (rand() % 255) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	typeEffect("[SCAN COMPLETE] NO THREATS DETECTED");
}

int main() {
	setGreekTimeZone();
	std::signal(SIGINT, handleAbort);
	srand(static_cast<unsigned>(std::time(nullptr)));

	std::string username, password;
	typeEffect("[SYSTEM ONLINE]");
	typeEffect("LOGIN REQUIRED");

	std::cout << "USERNAME: ";
	std::getline(std::cin, username);
	std::cout << "PASSWORD: ";
	std::getline(std::cin, password);

	if (username != "Harold" || password != "admin") {
		typeEffect("[ACCESS DENIED]");
		return 0;
	}

	typeEffect("[ACCESS GRANTED]");
	scanningAnimation();
	typeEffect("[INTERFACE READY]");

	std::string lastName = loadLastName();
	bool hasLastName = !lastName.empty();
	std::string question;

	while (true) {
		randomSurveillanceMessage();
		std::cout << "\n[" << getTimestamp() << "] QUERY: ";

		if (!std::getline(std::cin, question)) {
			typeEffect("[SESSION TERMINATED]");
			break;
		}

		std::string qUpper = toUpper(question);

		if (qUpper == "EXIT") {
			typeEffect("[SESSION TERMINATED]");
			break;
		}
		else if (qUpper == "ABORT") {
			typeEffect("[ABORTED] TYPING STOPPED");
			break;
		}
		else if (qUpper == "SHRED/KERNEL.STOP") {
			typeEffect("[ACTIVATING DELETION SEQUENCE]");
			typeEffect("[SHUTTING DOWN]");
			break;
		}
		else if (qUpper == "ADMINS") {
			typeEffect("ADMIN IS HAROLD FINCH");
		}
		else if (qUpper == "ANALOG INTERFACE") {
			typeEffect("ANALOG INTERFACE IS ROOT");
		}
		else if (qUpper == "PROJECTED ADMIN") {
			typeEffect("NO PROJECTED ADMIN");
		}
		else if (qUpper == "WHAT IS MY LAST NAME?") {
			if (!hasLastName) {
				typeEffect("[DATA MISSING] PLEASE INPUT LAST NAME:");
				std::getline(std::cin, lastName);
				hasLastName = true;
				saveLastName(lastName);
				typeEffect("[CONFIRMED] LAST NAME: " + toUpper(lastName));
			} else {
				typeEffect("[RETRIEVED] LAST NAME: " + toUpper(lastName));
			}
		}
		else if (qUpper == "FACE SCAN") {
			faceScan();
		}
		else if (qUpper == "THREAT ASSESSMENT") {
			threatAssessment();
		}
		else if (qUpper == "THREAT PROFILE") {
			threatProfile();
		}
		else if (qUpper == "PATTERN ANALYSIS") {
			patternAnalysis();
		}
		else if (qUpper == "SYSTEM STATUS") {
			systemStatus();
		}
		else if (qUpper == "TRACK SUBJECT") {
			trackSubject();
		}
		else if (qUpper == "GENERATE CASE") {
			generateCase();
		}
		else if (qUpper == "CASE FILE") {
			caseFile();
		}
		else if (qUpper == "ACTIVE CASES") {
			activeCases();
		}
		else if (qUpper == "RELEVANT PERSON") {
			relevantPerson();
		}
		else if (qUpper == "SOCIAL GRAPH") {
			socialGraph();
		}
		else if (qUpper == "ASSET STATUS") {
			assetStatus();
		}
		else if (qUpper == "MACHINE STATUS") {
			machineStatus();
		}
		else if (qUpper == "PREDICT OUTCOME") {
			predictOutcome();
		}
		else if (qUpper == "SURVEILLANCE STATUS") {
			surveillanceStatus();
		}
		else if (qUpper == "KNOWN PERSONS") {
			knownPersons();
		}
		else if (qUpper == "ALIASES") {
			knownAliases();
		}
		else if (qUpper == "KNOWN OFFICERS") {
			knownOfficers();
		}
		else if (qUpper == "NYPD OFFICERS") {
			knownOfficers("NYPD");
		}
		else if (qUpper == "CIA PERSONNEL") {
			knownOfficers("CIA");
		}
		else if (qUpper == "FBI PERSONNEL") {
			knownOfficers("FBI");
		}
		else if (qUpper == "RIKERS ARREST RECORDS") {
			rikersArrestRecords();
		}
		else if (qUpper == "PRECINCT ARREST RECORDS") {
			precinctArrestRecords();
		}
		else if (qUpper == "NETWORK SCAN") {
			networkScan();
		}
		else if (qUpper == "CLEAR") {
			clearScreen();
		}
		else if (qUpper == "HELP") {
			listCommands();
		}
		else {
			typeEffect("[NOT IN DATABASE]");
		}
	}

	return 0;
}