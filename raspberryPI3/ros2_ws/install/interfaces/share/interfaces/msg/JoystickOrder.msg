#General orders
bool start false 
int8 mode 0 # 0 -> Manual ; 1 -> Autonomous ; 2 -> Steering Calibration
bool record_path false #  1 -> start registering ; 0 -> stop registering

#Manual orders
float32 throttle 0  #[0 ; 1]
float32 steer 0     #[-1 ; 1]  
bool reverse false
