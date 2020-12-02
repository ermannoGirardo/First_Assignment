
#include "ros/ros.h"
#include "stdlib.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "my_assignment_1/Target_Position.h"

/**
*Define the constant to set the linear velocity proportional to the distance between the robot and the target
*/
#define alpha 5
/**
*Define Publisher that will publish velocity of robot on topic /cmd_vel
*/
ros::Publisher pub;
/**
*Define Client that will call custom service to spawn random target
*/
ros::ServiceClient client;

/**
*Define as global an instance of service Target_Position
*/

my_assignment_1::Target_Position target_pos; 

/**
*Define as global an instance of the topic /cmd_vel
*/
geometry_msgs::Twist vel;

/**
* /Function positionCallBack called when subscriber receives the position
*
* /-Parameter:
* 	
*	msg: declared as constant pointer of topic Odom (to establish the position of the robot)
*	
* /The funcion receive the position of the robot:
*
*	-If the robot has reached the target spawn new random target
*
*	-Else set linear velocity to reach the raget
*/

void positionCallback(const nav_msgs::Odometry::ConstPtr& msg) 
{
 	ROS_INFO("Robot Position [%f,%f]", msg->pose.pose.position.x , msg->pose.pose.position.y);
	if((abs(target_pos.response.x - msg->pose.pose.position.x)<=0.1)&&(abs(target_pos.response.y - msg->pose.pose.position.y)<=0.1))  
	{	ROS_INFO("Robot has reached the target,give me another one.");		
		client.call(target_pos);
	}											 
	else			
	{
		vel.linear.x=alpha*(target_pos.response.x - msg->pose.pose.position.x);
		vel.linear.y=alpha*(target_pos.response.y - msg->pose.pose.position.y);
		pub.publish(vel);
	}
}


/**
*MAIN FUNCTION
*
* /Parameters:
*	int argc, char **argv are mandatory for cpp files
*
* /Comments about the code:
*	
*	ros::init-->initialisation of the node robot_controller
*
*	ros::NodeHandle n --> set-up nodeHandle
*
*	pub=n.advertise<geometry_msgs::Twist> --> declare publisher and specify the topic
*
*	ros::Subscriber sub=n.subscribe("/odom",1000,positionCallback) --> define subscriber and specify the function called 
*
*	client = n.serviceClient<my_assignment_1::Target_Position> --> declare client and specify service type
*
*	client.call(target_pos) --> call manually the first time the service to generate the first random target	
*
*       ros::spin()--> blocks the main thread from exiting until ROS invokes a shutdown (for example Ctrl+C)
*/

int main(int argc, char **argv)
{
   	ros::init(argc,argv,"robot_controller");		
   	ros::NodeHandle n;		
   	pub=n.advertise<geometry_msgs::Twist>("/cmd_vel",1000);    
   	ros::Subscriber sub=n.subscribe("/odom",1000,positionCallback); 
   	client = n.serviceClient<my_assignment_1::Target_Position>("robot/target_pos");  
        client.call(target_pos);
   	ros::spin();

  	return 0;
}



