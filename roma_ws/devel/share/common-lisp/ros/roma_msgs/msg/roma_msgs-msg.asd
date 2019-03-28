
(cl:in-package :asdf)

(defsystem "roma_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "kalman_state" :depends-on ("_package_kalman_state"))
    (:file "_package_kalman_state" :depends-on ("_package"))
    (:file "localization_data" :depends-on ("_package_localization_data"))
    (:file "_package_localization_data" :depends-on ("_package"))
    (:file "motion_cmds" :depends-on ("_package_motion_cmds"))
    (:file "_package_motion_cmds" :depends-on ("_package"))
    (:file "motion_feedback" :depends-on ("_package_motion_feedback"))
    (:file "_package_motion_feedback" :depends-on ("_package"))
    (:file "obstacles" :depends-on ("_package_obstacles"))
    (:file "_package_obstacles" :depends-on ("_package"))
    (:file "sensor_data" :depends-on ("_package_sensor_data"))
    (:file "_package_sensor_data" :depends-on ("_package"))
  ))