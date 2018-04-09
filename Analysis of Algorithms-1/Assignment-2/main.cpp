#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

class Residence{ // Residence class to hold information
public:
    int population;
    int min_age;
    int max_age;
    string gender;
    int zip_code;
    string geo_id;

    Residence(int population, int min_age, int max_age, const string &gender, int zip_code, const string &geo_id)
            : population(population), min_age(min_age), max_age(max_age), gender(gender), zip_code(zip_code),
              geo_id(geo_id) {}

    Residence() {
        this->population=0;
        this->min_age=0;
        this->max_age=0;
        this->gender="noGender";
        this->zip_code=0;
        this->geo_id="noGeo_id";
    }


};
int Partition(Residence *residences, int first, int last);
void Quick_Sort(Residence *residences, int first, int last);

class ResidenceManager{	//ResidenceManager class to handle input-output operations and sorting issue 
    Residence *residences;
    clock_t time;
    double timeInSeconds;
public:
    ResidenceManager(int N) {

        residences = new Residence[N];
        int indexOfResidence=0;
        string line;

		
        ifstream fptr("population_by_zip_2010.csv");
        if(!fptr.is_open())
            cout << "error when file is opening"<<endl;

        getline(fptr,line); //first line will not be used
        int counter = N;    // number of line which will be sorted

        string str1,str2,str3,str4,str5,str6; // strings for holding the information

        while(fptr.good()){

            getline(fptr,str1,',');
            residences[indexOfResidence].population = atoi(str1.c_str());
            getline(fptr,str2,',');
            residences[indexOfResidence].min_age = atoi(str2.c_str());
            getline(fptr,str3,',');
            residences[indexOfResidence].max_age= atoi(str3.c_str());
            getline(fptr,str4,',');
            residences[indexOfResidence].gender = str4;
            getline(fptr,str5,',');
            residences[indexOfResidence].zip_code = atoi(str5.c_str());
            getline(fptr,str6,'\n');
            residences[indexOfResidence].geo_id =str6;

            counter--;
            indexOfResidence++;
            if(counter ==0)
                break;
        }

        fptr.close();
		
		// time calculation
        time = clock();
        Quick_Sort(residences,0,N-1);
        time = clock() - time;
        timeInSeconds = (double)time/CLOCKS_PER_SEC;

		
        ofstream myfile;
        myfile.open ("out.csv-sorted"); //generating output file

      
        myfile<<"population";  myfile<<',';
        myfile<<"minimum_age"; myfile<<',';
        myfile<<"maximum_age"; myfile<<',';
        myfile<<"gender"; 	   myfile<<',';
        myfile<<"zipcode"; 	   myfile<<',';
        myfile<<"geoid"; 	   myfile<<',';
        myfile<<'\n';

        for(int i=0;i<N;i++){
            myfile<<residences[i].population; myfile<<',';
            myfile<<residences[i].min_age; myfile<<',';
            myfile<<residences[i].max_age; myfile<<',';
            myfile<<residences[i].gender; myfile<<',';
            myfile<<residences[i].zip_code; myfile<<',';
            myfile<<residences[i].geo_id; myfile<<'\n';
        }

        delete []residences;


        myfile.close();
    }

    double getTimeInSeconds() const {
        return timeInSeconds;
    }
    clock_t getClock() const{
        return time;
    }
};

// implementation of the quick sort
void Quick_Sort(Residence *residences, int first, int last)
{

    if (first < last){
        int partitionValue = Partition(residences, first, last);
        Quick_Sort(residences, first, (partitionValue - 1));
        Quick_Sort(residences, (partitionValue + 1), last);
    }
}

int Partition(Residence *residences, int first, int last)
{
    int pivot = residences[last].population;
    string pivot2 = residences[last].geo_id;

    int i = first-1;
    Residence temp;

    for (int j = first; j <= last-1; j++){
        if (residences[j].population < pivot){
            i++;

            temp = residences[i];
            if(i!=j)
            residences[i] = residences[j];
            residences[j]=temp;

        }
        else if(residences[j].population == pivot){
            if(residences[j].geo_id < pivot2){

                i++;
                temp = residences[i];
                if(i!=j)
                residences[i] = residences[j];
                residences[j]=temp;
            }

        }

    }
    temp = residences[i+1];
    residences[i+1] = residences[last];
    residences[last] = temp;

    return (i+1);
}

// the main function
int main(int argc, char **argv) {


    if (argc ==2){
        int N= atoi(argv[1]);
        ResidenceManager *r = new ResidenceManager(N);
        cout << "Time for sorting "<< N <<" element input with quick sort: " << r->getTimeInSeconds() << endl;
    }
    else{
        cout << "Invalid parameters for program" << endl;
    }

    return 0;
}
