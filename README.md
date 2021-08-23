---
Author : Phạm Quang Minh 
Date : Aug 2021
Gmail : Engineer.pqm@gmail.com
Company : MKAC
---

## Readme
- Move (Robot) to known coordinates X,Y and W =1 

## REQUIREMENTS
This Project requires the following :

 * [Ubuntu 18.04 or newer](https://ubuntu.com/download/desktop)
 * [Ros Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)
 * [Turtlebot3](https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/)
 
## Usage
    1. < Bringup > Export IP   and enable the module. The system
       breadcrumb block has now been updated.
    2. Navigate to Administration > Configuration > User Interface > Easy
       Breadcrumb for configurations. Save Configurations.
       
Sử dụng `job_0` được cấu hình dynamic_reconfigure để chỉnh sửa, sau khi cấu hình xong thì copy (manual) sang job_1..n để sử dụng.

- Chạy `roslaunch scan_safety scan_safety.launch` trên pc robot
- Chạy `rosrun scan_safety show_safety.py` trên workstation pc để view.
- Chạy `rosrun rqt_reconfigure rqt_reconfigure` để thay đổi job, cập nhật tham số. (Muốn lưu lại tham số sau khi thay đổi thì hiện tại phải ghi trực tiếp vào file `config/safety_config.yaml`, chưa có cơ chế lưu trực tiếp từ reconfigure)

## Configuration




Done Move at directory Poin include file Cpp and Py include 

- Base_Move (....)
- Move.py and Move.cpp Advanced of file Base_move
- Move_ip(x and y coordinates entered from the keyboard)
- Move_with_case (use case replace input )

parameter storage position 

- Move_with_txt(data is stored as text)
- Move_with_dictionary(data is stored as dictionary)


Processing Muti-Poin Include ...

### Dynamic reconfigure

![](imgs/rr_scan.png)

* `current_job` và `foot_print` có thể thay đổi bằng [mission_manager](https://gitlab.com/mkac-agv/mission_manager)
