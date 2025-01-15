#include<iostream>
#include<string>
using namespace std;

struct Doctor
{
    string name;
    string specialization;
    string username;
    string password;
    bool available = true;
};

struct Appointment
{
    string patientName;
    string patientEmail;
    string doctorName;
    string time;
};

Doctor doctors[100];
int doctorCount = 3;
Appointment appointments[100];
int appointmentCount = 1;


void initializeDoctors()
{
    doctors[0] = { "DrNomi", "Dentist", "nomi", "nomi1234", true };
    doctors[1] = { "DrSagheer", "gynecologist", "sagheer", "sagheer1234", true };
    doctors[2] = { "DrZain", "Surgen", "zain", "zain1234", true };
}

void initializeAppointments()
{
    appointments[0] = { "Nawaz sharif", "abc123@gmail.com", "DrNomi", "10am" };
}


void showDoctors()
{
    if (doctorCount == 0)
    {
        cout << "No doctors available.\n";
        return;
    }

    cout << "\nList of Doctors:\n";
    for (int i = 0; i < doctorCount; ++i)
    {
        cout << "Name: " << doctors[i].name << ", Specialization: " << doctors[i].specialization
            << ", Available: " << (doctors[i].available ? "Yes" : "No") << endl;
    }
}

void addDoctor()
{
    Doctor newDoctor;
    cout << "\nEnter Doctor's Name: ";
    cin.ignore();
    getline(cin, newDoctor.name);
    cout << "Enter Doctor's Specialization: ";
    getline(cin, newDoctor.specialization);
    cout << "Enter Username for Doctor: ";
    cin >> newDoctor.username;
    cout << "Enter Password for Doctor: ";
    cin >> newDoctor.password;
    doctors[doctorCount++] = newDoctor;
    cout << "Doctor added successfully!\n";
}

void viewAllAppointments()
{
    if (appointmentCount == 0)
    {
        cout << "No appointments available.\n";
        return;
    }
    cout << "\n\nAppointment of Doctors:-";
    for (int i = 0; i < appointmentCount; ++i)
    {
        cout << "\nAppointment for: " << appointments[i].doctorName << "\nPatient Name: " << appointments[i].patientName
            << "\nEmail: " << appointments[i].patientEmail << "\nTime: " << appointments[i].time << endl;
    }
}


bool doctorLogin(string username, string password, string& doctorName)
{
    for (int i = 0; i < doctorCount; ++i)
    {
        if (doctors[i].username == username && doctors[i].password == password)
        {
            doctorName = doctors[i].name;
            return true;
        }
    }
    return false;
}

void editDoctorInfo(string& doctorName)
{
    for (int i = 0; i < doctorCount; ++i)
    {
        if (doctors[i].name == doctorName)
        {
            cout << "\nEnter new Name(if you want to update otherwise enter Current one): ";
            cin.ignore();
            getline(cin, doctors[i].name);
            cout << "Enter new Username(if you want to update otherwise enter Current one): ";
            cin >> doctors[i].username;
            cout << "Enter new Specialization(if you want to update otherwise enter Current one): ";
            cin.ignore();
            getline(cin, doctors[i].specialization);
            cout << "Information updated successfully!\n";
            return;
        }
    }
    cout << "Doctor not found!\n";
}

void setAvailability(string doctorName, bool available)
{
    for (int i = 0; i < doctorCount; ++i)
    {
        if (doctors[i].name == doctorName)
        {
            doctors[i].available = available;
            cout << "Availability updated successfully!\n";
            return;
        }
    }
    cout << "Doctor not found!\n";
}

void viewAppointments(string doctorName)
{
    bool found = false;
    for (int i = 0; i < appointmentCount; ++i)
    {
        if (appointments[i].doctorName == doctorName)
        {
            cout << "\nPatient: " << appointments[i].patientName << "\nEmail: " << appointments[i].patientEmail
                << "\nTime: " << appointments[i].time << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No appointments found for " << doctorName << ".\n";
    }
}

void BookAppointment(string& name, string& email)
{
    string doctorName, time;
    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your email: ";
    getline(cin, email);


    cout << "Enter Doctor's Name: ";
    getline(cin, doctorName);
    cout << "Enter Date,Day & Time(e.g 01/jan/2025,monday,9:00pm): ";
    getline(cin, time);

    for (int i = 0; i < doctorCount; ++i)
    {
        if (doctors[i].name == doctorName && doctors[i].available)
        {
            appointments[appointmentCount++] = { name, email, doctorName, time };
            cout << "Appointment booked successfully!\n";
            return;
        }
    }
    cout << "Doctor not available.\n";
}

void editAppointment(string patientName)
{
    string oldTime, newTime;
    cout << "\nEnter current appointment time: ";
    cin >> oldTime;

    for (int i = 0; i < appointmentCount; ++i)
    {
        if (appointments[i].patientName == patientName && appointments[i].time == oldTime)
        {
            cout << "Enter new appointment time: ";
            cin >> newTime;
            appointments[i].time = newTime;
            cout << "Appointment updated successfully!\n";
            return;
        }
    }
    cout << "Appointment not found!\n";
}

void cancelAppointment(string patientName)
{
    string time;
    cout << "\nEnter appointment time to cancel: ";
    cin >> time;

    for (int i = 0; i < appointmentCount; ++i)
    {
        if (appointments[i].patientName == patientName && appointments[i].time == time)
        {
            for (int j = i; j < appointmentCount - 1; ++j)
            {
                appointments[j] = appointments[j + 1];
            }
            --appointmentCount;
            cout << "Appointment canceled successfully!\n";
            return;
        }
    }
    cout << "Appointment not found!\n";
}

int main()
{
    int choice;
    string username, password, name, email;

    initializeDoctors();
    initializeAppointments();

    while (true)
    {
        cout << "**********DOCTOR_APPOINTMENT_SYSTEM**********\n\nWho are you:\n1. Admin\n2. Doctor\n3. Patient\n4. Exit\n\Enter a number to proceed: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\nEnter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;
            if (username == "admin" && password == "iamadmin")
            {
                int adminChoice;
                do
                {
                    cout << "\n**********ADMIN_PANEL**********\n1. Add Doctor\n2. View All Appointments\n3. Show All Doctors\n4. Logout\nEnter a number to proceed: ";
                    cin >> adminChoice;

                    if (adminChoice == 1)
                    {
                        addDoctor();
                    }
                    else if (adminChoice == 2)
                    {
                        viewAllAppointments();
                    }
                    else if (adminChoice == 3)
                    {
                        showDoctors();
                    }
                    else if (adminChoice == 4)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid option.\n";
                    }
                } while (true);
            }
            else
            {
                cout << "Invalid credentials.\n";
            }
        }
        else if (choice == 2)
        {
            string doctorName;
            cout << "\nEnter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            if (doctorLogin(username, password, doctorName))
            {
                int doctorChoice;
                do
                {
                    cout << "\n**********DOCTOR_PANEL**********\n1. Edit Info\n2. Set Availability\n3. View Appointments\n4. Logout\nEnter choice: ";
                    cin >> doctorChoice;

                    if (doctorChoice == 1)
                    {
                        editDoctorInfo(doctorName);
                    }
                    else if (doctorChoice == 2)
                    {
                        bool available;
                        cout << "Enter availability (1 for available, 0 for unavailable): ";
                        cin >> available;
                        setAvailability(doctorName, available);
                    }
                    else if (doctorChoice == 3)
                    {
                        viewAppointments(doctorName);
                    }
                    else if (doctorChoice == 4)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid option.\n";
                    }
                } while (true);
            }
            else
            {
                cout << "Invalid credentials.\n";
            }
        }
        else if (choice == 3)
        {
            int patientChoice;
            do
            {
                cout << "\n**********PATIENT_PANEL**********\n1. Show All Doctors\n2. Book Appointment\n3. Edit Appointment\n4. Cancel Appointment\n5. Exit\nEnter choice: ";
                cin >> patientChoice;

                if (patientChoice == 1)
                {
                    showDoctors();
                }
                else if (patientChoice == 2)
                {
                    BookAppointment(name, email);
                }
                else if (patientChoice == 3)
                {
                    editAppointment(name);
                }
                else if (patientChoice == 4)
                {
                    cancelAppointment(name);
                }
                else if (patientChoice == 5)
                {
                    break;
                }
                else
                {
                    cout << "Invalid option.\n";
                }
            } while (true);
        }
        else if (choice == 4)
        {
            cout << "Exiting...\n";
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}