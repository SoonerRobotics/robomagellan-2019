; Auto-generated. Do not edit!


(cl:in-package roma_msgs-msg)


;//! \htmlinclude motion_cmds.msg.html

(cl:defclass <motion_cmds> (roslisp-msg-protocol:ros-message)
  ((power
    :reader power
    :initarg :power
    :type cl:float
    :initform 0.0)
   (steer_ang
    :reader steer_ang
    :initarg :steer_ang
    :type cl:float
    :initform 0.0)
   (near_cone
    :reader near_cone
    :initarg :near_cone
    :type cl:boolean
    :initform cl:nil)
   (cone_visible
    :reader cone_visible
    :initarg :cone_visible
    :type cl:boolean
    :initform cl:nil)
   (opencv_error
    :reader opencv_error
    :initarg :opencv_error
    :type cl:float
    :initform 0.0))
)

(cl:defclass motion_cmds (<motion_cmds>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <motion_cmds>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'motion_cmds)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name roma_msgs-msg:<motion_cmds> is deprecated: use roma_msgs-msg:motion_cmds instead.")))

(cl:ensure-generic-function 'power-val :lambda-list '(m))
(cl:defmethod power-val ((m <motion_cmds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:power-val is deprecated.  Use roma_msgs-msg:power instead.")
  (power m))

(cl:ensure-generic-function 'steer_ang-val :lambda-list '(m))
(cl:defmethod steer_ang-val ((m <motion_cmds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:steer_ang-val is deprecated.  Use roma_msgs-msg:steer_ang instead.")
  (steer_ang m))

(cl:ensure-generic-function 'near_cone-val :lambda-list '(m))
(cl:defmethod near_cone-val ((m <motion_cmds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:near_cone-val is deprecated.  Use roma_msgs-msg:near_cone instead.")
  (near_cone m))

(cl:ensure-generic-function 'cone_visible-val :lambda-list '(m))
(cl:defmethod cone_visible-val ((m <motion_cmds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:cone_visible-val is deprecated.  Use roma_msgs-msg:cone_visible instead.")
  (cone_visible m))

(cl:ensure-generic-function 'opencv_error-val :lambda-list '(m))
(cl:defmethod opencv_error-val ((m <motion_cmds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roma_msgs-msg:opencv_error-val is deprecated.  Use roma_msgs-msg:opencv_error instead.")
  (opencv_error m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <motion_cmds>) ostream)
  "Serializes a message object of type '<motion_cmds>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'power))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steer_ang))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'near_cone) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'cone_visible) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'opencv_error))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <motion_cmds>) istream)
  "Deserializes a message object of type '<motion_cmds>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'power) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steer_ang) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'near_cone) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'cone_visible) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'opencv_error) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<motion_cmds>)))
  "Returns string type for a message object of type '<motion_cmds>"
  "roma_msgs/motion_cmds")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'motion_cmds)))
  "Returns string type for a message object of type 'motion_cmds"
  "roma_msgs/motion_cmds")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<motion_cmds>)))
  "Returns md5sum for a message object of type '<motion_cmds>"
  "b8d7592f04e59bfb9ef4b6b5b23f809d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'motion_cmds)))
  "Returns md5sum for a message object of type 'motion_cmds"
  "b8d7592f04e59bfb9ef4b6b5b23f809d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<motion_cmds>)))
  "Returns full string definition for message of type '<motion_cmds>"
  (cl:format cl:nil "float32 power~%float32 steer_ang~%bool near_cone~%bool cone_visible~%float32 opencv_error~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'motion_cmds)))
  "Returns full string definition for message of type 'motion_cmds"
  (cl:format cl:nil "float32 power~%float32 steer_ang~%bool near_cone~%bool cone_visible~%float32 opencv_error~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <motion_cmds>))
  (cl:+ 0
     4
     4
     1
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <motion_cmds>))
  "Converts a ROS message object to a list"
  (cl:list 'motion_cmds
    (cl:cons ':power (power msg))
    (cl:cons ':steer_ang (steer_ang msg))
    (cl:cons ':near_cone (near_cone msg))
    (cl:cons ':cone_visible (cone_visible msg))
    (cl:cons ':opencv_error (opencv_error msg))
))
