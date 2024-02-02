//Jason Siecienski
//CS 221

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

#include "ccc_empl.h"

const int NEWLINE_LENGTH = 2;
const int RECORD_SIZE = 30 + 10 + NEWLINE_LENGTH;

void write_employee(Employee e, ostream& out);

inline bool check_file_open(fstream& fs, const string& filename);
double calculate_average_salary(fstream& fs, int nrecord);//Additional functionality to calculate average sal.

/**
   Converts a string to a floating-point value, e.g.
   "3.14" -> 3.14.
   @param s a string representing a floating-point value
   @return the equivalent floating-point value
*/
double string_to_double(string s)
{
    istringstream instr(s);
    double x;
    //Added error handling.
    if (!(instr >> x)) {
        throw runtime_error("Conversion from string to double has failed.");
    }
    return x;
}

/**
   Raises an employee salary.
   @param e employee receiving raise
   @param percent the percentage of the raise
*/
void raise_salary(Employee& e, double percent)
{
    double new_salary = e.get_salary() * (1 + percent / 100);
    e.set_salary(new_salary);
}

/**
   Reads an employee record from a file.
   @param e filled with the employee
   @param in the stream to read from
*/
void read_employee(Employee& e, istream& in)
{
    string line;
    getline(in, line);

    if (in.fail())
        throw runtime_error("Failed to read from the stream.");

    // Taking into account potential differences in newline character length
    if (line.length() > RECORD_SIZE - NEWLINE_LENGTH) {
        line = line.substr(0, RECORD_SIZE - NEWLINE_LENGTH); // Truncate to expected length
    }

    string name = line.substr(0, 30);
    double salary = string_to_double(line.substr(30, 10));
    e = Employee(name, salary);

}

/**
   Writes an employee record to a stream.
   @param e the employee record to write
   @param out the stream to write to
*/
void write_employee(Employee e, ostream& out)
{

    out << e.get_name()
        << setw(10 + (30 - e.get_name().length()))
        << fixed << setprecision(2)
        << e.get_salary();
    //added error handling.
    if (out.fail()) {
        throw runtime_error("Failed to write to the stream.");
    }

}

int main()
{
    try {
        cout << "Please enter the data file name: ";
        string filename;
        cin >> filename;
        if (cin.fail())
        {
            throw runtime_error("Failed to read filename from input.");
        }
        fstream fs;
        fs.open(filename.c_str(), ios::in | ios::out);


        if (fs.fail())
        {
            throw runtime_error("Failed to seek in the file stream.");
        }

        fs.seekg(0, ios::end);
        if (fs.fail()) {
            throw runtime_error("Failed to seek in the file stream.");
        }

        int nrecord = fs.tellg() / RECORD_SIZE;
        if (nrecord <= 0) {
            throw runtime_error("No records found in the file.");
        }
        cout << "Would you like to calculate the average salary of all employees? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            fs.seekg(0, ios::beg); // Reset file pointer to the beginning
            double average_salary = calculate_average_salary(fs, nrecord);
            cout << "Average salary: " << fixed << setprecision(2) << average_salary << endl;
        }

        cout << "Please enter the record to update: (0 - " << nrecord - 1 << ") ";
        int pos;
        cin >> pos;
        if (cin.fail() || pos < 0 || pos >= nrecord) {
            throw runtime_error("Invalid record number entered.");
        }

        const double SALARY_CHANGE = 5.0;

        Employee e;
        fs.seekg(pos * RECORD_SIZE, ios::beg);
        if (fs.fail()) {
            throw runtime_error("Unable to go to the position in the file.");
        }

        read_employee(e, fs);
        raise_salary(e, SALARY_CHANGE);
        cout << "New salary: " << e.get_salary() << endl;

        fs.seekp(pos * RECORD_SIZE, ios::beg);
        if (fs.fail()) {
            throw runtime_error("Unable to go to the position in file for writing.");
        }

        write_employee(e, fs);

        fs.close();
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    // Perform the raise salary operation
    const double SALARY_CHANGE = 5.0;
    Employee e;
    fs.seekg(pos * RECORD_SIZE, ios::beg);

    // Check if seeking in the file stream fails
    if (fs.fail())
    {
        throw runtime_error("Unable to go to the position in the file.");
    }

    // Read the employee record
    read_employee(e, fs);

    // Raise the salary
    raise_salary(e, SALARY_CHANGE);

    // Display the new salary
    cout << "New salary: " << e.get_salary() << endl;

    fs.seekp(pos * RECORD_SIZE, ios::beg);

    // Check if seeking in the file for writing fails
    if (fs.fail())
    {
        throw runtime_error("Unable to go to the position in file for writing.");
    }

    // Write the updated employee record
    write_employee(e, fs);

    fs.close();
}
catch (const runtime_error& e)
{
    cerr << "Error: " << e.what() << endl;
    return 1;
}

return 0;
}
 
//Added to check if the file was opened successfully.
inline bool check_file_open(fstream& fs, const string& filename) {
    if (!fs) {
        cout << "Error: Unable to open file '" << filename << "'." << endl;
        return false;
    }
    return true;
}
//Additional functionality: Iterates through all records in the file and reads each employy salary, then computes the
//average.
double calculate_average_salary(fstream& fs, int nrecord) {
    double total_salary = 0.0;
    Employee e;

    for (int i = 0; i < nrecord; ++i) {
        fs.seekg(i * RECORD_SIZE, ios::beg);
        read_employee(e, fs);
        total_salary += e.get_salary();
    }

    return (nrecord > 0) ? total_salary / nrecord : 0.0;
}