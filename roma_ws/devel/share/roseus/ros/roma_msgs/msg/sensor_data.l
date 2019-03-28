;; Auto-generated. Do not edit!


(when (boundp 'roma_msgs::sensor_data)
  (if (not (find-package "ROMA_MSGS"))
    (make-package "ROMA_MSGS"))
  (shadow 'sensor_data (find-package "ROMA_MSGS")))
(unless (find-package "ROMA_MSGS::SENSOR_DATA")
  (make-package "ROMA_MSGS::SENSOR_DATA"))

(in-package "ROS")
;;//! \htmlinclude sensor_data.msg.html


(defclass roma_msgs::sensor_data
  :super ros::object
  :slots (_gps_lat _gps_lon _vel _accel_x _heading _steer_ang ))

(defmethod roma_msgs::sensor_data
  (:init
   (&key
    ((:gps_lat __gps_lat) 0.0)
    ((:gps_lon __gps_lon) 0.0)
    ((:vel __vel) 0.0)
    ((:accel_x __accel_x) 0.0)
    ((:heading __heading) 0.0)
    ((:steer_ang __steer_ang) 0.0)
    )
   (send-super :init)
   (setq _gps_lat (float __gps_lat))
   (setq _gps_lon (float __gps_lon))
   (setq _vel (float __vel))
   (setq _accel_x (float __accel_x))
   (setq _heading (float __heading))
   (setq _steer_ang (float __steer_ang))
   self)
  (:gps_lat
   (&optional __gps_lat)
   (if __gps_lat (setq _gps_lat __gps_lat)) _gps_lat)
  (:gps_lon
   (&optional __gps_lon)
   (if __gps_lon (setq _gps_lon __gps_lon)) _gps_lon)
  (:vel
   (&optional __vel)
   (if __vel (setq _vel __vel)) _vel)
  (:accel_x
   (&optional __accel_x)
   (if __accel_x (setq _accel_x __accel_x)) _accel_x)
  (:heading
   (&optional __heading)
   (if __heading (setq _heading __heading)) _heading)
  (:steer_ang
   (&optional __steer_ang)
   (if __steer_ang (setq _steer_ang __steer_ang)) _steer_ang)
  (:serialization-length
   ()
   (+
    ;; float64 _gps_lat
    8
    ;; float64 _gps_lon
    8
    ;; float64 _vel
    8
    ;; float64 _accel_x
    8
    ;; float64 _heading
    8
    ;; float64 _steer_ang
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _gps_lat
       (sys::poke _gps_lat (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _gps_lon
       (sys::poke _gps_lon (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _vel
       (sys::poke _vel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _accel_x
       (sys::poke _accel_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _heading
       (sys::poke _heading (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_ang
       (sys::poke _steer_ang (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _gps_lat
     (setq _gps_lat (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _gps_lon
     (setq _gps_lon (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _vel
     (setq _vel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _accel_x
     (setq _accel_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _heading
     (setq _heading (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_ang
     (setq _steer_ang (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get roma_msgs::sensor_data :md5sum-) "3ff8996641964b6ddc02189f77b82f67")
(setf (get roma_msgs::sensor_data :datatype-) "roma_msgs/sensor_data")
(setf (get roma_msgs::sensor_data :definition-)
      "float64 gps_lat
float64 gps_lon
float64 vel
float64 accel_x
float64 heading
float64 steer_ang
")



(provide :roma_msgs/sensor_data "3ff8996641964b6ddc02189f77b82f67")


