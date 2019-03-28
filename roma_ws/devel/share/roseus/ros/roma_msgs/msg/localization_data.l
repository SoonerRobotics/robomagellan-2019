;; Auto-generated. Do not edit!


(when (boundp 'roma_msgs::localization_data)
  (if (not (find-package "ROMA_MSGS"))
    (make-package "ROMA_MSGS"))
  (shadow 'localization_data (find-package "ROMA_MSGS")))
(unless (find-package "ROMA_MSGS::LOCALIZATION_DATA")
  (make-package "ROMA_MSGS::LOCALIZATION_DATA"))

(in-package "ROS")
;;//! \htmlinclude localization_data.msg.html


(defclass roma_msgs::localization_data
  :super ros::object
  :slots (_gps_lat _gps_lon _vel _accel_x _heading ))

(defmethod roma_msgs::localization_data
  (:init
   (&key
    ((:gps_lat __gps_lat) 0.0)
    ((:gps_lon __gps_lon) 0.0)
    ((:vel __vel) 0.0)
    ((:accel_x __accel_x) 0.0)
    ((:heading __heading) 0.0)
    )
   (send-super :init)
   (setq _gps_lat (float __gps_lat))
   (setq _gps_lon (float __gps_lon))
   (setq _vel (float __vel))
   (setq _accel_x (float __accel_x))
   (setq _heading (float __heading))
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
  (:serialization-length
   ()
   (+
    ;; float32 _gps_lat
    4
    ;; float32 _gps_lon
    4
    ;; float32 _vel
    4
    ;; float32 _accel_x
    4
    ;; float32 _heading
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _gps_lat
       (sys::poke _gps_lat (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _gps_lon
       (sys::poke _gps_lon (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vel
       (sys::poke _vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _accel_x
       (sys::poke _accel_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading
       (sys::poke _heading (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _gps_lat
     (setq _gps_lat (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _gps_lon
     (setq _gps_lon (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vel
     (setq _vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _accel_x
     (setq _accel_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading
     (setq _heading (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get roma_msgs::localization_data :md5sum-) "9e77329e7cd0c33db1d7f2019780b07a")
(setf (get roma_msgs::localization_data :datatype-) "roma_msgs/localization_data")
(setf (get roma_msgs::localization_data :definition-)
      "float32 gps_lat
float32 gps_lon
float32 vel
float32 accel_x
float32 heading
")



(provide :roma_msgs/localization_data "9e77329e7cd0c33db1d7f2019780b07a")


