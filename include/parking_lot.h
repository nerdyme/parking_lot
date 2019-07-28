	#pragma once

	#include <unordered_map>
	#include <map>
	#include <queue>
    #include <iomanip>

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
	        //called by the wrapper abstract_input.h
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

				std::setiosflags(std::ios::right);
				if (lot_size == 0) {
					std::cout << "Sorry, parking lot is not created" << std::endl;

				} else if (alloted_slot_to_reg.size() > 0) {
					std::cout <<"Slot No." << std::setw(19) << "Registration No" <<std::setw(10) << "Colour"<<std::endl;
					
					for(const auto reg_num : alloted_slot_to_reg) {

						auto reg_ite = reg_to_carinfo.find(reg_num.second);
						if(reg_ite == reg_to_carinfo.end()) {
							std::cout << "Something wrong/inconsistent in data structures used" <<std::endl; //debugging
							return;
						}

						std::cout<< reg_ite->second.slot << std::setw(24) << reg_ite->second.registration_no
						  << std::setw(11) << reg_ite->second.color<< std::endl;
					}
					
				} else {
					std::cout << "Parking lot is empty" << std::endl;
				}

			}

			void leave(int slot) {

				auto reg_ite = alloted_slot_to_reg.find(slot);
				if (reg_ite == alloted_slot_to_reg.end()) {
					std::cout << "No Car is not present at slot " << slot << std::endl;
					return;

				} else {

					auto carinfo_ite = reg_to_carinfo.find(reg_ite->second);
					if(carinfo_ite == reg_to_carinfo.end()) {
						std::cout<< " Something is wrong/inconsistent in the parking lot data you have" << std::endl; //debugging
						return;
					}

					const auto carinfo_val = carinfo_ite->second;

					
					alloted_slot_to_reg.erase(reg_ite);
					reg_to_carinfo.erase(carinfo_ite);
					empty_lots.push(slot);
					color_to_vinfo[carinfo_val.color].erase(slot);

					if(color_to_vinfo.find(carinfo_val.color) != color_to_vinfo.end() && 
						color_to_vinfo.find(carinfo_val.color)->second.size() == 0)
						color_to_vinfo.erase(carinfo_val.color);

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

				int allot_slot = empty_lots.top(); //Will always give minimum available slot as it is priority queue implemented with min heap
				empty_lots.pop();
				alloted_slot_to_reg.emplace(std::make_pair(allot_slot, reg_num));
				reg_to_carinfo.emplace(std::make_pair(reg_num, carinfo(reg_num, color, allot_slot)));
				color_to_vinfo[color][allot_slot] = reg_num;

				std::cout<<"Allocated slot number: "<<allot_slot <<std::endl;
			}

			void slot_num_for_reg_num(const std::string& reg_num) const {

				auto car_ite = reg_to_carinfo.find(reg_num);
				if(car_ite != reg_to_carinfo.end()) {

					std::cout << car_ite->second.slot << std::endl;

				} else {
					std::cout<<"Not found" <<std::endl;
				}

			}

			void slot_nums_with_color(std::string color) const {

				std::string out="";
				auto vinfo_ite = color_to_vinfo.find(color);
				if (vinfo_ite == color_to_vinfo.end()) {
					std::cout << "No car with the color "<<color << " is parked in the parking lot" << std::endl;
					return;
				}

				for(const auto &vinfo : vinfo_ite->second) {
						out += std::to_string(vinfo.first) + std::string(", ");
				}

				out.pop_back();
				out.pop_back();
				std::cout << out <<std::endl;
			}

			void reg_nums_with_color(std::string color) const {

				std::string out="";
				auto vinfo_ite = color_to_vinfo.find(color);
				if (vinfo_ite == color_to_vinfo.end()) {
					std::cout << "No car with the color "<<color << " is parked in the parking lot" << std::endl;
					return;
				}

				for(const auto &vinfo : vinfo_ite->second) {
						out += vinfo.second + std::string(", ");
				}

				out.pop_back();
				out.pop_back();
				std::cout << out <<std::endl;
			 }


			 ~ParkingLot() {

			 	//CLear all the dynamic memory allocated space
			 	alloted_slot_to_reg.clear();
	        	reg_to_carinfo.clear();

	        	for (auto vinfo : color_to_vinfo) {
	        		vinfo.second.clear();  //First clear internal map corresponding to each color
	        	}
	       			color_to_vinfo.clear();
			 }
	    };

	//Definition of static data member
	ParkingLot *ParkingLot::parking_lot = nullptr;
