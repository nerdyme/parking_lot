
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "parking_lot.h"

class AbstractInput {

private :

	ParkingLot* parking_lot{nullptr};

public :

	virtual ~AbstractInput() {} //Destructor of base class should be made virtual

	void verifyCommand(std::string input) {
		
		std::vector<std::string> tokens; 
      
	    std::istringstream ss(input); 
	      
	    std::string intermediate; 
	      
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
	    std::string command = tokens[0];


	    if (command.compare("create_parking_lot")) {  //Create

	    		if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			} 
			int noOfParkingSlots = stoi(tokens[1]);
			parking_lot = ParkingLot::createParkingLot(noOfParkingSlots);
			

	    } else if (command.compare("park")) {  //Park

	    	if(cmd_args != 3) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			} 
			std::string reg_num = tokens[1];
			std::string color = tokens[2];

			if(parking_lot)
				parking_lot->park(reg_num, color);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			

	    } else if (command.compare("leave")) { //leave

	    	if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			} 
			int leave_slot = stoi(tokens[1]);

			if(parking_lot)
				parking_lot->leave(leave_slot);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			

	    } else if (command.compare("status")) {    //Status

	    	if(cmd_args != 1) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			}

			if(parking_lot)
				parking_lot->status();
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			

	    } else if (command.compare("registration_numbers_for_cars_with_colour")) {

	    	if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			}
			std::string color = tokens[1];
			if(parking_lot)
				parking_lot->reg_nums_with_color(color);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
			

	    } else if (command.compare("slot_numbers_for_cars_with_colour")) {

	    	if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			}
			std::string color = tokens[1];
			if(parking_lot)
				parking_lot->slot_nums_with_color(color);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
		

	    } else if (command.compare("slot_number_for_registration_number")) {

	    	if(cmd_args != 2) {
				std::cout <<  "Invalid no of arguments for command : " << command << std::endl;
				exit(EXIT_FAILURE);
			}
			std::string reg_num = tokens[1];
			if(parking_lot)
				parking_lot->slot_num_for_reg_num(reg_num);
			else
			{
				std::cout <<  "No Parking lot created, Create Parking Lot first, Invalid " << command << std::endl;
				exit(EXIT_FAILURE);	
			}
		

	    } else {

	    	std::cout << " Invalid command" <<std::endl;
	    	exit(EXIT_FAILURE);
	    }
	
	}


	virtual void read() = 0; //pure virtual method to be implemented by the derived class of abstractinput
};