// Auto-generated. Do not edit!

// (in-package roma_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class motion_cmds {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.power = null;
      this.steer_ang = null;
      this.near_cone = null;
      this.cone_visible = null;
      this.opencv_error = null;
    }
    else {
      if (initObj.hasOwnProperty('power')) {
        this.power = initObj.power
      }
      else {
        this.power = 0.0;
      }
      if (initObj.hasOwnProperty('steer_ang')) {
        this.steer_ang = initObj.steer_ang
      }
      else {
        this.steer_ang = 0.0;
      }
      if (initObj.hasOwnProperty('near_cone')) {
        this.near_cone = initObj.near_cone
      }
      else {
        this.near_cone = false;
      }
      if (initObj.hasOwnProperty('cone_visible')) {
        this.cone_visible = initObj.cone_visible
      }
      else {
        this.cone_visible = false;
      }
      if (initObj.hasOwnProperty('opencv_error')) {
        this.opencv_error = initObj.opencv_error
      }
      else {
        this.opencv_error = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type motion_cmds
    // Serialize message field [power]
    bufferOffset = _serializer.float32(obj.power, buffer, bufferOffset);
    // Serialize message field [steer_ang]
    bufferOffset = _serializer.float32(obj.steer_ang, buffer, bufferOffset);
    // Serialize message field [near_cone]
    bufferOffset = _serializer.bool(obj.near_cone, buffer, bufferOffset);
    // Serialize message field [cone_visible]
    bufferOffset = _serializer.bool(obj.cone_visible, buffer, bufferOffset);
    // Serialize message field [opencv_error]
    bufferOffset = _serializer.float32(obj.opencv_error, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type motion_cmds
    let len;
    let data = new motion_cmds(null);
    // Deserialize message field [power]
    data.power = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [steer_ang]
    data.steer_ang = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [near_cone]
    data.near_cone = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [cone_visible]
    data.cone_visible = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [opencv_error]
    data.opencv_error = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 14;
  }

  static datatype() {
    // Returns string type for a message object
    return 'roma_msgs/motion_cmds';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b8d7592f04e59bfb9ef4b6b5b23f809d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 power
    float32 steer_ang
    bool near_cone
    bool cone_visible
    float32 opencv_error
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new motion_cmds(null);
    if (msg.power !== undefined) {
      resolved.power = msg.power;
    }
    else {
      resolved.power = 0.0
    }

    if (msg.steer_ang !== undefined) {
      resolved.steer_ang = msg.steer_ang;
    }
    else {
      resolved.steer_ang = 0.0
    }

    if (msg.near_cone !== undefined) {
      resolved.near_cone = msg.near_cone;
    }
    else {
      resolved.near_cone = false
    }

    if (msg.cone_visible !== undefined) {
      resolved.cone_visible = msg.cone_visible;
    }
    else {
      resolved.cone_visible = false
    }

    if (msg.opencv_error !== undefined) {
      resolved.opencv_error = msg.opencv_error;
    }
    else {
      resolved.opencv_error = 0.0
    }

    return resolved;
    }
};

module.exports = motion_cmds;
