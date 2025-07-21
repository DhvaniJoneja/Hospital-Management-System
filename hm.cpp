#include<iostream>
#include<ncurses.h>
#include<menu.h>
#include<fstream>
#include<vector>
#include<cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

char* choices1[]= {
    "1.Management",
    "2.Doctor",
    "3.Patient",
    "4.Exit"
};
char* choices_m[] = {
    "1. Appointment",
    "2. Admission",
    "3. Exit management menu"
};
char* choices_dr[] = {
    "1. Jr. Doctor",
    "2. Specialist",
    "3. Exit Doctor menu"
};
char* choices_p[] = {
    "1. Prescription",
    "2. Test report",
    "3. Exit"
};
char* choices_ap[] = {
    "1. View Admission Details",
    "2. Admit Patient",
    "3. Exit"
};
char* options[] = {
    "Deluxe Room",
    "Super Deluxe Room",
    "Suite Room",
    "General Ward",
    "ICU Ward"
};
int password_check(string pass, string name);
int win_for_pass(string category);
class Doctor{
protected:
    char Dr_name[100];
public:
    int get_details(){
        int flag=0;
        char dr_name[100];
        WINDOW *win;
        int width = 42;
        int height = 10;
        int starty = (LINES-10)/2;
        int startx = (COLS-width)/2;
        win = newwin(height, width, starty, startx);
        keypad(win, TRUE);
        box(win, 0, 0);
        refresh();
        wrefresh(win);
        mvwprintw(win,2,1,"Enter Name : ");
        wrefresh(win);
        echo();
        wgetnstr(win, dr_name, 100);
        noecho();
        if(find_doctor(dr_name)) {
            strcpy(Dr_name, dr_name);
            mvwprintw(win, 6, 1, "Doctor found!!");
            wrefresh(win);
            napms(1200);
            werase(win);       
            wrefresh(win);    
            delwin(win);    
            flag = win_for_pass(Dr_name);
            return flag;
        } else {
            mvwprintw(win, 4, 1, "Doctor not found!!");
            wrefresh(win);
            napms(1200);
            werase(win);       
            wrefresh(win);    
            delwin(win);
            return flag;  
        }
    }
    int find_doctor(const string& doctor_name){
        ifstream file("doctor.txt");
        string line;
        string buffer;
        if(!file){    
            return 0;
        }
        while(getline(file,line, ',')){
            getline(file, buffer);
            if(line==doctor_name){
                return 1;
            }
        }
        return 0;
    }
};

class JrDoctor:public Doctor{
    private:
    string PatientName;
    public:
    int get_details(){
        int flag=0;
        char dr_name[100];
        WINDOW *win;
        int width = 42;
        int height = 10;
        int starty = (LINES-10)/2;
        int startx = (COLS-width)/2;
        win = newwin(height, width, starty, startx);
        keypad(win, TRUE);
        box(win, 0, 0);
        refresh();
        wrefresh(win);
        mvwprintw(win,2,1,"Enter Name : ");
        wrefresh(win);
        echo();
        wgetnstr(win, dr_name, 100);
        noecho();
        if(find_doctor(dr_name)) {
            strcpy(Dr_name, dr_name);
            mvwprintw(win, 6, 1, "Doctor found!!");
            wrefresh(win);
            napms(1200);
            werase(win);       
            wrefresh(win);    
            delwin(win);    
            flag = win_for_pass(Dr_name);
            return flag;
        } else {
            mvwprintw(win, 4, 1, "Doctor not found!!");
            wrefresh(win);
            napms(1200);
            werase(win);       
            wrefresh(win);    
            delwin(win);
            return flag;  
        }
    }
    void add_Bp(WINDOW *win){
        char p_name[100];
        mvwprintw(win, 3, 1, "Enter Patient name:");
        wrefresh(win);
        echo();
        wgetnstr(win, p_name, 99);
        noecho();
        PatientName = p_name;
        string FileName=PatientName+".txt";
        ifstream file(FileName);
        if(file.good()==0){
            mvwprintw(win, 8, 1, "File does not exist!!");
            wrefresh(win);
            napms(1200);
            file.close();
            return;
        }
        file.close();
        ofstream fout(FileName,ios::app);
        char BloodPressure[10],Pulse[10];
        mvwprintw(win, 5, 1, "Enter Blood Pressure:");
        wrefresh(win);
        echo();
        wgetnstr(win, BloodPressure, 9);
        noecho();
        mvwprintw(win, 7, 1, "Enter Pulse:");
        wrefresh(win);
        echo();
        wgetnstr(win, Pulse, 9);
        noecho();

        fout<<"Blood Pressure:"<<BloodPressure<<endl;
        fout<<"Pulse:"<<Pulse<<endl;
        fout.close();
        mvwprintw(win,9, 1, "Data Successfully added!!");
        wrefresh(win);
        napms(1200);
    }
    void jr_d_win() {
        WINDOW *win;
        int width = 50;
        int height = 15;
        int starty = (LINES-10)/2;
        int startx = (COLS-width)/2;
        win = newwin(height, width, starty, startx);
        keypad(win, TRUE);
        box(win, 0, 0);
        refresh();
        wrefresh(win);
        add_Bp(win);
        werase(win);
        wrefresh(win);
        delwin(win);
    }
    int find_doctor(const string& doctor_name){
        ifstream file("jr doctor.txt");
        string line;
        if(!file){    
            return 0;
        }
        while(getline(file,line)){
            if(line==doctor_name){
                return 1;
            }
        }
        return 0;
    }
};
char* specialities[] = {
    "Cardiologist",
    "Dermatologist",
    "Neurologist",
    "Pediatrician",
    "Orthopedic Surgeon",
    "Oncologist",
    "Psychiatrist",
    "Ophthalmologist",
    "Endocrinologist",
    "Gastroenterologist"
};
class Specialist: public Doctor{
public:
    string getPatientName(WINDOW *win) {
        string patientName;
        char pname[100];
        mvwprintw(win, 3, 1, "Enter patient name: ");
        wrefresh(win);
        echo();
        wgetnstr(win, pname, 99);
        noecho();
        patientName = (string) pname;
        return patientName;
    }
    bool patientFileExists(const string& patientName) { 
        string fileName = patientName + ".txt";
        ifstream file(fileName);
        if (file.is_open()) {
            file.close();
            return true;
        }
        return false;
    }
    void take_input(WINDOW *win) {
        string patient = getPatientName(win);
        if(patientFileExists(patient)) {
            char symptoms[100];
            mvwprintw(win, 5, 1, "Enter symptoms of patient (in csv format): ");
            wrefresh(win);
            echo();
            wgetnstr(win, symptoms, 99);
            noecho();
            string symp = (string) symptoms;
            recordSymptoms(patient, symp);
            char diag[100];
            mvwprintw(win, 7, 1, "Enter the diagnosis of patient: ");
            wrefresh(win);
            echo();
            wgetnstr(win, diag, 99);
            noecho();
            string diagnosis = (string) diag;
            recordSymptoms(patient, diagnosis);

            char t[100];
            mvwprintw(win, 9, 1, "Enter tests that patient needs to get done (in csv format, nil for no tests): ");
            wrefresh(win);
            echo();
            wgetnstr(win, t, 99);
            noecho();
            string tests = (string) t;
            recordTests(patient, tests);
        }
    }
    void recordSymptoms(const string& patientName, const string& symptoms) {
        string fileName = patientName + ".txt";
        ofstream file(fileName, ios::app);
        if (!file) {
            return;
        }
        file << symptoms << endl;
        file.close();
    }
    void recordDiagnosis (const string& patientName, const string& diagnosis){
        string fileName= patientName + ".txt";
        ofstream file(fileName, ios::app);
        if (!file){
            return;
        }
        file<< diagnosis<<endl;
        file.close(); 
    }
    void recordTests (const string& patientName, const string& tests){
        string fileName= patientName + ".txt";
        ofstream file(fileName, ios::app);
        if (!file){
            return;
        }
        file<< tests <<endl;
        file.close(); 
    }
    
    void sp_d_win() {
        WINDOW *win;
        int width = COLS - 8;
        int height = LINES - 8;
        int starty = (LINES-height)/2;
        int startx = (COLS-width)/2;
        win = newwin(height, width, starty, startx);
        keypad(win, TRUE);
        box(win, 0, 0);
        refresh();
        wrefresh(win);
        string heading = "PRESCRIPTION";
        int headingx = (width - heading.size())/2;
        mvwprintw(win, 1, headingx, "PRESCRIPTION");
        mvwhline(win, 2, 1, 0, width-2);
        wrefresh(win);
        take_input(win);
        werase(win);
        wrefresh(win);
        delwin(win);
    }
};
void win1_for_management();
void win1_for_doctor();
void win3_for_management();
void win1_for_patient();
void win2_for_patient(string patientName);
void test_report(WINDOW *win, string patientName);
void prescription(WINDOW *win, string patientName, WINDOW* win2);
void viewAdmissionDetails(vector<char*>&app);
void menu_for_ad_det(WINDOW *win);
void Admission(WINDOW *win) ;
void generateBill(string patientName, string roomType, int roomNumber, int days, int costPerDay) ;
void updateAdmissionDetails(string patientName, int roomNumber);
bool check_test(string patientName);
bool check_admit(float hb, float tlc, float pcv);
void win2_for_management(WINDOW *win);

class Appointment {
    string patient_name;
    char password[10];
    string speciality;
    string Dr_name;
public:
    void get_details(WINDOW  *win) {
        char n[101];
        mvwprintw(win, 2,1,"Enter patient name : ");
        wrefresh(win);
        wgetnstr(win, n, 100);
        patient_name= string(n);
        mvwprintw(win, 4, 1, "Which speciality doctor to be consulted?");
        wrefresh(win);
        int n_choices;
        n_choices = ARRAY_SIZE(specialities);
        ITEM **items;
        MENU *menu;
        items = new ITEM*[n_choices+1];
        for(int i=0; i<n_choices; i++) {
            items[i] = new_item(specialities[i], "");
        }
        items[n_choices] = NULL;
        menu = new_menu(items);
        set_menu_win(menu, win);
        set_menu_sub(menu, derwin(win,15,20, 5, 1));
        set_menu_mark(menu, "->");
        post_menu(menu);
        wrefresh(win);
        int ch;
        int flag=1;
        while(flag) {
            ch=wgetch(win);
            switch(ch) {
                case KEY_DOWN:
                    menu_driver(menu, REQ_DOWN_ITEM);
                    break;
                case KEY_UP:
                    menu_driver(menu, REQ_UP_ITEM);
                    break;
                case 10: 
                    speciality = item_name(current_item(menu));
                    flag=0;
                    break;
            }
        }
        unpost_menu(menu);
        free_menu(menu);
        for (int i = 0; i < n_choices; ++i) {
            free_item(items[i]);
        }
        delete[] items;
    }
    int find_doctors(vector<char*>& names) {
        fstream fio;
        fio.open("doctor.txt");
        string dr_name;
        string sp;
        int slots;
        int flag=0;
        while(fio.good()) {
            getline(fio, dr_name, ',');
            getline(fio, sp, ',');
            fio>>slots;
            fio.get();
            char* n;
            if(speciality==sp && slots>0) {
                n = new char[dr_name.size()+1];
                strcpy(n, dr_name.c_str());
                names.push_back(n);
                flag = 1;
            }
        }
        if (flag==1) {
            return 1;
        }  
        else if(flag==0) {
            return 0;
        }
        fio.close();
        return 0;
    }
    void choose_doctor(string n, WINDOW *win, WINDOW *win1) {
        fstream fio;
        fio.open("doctor.txt");
        string dr;
        string sp;
        int slots;
        Dr_name = n;
        while(fio.good()) {
            getline(fio, dr, ',');
            getline(fio, sp, ',');
            fio>>slots;
            fio.get();
            if(sp==speciality) {
                if(dr==Dr_name) {
                    if(slots>0) {
                        for (int i = 5; i < 10; ++i) {
                            wmove(win, i, 1);
                            for (int j = 0; j < 25; ++j) {
                                waddch(win, ' ');
                            }
                        }
                        wmove(win, 4, 1);
                        int condition = strlen("Which speciality doctor to be consulted?");
                        for(int i=0; i<condition; i++) {
                            waddch(win, ' ');
                        }                
                        mvwprintw(win, 4, 1, "Appointment Booked Successfully!!");
                        mvwprintw(win, 6, 1, "Enter password to access file : " );
                        wrefresh(win);
                        echo();
                        wgetnstr(win, password, 10);
                        noecho();
                        wrefresh(win);
                        ofstream fout;
                        fout.open("passwords.txt", ios::app);
                        fout<<"\n";
                        fout<<patient_name;
                        fout<<",";
                        fout<<password;
                        ofstream fo;
                        fo.open(patient_name + ".txt");
                        fo<<patient_name;
                        fo<<",";
                        fo<<Dr_name<<endl;
                        fo.close();
                        fout.close();
                        fio.close();
                        Decrease_slots(Dr_name, speciality);
                        mvwprintw(win, 8, 1, "Added successfully!!");
                        werase(win);
                        wrefresh(win);
                        delwin(win);    
                        touchwin(win1);
                        wrefresh(win1);
                        return;
                    }
                } 
            }
        }
        fio.close();
    }
    void Decrease_slots(string dr_name, string speciality) {
        ifstream myfile;
        myfile.open("doctor.txt");
        ofstream temp;
        temp.open("tempfile.txt");
        string dr, sp;
        int slots;
        while(getline(myfile, dr, ',')) {
            getline(myfile, sp, ',');
            myfile>>slots;
            myfile.get();
            if(dr==dr_name) {
                if(sp==speciality) {
                    slots-=1;
                }
            }
            temp<<dr<<","<<sp<<","<<slots<<endl;
        }
        remove("doctor.txt");
        rename("tempfile.txt", "doctor.txt");
    }
};
void win2_for_management(WINDOW *win) {
    WINDOW *win_m;
    ITEM **items;
    MENU *menu;
    int n_choices;
    int height, width;
    height = LINES-4;
    width = COLS - 4;
    int startx, starty;
    startx = 2;
    starty = 2;
    win_m = newwin(height, width, starty, startx);
    keypad(win_m, TRUE);
    box(win_m, 0, 0);
    refresh();
    wrefresh(win_m);
    echo();
    Appointment app;
    app.get_details(win_m);
    noecho();
    vector<char*> names;
    if(app.find_doctors(names)){
        n_choices = names.size();
        items = new ITEM*[n_choices+1];
        for(int i=0; i<n_choices; i++) {
            items[i] = new_item(names[i], "");
        }
        items[n_choices] = NULL;
        wmove(win_m,4, 1);
        int condition = strlen("Which speciality doctor to be consulted?");
        for(int i=0; i<condition; i++) {
            waddch(win_m, ' ');
        } 
        mvwprintw(win_m, 4,1, "Available Doctors: ");
        wrefresh(win_m);
        menu = new_menu(items);
        set_menu_win(menu, win_m);
        set_menu_sub(menu, derwin(win_m,5,25, 5, 1));
        set_menu_mark(menu, "->");
        post_menu(menu);
        wrefresh(win_m);
        int ch;
        int flag=1;
        while((ch = wgetch(win_m))!=27 && flag!=0) {
            switch(ch) {
                case KEY_DOWN : 
                    menu_driver(menu, REQ_DOWN_ITEM);
                    break;
                case KEY_UP : 
                    menu_driver(menu, REQ_UP_ITEM);
                    break;
                case 10 : 
                    const char* selected = item_name(current_item(menu));
                    string dr_name(selected);
                    unpost_menu(menu);
                    free_menu(menu);        
                    app.choose_doctor(dr_name, win_m, win);
                    flag=0;
                    break;
            }
        }
        for (int i = 0; i < n_choices; ++i) {
            free_item(items[i]);
        }
        delete[] items;
        for (int i = 0; i < n_choices; ++i) {
            delete[] names[i]; 
        }
    } else {
        for (int i = 5; i < 10; ++i) {
            wmove(win_m, i, 1);
            for (int j = 0; j < 25; ++j) {
                waddch(win_m, ' ');
            }
        }
        wmove(win_m, 4, 1);
        int condition = strlen("Which speciality doctor to be consulted?");
        for(int i=0; i<condition; i++) {
            waddch(win_m, ' ');
        }
        mvwprintw(win_m, 4,1, "Doctor not found!! Exitting..");
        wrefresh(win_m);
        napms(1200);
        werase(win_m);
        wrefresh(win_m);
        delwin(win_m);
    }
}
int password_check(string pass, string name) {
    ifstream input;
    input.open("passwords.txt");
    string password;
    string buffer;
    int flag=1;
    while(input) {
        getline(input,buffer,',');
        if(buffer==name) 
            flag=1;
        else 
            flag=0;
        if(flag==0) {
            getline(input,buffer);
        } else {
            getline(input, password);
            break;
        }
    }
    input.close();
    if(password==pass) {
        return 1;
    } else {
        return 0;
    }
}
int main() {
    srand(time(0));

    WINDOW *intro;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);

    int height = 10;
    int width = 45;
    int sty = (LINES - height) / 2;
    int stx = (COLS - width) / 2;
    
    intro = newwin(height, width, sty, stx);
    keypad(intro, TRUE);
    box(intro, 0, 0);
    refresh();
    wrefresh(intro);
    mvwprintw(intro, 2 ,(45/2) - 5, "WELCOME TO");
    mvwprintw(intro, 4, (45/2)-12, "HOSPITAL MANAGEMENT SYSTEM");
    mvwprintw(intro, 8, 2, "Entering...");
    wrefresh(intro);
    napms(1500);
    werase(intro);
    wrefresh(intro);
    delwin(intro);

    ITEM **items;
    MENU *menu;
    WINDOW *win;
    int n_choices;

    int width1 =40;
    int height1=8; 

    int startx=(COLS-width1)/2;
    int starty=(LINES-height1)/2;

    win=newwin(height1, width1, starty, startx);
    keypad(win, TRUE);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    n_choices = ARRAY_SIZE(choices1);
    items = new ITEM*[n_choices+1];
    for(int i=0; i<n_choices; i++) {
        items[i]=new_item(choices1[i], "");
    }
    items[n_choices] = NULL;

    menu = new_menu(items);
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win,5, 30, 1, 1));
    set_menu_mark(menu, "->");
    post_menu(menu);
    wrefresh(win);

    int flag=0;
    
    int ch;
    while((ch= wgetch(win))!= 27) {
        switch(ch) {
            case KEY_DOWN : 
                menu_driver(menu,REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10:
                string category;
                category = item_name(current_item(menu));
                if(category=="1.Management") {
                    flag = win_for_pass("management");
                    if(flag==1) {
                        win1_for_management();
                        touchwin(win);
                        wrefresh(win);
                    } else {
                        touchwin(win);
                        wrefresh(win);
                    }
                } else if(category=="2.Doctor") {
                    win1_for_doctor();
                    touchwin(win);
                    wrefresh(win);
                }
                else if(category=="3.Patient") {
                    win1_for_patient();
                    touchwin(win);
                    wrefresh(win);
                }
                else if (category=="4.Exit"){
                    endwin();
                    return 0;
                } 
        }
    }
    unpost_menu(menu);
    free_menu(menu);
    for (int i = 0; i < n_choices; i++) {
        free_item(items[i]);
    }
    delete[] items;
    endwin();

    return 0;
}
int win_for_pass(string category) {
    WINDOW *pass_win;
    int width = 42;
    int height = 10;
    int starty = (LINES-10)/2;
    int startx = (COLS-width)/2;
    pass_win = newwin(height, width, starty, startx);
    keypad(pass_win, TRUE);
    box(pass_win, 0, 0);
    refresh();
    wrefresh(pass_win);
    mvwprintw(pass_win,2,1,"Enter password : ");
    wrefresh(pass_win);
    int cur_x, cur_y;
    getyx(pass_win, cur_y, cur_x);
    char* pass = new char[20];
    int i = 0;
    int ch;
    while((ch = wgetch(pass_win))!='\n') {
        getyx(pass_win, cur_y, cur_x);
        if(ch==KEY_BACKSPACE || ch==127) {
            if(i>0) {
                i--;
                wmove(pass_win, cur_y, cur_x-1);
                waddch(pass_win, ' ');
                wmove(pass_win, cur_y, cur_x-1);
                wrefresh(pass_win);
            }
        } else {
            pass[i] = ch;
            mvwaddch(pass_win, cur_y, cur_x, '*');
            i++;
            wrefresh(pass_win);
        }
    }
    pass[i]='\0';
    int x = password_check(pass, category);
    if(x) {
        mvwprintw(pass_win, 7, 2, "Correct password. Granting access...");
        wrefresh(pass_win);
        napms(1000);
        werase(pass_win);
        wrefresh(pass_win);
        delwin(pass_win);
        return 1;
    } else {
        mvwprintw(pass_win, 7, 2, "Incorrect Password!! Exiting...");
        wrefresh(pass_win);
        napms(1200);
        werase(pass_win);
        wrefresh(pass_win);
        delwin(pass_win);
        return 0;
    }
}
void win1_for_management() {
    WINDOW *win;
    ITEM **items;
    MENU *menu;
    int n_choices;

    n_choices= ARRAY_SIZE(choices_m);
    items = new ITEM*[n_choices + 1];
    for(int i=0; i<n_choices; i++) {
        items[i] = new_item(choices_m[i], "");
    }
    items[n_choices]= NULL;

    int width = 42;
    int height = 10;
    int starty = (LINES-10)/2;
    int startx = (COLS-width)/2;
    win = newwin(height, width, starty, startx);
    keypad(win, TRUE);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    menu = new_menu(items);
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, 5 , 30, 3, 1));
    set_menu_mark(menu, "->");
    post_menu(menu);
    wrefresh(win);

    int ch;

    while((ch = wgetch(win))!=27) {
        switch(ch){
            case KEY_DOWN :
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP :
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10 :
                string item;
                item = item_name(current_item(menu));
                if(item == "1. Appointment") {
                    win2_for_management(win);
                    touchwin(win);
                    wrefresh(win);

                }
                else if(item=="2. Admission"){
                    win3_for_management();
                    touchwin(win);
                    wrefresh(win);
                } 
                else if(item== "3. Exit management menu") {
                    unpost_menu(menu);
                    free_menu(menu);
                    for (int i = 0; i < n_choices; i++) {
                        free_item(items[i]);
                    }
                    delete[] items;
                    werase(win);
                    wrefresh(win);
                    delwin(win);
                    return;          
                }
        }
    }
    unpost_menu(menu);
    free_menu(menu);
    for (int i = 0; i < n_choices; ++i) {
        free_item(items[i]);
    }
    delete[] items;
}

void win1_for_doctor() {
    WINDOW *win;
    ITEM **items;
    MENU *menu;
    int n_choices;
    int flag=0;

    n_choices= ARRAY_SIZE(choices_dr);
    items = new ITEM*[n_choices + 1];
    for(int i=0; i<n_choices; i++) {
        items[i] = new_item(choices_dr[i], "");
    }
    items[n_choices]= NULL;

    int width = 42;
    int height = 10;
    int starty = (LINES-10)/2;
    int startx = (COLS-width)/2;
    win = newwin(height, width, starty, startx);
    keypad(win, TRUE);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    menu = new_menu(items);
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, 5 , 30, 3, 1));
    set_menu_mark(menu, "->");
    post_menu(menu);
    wrefresh(win);
    string heading = "DOCTOR MENU";
    mvwprintw(win, 1, (width-heading.size())/2, "DOCTOR MENU");
    mvwhline(win, 2, 1, 0, width-2);
    wrefresh(win);

    int ch;

    while((ch = wgetch(win))!=27) {
        switch(ch){
            case KEY_DOWN :
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP :
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10 :
                string item;
                item = item_name(current_item(menu));
                if(item == "1. Jr. Doctor") {
                    JrDoctor d;
                    flag = d.get_details();
                    touchwin(win);
                    wrefresh(win);
                    if(flag) {
                        d.jr_d_win();
                        touchwin(win);
                        wrefresh(win);    
                    }

                }
                else if(item == "2. Specialist"){
                    Specialist d;
                    flag = d.get_details();
                    touchwin(win);
                    wrefresh(win);
                    if(flag) {
                        d.sp_d_win();
                        touchwin(win);
                        wrefresh(win);    
                    }
                }
                else if(item== "3. Exit Doctor menu") {
                    unpost_menu(menu);
                    free_menu(menu);
                    for (int i = 0; i < n_choices; i++) {
                        free_item(items[i]);
                    }
                    delete[] items;
                    werase(win);
                    wrefresh(win);
                    delwin(win);
                    return;          
                }
        }
    }
    unpost_menu(menu);
    free_menu(menu);
    for (int i = 0; i < n_choices; ++i) {
        free_item(items[i]);
    }
    delete[] items;
}
void win1_for_patient() {
    WINDOW *win;
    int width = 42;
    int height = 10;
    int starty = (LINES-10)/2;
    int startx = (COLS-width)/2;
    int flag=0;
    win = newwin(height, width, starty, startx);
    keypad(win, TRUE);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    mvwprintw(win,2,1,"Enter name : ");
    wrefresh(win);
    echo();
    char category[20];
    wgetnstr(win, category, 19);
    noecho();
    string patient_name = string(category);
    string filename = patient_name + ".txt";
    ifstream file;
    file.open(filename);
    if(file.good()) {
        file.close();
        flag = win_for_pass(category);
    } else {
        file.close();
        mvwprintw(win, 8, 1, "Patient does not exist!!");
        wrefresh(win);
        napms(1200);
        flag = 0;
    }
    if(flag) {
        win2_for_patient(patient_name);
    }
    werase(win);
    wrefresh(win);
    delwin(win);
}

void win2_for_patient(string patientName) {
    WINDOW *win1, *win2;
    int h1 = LINES -2;
    int h2 = h1;
    int width1 = 20;
    int width2 = COLS - 22;
    int starty1 = 1;
    int starty2 = starty1;
    int startx1 = 1;
    int startx2 = 22;
    win1 = newwin(h1, width1, starty1, startx1);
    keypad(win1, TRUE);
    box(win1, 0, 0);
    refresh();
    wrefresh(win1);
    win2 = newwin(h2, width2, starty2, startx2);
    keypad(win2, TRUE);
    box(win2, 0, 0);
    refresh();
    wrefresh(win2);

    ITEM **items;
    MENU *menu;
    int n_choices;

    n_choices = ARRAY_SIZE(choices_p);
    items = new ITEM*[n_choices+1];
    for(int i=0; i<n_choices; i++) {
        items[i] = new_item(choices_p[i], "");
    }
    items[n_choices] = NULL;

    menu = new_menu(items);
    set_menu_win(menu, win1);
    set_menu_sub(menu, derwin(win1, h1-4, 18, 2, 1));
    set_menu_mark(menu, "->");
    post_menu(menu);
    wrefresh(win1);
    int ch;
    while((ch=wgetch(win1))!=27) {
        switch(ch) {
            case KEY_UP :
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_DOWN :
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case 10 :
                string item;
                item = item_name(current_item(menu));
                if(item == "1. Prescription") {
                    prescription(win2, patientName, win1);
                    touchwin(win1);
                    wrefresh(win1);
                    post_menu(menu);
                    wrefresh(win1); 
                }
                else if(item == "2. Test report") {
                    test_report(win2, patientName);
                    touchwin(win1);
                    wrefresh(win1);
                    post_menu(menu);
                    wrefresh(win1); 
                }
                else if(item == "3. Exit") {
                    unpost_menu(menu);
                    free_menu(menu);
                    for (int i = 0; i < n_choices; i++) {
                        free_item(items[i]);
                    }
                    delete[] items;
                    werase(win1);
                    wrefresh(win1);
                    delwin(win1);
                    werase(win2);
                    wrefresh(win2);
                    delwin(win2);
                    return;          
                }
        }
    }
}
void win3_for_management() {
    WINDOW *heading, *win1, *win2;
    int height_h = 4;
    int width_h = COLS -1;
    int startx_h = 1;
    int starty_h = 1;
    heading = newwin(height_h, width_h, starty_h, startx_h);
    keypad(heading, TRUE);
    box(heading, 0, 0);
    refresh();
    wrefresh(heading);
    mvwprintw(heading, 1, (width_h/2)-9, "A D M I S S I O N");
    wrefresh(heading);
    int height1 = LINES - 7;
    int width1 = 30;
    int startx_1= 1;
    int starty_1= 5;
    win1= newwin(height1, width1, starty_1, startx_1);
    keypad(win1, TRUE);
    box(win1, 0, 0);
    refresh();
    wrefresh(win1);
    int height2 = LINES-7;
    int width2 = COLS - 32;
    int starty_2 = 5;
    int startx_2 = 32;
    win2= newwin(height2, width2, starty_2, startx_2);
    keypad(win2, TRUE);
    box(win2, 0, 0);
    refresh();
    wrefresh(win2);
    ITEM  **items;
    MENU *menu;
    int n_choices = ARRAY_SIZE(choices_ap);
    items = new ITEM*[n_choices+1];
    for(int i=0; i<n_choices; i++) {
        items[i] = new_item(choices_ap[i], "");
    }
    items[n_choices] = NULL;

    menu = new_menu(items);
    set_menu_win(menu, win1);
    set_menu_sub(menu, derwin(win1, height1-4, 28, 3, 1));
    set_menu_mark(menu, "->");
    post_menu(menu);
    wrefresh(win1);

    int ch;

    while((ch=wgetch(win1))!=27) {
        switch(ch) {
            case KEY_UP :
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_DOWN :
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case 10 :{
                string category;
                category = item_name(current_item(menu));
                if(category=="1. View Admission Details") {
                    menu_for_ad_det(win2);
                    touchwin(win1);
                    wrefresh(win1);
                    post_menu(menu);
                    wrefresh(win1); 
                }
                else if(category=="2. Admit Patient") {
                    Admission(win2);
                    touchwin(win1);
                    wrefresh(win1);
                    post_menu(menu);
                    wrefresh(win1); 
                }
                else if(category=="3. Exit") {
                    unpost_menu(menu);
                    free_menu(menu);
                    for (int i = 0; i < n_choices; i++) {
                        free_item(items[i]);
                    }
                    delete[] items;
                    werase(win1);
                    wrefresh(win1);
                    delwin(win1);
                    werase(win2);
                    wrefresh(win2);
                    delwin(win2);
                    werase(heading);
                    wrefresh(heading);
                    delwin(heading);
                    return;          
                }
            }
        }
    }
}

void menu_for_ad_det(WINDOW *win) {
    vector<char*> vec;
    viewAdmissionDetails(vec);
    ITEM  **items;
    MENU *menu;
    int n_choices = vec.size();
    items = new ITEM*[n_choices+1];
    for(int i=0; i<n_choices; i++) {
        items[i] = new_item(vec[i], "");
    }
    items[n_choices] = NULL;

    mvwprintw(win, 2, 2, "%s", "The admission details of patients are : ");
    menu = new_menu(items);
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, LINES-12, 40, 4, 2));
    set_menu_format(menu, 15, 1);
    set_menu_mark(menu, "->");
    post_menu(menu);
    wrefresh(win);
    mvwprintw(win, LINES-10, 2, "Press Esc key to return...");
    wrefresh(win);

    int ch;
    while((ch=wgetch(win))!=27) {
        switch(ch) {
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case 27:
                break;
        }
    }
    unpost_menu(menu);
    free_menu(menu);
    for (int i = 0; i < n_choices; ++i) {
        free_item(items[i]);
        delete[] vec[i]; 
    }
    delete[] items;

    werase(win);
    box(win, 0, 0);
    wrefresh(win);
}
void viewAdmissionDetails(vector<char*>&app) {
    ifstream fio;
    fio.open("admission_details.txt");
    string nm;
    while (getline(fio, nm)) { 
            char *n;
            n = new char [nm.size()+1];
            strcpy(n,nm.c_str());
            app.push_back(n);
    }
    fio.close();
}
void Admission(WINDOW *win) {

    char pname[100];
    string patientName;
    mvwprintw(win, 2, 2, "%s", "Enter Patient name : ");
    wrefresh(win);
    echo();
    wgetnstr(win, pname, 99);
    noecho();
    patientName = (string)pname;

    ifstream fin;
    fin.open(patientName+".txt");
    if(fin.is_open()) {
        fin.close();
        int days;
        char day[10];
        mvwprintw(win, 4, 2, "%s", "Enter the number of days : ");
        wrefresh(win);
        echo();
        wgetnstr(win, day, 9);
        noecho();
        days = atoi(day);
        mvwprintw(win, 6, 2, "%s", "Choose Room Type: ");
        string roomChoice;
        ITEM  **items;
        MENU *menu;
        int n_choices = ARRAY_SIZE(options);
        items = new ITEM*[n_choices+1];
        for(int i=0; i<n_choices; i++) {
            items[i] = new_item(options[i], "");
        }
        items[n_choices] = NULL;
    
        menu = new_menu(items);
        set_menu_win(menu, win);
        set_menu_sub(menu, derwin(win, 10, 60, 8, 2));
        set_menu_mark(menu, "->");
        post_menu(menu);
        wrefresh(win);
    
        int ch;
        int flag=1;
        while((ch=wgetch(win))!=27) {
            switch(ch) {
                case KEY_UP :
                    menu_driver(menu, REQ_UP_ITEM);
                    break;
                case KEY_DOWN :
                    menu_driver(menu, REQ_DOWN_ITEM);
                    break;
                case 10 :
                    if (current_item(menu)) {
                        const char* selected = item_name(current_item(menu));
                            if (selected) {
                                roomChoice = selected;
                            } else {
                                roomChoice = "";
                            }
                    } else {
                        roomChoice = "";
                    }
                    unpost_menu(menu);
                    free_menu(menu);
                    for (int i = 0; i < n_choices; ++i) {
                    free_item(items[i]);
                    }
                    delete[] items;
                    flag=0;
                    break;
            }
            if(flag==0) {
                break;
            }
        }
        if (roomChoice.empty()) {
            mvwprintw(win, 18, 2, "No room selected or invalid selection.");
            wrefresh(win);
            return;  
        }                    
        string roomType;
        int costPerDay = 0;
        int roomNumber = (rand() % 100) + 200;
        if(roomChoice=="1. Deluxe Room"){
            costPerDay = 5000;
            roomType = "Deluxe Room";
        }
        else if (roomChoice=="2. Super Deluxe Room"){
            costPerDay = 8000;
            roomType = "Super Deluxe Room";
        }
        else if(roomChoice=="3. Suite Room"){
            costPerDay = 12000;
            roomType= "Suite Room";
        }
        else if(roomChoice=="4. General Ward") {
            costPerDay=2000;
            roomType = "General Ward";
        }
        else if(roomChoice=="5. ICU Ward") {
            costPerDay=25000;
            roomType = "ICU Ward";
        }
        int total=costPerDay*days;
    
        ofstream outFile(patientName + ".txt",ios::app);
        if (outFile) {
            outFile << "Patient is admitted\n";
            outFile << "Room Type: " << roomType << endl;
            outFile << "Room No: " << roomNumber << endl;
            outFile.close();
            int n=days;
            updateAdmissionDetails(patientName, roomNumber);
        }
    
    } else {
        mvwprintw(win, 4, 2, "%s", "Patient not found!");
        wrefresh(win);
    }
    werase(win);
    box(win, 0, 0);
    wrefresh(win);

}
void updateAdmissionDetails(string patientName, int roomNumber) {
    ofstream admissionFile("admission_details.txt", ios::app);
    if (admissionFile) {
        admissionFile << patientName << " - Room " << roomNumber << endl;
        admissionFile.close();
    }
}
void generateBill(string patientName, string roomType, int roomNumber, int days, int costPerDay) {
    int totalCost = days * costPerDay;

    cout << "\n=== BILL DETAILS ===" << endl;
    cout << "Patient Name: " << patientName << endl;
    cout << "Room Type: " << roomType << endl;
    cout << "Room Number: " << roomNumber << endl;
    cout << "No. of Days: " << days << endl;
    cout << "Total Cost: ₹" << totalCost << endl;
}
void prescription(WINDOW *win, string patientName, WINDOW *win2) {
    ifstream fin;
    fin.open(patientName+".txt");
    string heading = "PRESCRIPTION";
    int headingx = (COLS-22 - heading.size())/2;
    mvwprintw(win, 1, headingx, "PRESCRIPTION");
    mvwhline(win, 2, 1, 0 , COLS-24);
    wrefresh(win);
    int lines = 1;
    string buffer;
    string line;
    int commas = 0;
    int items =0;
    int j=0;
    while(lines!=7) {
        switch(lines) {
            case 1:
                line = "Name : ";
                getline(fin, buffer, ',');
                line += buffer;
                mvwprintw(win, 4, 6, "%s", line.c_str());
                wrefresh(win);

                getline(fin, buffer);
                line = "Doctor's name : ";
                line+= buffer;
                mvwprintw(win, 4, 48, "%s", line.c_str());
                wrefresh(win);

                for (int i = 0; i < COLS-26; i++) {
                    if (i % 2 == 0) {
                        mvwaddch(win, 6, 2 + i, '-');
                    } else {
                        mvwaddch(win, 6, 2 + i, ' ');
                    }
                }
                wrefresh(win);
                lines+=1;
                break;
            case 2:
                getline(fin, line);
                mvwprintw(win, 8, 6, "%s", line.c_str());
                wrefresh(win);
                lines++;
                break;
            case 3:
                getline(fin, line);
                mvwprintw(win, 8, 48, "%s", line.c_str());
                wrefresh(win);
                lines++;
                break;
            case 4: {
                commas = 0;
                char ch= '\0';
                streampos pos = fin.tellg();
                ch = fin.get();
                while(ch!='\n') {
                    if(ch==','){
                    commas++;
                    }
                    ch = fin.get();
                }
                fin.seekg(pos);
                items = commas+1;
                line = "Symptoms : ";
                mvwprintw(win, 12, 6, "%s", line.c_str());
                wrefresh(win);
                for(int i=0; i<items; i++) {
                    if(i==items-1) {
                        getline(fin, line);
                        mvwprintw(win, 12+j, 18, "%s", line.c_str());
                        wrefresh(win);
                        j++;
                    } else {
                        getline(fin, line, ',');
                        mvwprintw(win, 12+j, 18, "%s", line.c_str());
                        wrefresh(win);
                        j++;
                    }
                }
                lines++;
                break; 
            }
            case 5:
                line = "Diagnosis : ";
                getline(fin, buffer);
                line+= buffer;
                mvwprintw(win, 12+j+3, 6, "%s", line.c_str());
                wrefresh(win);
                lines++;
                break;
            case 6:
                line = "Tests : ";
                getline(fin, buffer);
                line+=buffer;
                mvwprintw(win, 12+j+8, 6, "%s", line.c_str());
                wrefresh(win);
                lines++;
                break;
        }
    }
    fin.close();
    mvwprintw(win, LINES - 4, 4, "Press any key to return...");
    wrefresh(win);
    wgetch(win);  
    werase(win);
    box(win, 0, 0);
    wrefresh(win);
}
void test_report(WINDOW *win, string patientName) {
    ifstream fin;
    fin.open(patientName+".txt");
    string heading = "TEST REPORT";
    int headingx = (COLS-22 - heading.size())/2;
    mvwprintw(win, 1, headingx, "TEST REPORT");
    mvwhline(win, 2, 1, 0 , COLS-24);
    wrefresh(win);
    string line, buffer;
    line = "Name : ";
    getline(fin, buffer, ',');
    line += buffer;
    mvwprintw(win, 4, 6, "%s", line.c_str());
    wrefresh(win);

    getline(fin, buffer);
    line = "Doctor's name : ";
    line+= buffer;
    mvwprintw(win, 4, 48, "%s", line.c_str());
    wrefresh(win);

    for (int i = 0; i < COLS-26; i++) {
        if (i % 2 == 0) {
            mvwaddch(win, 6, 2 + i, '-');
        } else {
            mvwaddch(win, 6, 2 + i, ' ');
        }
    }
    wrefresh(win);
    int flag = check_test(patientName);
    if(flag==0) {
        mvwprintw(win, 8, 6, "Report not found");
    } else {
        float hb, pcv, tlc;
        hb = 10.0 + static_cast<float>(rand()) / RAND_MAX * 3.0;
        pcv = 30.0 + static_cast<float>(rand()) / RAND_MAX * 15.0;
        tlc = 12.0 + static_cast<float>(rand()) / RAND_MAX * 6.0;
        mvwprintw(win, 8, 6, "COMPLETE BLOOD COUNT(CBC)");
        mvwprintw(win, 10, 6, "Test Name");
        mvwprintw(win, 10, 36, "Result");
        mvwprintw(win, 10, 53, "Bio. Ref.interval");
        mvwprintw(win, 12, 6, "Haemoglobin");
        mvwprintw(win, 14, 6, "Packed cell Volume");
        mvwprintw(win, 16, 6, "Total Leukocyte count");
        mvwprintw(win, 12, 36, "%.2f", hb);
        mvwprintw(win, 14, 36, "%.2f",pcv);
        mvwprintw(win, 16, 36, "%.2f", tlc);
        mvwprintw(win, 12, 53, "13.00 - 17.00");
        mvwprintw(win, 14, 53, "40.00 - 50.00");
        mvwprintw(win, 16, 53, "4.00 - 10.00");
        wrefresh(win);
        if(check_admit(hb, tlc, pcv)) {
            int days = rand() % 4 + 2;
            mvwprintw(win, 25, 6, "Patient needs to be admitted for %d days", days);
        }
    }
    fin.close();
    mvwprintw(win, LINES - 4, 4, "Press any key to return...");
    wrefresh(win);
    wgetch(win);  
    werase(win);
    box(win, 0, 0);
    wrefresh(win);
}
bool check_test(string patientName) {
    ifstream fin;
    fin.open(patientName + ".txt");
    string buffer;
    int i=0;
    while(i!=5) {
        getline(fin, buffer);
        i++;
    }
    string line;
    getline(fin, line);
    fin.close();
    if(line=="nil") {
        return 0;
    } else {
        return 1;
    }
}
bool check_admit(float hb, float tlc, float pcv) {
    if(tlc>10.0 && pcv<40) {
        return 1;
    } else {
        return 0;
    }
}
