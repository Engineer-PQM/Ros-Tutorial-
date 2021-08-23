---
Author : Phạm Quang Minh 
Date : Aug 2021
Gmail : Engineer.pqm@gmail.com
---
STARTING THE BOT
----------------
### CONTENTS OF THIS FILE
----------------
- Move (Robot) to known coordinates X,Y and W =1 

### REQUIREMENTS
----------------
This Project requires the following :

 * [Ubuntu 18.04 or newer](https://ubuntu.com/download/desktop)
 * [Ros Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)
 * [Turtlebot3](https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/)


STARTING THE BOT
----------------



Done Move at directory Poin include file Cpp and Py include 

- Base_Move (....)
- Move.py and Move.cpp Advanced of file Base_move
- Move_ip(x and y coordinates entered from the keyboard)
- Move_with_case (use case replace input )

parameter storage position 

- Move_with_txt(data is stored as text)
- Move_with_dictionary(data is stored as dictionary)


Processing Muti-Poin Include ...


Loading ..........................

File Library contains Paramater position and orientation (Dictionary)

This module requires the following modules:

 * [Views](https://www.drupal.org/project/views)
 * [Panels](https://www.drupal.org/project/panels)
# Readme

- Xác định các vùng an toàn
- Phát hiện vật cản trong các vùng an toàn

## Requirements

- safety_msgs: <https://gitlab.com/mkac-agv/safety_msgs>

## Usage

Sử dụng `job_0` được cấu hình dynamic_reconfigure để chỉnh sửa, sau khi cấu hình xong thì copy (manual) sang job_1..n để sử dụng.

- Chạy `roslaunch scan_safety scan_safety.launch` trên pc robot
- Chạy `rosrun scan_safety show_safety.py` trên workstation pc để view.
- Chạy `rosrun rqt_reconfigure rqt_reconfigure` để thay đổi job, cập nhật tham số. (Muốn lưu lại tham số sau khi thay đổi thì hiện tại phải ghi trực tiếp vào file `config/safety_config.yaml`, chưa có cơ chế lưu trực tiếp từ reconfigure)

## Configuration

### File config
