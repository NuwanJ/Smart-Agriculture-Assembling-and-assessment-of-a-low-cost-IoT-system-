const db = require("../services/database.js");
const mqtt = require("../services/mqtt.js");

const Sensor = db.sensors;
const SensorData = db.sensorData;

const Op = db.Sequelize.Op;
const { QueryTypes } = require('sequelize');

// -----------------------------------------------------------------------------
// Creates  a new sensor log
// -----------------------------------------------------------------------------
exports.createLog = (req, res) => {

   if (!req.body.sensorId) {
      res.status(400).send({
         message: "sensorId can not be empty!"
      });
      return;
   }
   const sensor = {
      sensorId: req.body.sensorId,
      seqNo: req.body.seqNo,
      temp1: req.body.temp1,
      temp2: req.body.temp2,
      temp3: req.body.temp3,
      humidity1: req.body.humidity1,
      humidity2: req.body.humidity2,
      humidity3: req.body.humidity3,
      light: req.body.light,
      soilMoisture: req.body.soilMoisture,
      version: 1
   };
   Sensor.create(sensor)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while creating the Sensor."
      });
   });
};

// -----------------------------------------------------------------------------
// Creates  a new sensor
// -----------------------------------------------------------------------------
exports.createSensor = (req, res) => {
   if (!req.body.id) {
      res.status(400).send({
         message: "Id can not be empty!"
      });
      return;
   }
   const sensordata = {
      id: req.body.id,
      siteId: req.body.siteId,
      x: req.body.x,
      y: req.body.y,
      state: req.body.state,
      firmwareVersion: req.body.firmwareVersion,
      notes: req.body.notes
   };

   SensorData.create(sensordata)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while creating the SensorData."
      });
   });
};

// -----------------------------------------------------------------------------
// Retrieve all Sensors logs from the database.
// -----------------------------------------------------------------------------
exports.findAllLogs = (req, res) => {
   const sensorId = req.query.sensorId;
   var condition = sensorId ? { sensorId: { [Op.like]: `%${sensorId}%` } } : null;

   Sensor.findAll({ where: condition })
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while retrieving Sensors."
      });
   });
};

// -----------------------------------------------------------------------------
// Find a single Sensor Log entry using the id
// -----------------------------------------------------------------------------
exports.findOneLog = (req, res) => {
   const id = req.params.id;

   Sensor.findByPk(id)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message: "Error retrieving Sensor with id=" + id
      });
   });

};

// -----------------------------------------------------------------------------
// Find a single Sensor Log entries of a Sensor device
// -----------------------------------------------------------------------------
exports.getLogsByDevice = (req, res) => {
   const id = req.params.deviceId;
   var condition = {sensorId: {[Op.eq]: id}};

   Sensor.findAll({ where: condition })
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while retrieving data."
      });
   });
}

// -----------------------------------------------------------------------------
// Find latest log entery of each sensor for a given site
// -----------------------------------------------------------------------------
exports.getLogsBySiteLatest = async (req, res) => {
   const id = req.params.siteId;
   const q = "SELECT * FROM (SELECT l.sensorId, temp1, temp2, humidity1, humidity2, light, soilMoisture, l.createdAt FROM sensor_log as l, sensor_data as d WHERE l.sensorId=d.id AND d.siteId="+ id + " ORDER BY l.createdAt DESC) as d WHERE 1 GROUP BY sensorId;";

   const response = await db.sequelize.query(q,{
      type: QueryTypes.SELECT
   })
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while retrieving Control Log."
      });
   });
}

// -----------------------------------------------------------------------------
// Find a the latest Sensor Log entries of a Sensor device
// -----------------------------------------------------------------------------
exports.getLogLatest = async (req, res) => {
   const id = req.params.deviceId;
   const response = await db.sequelize.query("SELECT * FROM `sensor_log` WHERE `sensorId` LIKE '"+ id +"' ORDER BY `createdAt` DESC LIMIT 1",{
      type: QueryTypes.SELECT
   })
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while retrieving Control Log."
      });
   });
}

// -----------------------------------------------------------------------------
// Retrieve all Sensor Data
// -----------------------------------------------------------------------------
exports.findAllData = (req, res) => {
   const id = req.query.id;
   var condition = id ? { id: { [Op.like]: `%${id}%` } } : null;

   SensorData.findAll({ where: condition })
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while retrieving data."
      });
   });
};

// -----------------------------------------------------------------------------
// Retrieve one Sensor Data, by it's device Id
// -----------------------------------------------------------------------------
exports.findOneData = (req, res) => {
   const id = req.params.id;
   SensorData.findByPk(id)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message: "Error retrieving SensorData with id=" + id
      });
   });

};

// -----------------------------------------------------------------------------
// Retrieve all Sensor Data, which are assigned to a given site
// -----------------------------------------------------------------------------
exports.getDataBySite = (req, res) => {
   const id = req.params.siteId;
   var condition = {siteId: {[Op.eq]: id}};

   SensorData.findAll({ where: condition })
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while retrieving data."
      });
   });
}

// -----------------------------------------------------------------------------
// Sends the input JSON to the sensor device using MQTT publish
// -----------------------------------------------------------------------------
exports.mqtt = async (req,res) => {
   if (!req.body.id) {
      res.status(400).send({
         message: "Id can not be empty!"
      });
      return;
   }

   mqtt.sendMsgToSensor(req, (resp)=>{
      res.send(resp);
   });

}



/*
exports.updateLog = (req, res) => {
   const id = req.params.id;

   Sensor.update(req.body, {
      where: { id: id }
   })
   .then(num => {
      if (num == 1) {
         res.send({
            message: "Sensor was updated successfully."
         });
      } else {
         res.send({
            message: `Cannot update Sensor with id=${id}. Maybe Sensor was not found!`
         });
      }
   })
   .catch(err => {
      res.status(500).send({
         message: "Error updating Sensor with id=" + id
      });
   });
};
*/

/*
exports.deleteLog = (req, res) => {
   const id = req.params.id;

   Sensor.destroy({
      where: { id: id }
   })
   .then(num => {
      if (num == 1) {
         res.send({
            message: "Sensor was deleted successfully!"
         });
      } else {
         res.send({
            message: `Cannot delete Sensor with id=${id}. Maybe Sensor was not found!`
         });
      }
   })
   .catch(err => {
      res.status(500).send({
         message: "Could not delete Sensor with id=" + id
      });
   });
};
*/

exports.deleteAllLogs = (req, res) => {
   Sensor.destroy({
      where: {},
      truncate: false
   })
   .then(nums => {
      res.send({ message: `${nums} Sensors were deleted successfully!` });
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while removing all Sensors."
      });
   });
};




/*
exports.updateData = (req, res) => {
   const id = req.params.id;

   SensorData.update(req.body, {
      where: { id: id }
   })
   .then(num => {
      if (num == 1) {
         res.send({
            message: "SensorData was updated successfully."
         });
      } else {
         res.send({
            message: `Cannot update SensorData with id=${id}. Maybe it was not found!`
         });
      }
   })
   .catch(err => {
      res.status(500).send({
         message: "Error updating SensorData with id=" + id
      });
   });
};
*/

/*
exports.deleteData = (req, res) => {
   const id = req.params.id;

   SensorData.destroy({
      where: { id: id }
   })
   .then(num => {
      if (num == 1) {
         res.send({
            message: "SensorData was deleted successfully!"
         });
      } else {
         res.send({
            message: `Cannot delete SensorData with id=${id}. Maybe SensorData was not found!`
         });
      }
   })
   .catch(err => {
      res.status(500).send({
         message: "Could not delete SetValue with id=" + id
      });
   });
};
*/


exports.deleteAllData = (req, res) => {
   SensorData.destroy({
      where: {},
      truncate: false
   })
   .then(nums => {
      res.send({ message: `${nums} SensorData were deleted successfully!` });
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while removing all SensorData."
      });
   });
};
