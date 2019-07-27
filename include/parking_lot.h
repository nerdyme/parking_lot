#pragma once

#include <unordered_map>

struct carinfo {
        std::string registration_no;
        std::string color;
        int slot;

        carinfo()=delete;
        carinfo(std::string registration_no, std::string color, int slot ) :
        registration_no(registration_no), color(color), slot(slot) {}
    };

    class ParkingLot {

        private:

        	const int lot_size{0};
        	static ParkingLot *parking_lot {nullptr};

        //Create a min heap for empty parking lots 
        std::priority_queue <int, std::vector<int>, std::greater<int> > empty_lots;

        std::unordered_map< int, std::string> alloted_slot_to_reg;
        std::unordered_map <std::string, carinfo> reg_to_carinfo;
        std::unordered_map <std::string, std::unordered_map<int, std::string> > color_to_vinfo; //vinfo is map of slot to reg_num

        //Make the constructor private so that only one parking lot 
        //will be created that will be through the static function declared in public section
        ParkingLot(int lot_size = 0) : lot_size(lot_size) {

        	for(int i=1; i <=lot_size; ++i)
        		empty_lots.push(i);   //All lots are empty initially

        	std::cout << "Created a parking lot with "<< lot_size <<" slots" << std::endl;

        }

      public:
        
        

        static ParkingLot createParkingLot(int noOfParkingSlots) {
			if(parking_lot != NULL) {
				return parking_lot;
			} else {
				parking_lot = 
						new ParkingLot(noOfParkingSlots);
				return parking_lot;
			}

		}

		//Functionalities required

		void status() {

		}

		void leave(int slot) {

			auto reg_ite = alloted_slot_to_reg.find(slot);
			std::string reg_no;
			if (reg_ite == alloted_slot_to_reg.end()) {
				std::cout << "No Car is not present at slot " << slot << std::endl;
				return;

			} else {
				std::string reg_num = reg_ite->second;

				alloted_slot_to_reg.erase(reg_ite);
				reg_to_carinfo.erase(reg_num);
				//todo - erase from color_to_vinfo


				empty_lots.push(slot);
			}
			

		}

		void park(const std::string& reg_num, const std::string& color) {

			if (lot_size == 0) {
				std::cout<< " No Parking Lot is created, First create the parking lot space "<<std::endl;
				return;

			}

			if(empty_lots.size() == 0) {
				std::cout<< " Parking Lot is full, Sorry No space"<<std::endl;
				return;
			}

			int allot_slot = empty_lots.top();
			empty_lots.pop();
			alloted_slot_to_reg.emplace({allot_slot, reg_num});
			reg_to_carinfo.emplace({reg_num, carinfo(reg_num, color, allot_slot)});  //can use std::move to move carinfo object
			//color_to_vinfo.emplace({color, {allot_slot, reg_num}}); //todo
			


		}

		void slot_num_for_reg_num(const std::string& reg_num) {

			auto car_ite = reg_to_carinfo.find(reg_num);
			if(car_ite != reg_to_carinfo.end()) {

				std::cout << car_ite->second.slot << std::endl;

			} else {
				std::cout<<"Not found" <<std::endl;

			}

		}

		void slot_nums_with_color(std::string color) {

		}

		void reg_nums_with_color(std::string color) {

		 }









    };