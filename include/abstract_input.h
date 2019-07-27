
#pragma once

#include <string>
#include <vector>
#include <parking_lot.h>

class AbstractInput {

private :

	ParkingLot parking_lot{nullptr};

public :
	void verifyCommand(std::string input) {
		using namespace std;
		vector <string> tokens; 
      
	    stringstream ss(input); 
	      
	    string intermediate; 
	      
	    // Tokenizing w.r.t. space ' ' 
	    while(getline(ss, intermediate, ' ')) 
	    { 
	        tokens.push_back(intermediate); 
	    }

	    int cmd_args = tokens.size();



	    if(cmd_args <= 1) {
	    	std::cout << "Wrong input of command" <<'\n';
	    	exit(EXIT_FAILURE);

	    } 
	    string command = tokens[0];


	    if (command.equals("create_parking_lot")) {  //Create

	    		if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			} 
			int noOfParkingSlots = stoi(tokens[1]);
			parking_lot = ParkingLot.createParkingLot(noOfPrakingSlots);
			break;

	    } else if (command.equals("park")) {  //Park

	    	if(cmd_args != 3) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			} 
			string reg_num = tokens[1];
			string color = tokens[2];

			if(parking_lot)
				parkinglot.park(reg_num, color);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			break;

	    } else if (command.equals("leave")) { //leave

	    	if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			} 
			int leave_slot = stoi(tokens[1]);

			if(parking_lot)
				parkinglot.leave(leave_slot);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			break;

	    } else if (command.equals("status")) {

	    	if(cmd_args != 1) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			}

			if(parking_lot)
				parkinglot.status();
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			break;

	    } else if (command.equals("registration_numbers_for_cars_with_colour")) {

	    	if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			}
			string color = tokens[1];
			if(parking_lot)
				parkinglot.reg_nums_with_color(color);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			break;

	    } else if (command.equals("slot_numbers_for_cars_with_colour")) {

	    	if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			}
			string color = tokens[1];
			if(parking_lot)
				parkinglot.slot_nums_with_color(color);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			break;

	    } else if (command.equals("slot_number_for_registration_number")) {

	    	if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			}
			string reg_num = tokens[1];
			if(parking_lot)
				parkinglot.slot_num_for_reg_num(color);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			break;

	    } else {

	    	std::cout << " Invalid command" <<std::endl;
	    	exit(EXIT_FAILURE);
	    }
	
	}


	void read() = 0; //pure virtual method to be implemented by the derived class of abstractinput
};