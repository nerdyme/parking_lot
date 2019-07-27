#pragma once

#include <unordered_map>
#include <map>
#include <queue>

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
        	static ParkingLot *parking_lot;

        //Create a min heap for empty parking lots 
        std::priority_queue <int, std::vector<int>, std::greater<int> > empty_lots;

        std::map< int, std::string> alloted_slot_to_reg;  //Take it as map as we need the status of each slot in sorted order
        std::unordered_map <std::string, carinfo> reg_to_carinfo;
        std::unordered_map <std::string, std::map<int, std::string> > color_to_vinfo; //vinfo is map of slot to reg_num

        //Make the constructor private so that only one parking lot 
        //will be created that will be through the static function declared in public section
        ParkingLot(int lot_size = 0) : lot_size(lot_size) {

        	for(int i=1; i <=lot_size; ++i)
        		empty_lots.push(i);   //All lots are empty initially

        	std::cout << "Created a parking lot with "<< lot_size <<" slots" << std::endl;

        }

      public:
        
        

        static ParkingLot* createParkingLot(int noOfParkingSlots) {
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

			if (lot_size == 0) {
				std::cout << "Sorry, parking lot is not created" << std::endl;

			} else if (alloted_slot_to_reg.size() > 0) {
				std::cout << "Slot No.\tRegistration No.\tColor"<<std::endl;
				
				for(const auto reg_num : alloted_slot_to_reg) {

					auto reg_ite = reg_to_carinfo.find(reg_num.second);
					if(reg_ite == reg_to_carinfo.end()) {
						std::cout << "Something wrong/inconsistent in data structures used" <<std::endl; //debugging
						return;
					}

					std::cout<<reg_ite->second.slot<<'\t' << reg_ite->second.registration_no << '\t' << reg_ite->second.color<< std::endl;
				}
				
			} else {
				std::cout << "Parking lot is empty" << std::endl;
			}

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

				auto carinfo_ite = reg_to_carinfo.find(reg_num);
				if(carinfo_ite == reg_to_carinfo.end()) {
					std::cout<< " Something is wrong/inconsistent in the parking lot data you have" << std::endl; //debugging
					return;
				}

				const auto carinf = carinfo_ite->second;

				
				//todo - erase from color_to_vinfo
				color_to_vinfo[carinf.color].erase(slot);


				reg_to_carinfo.erase(carinfo_ite);
				empty_lots.push(slot);

				std::cout<<"Slot number "<<slot<<" is free"<<std::endl;
			}
			

		}

		void park(const std::string& reg_num, const std::string& color) {

			if (lot_size == 0) {
				std::cout<< " No Parking Lot is created, First create the parking lot space "<<std::endl;
				return;

			}

			if(empty_lots.size() == 0) {
				std::cout<< "Sorry, parking lot is full"<<std::endl;
				return;
			}

			int allot_slot = empty_lots.top(); //Will always give minimum available slot as it is priority queue implemented using heaps
			empty_lots.pop();
			alloted_slot_to_reg.emplace(std::make_pair(allot_slot, reg_num));
			reg_to_carinfo.emplace(std::make_pair(reg_num, std::move(carinfo(reg_num, color, allot_slot))));  //can use std::move to move carinfo object
			color_to_vinfo[color][allot_slot] = reg_num; //todo

			std::cout<<"Allocated slot number: "<<allot_slot <<std::endl;
			


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

			std::string out="";
			auto vinfo_ite = color_to_vinfo.find(color);
			if (vinfo_ite == color_to_vinfo.end()) {
				std::cout << "No car with the color "<<color << " is parked in the parking lot" << std::endl;
				return;
			}

			for(const auto &vinfo : vinfo_ite->second) {
					out += std::to_string(vinfo.first) + std::string(",");
			}

			std::cout<<out<<std::endl;

		}

		void reg_nums_with_color(std::string color) {
			auto vinfo_ite = color_to_vinfo.find(color);
			if (vinfo_ite == color_to_vinfo.end()) {
				std::cout << "No car with the color "<<color << " is parked in the parking lot" << std::endl;
				return;
			}


		 }


		 ~ParkingLot() {

		 	//CLear all the dynamic memory allocated space
		 	alloted_slot_to_reg.clear();
        	reg_to_carinfo.clear();
       		color_to_vinfo.clear();
		 }



    };

//Definition of static data member
ParkingLot *ParkingLot::parking_lot = nullptr;
