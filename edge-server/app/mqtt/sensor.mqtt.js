const axiosConfig = require("../config/axios.config.js");
const axios = require('axios');
const api = axios.create(axiosConfig.config);

exports.upload = (body) => {
   data = JSON.parse(body);
   //console.log(data);

   /*
   /v1/sensors/
   v1/sensor/upload: {"id":"1001","seqNo":"10","t": {"0":"26.60","1":"28.10"},"h": {"0":"85.90","1":"83.00"},"l":"6.250","s":"0.336"}
   */
   api.post('/v1/sensors/log/', {
      sensorId: data.id,
      seqNo: data.s,
      temp1: data.t[0],
      temp2: data.t[1],
      temp3: data.t[2],
      humidity1: data.h[0],
      humidity2: data.h[1],
      humidity3: data.h[2],
      light: data.l,
      soilMoisture: 0, // data.s
      version: 1
   })
   .then(function (response) {
      //console.log(response.data);
      console.log("success: mqtt.sensor.js: /v1/sensors/");
   })
   .catch(function (error) {
      console.log('error: mqtt.sensor.js: /v1/sensors/');
      console.log(error.response);
   });
};

exports.log = (body) => {

   data = JSON.parse(body);

   const id = data.id;
   const priority = data.p;
   const message = data.msg;

   api.post('/v1/logs/', {
      type:'SENSOR',
      priority:priority,
      message: id + ': ' + message
   })
   .then((res)=>{
      console.log("success: mqtt.sensor.js: /v1/logs/");
   })
   .catch((err)=>{
      console.log("error: mqtt.sensor.js: /v1/logs/");
      console.log(error.response.data);
   })
}
