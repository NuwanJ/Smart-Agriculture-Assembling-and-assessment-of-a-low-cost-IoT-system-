const db = require("../services/database.js");
const mqtt = require("../services/mqtt.js");

const Control = db.controller;
const Op = db.Sequelize.Op;
const { QueryTypes } = require('sequelize');

// -----------------------------------------------------------------------------
// Creates  a new controller log
// -----------------------------------------------------------------------------
exports.createLog = (req, res) => {
   // Validate request
   if (!req.body.controllerId) {
      res.status(400).send({
         //console.log(req.body);
         message: "controllerId can not be empty!" + JSON.stringify(req.body)
      });
      return;
   }

   const control = {
      controllerId: req.body.controllerId,
      blower: req.body.blower.toString(),
      mist: req.body.mist.toString(),
      irrigation: req.body.irrigation.toString(),
      curtain: req.body.curtain.toString(),
      version: req.body.version
   };

   Control.create(control)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while creating the Controller."
      });
   });
};

// -----------------------------------------------------------------------------
// Retrieve all Control logs from the database.
// -----------------------------------------------------------------------------
exports.findAllLogs = (req, res) => {
   const controllerId = req.query.controllerId;
   var condition = controllerId ? { controllerId: { [Op.like]: `%${controllerId}%` } } : null;

   Control.findAll({ where: condition })
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while retrieving Control Log."
      });
   });

};

// -----------------------------------------------------------------------------
// Find a single Control Log entry using the id
// -----------------------------------------------------------------------------
exports.findOneLog = (req, res) => {
   const id = req.params.id;

   Control.findByPk(id)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message: "Error retrieving Control with id=" + id
      });
   });

};

// -----------------------------------------------------------------------------
// Retrieve one Sensor Data, by it's device Id
// -----------------------------------------------------------------------------
exports.findById = (req, res) => {
   const id =  req.params.deviceId;
   var condition = {controllerId: {[Op.eq]: id}};

console.log(id);

   Control.findAll({ where: condition })
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
// Sends the input JSON to the controller device using MQTT publish
// -----------------------------------------------------------------------------
exports.mqtt = async (req,res) => {
   if (!req.body.id) {
      res.status(400).send({
         message: "Id can not be empty!"
      });
      return;
   }
   mqtt.sendMsgToController(req, (resp)=>{
      res.send(resp);
   });
};


/*
exports.update = (req, res) => {
const id = req.params.id;

Control.update(req.body, {
where: { id: id }
})
.then(num => {
if (num == 1) {
res.send({
message: "Control log was updated successfully."
});
} else {
res.send({
message: `Cannot update Controller with id=${id}. Maybe Control log was not found!`
});
}
})
.catch(err => {
res.status(500).send({
message: "Error updating Controller with id=" + id
});
});
};
*/



/*
exports.delete = (req, res) => {
const id = req.params.id;

Control.destroy({
where: { id: id }
})
.then(num => {
if (num == 1) {
res.send({
message: "Controller log was deleted successfully!"
});
} else {
res.send({
message: `Cannot delete Sensor with id=${id}. Maybe Controller was not found!`
});
}
})
.catch(err => {
res.status(500).send({
message: "Could not delete Controller log with id=" + id
});
});
};
*/



/*
exports.deleteAll = (req, res) => {
Control.destroy({
where: {},
truncate: false
})
.then(nums => {
res.send({ message: `${nums} Controllers were deleted successfully!` });
})
.catch(err => {
res.status(500).send({
message:
err.message || "Some error occurred while removing all Controllers."
});
});
};
*/
