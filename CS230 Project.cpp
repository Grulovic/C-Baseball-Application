/* ------------------------------------------------------------------ *
 * Stefan Grulovic
 * DATE: 11/02/2017
 * TITLE: CS230 Project
 * DESCRIPTION: All the information is included in the word file that comes with this.
 * COPYRIGHT: Releases as open source code under the GNU public license agreement.
 * CONTACT: 20150280@student.act.edu
 * ------------------------------------------------------------------ */
//Following includes all the neaded libraries
#include<iostream>
#include<fstream>
#include <vector>
#include <iomanip>

using namespace std;
//------------------------------------------------------------------------------------------------------------//
//STRUCT/OBJECT DECLARATION: This struct is used to create objects that will be later used in the vector
struct player{
    string name; //name_lastname(initial)
    int g;       //games
    int hr;      //home_runs
    int so;      //strikeouts
    double hrg;  //home_runs per game
    double sog;  //strikeouts per game

    //Struct constructors
    player(){};//empty consturctor
    player(string player_name, int player_g, int player_hr, int player_so, double player_hrg, double player_sog){//with values constructor
        name = player_name;
        g = player_g;
        hr = player_hr;
        so = player_so;
        hrg = player_hrg;
        sog = player_sog;
    };
    //Struct functions
    void display(){
        cout<<left<<setw(15)<< name <<setw(8) << g <<setw(8) << hr <<setw(8) << so <<setw(8) << setprecision(2) << hrg <<setw(10) <<  setprecision(2) << sog <<endl;
    };
    void set_hrg(){//calculates the home runs per game
        hrg =  (double)hr / (double)g;
    }
    void set_sog(){//calculates the strikeouts per game
        sog = (double)so / (double)g;
    }
    
};
//------------------------------------------------------------------------------------------------------------//
//FUNTIONS DECLARATION:
void swap_players( player& player1, player& player2);
void sort_vector(vector<player>& vector, int sort, char asc_or_dsc);
void limit_search(vector<player> vector, int column, double limit);
void display_vector( string table_name, vector<player> vector);

//------------------------------------------------------------------------------------------------------------//
//MAIN FUNCTION:
int main(){
    //VARIABLE DECLARATION
    //menu
    int option;
    
    vector <player> player_list; //vector for storing the player objects
    
    bool option3_check = true, option1_check = true; //boolean checks if the user first did what was required for the requested option to work
    
//MENU:
    do{ //do while loop for the menu with 6 options
        cout <<"\n\n\n\n";
        cout <<"__________________________________________________\n";
        cout <<"MENU: \n";
        cout <<"__________________________________________________\n";
        cout << "1)  Read player data from a file. " << endl;
        cout << "2)  Search players by stat limit." << endl;
        cout << "3)  Calculate home runs and strikeouts per game." << endl;
        cout << "4)  Sort player data." << endl;
        cout << "5)  Export player data to file. " << endl;
        cout << "6)  EXIT." << endl;
        cout<<"__________________________________________________\n" ;
        
        do{
        cout << "Please select an option : ";
        cin >> option;
        }while(option<=0 || option>6);
        
//OPTION 1:
        if(option == 1){//Following ask the user for the file that will be read and its data stored into the vector
            
            cout<<"\n\n\n\n";
            //Variable declaration
            string temp_name, imported_file_name;
            int temp_g, temp_hr, temp_so;
            
            
            cout<<"Please enter the name, extension and the directory of the file: ";
            cin>>imported_file_name;
            fstream file ( imported_file_name.c_str() );
            
            if(file.is_open()){
                if(file.is_open()){
                    while(file.good()){
                        for(int i=0; i<12; i++){
                        file>>temp_name>>temp_g>>temp_hr>>temp_so;//Reads the file in specific pattern and stores values in temp variables
                        player_list.push_back(player(temp_name, temp_g, temp_hr, temp_so, 0, 0));//Then uses the data inside a constructor in order to create new
                                                                                                //objects which are then stored in a vector
                        }
                    }
                }
            
            }else cout<<"\nUNABLE TO OPEN FILE!\n";
            
            cout<<"______________________________________________________\n";
            cout<<"\nDATA SUCCESSFULLY INPUTED!\n";
            cout<<"______________________________________________________\n";

            
            display_vector("\nINPUTED DATA: ", player_list);//Function for displaying the data from the vector
            
            
            option1_check = false;
//OPTION 2:
        }else if(option == 2){//Following option shows the players that are in the user specified column lower limit
            
            cout<<"\n\n\n\n";
            
            if(option1_check){//Checks wether the user has inputed data in order for this option to work
                cout<<"In order for this option to work first go to option 1! ";
                continue;
            }
            //Variable declaration
            int limit_menu;
            string limit_menu_string;
            double limit;
            
            cout<<"__________________________________________________\n";
            cout<<"LIMIT SEARCH MENU: \n";
            cout<<"__________________________________________________\n";
            cout<<"1 - G (Games) \n2 - HR (Home runs) \n3 - SO (Strikeouts) \n4 - HR/G (Home runs per game) \n5 - SO/G (Strikeouts per game) \n";
            
            do{
            cout<<"\nPlease enter by which stat you want to limit search: ";
            cin>>limit_menu;//Ask the user for the option/column that will be sent later to a function
            }while(limit_menu <= 0 || limit_menu > 5);
            
            if(option3_check && (limit_menu == 4 || limit_menu == 5 ) ){//Checks wether the user has calculated the required data in order for sorting to work
                cout<<"In order to search by this stat you need to first go to option 3! ";
                continue;
            }
            
            do
			{cout<<"Please enter the limit: ";//Asks the user for the limit of the search that will be sent later to a function
            cin>>limit;
			}while(limit < 0);
            
            switch(limit_menu){//Menu that calls the limit_search function with specific options
                case 1:
                    limit_search(player_list, 1, limit);
                    break;
                case 2:
                    limit_search(player_list, 2, limit);
                    break;
                case 3:
                    limit_search(player_list, 3, limit);
                    break;
                case 4:
                    limit_search(player_list, 4, limit);
                    break;
                case 5:
                    limit_search(player_list, 5, limit);
                    break;
                default:
                    cout<<"Wrong or not avilable input.\nPlease enter by which stat you want to limit search: ";
                    cin>>limit_menu;
                    break;
                    
            }
//OPTION 3:
        }else if(option == 3){//Following option calculates the empty field of the vector objects
            
            cout<<"\n\n\n\n";
            
            if(option1_check){//Checks wether the user has inputed data in order for this option to work
                cout<<"In order for this option to work first go to option 1! ";
                continue;
            }
            
            for(int i=0; i<player_list.size(); i++){//Calls the funtions from player object to calculate the empty fields
                player_list[i].set_hrg();
                player_list[i].set_sog();
            }
            
            cout<<"______________________________________________________\n";
            cout<<"\nDATA SUCCESSFULLY CALCULATED!\n";
            cout<<"______________________________________________________\n";
            
            display_vector("\nCALCULATED DATA: ", player_list);//Function for displaying the data from the vector
            
            option3_check = false;
//OPTION 4:
        }else if(option == 4){// Following option sorts the vector objects in the user specified column data order
            
            cout<<"\n\n\n\n";
            
            if(option1_check){//Checks wether the user has inputed data in order for this option to work
                cout<<"In order for this option to work first go to option 1! ";
                continue;
            }
            //Variable declaration
            int sort_menu;
            char asc_or_dsc;
            
            cout<<"__________________________________________________\n";
            cout<<"SORTING: \n";
            cout<<"__________________________________________________\n";
            cout<<"1 - Player\n2 - G (Games) \n3 - HR (Home runs) \n4 - SO (Strikeouts) \n5 - HR/G (Home runs per game) \n6 - SO/G (Strikeouts per game) \n";
            
            do{
            cout<<"\nBy which stat you want to sort: ";
            cin>>sort_menu;//Ask the user for the option/column that will be sent later to a function
            }while(sort_menu <= 0 || sort_menu > 6);
            
            if(option3_check && (sort_menu == 5 || sort_menu == 6 ) ){//Checks wether the user has calculated the required data in order for sorting to work
                cout<<"In order to search by this stat you need to first go to option 3! ";
                continue;
            }
            
            do{
            cout<<"Ascending (A) or Descending (D) ? ";//Asks the user for the ascending or descending order that will be sent later to a function
            cin >> asc_or_dsc;
            }while( asc_or_dsc != 'a' && asc_or_dsc != 'A' && asc_or_dsc != 'd' && asc_or_dsc != 'D' );
            
            switch(sort_menu){//Menu that calls the sort_vector function with specific options
                case 1:
                        sort_vector(player_list, 1, asc_or_dsc);
                    break;
                case 2:
                        sort_vector(player_list, 2, asc_or_dsc);
                    break;
                case 3:
                        sort_vector(player_list, 3, asc_or_dsc);
                    break;
                case 4:
                        sort_vector(player_list, 4, asc_or_dsc);
                    break;
                case 5:
                        sort_vector(player_list, 5, asc_or_dsc);
                    
                    break;
                case 6:
                        sort_vector(player_list, 6, asc_or_dsc);
                    
                    break;
                default:
                    cout<<"Wrong or not avilable input.\nPlease enter again: ";
                    cin>>sort_menu;
                    break;
            }
            
            
            
            cout<<"______________________________________________________\n";
            cout<<"\nDATA SUCCESSFULLY SORTED!\n";
            cout<<"______________________________________________________\n\n";
            
            display_vector("\nSORTED DATA:" , player_list);
//OPTION 5:
        }else if(option == 5){//Following option ask the user for the file where the vector data will be exported
            
            cout<<"\n\n\n\n";
            //Variable declaration
            string exported_file_name;
            
            if(option1_check){//Checks wether the user has inputed data in order for this option to work
                cout<<"In order for this option to work first go to option 1! ";
                continue;
            }
            
            cout<<"Please enter the name, extension and the directory of the file: ";
            cin>>exported_file_name;
            ofstream exported_file ( exported_file_name.c_str() );
            
            if(exported_file.is_open()){
                for(int i=0; i<player_list.size(); i++){
                    exported_file<<player_list[i].name<<" "<<player_list[i].g<<" "<<player_list[i].hr<<" "<<player_list[i].so<<" "<<player_list[i].hrg<<" "<<player_list[i].sog<<"\n"; //Exports the data to a user specified file
                }
            }else cout<<"\nUNABLE TO EXPORT DATA!\n";
            
            cout<<"______________________________________________________\n";
            cout<<"\nDATA SUCCESSFULLY EXPORTED!\n";
            cout<<"______________________________________________________\n";

            
            display_vector("\nEXPORTED DATA: ", player_list);//Function for displaying the data from the vector
        
        }
    }while(option != 6);
    
//EXIT
    system("PAUSE");
    return 0;
}
//------------------------------------------------------------------------------------------------------------//
//FUNCTIONS:
//------------------------------------------------------------------------------------------------------------//
//Function for swapping two players information
void swap_players( player& player1, player& player2){
    player temp_player;
    
    temp_player = player1;
    player1 = player2;
    player2 = temp_player;
}
//------------------------------------------------------------------------------------------------------------//
//Function for displaying the vector in a table format with coresponding column names
void display_vector( string table_name, vector<player> vector){
    
    cout<< table_name;//Displays the user specified name for the table
    cout<<"\n______________________________________________________\n";
    cout<<left<<setw(15)<<"Player"<<left<<setw(8)<<"G"<<left<<setw(8)<<"HR"<<left<<setw(8)<<"SO"<<left<<setw(8)<<"HR/G"<<left<<setw(10)<<"SO/G"<<endl;
    cout<<"______________________________________________________\n";
    
    for(int i=0; i<vector.size(); i++){
        vector[i].display();
    }
    
    cout<<"______________________________________________________\n";
}

//------------------------------------------------------------------------------------------------------------//
//Funtion for showing the vector elements that are in the column limit of the limit search
void limit_search(vector<player> vector, int column, double limit){
    
    cout<<"\nLIMIT SEARCH: \n";
    cout<<"______________________________________________________\n";
    cout<<left<<setw(15)<<"Player"<<left<<setw(8)<<"G"<<left<<setw(8)<<"HR"<<left<<setw(8)<<"SO"<<left<<setw(8)<<"HR/G"<<left<<setw(8)<<"SO/G"<<endl;
    cout<<"______________________________________________________\n";
    
    for(int i=0; i<vector.size(); i++){
        
        if(column==1 && (vector[i].g > limit) ){//Check wether the players stat is in the range
            vector[i].display();                //if so it then displays it using the display method from the struct player
        }
        else if (column==2 && (vector[i].hr > limit) ){
            vector[i].display();
        }
        else if (column==3 && (vector[i].so > limit) ){
            vector[i].display();
        }
        else if (column==4 && (vector[i].hrg > limit) ){
            vector[i].display();
        }
        else if (column==5 && (vector[i].sog > limit) ){
            vector[i].display();
        }
    }
    cout<<"______________________________________________________"<<endl;
}
//------------------------------------------------------------------------------------------------------------//
//Function for sorting the vector by column in an ascending or desceding order
void sort_vector(vector<player>& vector, int sort, char asc_or_dsc){
    //Following is sorting for each column in ascending order
    if( asc_or_dsc == 'a' || asc_or_dsc == 'A'){
        
        for(int i=0; i<vector.size(); i++){//Two loops for comparing the two values
            for(int j=i+1; j<vector.size(); j++){
                if( sort==1 && ( vector[i].name > vector[j].name ) ){//It uses a specific column compares the two values and if true swaps the two players
                    swap_players(vector[i], vector[j]);                //by using the swap_players method
                }
                else if( sort==2 && ( vector[i].g > vector[j].g ) ){
                    swap_players(vector[i], vector[j]);
                }
                else if( sort==3 && ( vector[i].hr > vector[j].hr ) ){
                    swap_players(vector[i], vector[j]);
                }
                else if( sort==4 && ( vector[i].so > vector[j].so ) ){
                    swap_players(vector[i], vector[j]);
                }
                else if( sort==5 && ( vector[i].hrg > vector[j].hrg ) ){
                    swap_players(vector[i], vector[j]);
                }
                else if( sort==6 && ( vector[i].sog > vector[j].sog ) ){
                    swap_players(vector[i], vector[j]);
                }
            }
        }
    //Following is sorting for each column in descending order
    }else if (asc_or_dsc == 'd' || asc_or_dsc == 'D'){
        
        for(int i=0; i<vector.size(); i++){//Two loops for comparing the two values
            for(int j=i+1; j<vector.size(); j++){
                if( sort==1 && ( vector[i].name < vector[j].name ) ){//It uses a specific column compares the two values and if true swaps the two players
                    swap_players(vector[i], vector[j]);                //by using the swap_players method
                }
                else if( sort==2 && ( vector[i].g < vector[j].g ) ){
                    swap_players(vector[i], vector[j]);
                }
                else if( sort==3 && ( vector[i].hr < vector[j].hr ) ){
                    swap_players(vector[i], vector[j]);
                }
                else if( sort==4 && ( vector[i].so < vector[j].so ) ){
                    swap_players(vector[i], vector[j]);
                }
                else if( sort==5 && ( vector[i].hrg < vector[j].hrg ) ){
                    swap_players(vector[i], vector[j]);
                }
                else if( sort==6 && ( vector[i].sog < vector[j].sog ) ){
                    swap_players(vector[i], vector[j]);
                }
            }
        }
        
    }
    
}
//------------------------------------------------------------------------------------------------------------//
