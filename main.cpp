#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include "slist.h"

using namespace std;

class Airport;

double distanceEarth(Airport* air1, Airport* air2);

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

void heapify(Slist *list, Airport *reference, int n, int i);
void heapSort(Slist *list, int n, Airport *reference);

Slist* distanceList(Slist *list, Airport *ref, double distance);

class Airport: public CustomNode {
public:
	Airport() {
		elevation = 0;
		longitude=0;
		latitude=0;
	}

	string code;
    string type;
    string name;

	///The elevation of the airport in feet
	double elevation;
	double   longitude;
	double   latitude;

    string continent;
	string country;
	string region;
	string municipality;
	string gps_code;
	string iata_code;

    string local_code;

	string toString() override {
    	string ret = code + "\t| " + type;
    	if(type.size() < 14) ret += "\t";
    	ret += "| " + name + "\t";

    	if(name.size() < 9) ret += "\t\t\t\t\t\t";
    	else if(name.size() < 14) ret += "\t\t\t\t\t";
    	else if(name.size() < 22) ret += "\t\t\t\t";
    	else if(name.size() < 30) ret += "\t\t\t";
		else if(name.size() < 41) ret += "\t\t";

    	ret += "| " + to_string(longitude) + "\t| " + to_string(latitude) + " | " + to_string(elevation);
    	if(to_string(elevation).size() < 10) ret += "\t";

    	ret += "\t| " + continent + " | " + country + " | " + region + " | " + municipality;

    	if(municipality.size() < 4) ret += "\t\t\t";
    	else if(municipality.size() < 12) ret += "\t\t";
		else if(municipality.size() < 17) ret += "\t";
		//else if(municipality.size() == 14) ret += "\t";
		ret += " | " + gps_code;

		if(gps_code.size() < 4) ret += " ";
		//cout << "Name: " << name << endl;
		return ret + " | " + iata_code + " | " + local_code;
    }

    string toString(CustomNode* ref) override {
		return toString() + " | " + to_string(distanceEarth(this, reinterpret_cast<Airport *>(ref)));
	}

	void setCode(char* c) {
    	code = c;
    }
	void setType(char* c) {
		type = c;
	}
	void setName(char* c) {
		name = c;
	}
	void setLong(char* c) {
		longitude = atof(c);
	}
	void setLat(char* c) {
    	latitude = atof(c);
    }
	void setContinent(char* c) {
    	continent = c;
    }
	void setCountry(char* c) {
		country = c;
	}
	void setRegion(char* c) {
		region = c;
	}
	void setMunicipality(char* c) {
		municipality = c;
	}
	void setGPS(char* c) {
		gps_code = c;
	}
	void setIata(char* c) {
		iata_code = c;
	}
	void setLocal(char* c) {
		local_code = c;
	}
	void setElevation(char* c) {
    	elevation = atof(c);
    }

	CustomNode* copyData() override {
		auto *air = new Airport;
		air->code = code;
		air->name = name;
		air->latitude = latitude;
		air->longitude = longitude;
		air->type = type;
		air->elevation = elevation;
		air->continent = continent;
		air->country = country;
		air->region = region;
		air->municipality = municipality;
		air->gps_code = gps_code;
		air->iata_code = iata_code;
		air->local_code = local_code;

		return air;
	};

    double getLong() {return longitude;}
	double getLat() {return latitude;}
	int compare(Airport* other, Airport* reference) {
		double thisD = distanceEarth(reference, this);
		double otherD = distanceEarth(reference, other);
		if(thisD == otherD) return 0;
		else if(thisD < otherD) return -1;
		else return 1;
	}
};

int main()
{
    ifstream infile;
    int i=0;
    auto* airportArr = new Slist;
    int   airportCount;
    infile.open ("C:/Users/Alex/ClionProjects/LASAlle/lasalle-2-0-singly-linked-list-library-theuncleofAlex/airport-codes_US.csv", ifstream::in);
	infile.seekg(125);
	Airport* aus;
	if (infile.is_open()) {

		int c = 0;
		while (infile.good()) {
			auto *air = new Airport();
			char chars[70];

			chars[0] = 'a';

			if (infile.good()) chars[0] = 'g';
			infile.clear();
			infile.getline(chars, 256, ',');
			air->setCode(chars);
			infile.getline(chars, 256, ',');
			air->setType(chars);
			infile.getline(chars, 256, ',');
			air->setName(chars);

			infile.getline(chars, 256, ',');
			air->setLong(chars);
			infile.getline(chars, 256, ',');
			air->setLat(chars);
			infile.getline(chars, 256, ',');
			air->setElevation(chars);

			infile.getline(chars, 256, ',');
			air->setContinent(chars);
			infile.getline(chars, 256, ',');
			air->setCountry(chars);
			infile.getline(chars, 256, ',');
			air->setRegion(chars);
			infile.getline(chars, 256, ',');
			air->setMunicipality(chars);
			infile.getline(chars, 256, ',');
			air->setGPS(chars);
			infile.getline(chars, 256, ',');
			air->setIata(chars);
			infile.getline(chars, 256, ',');
			air->setLocal(chars);

			if(air->code == "KAUS") aus = dynamic_cast<Airport *>(air->copyData());

			infile.seekg(1, ios::cur);

			if (air->type.find("airport") != string::npos) {
				airportArr->add(air);
			}

			i++;
			c++;
		}

		airportCount = airportArr->size();
		infile.close();

		cout << "You may experience some delays while the list is sorted." << endl;
		heapSort(airportArr, airportArr->size(), aus);

		Slist* hundred = distanceList(airportArr, aus, 100);
		hundred->remove(0);
		hundred->toString(aus);
		cout << "Farthest airport from aus:\n" << airportArr->get(airportArr->size()-1)->toString(aus) << endl;

    } else {
        cout << "Error opening file";
    }
    infile.close();
	delete aus;
	delete airportArr;
}



#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

double distanceEarth(Airport* air1, Airport* air2) {
	return distanceEarth(air1->getLong(), air1->getLat(), air2->getLong(), air2->getLat());
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void heapSort(Slist *list, int n, Airport *reference) {
	for(int i = n/2-1; i>=0; --i) {
		heapify(list, reference, n, i);
	}
	cout << "Halfway there!" << endl;
	for(int i = n-1; i>=0; --i) {
		list->swap(0, i);

		heapify(list, reference, i, 0);
	}
}

Slist* distanceList(Slist *list, Airport *ref, double distance) {
	auto * ret = new Slist;
	auto * last = dynamic_cast<Airport *>(list->head->ptr);
	int index = 0;
	int size = list->size();
	while(index < size && last != nullptr) {
		if(distanceEarth(last, ref) <= distance) {
			ret->add(last->copyData());
		}
		last = dynamic_cast<Airport *>(last->ptr);
		++index;
	}
	return ret;
}

void heapify(Slist *list, Airport *reference, int n, int i) {
	int largest = i;
	int l = 2*i+1;
	int r = 2*i+2;

	if(l<n && dynamic_cast<Airport*>(list->get(l))->compare(dynamic_cast<Airport *>(list->get(largest)), reference) > 0) {
		largest = l;
	}
	if(r < n && dynamic_cast<Airport*>(list->get(r))->compare(dynamic_cast<Airport *>(list->get(largest)), reference) > 0) {
		largest = r;
	}

	if(largest != i) {
		list->swap(i, largest);
		heapify(list, reference, n, largest);
	}
}