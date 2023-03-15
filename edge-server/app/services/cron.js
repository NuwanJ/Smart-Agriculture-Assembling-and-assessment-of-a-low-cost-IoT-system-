/*
# ┌────────────── second (optional)
# │ ┌──────────── minute
# │ │ ┌────────── hour
# │ │ │ ┌──────── day of month
# │ │ │ │ ┌────── month
# │ │ │ │ │ ┌──── day of week
# │ │ │ │ │ │
# │ │ │ │ │ │
# * * * * * *
*/

'use strict'

var cron = require('node-cron');
const sensorRead = require("../cron/sensor.read.cron.js");
var mqtt;

exports.begin = (mqtt, db) => {
   this.mqtt = mqtt;

   // Start cron jobs
   this.sensorUpdate(mqtt,db);
}

exports.sensorUpdate = (mqtt, db) => {
   const interval = '*/5 * * * * *'; // Updates every 30 seconds

   cron.schedule(interval, ()=>{
      console.log("mqtt: v1/sensor/read");

      db.AgriData.findOne({where: {dKey: 'seqNo'}})
      .then(data => {
         var seqNo = data.dataValues.dValue;
         const sleepDuration  = 0;

         // Send a request with given seqNumber
         mqtt.client.publish('v1/sensor/read', (seqNo + " " + sleepDuration), {retain:false,qos:1});
         db.AgriData.increment('dValue', { where: {dKey: 'seqNo'}});    // Update the seqNumber by one
         console.log('success: sensor.cron.js: /v1/sensor/read > ' + seqNo )
         const timeout = 5000;

         setTimeout(()=>{
            const siteId = 1000;
            mqtt.controllerUpdate(siteId, ()=>{
               // callback
            })
         }, timeout);

      })
      .catch(err => {
         console.log(err.message || "Some error occurred while v1/sensor/read.")
      });
   },{
      scheduled: true,
      timezone: "Asia/Colombo"
   });
}
