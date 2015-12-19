/***********************************************************
 ** Author: Carlos Carrillo                                *
 ** Date:   11/25/2015                                     *
 ** Description: This program runs 2 simulations. In one,  *
 *  it will have people arriving and being put into a      *
 *  single queue. Each time “click” it pull out one for    *
 *  each server. If there are fewer people then servers,   *
 *  some of the servers are unused. In the other           *
 *  simulation you have one queue per server. Every time   *
 *  click you will put people into the queues. Every       *
 *  time click you will take one person out of each queue. *
 **********************************************************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <queue>

using namespace std;

int varyArrivals(int, int);
int simulation2(int);
queue<int> iQueue; // STL queue container adapter.
int intValid(); // input validation function prototype

int main()
{
    int extraCustomer;
    int servers;
    int clients;
    int choice;
    double duration1;
    double duration2;
    
    cout<<"\n*** WELCOME TO THE PROGRAM ***\n"<<endl;
    cout <<"How many servers (N) would you like? ";
    servers = intValid();
    
    do
    {
        do
        {
            //main menu
            cout<<"\n**PLEASE SELECT ONE OF THE NEXT OPTIONS**\n"<<endl;
            cout<<"Enter 1 to simulate one line FOR n servers." <<endl;
            cout<<"Enter 2 to simulate one line PER EACH server." <<endl;
            cout<<"Enter 3 to EXIT the program." <<endl;
            
            cout<<"\nNOTE: Run BOTH simulations to see the time process difference." <<endl;
            
            //Prompt the user to enter an option from the menu
            cout << "\nPlease enter your option: ";
            choice = intValid();; //take the input value
            cout <<endl;
            
            if(choice == 1) //simulate one line FOR n servers.
            {
                std::clock_t start = std::clock(); //initialize clock timer
                
                for (int i=1; i<8; i++){
                    
                    cout <<"\n***** FIRST SIMULATION: CYCLE #"<<i<<" STARTS! *****"<<endl;
                    
                    // call function to vary arrival rate according to the number of servers
                    clients = varyArrivals (servers, i);
                    cout <<"CUSTOMERS = "<<clients<<endl;
                    cout <<"SERVERS = "<<servers<<endl;
                    
                    // first step: Customers arrive to the line
                    cout << "\n*** CUSTOMERS START FORMING THE WAITING LINE!!... ***\n";
                    for (int j=1; j<clients+1; j++){
                        cout <<"Customer #"<<j<<" arrives! ";
                        iQueue.push(j);
                        cout <<endl;}
                    
                    // second step: customers are served
                    cout << "\n*** SERVERS START TAKING CARE OF THE CUSTOMERS... ***\n";
                    while(!iQueue.empty()){
                        cout <<"Customer #"<<iQueue.front()<<" has been served! " <<clients-1<<" customers left...";
                        iQueue.pop();
                        clients--;
                        cout <<endl;}
                    cout <<"\n***** FIRST SIMULATION: END OF CYCLE #"<<i<<" *****\n"<<endl;
                    system("sleep 1"); // delay for user to see the process
                }
                
                duration1 = (std::clock() - start)/(double)CLOCKS_PER_SEC; //stop clock timer
                cout <<"PROCESS TIME = "<<duration1<<endl; //time results
            }
            
            
            else if(choice == 2) //simulate one line PER EACH server.
            {
                std::clock_t start1 = std::clock(); //initialize clock timer
                
                for (int i=1; i<8; i++){
                    
                    cout <<"\n***** SECOND SIMULATION: CYCLE #"<<i<<" STARTS! *****"<<endl;
                    clients = varyArrivals (servers, i);
                    cout <<"CUSTOMERS = "<<clients<<endl;
                    cout <<"SERVERS = "<<servers<<endl;
                    
                    while (clients % servers != 0){
                        extraCustomer = 1;
                        cout <<"\n*** THERE IS AN EXTRA CUSTOMER FOR ONE OF THE SERVERS. ***"<<endl;
                        iQueue.push(extraCustomer);
                        cout <<"Lone Customer is being served..."<<endl;
                        cout <<"Lone Customer has been served! "<<clients-1<<" customers left...\n"<<endl;
                        iQueue.pop();
                        clients--;
                        extraCustomer++;}
                    
                    clients = (clients/servers);
                    cout <<"CUSTOMERS PER SERVER = "<<clients<<endl;
                    
                    for (int j=0; j<servers; j++){
                        simulation2(clients);}
                    cout <<"\n***** SECOND SIMULATION: END OF CYCLE #"<<i<<" *****\n"<<endl;
                    system("sleep 1"); // delay for user to see the process
                }
                
                duration2 = (std::clock() - start1)/(double)CLOCKS_PER_SEC; //stop clock timer
                cout <<"PROCESS TIME = "<<duration2<<endl; //time results
            }
            
            else if(choice == 3)//EXIT the program
            {
                return 0;
            }
            
            else if (!isdigit(choice)) //input validation
            {
                cout << "Invalid option entered. Try again!\n" << endl;
                return 0;
            }
            
            cout <<"\nPROCESS TIME FOR SIMULATION 1 = "<<(duration1)<<endl;
            cout <<"PROCESS TIME FOR SIMULATION 2 = "<<(duration2)<<endl;
            cout<<"\nNOTE: Run BOTH simulations to see the time process difference.\n" <<endl;
            
        }while(choice != 1 && choice != 2 && choice != 3 && choice != 4);
        
    }while(choice);
    
    return 0;
}

/*******************************************************************
 *                         simulation2                             *
 * This function creates a queue per each server used by the user. *
 * It also fills each queue up and then removes all its member.    *
 ******************************************************************/

int simulation2(int clientela)
{
    cout <<"\n*** CUSTOMERS START FORMING THE WAITING LINE!!... ***\n";
    for (int i = 1; i < clientela+1; i++){
        cout <<"Customer #"<<i<<" arrives! ";
        iQueue.push(i);
        cout <<endl;}
    
    cout <<"\n*** SERVER START TAKING CARE OF THE CUSTOMERS... ***\n";
    while(!iQueue.empty()){
        cout <<"Customer #"<<iQueue.front()<<" has been served! "<<clientela-1<<" customers left...";
        iQueue.pop();
        clientela--;
        cout <<endl;}
    
    return clientela;
}
    
/*******************************************************************
*                        varyArrivals                              *
* This function retuns different arrival rates according to the    *
* the number of servers. It increases the number of arrivals from  *
* "arrivals = (n - 2)" to "arrivals = ((n*3) + RDN)", and then     *
* decreases the arrivals from "arrivals = ((n*3) + RDN)" to        *
* "arrivals = (n - 2)".                                            *
*******************************************************************/
    
int varyArrivals(int n, int index)
{
    int random;
    int change;
    int output;
    
    if(index ==1){
        cout <<"\nSIMULATION WHEN CUSTOMERS = (N-2)"<<endl;
        output = (n - 2);}
    
    if(index ==2){
        cout <<"\nSIMULATION WHEN CUSTOMERS = (N)"<<endl;
        output = n;}
    
    if(index ==3){
        cout <<"\nSIMULATION WHEN CUSTOMERS = ((N * 2) + RND)"<<endl;
        change = (n * 2);
        random = (rand() % change) + 1;
        output = (change + random);}
    
    if(index ==4){
        cout <<"\nSIMULATION WHEN CUSTOMERS = ((N * 3) + RND)"<<endl;
        change = (n * 3);
        random = (rand() % change) + 1;
        output = (change + random);}
    
    if(index ==5){
        cout <<"\nSIMULATION WHEN CUSTOMERS = ((N * 2) + RND)"<<endl;
        change = (n * 2);
        random = (rand() % change) + 1;
        output = (change + random);}
    
    if(index ==6){
         cout <<"\nSIMULATION WHEN CUSTOMERS = (N)"<<endl;
        output = n;}
    
    if(index ==7){
        cout <<"\nSIMULATION WHEN CUSTOMERS = (N-2)"<<endl;
        output = (n - 2);}
    
    return output;
}

/*******************************************************************
 *                           intValid                              *
 * This function validates an integer input and displays an error  *
 * message to the user when an invalid input has been entered.     *
 * (borrowed from TA Ian).                                         *
 ******************************************************************/
int intValid()
{
    int input;
    std::cin >> input;
    
    while (true)
    { //loops until the right input comes
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(512, '\n');
            std::cout <<"Invalid option entered. Try again!\n";
            std::cin >> input;
        }
        else break;
    }
    return input;
}








