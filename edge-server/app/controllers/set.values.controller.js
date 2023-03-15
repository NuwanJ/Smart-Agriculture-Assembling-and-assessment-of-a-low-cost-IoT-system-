const db = require("../services/database.js");

const SetValues = db.setValues;
const Op = db.Sequelize.Op;

exports.create = (req, res) => {
   if (!req.body.siteId) {
      res.status(400).send({
         message: "SiteId can not be empty!"
      });
      return;
   }
   const setvalues = {
      siteId: req.body.siteId,
      temp: req.body.temp,
      humidity: req.body.humidity,
      light: req.body.light,
      version: req.body.version
   };

   SetValues.create(setvalues)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while creating the SetValues."
      });
   });
};

exports.findAll = (req, res) => {
   const siteId = req.query.siteId;
   var condition = siteId ? { siteId: { [Op.like]: `%${siteId}%` } } : null;

   SetValues.findAll({ where: condition })
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

exports.findOne = (req, res) => {
   const id = req.params.id;
   SetValues.findByPk(id)
   .then(data => {
      res.send(data);
   })
   .catch(err => {
      res.status(500).send({
         message: "Error retrieving Sensor with siteId=" + id
      });
   });

};

exports.update = (req, res) => {
   const id = req.params.id;

   SetValues.update(req.body, {
      where: { siteId: id }
   })
   .then(num => {
      if (num == 1) {
         res.send({
            message: "SetValue was updated successfully."
         });
      } else {
         res.send({
            message: `Cannot update Sensor with siteId=${id}. Maybe it was not found!`
         });
      }
   })
   .catch(err => {
      res.status(500).send({
         message: "Error updating SetValue with siteId=" + id
      });
   });
};

exports.delete = (req, res) => {
   const id = req.params.id;

   SetValues.destroy({
      where: { siteId: id }
   })
   .then(num => {
      if (num == 1) {
         res.send({
            message: "SetValue was deleted successfully!"
         });
      } else {
         res.send({
            message: `Cannot delete SetValue with id=${id}. Maybe SetValue was not found!`
         });
      }
   })
   .catch(err => {
      res.status(500).send({
         message: "Could not delete SetValue with siteId=" + id
      });
   });
};

exports.deleteAll = (req, res) => {
   SetValues.destroy({
      where: {},
      truncate: false
   })
   .then(nums => {
      res.send({ message: `${nums} SetValues were deleted successfully!` });
   })
   .catch(err => {
      res.status(500).send({
         message:
         err.message || "Some error occurred while removing all SetValues."
      });
   });
};
