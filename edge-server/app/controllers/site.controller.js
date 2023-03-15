
const db = require("../services/database.js");

const Site = db.site;
const Op = db.Sequelize.Op;

// -----------------------------------------------------------------------------
// Creates  a new site
// -----------------------------------------------------------------------------
exports.create = (req, res) => {
   if (!req.body.id) {
      res.status(400).send({
         message: "id can not be empty!"
      });
      return;
   }
   const site = {
      id: req.body.id,
      title: req.body.title,
      controllerId: req.body.controllerId,
      width: req.body.width,
      length: req.body.length,
      status: req.body.status,
      notes: req.body.notes
   };
   Site.create(site)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while creating the Site."
      });
   });
};

// -----------------------------------------------------------------------------
// Retrieve all sites on the database.
// -----------------------------------------------------------------------------
exports.findAll = (req, res) => {
   const id = req.query.id;
   var condition = id ? { id: { [Op.like]: `%${id}%` } } : null;

   Site.findAll({ where: condition })
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
// Find a single Site entry using the id
// -----------------------------------------------------------------------------
exports.findOne = (req, res) => {
   const id = req.params.siteId;

   Site.findByPk(id)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message: "Error retrieving Site with id=" + id
      });
   });

};

// -----------------------------------------------------------------------------
// Process the controller states on a paticular site
// -----------------------------------------------------------------------------
/*exports.process = async (req, res) => {
   const id = req.params.siteId;

   if (!id) {
      res.status(400).send({
         message: "site Id can not be empty!" + JSON.stringify(req.body)
      });
      return;
   }

   process.siteControl(id, (resp)=>{
      res.send(resp);
   });

}*/

// Update a Sensor by the id in the request
/*
exports.update = (req, res) => {
   const id = req.params.id;

   Site.update(req.body, {
      where: { id: id }
   })
   .then(num => {
      if (num == 1) {
         res.send({
            message: "Site was updated successfully."
         });
      } else {
         res.send({
            message: `Cannot update Site with id=${id}. Maybe Site was not found!`
         });
      }
   })
   .catch(err => {
      res.status(500).send({
         message: "Error updating Site with id=" + id
      });
   });
};
*/

// Delete a Sensor with the specified id in the request
/*
exports.delete = (req, res) => {
   const id = req.params.id;

   Site.destroy({
      where: { id: id }
   })
   .then(num => {
      if (num == 1) {
         res.send({
            message: "Site was deleted successfully!"
         });
      } else {
         res.send({
            message: `Cannot delete Site with id=${id}. Maybe Site was not found!`
         });
      }
   })
   .catch(err => {
      res.status(500).send({
         message: "Could not delete Site with id=" + id
      });
   });
};
*/


// Delete all Sensors from the database.
/*
exports.deleteAll = (req, res) => {
   Site.destroy({
      where: {},
      truncate: false
   })
   .then(nums => {
      res.send({ message: `${nums} Sites were deleted successfully!` });
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while removing all Sites."
      });
   });
};
*/
