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

class localization_data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_lat = null;
      this.gps_lon = null;
      this.vel = null;
      this.accel_x = null;
      this.heading = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_lat')) {
        this.gps_lat = initObj.gps_lat
      }
      else {
        this.gps_lat = 0.0;
      }
      if (initObj.hasOwnProperty('gps_lon')) {
        this.gps_lon = initObj.gps_lon
      }
      else {
        this.gps_lon = 0.0;
      }
      if (initObj.hasOwnProperty('vel')) {
        this.vel = initObj.vel
      }
      else {
        this.vel = 0.0;
      }
      if (initObj.hasOwnProperty('accel_x')) {
        this.accel_x = initObj.accel_x
      }
      else {
        this.accel_x = 0.0;
      }
      if (initObj.hasOwnProperty('heading')) {
        this.heading = initObj.heading
      }
      else {
        this.heading = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type localization_data
    // Serialize message field [gps_lat]
    bufferOffset = _serializer.float32(obj.gps_lat, buffer, bufferOffset);
    // Serialize message field [gps_lon]
    bufferOffset = _serializer.float32(obj.gps_lon, buffer, bufferOffset);
    // Serialize message field [vel]
    bufferOffset = _serializer.float32(obj.vel, buffer, bufferOffset);
    // Serialize message field [accel_x]
    bufferOffset = _serializer.float32(obj.accel_x, buffer, bufferOffset);
    // Serialize message field [heading]
    bufferOffset = _serializer.float32(obj.heading, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type localization_data
    let len;
    let data = new localization_data(null);
    // Deserialize message field [gps_lat]
    data.gps_lat = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [gps_lon]
    data.gps_lon = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vel]
    data.vel = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [accel_x]
    data.accel_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading]
    data.heading = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'roma_msgs/localization_data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9e77329e7cd0c33db1d7f2019780b07a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 gps_lat
    float32 gps_lon
    float32 vel
    float32 accel_x
    float32 heading
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new localization_data(null);
    if (msg.gps_lat !== undefined) {
      resolved.gps_lat = msg.gps_lat;
    }
    else {
      resolved.gps_lat = 0.0
    }

    if (msg.gps_lon !== undefined) {
      resolved.gps_lon = msg.gps_lon;
    }
    else {
      resolved.gps_lon = 0.0
    }

    if (msg.vel !== undefined) {
      resolved.vel = msg.vel;
    }
    else {
      resolved.vel = 0.0
    }

    if (msg.accel_x !== undefined) {
      resolved.accel_x = msg.accel_x;
    }
    else {
      resolved.accel_x = 0.0
    }

    if (msg.heading !== undefined) {
      resolved.heading = msg.heading;
    }
    else {
      resolved.heading = 0.0
    }

    return resolved;
    }
};

module.exports = localization_data;
