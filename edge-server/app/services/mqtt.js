const mqttClient = require("mqtt");
const axios = require("axios");

const mqttConfig = require("../config/mqtt.config.js");
const axiosConfig = require("../config/axios.config.js");

const mqttSensor = require("../mqtt/sensor.mqtt.js");
const mqttController = require("../mqtt/control.mqtt.js");

const mqtt = mqttClient.connect(mqttConfig.HOST, mqttConfig.options);
const api = axios.create(axiosConfig.config);

mqtt.on("message", (topic, message, packet) => {
  // Only look for freash messages
  if (packet.retain === false) {
    console.log(topic + ": " + message);

    // Currently subscribed
    if (topic == "v1/sensor/upload") {
      mqttSensor.upload(message);
    } else if (topic == "v1/sensor/log") {
      mqttSensor.log(message);
    } else if (topic == "v1/controller/upload") {
      mqttController.upload(message);
    } else if (topic == "v1/controller/log") {
      mqttController.log(message);
    }
  }
});

mqtt.on("error", function (err) {
  console.log("error: mqtt");
  console.log(err);
});

exports.start = () => {
  mqtt.on("connect", () => {
    const options = { qos: 2, rap: true, rh: true };

    mqtt.subscribe("v1/sensor/upload", options);
    mqtt.subscribe("v1/sensor/log", options);

    mqtt.subscribe("v1/controller/upload", options);
    mqtt.subscribe("v1/controller/log", options);

    //mqtt.subscribe('controller/req');
  });
};

exports.sendMsgToSensor = (req, callback) => {
  data = req.body;
  mqtt.publish(
    "v1/sensor/" + req.body.id,
    JSON.stringify(req.body),
    function () {
      console.log("mqtt: v1/sensor" + req.body.id);
      callback({ message: "Success" });
    }
  );
};

exports.sendMsgToController = (req, callback) => {
  data = req.body;
  mqtt.publish(
    "v1/controller/" + req.body.id,
    JSON.stringify(req.body),
    function () {
      console.log("mqtt: v1/controller/" + req.body.id);
      callback({ message: "Success" });
    }
  );
};

exports.controllerUpdate = (id, callback) => {
  const api = axios.create(axiosConfig.config);
  const site = process.env.API_SERVER || "agbc-fe.pdn.ac.lk";
  const url = "/dashboard/api/calculations.php?token=55ab5c3e616bc2996cccdb1";

  api.get(site + url).then((response) => {
    if (
      response.data.StatusCode == "Success" ||
      response.data.StatusCode == "Calculation not possible"
    ) {
      const dataValues = response.data.values;
      const dataUpdated = response.data.updated;

      //console.log(response.data.StatusCode);
      console.log(response.data.values);
      console.log(response.data.updated);

      // Do not run following lines in the test environment
      // // Only invoke if the value is changed
      // //if(dataUpdated.blower == 1)
      // mqtt.publish(
      //   "v1/controller/" + id + "/blower",
      //   dataValues.blower.toString(),
      //   { retain: true, qos: 1 }
      // );
      // //if(dataUpdated.mist ==1)
      // mqtt.publish(
      //   "v1/controller/" + id + "/mist",
      //   dataValues.mist.toString(),
      //   { retain: true, qos: 1 }
      // );

      // if (dataUpdated.curtain == 1)
      //   mqtt.publish(
      //     "v1/controller/" + id + "/curtain",
      //     dataValues.curtain.toString(),
      //     {}
      //   ); // No retain
      // if (dataUpdated.water == 1)
      //   mqtt.publish(
      //     "v1/controller/" + id + "/water",
      //     dataValues.water.toString(),
      //     { retain: true, qos: 1 }
      //   );
    } else {
      console.log(response.data);
    }
  });
};

exports.client = mqtt;
