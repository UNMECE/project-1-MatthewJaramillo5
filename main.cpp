#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
struct _capacitor{
	double *time;
	double *voltage;
	double *current;
	double C;
};
typedef struct _capacitor Capacitor;

void calculateConstantCurrent(Capacitor &cap, double I, double delta_t, int num_steps){
	int t;
	for(t = 1; t < num_steps; t++){
		cap.voltage[t] = cap.voltage[t - 1] + I * delta_t / cap.C;
		cap.time[t] = cap.time[t - 1] + delta_t;

		if(t % 200 == 0){
			cout << "Time: " << cap.time[t] << " s, Voltage: " << cap.voltage[t]
			<< " V, Current: " << I << " A" << endl;
		}
	}
}

void calculateConstantVoltage(Capacitor &cap, double R, double V0, double delta_t, int num_steps){
	cap.current[0] = V0 / R;
	int t;
	for(t = 1; t < num_steps; t++){
		cap.current[t] = cap.current[t - 1] - (cap.current[t - 1] / (R * cap.C)) * delta_t;
		cap.voltage[t] = V0 - cap.current[t] * R;

		cap.time[t] = cap.time[t - 1] + delta_t;
		if(t % 200 == 0){
			cout << "Time: " << cap.time[t] << " s, Voltage: " << cap.voltage[t]
                 << " V, Current: " << cap.current[t] << " A" << endl;
		}
	}
}

int main(){
	const double delta_t = 1e-10;
	const double final_time = 5e-6;
	const int num_steps = static_cast<int>(final_time / delta_t);

	const double R = 1e3; // resistance in Ohms
	const double C = 100e-12; // Capacitance in Farads
	const double I = 1e-2; // Current in Amps
	const double V0 = 10.0; // Voltage in Volts

	Capacitor cap;
    	cap.C = C;
	cap.time = new double[num_steps];
	cap.voltage = new double[num_steps];
	cap.current = new double[num_steps];

	cap.time[0] = 0.0;
	cap.voltage[0] = 0.0;
	cap.current[0] = I;

	cout << "Constant Current Source:" << endl;
  	calculateConstantCurrent(cap, I, delta_t, num_steps);

	cap.voltage[0] = 0.0;
   	cap.current[0] = V0 / R;

	cout << "\nConstant Voltage Source:" << endl;
   	calculateConstantVoltage(cap, R, V0, delta_t, num_steps);

	delete[] cap.time;
    	delete[] cap.voltage;
    	delete[] cap.current;

    	return 0;
}
