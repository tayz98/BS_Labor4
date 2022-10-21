/*
* <makefile Programm>
* Autoren:
* Sören Zacharias
* Alexander Nachtigal
* Datum : 21.10.2022
* Beschreibung: 
* Das Programm frag den User nach einen Dateinamen und erstellt dann eine Datei mit dem von User eingegebenen Namen.
* Außerdem bekommt der Besitzer der Datei vollen Zugriff auf diese.
*/

#include <stdio.h> // wird für fgets und printf verwendet
#include <string.h> // wird für strlen benötigt
#include <fcntl.h> // wird für creat(), mode_t mode benötigt
#include <unistd.h> // wird für close() benötigt
#include <sys/stat.h> // wird für die Berechtigungsmaske z. B "#define S_IRWXU 0000700" benötigt
#define MAXLENGTH 31 // das Array für den Dateinamen soll 31 Zeichen groß sein wg. Null Byte
#define MAXPATHLENGTH 50 // der Pfad darf max. nur 50 Zeichen lang sein

// vorab definierte Funktionen:
void askForFile(char *);

// Startpunkt des Programmes
int main (void) {
	int fd; // file descriptor zur Identifizierung der zu erstellenden Datei
	mode_t mode = S_IRWXU; // Zugriff für den Besitzer der Datei
	char fileName [MAXLENGTH]; // deklarierung des Char Arrays
	askForFile(fileName); // ruft die Funktion askForFile mit dem char Array fileName als Parameter auf
	printf("%s \n", fileName); // gibt den eingegeben Dateinamen aus
	char filePath[MAXPATHLENGTH] = "./";// Ordner, in dem die Datei erstellt werden soll.

	// nun werden die char Arrays filePath und fileName miteinander konkateniert.
	// um einen Buffer-Overflow zu vermeiden, wird strncat statt strcat verwendet.
	strncat(filePath, fileName, MAXPATHLENGTH - strlen(fileName) - 1 ); // -1 wegen Null Byte
	fd = creat(filePath, mode); //  hier wird die Datei erstellt. der fd bekommt eine ID
	close(fd); // der fd wird nicht mehr benötigt und geschlossen.
	return 0;
}

// Diese Funktion erwartet eine Eingabe von dem User
// und speichert diese in das Char Array aus der Main Fkt
void askForFile(char *string) {
	printf("Name der neuen Datei: ");
	fgets(string, MAXLENGTH, stdin); // liest den Input des Users und schreibt diesen in das Char-Array
}
