
#include "ros/ros.h"
#include "my_assignment_1/Target_Position.h"

/**
*Define constants to fix the limits of the domain
*/
#define min -6.0
#define max +6.0

/**
* /Function callBack executed when client calls
* 
* /Parameters:
*	an instance for the request(not used) and an instance for the reply of the srv Target_Position
* 
* /Comments about the code:
*
*				res.x=min+(rand()/(RAND_MAX/(max-min)))--> set the x component randomly between (-6;6)
*
*				res.y=min+(rand()/(RAND_MAX/(max-min))) --> set the y component randomly between (-6;6)
*
*				ROS_INFO --> print on screen string between ""
*/

bool target_pos(my_assignment_1::Target_Position::Request &req, my_assignment_1::Target_Position::Response &res){
	res.x=min+(rand()/(RAND_MAX/(max-min)));
	res.y=min+(rand()/(RAND_MAX/(max-min)));
	ROS_INFO("Robot has reached the target!");
        ROS_INFO("The Coordinates of the new target are: [%f] [%f]", res.x,res.y);
	return true;
}


/**
* /Main function:
*
* /Parameters:
*	
*	int argc, char **argv are mandatory for cpp files
* 
* /Comments about the code:
*
*	ros::init-->initialisation of the node position_server
*
*	ros::NodeHandle n --> set-up nodeHandle
*
*	ros::ServiceServer service= n.advertiseService("robot/target_pos",target_pos) --> define server and specify function callBack
*
*	ros::spin()--> blocks the main thread from exiting until ROS invokes a shutdown (for example Ctrl+C)
*/

int main(int argc, char **argv)
{
   ros::init(argc, argv, "position_server");	
   ros::NodeHandle n;	
   ros::ServiceServer service= n.advertiseService("robot/target_pos",target_pos);  
   ros::spin();

   return 0;
}
