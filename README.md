---
Date : Aug 2021
Author : Phạm Quang Minh 
Gmail : Engineer.pqm@gmail.com
---
<h3 align="center">-------------------------------------</h3>

<!-- ABOUT THE PROJECT -->
## About The Project



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#Threads">Threads</a></li>
    <li><a href="#REQUIREMENTS">REQUIREMENTS</a></li>
    <li><a href="#Usage">Usage</a></li>
    <li><a href="#Configuration">Configuration</a></li>
        <li>
      <a href="#Explanation">About The Project</a>
      <ul>
        <li><a href="#Actionlib">Actionlib</a></li>
        <li><a href="#TOPIC Move_base">TOPIC Move_base</a></li>
      </ul>
    </li>
    <li>
      <a href="#Code">Code</a>
      <ul>
        <li><a href="#Directory Poin">Directory Poin</a></li>
        <li><a href="#Directory Muti-Poin ">Directory Muti-Poin </a></li>
      </ul>
    </li>
    <li><a href="#END">END</a></li>
  </ol>
</details>

## Threads.
    Move (Robot) to known coordinates X,Y and W =1.

## REQUIREMENTS.
This Project requires the following :

 * [Ubuntu 18.04 or newer](https://ubuntu.com/download/desktop)
 * [Ros Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)
 * [Turtlebot3](https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/)
 
 ```
$ echo "export TURTLEBOT3_MODEL=burger" >> ~/.bashrc
$ echo "export ROS_HOSTNAME=192.168.1.66" >> ~/.bashrc
$ echo "ROS_MASTER_URI=http://192.168.1.66:11311" >> ~/.bashrc
```
 
## Usage.
    1. (Bringup) Connect PC to a WiFi device and find the assigned IP address 
       
    2. (Simulation) Can use Gazebo or use Stage , In this project we use Stage (contact by gmail above)

       
Commonly used commands

- Map
Depending on the usage environment, we have different maps , If Bringup run `roslaunch turtlebot3_bringup turtlebot3_robot.launch` , If Simulation world run `roslaunch turtlebot3_gazebo turtlebot3_world.launch` ....


- Key
`roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch`

- Auto run
`roslaunch turtlebot3_gazebo turtlebot3_simulation.launch` initialization map

- Slam
`roslaunch turtlebot3_slam turtlebot3_slam.launch slam_methods:=gmapping`


- Save_map
`rosrun map_server map_saver -f ~/map` create 2 files named : map (map.pgm and map.yaml)

- Rviz 
` roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/map.yaml` User map from Slam (map.yaml)


## Configuration.


⭐️ NOTE.
-   The explanation only states the purpose and description

-   There are detailed explanations in each piece of code

-   Đoạn nào giải thích sẽ VietSub cho dễ  hiểu 

## Explanation. 

#### Actionlib

Có ba hình thức giao tiếp trong ROS :  
- Topics : đây là giao tiếp 1 chiều (publishers vs subscribers )
- Services : Cái này là giao tiếp 2 chiều nhưng không có thông tin về  progress
- Actions : Cái này có thể khắc phục được cả nhược điểm 2 cái trên và Thường được sử dụng trong các hoạt động có tính theo dõi và phản hồi liên tục , đây cũng là phương thức giao tiếp chính trong bài 

Các ActionClient và ActionServer giao tiếp thông qua một "ROS Action Protocol"


![Action](http://library.isr.ist.utl.pt/docs/roswiki/attachments/actionlib/client_server_interaction.png)


Chúng ta có thể điều khiển robot đến một mục tiêu, sử dụng base_move và amcl tuy nhiên amcl chỉ thuật là giá trị mang tính chất điều khiển động cơ như vận tốc V.v.. 

Nhưng không thể đạt được 1 số giá trị mang tích chất về  tọa độ (Goal) V.v.. 

#### TOPIC Move_base 

 Đơn giản mà nói Move_base là 1 trong phần tử chính của ROS Navigation stack Nó di chuyển robot từ vị trí hiện tại của nó đến vị trí mục tiêu được published trong topic move_base/goal .

Mục tiêu điều hướng 2D trong Rviz để chỉ định vị trí và hướng mục tiêu. Vị trí này (x, y, z) và hướng (x, y, z, w) tuy nhiên w = 1 để không xoay trục tọa độ 

Mục tiêu của bài này là sử dụng Node để điều hướng thay vì sử dụng Rviz 

![Move_base](http://library.isr.ist.utl.pt/docs/roswiki/attachments/move_base/overview_tf.png)

Về cơ bản mà nói thì ta sẽ sử dụng move_base_msgs.msg trong nhiệm vụ điều hướng (NAVIGATION) và hiện nay ta sẽ sử dụng 2 thứ trong đó là MoveBaseGoal và MoveBaseAction

   File : move_base_msgs/MoveBaseAction.msg Include  

- MoveBaseActionGoal action_goal
- MoveBaseActionResult action_result
- MoveBaseActionFeedback action_feedback


        Quả Thực cái này rất dài nên khi nào sử dụng sẽ giải thích sau 
        
File : move_base_msgs/MoveBaseGoal.msg structure :

      geometry_msgs/PoseStamped target_pose
      Header header
        uint32 seq
        time stamp
        string frame_id
      geometry_msgs/Pose pose
        geometry_msgs/Point position
            float64 x
            float64 y
            float64 z
        geometry_msgs/Quaternion orientation
            float64 x
            float64 y
            float64 z
            float64 w
    
  Ta có thể dễ dàng xét được vị trí Goal cho Robot bằng cách thêm giá trị x/y vào MoveBaseGoal nếu ta xét id = "map" và như đã nói ta sẽ để w = 1 để đảm bảo không xoay trục tọa độ các giá trị còn lại có thể có hoặc không 
       
        moveBaseGoal.target_pose.header.frame_id = "map"
        moveBaseGoal.target_pose.pose.position.x = x
        moveBaseGoal.target_pose.pose.position.y = y
        moveBaseGoal.target_pose.pose.orientation.w = 1.0

Ta có thể xét giá trị như trên trong Terminal bằng cách 

         rostopic pub /move_base_simple/goal geometry_msgs/PoseStamped '{header: {stamp: now, frame_id: "map"}, pose: {position: {x: 0.0, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}'
         

## Code.

#### Directory Poin : Poin and Poin (Từng điểm một)

* Base_Move.py 
    > Cái này dễ , đơn giản chỉ sử dụng 1 node pub giá trị x/y lên moveBaseGoal
* Move.py and Move.cpp
    > Cả 2 file có ý nghĩa và nhiệm vụ như nhau chỉ là ngôn ngữ sử dụng (về cơ bản mà nói nó cải tiến hơn so với file Base_move ở chỗ nó tạo ra 1 cái action client và gọi với action definition file "MoveBaseAction")

* Move_ip.cpp [Video Demo](https://drive.google.com/file/d/1mrTuHhitEaFwosD5H75a5c9AG8L4a5cv/view?usp=sharing)
    > Dữ liệu x/y được nhập từ bàn phím  
* Move_with_case.cpp [Video Demo](https://drive.google.com/file/d/1mvjackHJ7GJvbxHQibSqembTMlMyC_2k/view?usp=sharing)
    > Khác cái trên ở chỗ  chỉ cần nhập 1 hoặc 2 nó sẽ tới vị trí cho trước thay vì nhập cả x và y 

Với giá trị được lưu trong 1 file khác 

* Move_with_txt.py
   > Dữ liệu được lưu trữ dưới dạng text và Sử dụng split(",") để tách giá trị giữa dấu , 
  
* Move_with_dictionary.py [Video Demo](https://drive.google.com/file/d/1GcPGdj0GGRlgUv0CH6B-aCYBWdvZqyLB/view?usp=sharing)
    > Do dữ được lưu dưới dạng file Dictionry xem trong mục Library/Dictionary.py (Dạng này thì tường minh hơn so với dạng file text ).



#### Directory Muti-Poin : Di chuyển nhiều điểm 
* Done.py 
    > (Suử dụng như tệp Txt lưu dữ liệu dưới dạng mảng rồi lần lượt ghi giá trị lên tạo độ)

* Muti.py [Video Demo](https://drive.google.com/file/d/1zmwep9HPIQRpnQsmVdFMnbTnclCE7q0b/view?usp=sharing)
    > (Sử dụng hàm có giá trị và ghi từng giá trị tương ứng lên )

* File Main.py và test.py là file tham khảo được sử dụng và bóc tách để tìm hiểu các thành phần ở trong 

                                           Rất xin lỗi Video hơi LAG

23/8/2021

# END  

