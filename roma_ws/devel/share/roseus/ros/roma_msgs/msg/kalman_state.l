;; Auto-generated. Do not edit!


(when (boundp 'roma_msgs::kalman_state)
  (if (not (find-package "ROMA_MSGS"))
    (make-package "ROMA_MSGS"))
  (shadow 'kalman_state (find-package "ROMA_MSGS")))
(unless (find-package "ROMA_MSGS::KALMAN_STATE")
  (make-package "ROMA_MSGS::KALMAN_STATE"))

(in-package "ROS")
;;//! \htmlinclude kalman_state.msg.html


(defclass roma_msgs::kalman_state
  :super ros::object
  :slots (_latitude _longitude _velocity _accel _heading _steer_ang ))

(defmethod roma_msgs::kalman_state
  (:init
   (&key
    ((:latitude __latitude) 0.0)
    ((:longitude __longitude) 0.0)
    ((:velocity __velocity) 0.0)
    ((:accel __accel) 0.0)
    ((:heading __heading) 0.0)
    ((:steer_ang __steer_ang) 0.0)
    )
   (send-super :init)
   (setq _latitude (float __latitude))
   (setq _longitude (float __longitude))
   (setq _velocity (float __velocity))
   (setq _accel (float __accel))
   (setq _heading (float __heading))
   (setq _steer_ang (float __steer_ang))
   self)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:velocity
   (&optional __velocity)
   (if __velocity (setq _velocity __velocity)) _velocity)
  (:accel
   (&optional __accel)
   (if __accel (setq _accel __accel)) _accel)
  (:heading
   (&optional __heading)
   (if __heading (setq _heading __heading)) _heading)
  (:steer_ang
   (&optional __steer_ang)
   (if __steer_ang (setq _steer_ang __steer_ang)) _steer_ang)
  (:serialization-length
   ()
   (+
    ;; float64 _latitude
    8
    ;; float64 _longitude
    8
    ;; float64 _velocity
    8
    ;; float64 _accel
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
     ;; float64 _latitude
       (sys::poke _latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _longitude
       (sys::poke _longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity
       (sys::poke _velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _accel
       (sys::poke _accel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _heading
       (sys::poke _heading (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer_ang
       (sys::poke _steer_ang (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _latitude
     (setq _latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _longitude
     (setq _longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity
     (setq _velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _accel
     (setq _accel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _heading
     (setq _heading (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer_ang
     (setq _steer_ang (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get roma_msgs::kalman_state :md5sum-) "c3db7ca6e3b082f234a4561fcd0ad615")
(setf (get roma_msgs::kalman_state :datatype-) "roma_msgs/kalman_state")
(setf (get roma_msgs::kalman_state :definition-)
      "float64 latitude
float64 longitude
float64 velocity
float64 accel
float64 heading
float64 steer_ang
")



(provide :roma_msgs/kalman_state "c3db7ca6e3b082f234a4561fcd0ad615")


