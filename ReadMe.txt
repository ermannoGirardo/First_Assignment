Inside my_assignment_1 you will find:
				-rqt_graph of the simulation
				-CMakeList.txt is the best and user-friendly software solution to build c++ project.
				-package.xml is the Package Manifest of the ros package.
				-src folder with c++ file of the two nodes.
				-srv folder with the request/reply of the custom service
				-docs folder with the documentation builded with DoxyGen and ReadMe.txt file

How to launch this Ros package?
1)Must have a ROS workspace already installed 
2)Into working directory download from GitHub repository the environment for the simulation: https://github.com/CarmineD8/assignment1.git --> Rename the folder assignment1 for using the command at point 4)
3)This package include 2 nodes:
				-position_server: provides random target, published via custom service, that robot must reaches
				-robot_controller: a publisher publish on topic /cmd_vel the linear velocity of the robot, a subscriber publish on topic /odom the 							   instantaneos position of the robot.

4)Digit the command rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world on the linux shell to launch the environment of the simulation.
5)Digit the command rosrun my_assignment_1 position_server on the linux shell to launch the server node.
6)Digit the command  rosrun my_assignment_1 robot_controller on the linux shell to launch the robot_controller node.
7) If the procedure has been successful you will see the robot moving into the environment and when the robot will reach the target a new target will be generated.
				



