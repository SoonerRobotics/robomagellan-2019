; Auto-generated. Do not edit!


(cl:in-package roma_msgs-msg)


;//! \htmlinclude localization_data.msg.html

(cl:defclass <localization_data> (roslisp-msg-protocol:ros-message)
  ((gps_lat
    :reader gps_lat
    :initarg :gps_lat
    :type cl:float
    :initform 0.0)
   (gps_lon
    :reader gps_lon
    :initarg :gps_lon
    :type cl:float
    :initform 0.0)
   (vel
    :reader vel
    :initarg :vel
    :type cl:float
    :initform 0.0)
   (accel_x
    :reader accel_x
    :initarg :accel_x
    :type cl:float
    :initform 0.0)
   (heading
    :reader heading
    :initarg :heading
    :type cl:float
    :initform 0.0))
)

(cl:defclass localization_data (<localization_data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <localization_data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'localization_data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name roma_msgs-msg:<localization_data> is deprecated: use roma_msgs-msg:localization_data instead.")))

(cl:ensure-generic-function 'gps_lat-val :lambda-list '(m))
(cl:defmethod gps_lat-val ((m <localization_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:gps_lat-val is deprecated.  Use roma_msgs-msg:gps_lat instead.")
  (gps_lat m))

(cl:ensure-generic-function 'gps_lon-val :lambda-list '(m))
(cl:defmethod gps_lon-val ((m <localization_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:gps_lon-val is deprecated.  Use roma_msgs-msg:gps_lon instead.")
  (gps_lon m))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <localization_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:vel-val is deprecated.  Use roma_msgs-msg:vel instead.")
  (vel m))

(cl:ensure-generic-function 'accel_x-val :lambda-list '(m))
(cl:defmethod accel_x-val ((m <localization_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:accel_x-val is deprecated.  Use roma_msgs-msg:accel_x instead.")
  (accel_x m))

(cl:ensure-generic-function 'heading-val :lambda-list '(m))
(cl:defmethod heading-val ((m <localization_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:heading-val is deprecated.  Use roma_msgs-msg:heading instead.")
  (heading m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <localization_data>) ostream)
  "Serializes a message object of type '<localization_data>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gps_lat))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gps_lon))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'accel_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <localization_data>) istream)
  "Deserializes a message object of type '<localization_data>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gps_lat) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gps_lon) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'accel_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<localization_data>)))
  "Returns string type for a message object of type '<localization_data>"
  "roma_msgs/localization_data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'localization_data)))
  "Returns string type for a message object of type 'localization_data"
  "roma_msgs/localization_data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<localization_data>)))
  "Returns md5sum for a message object of type '<localization_data>"
  "9e77329e7cd0c33db1d7f2019780b07a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'localization_data)))
  "Returns md5sum for a message object of type 'localization_data"
  "9e77329e7cd0c33db1d7f2019780b07a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<localization_data>)))
  "Returns full string definition for message of type '<localization_data>"
  (cl:format cl:nil "float32 gps_lat~%float32 gps_lon~%float32 vel~%float32 accel_x~%float32 heading~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'localization_data)))
  "Returns full string definition for message of type 'localization_data"
  (cl:format cl:nil "float32 gps_lat~%float32 gps_lon~%float32 vel~%float32 accel_x~%float32 heading~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <localization_data>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <localization_data>))
  "Converts a ROS message object to a list"
  (cl:list 'localization_data
    (cl:cons ':gps_lat (gps_lat msg))
    (cl:cons ':gps_lon (gps_lon msg))
    (cl:cons ':vel (vel msg))
    (cl:cons ':accel_x (accel_x msg))
    (cl:cons ':heading (heading msg))
))
