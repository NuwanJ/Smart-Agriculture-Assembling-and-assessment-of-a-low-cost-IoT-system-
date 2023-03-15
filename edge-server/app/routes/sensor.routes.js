
const sensors = require("../controllers/sensor.controller.js");
var router = require("express").Router();


// Create a sensor
router.post("/log/", sensors.createLog);

// Create a new sensor log entry
router.post("/data/", sensors.createSensor);

// Select log entrie(s)
router.get("/log/", sensors.findAllLogs);
router.get("/log/:id", sensors.findOneLog);

router.get("/log/device/:deviceId", sensors.getLogsByDevice);
router.get("/log/site/:siteId", sensors.getLogsBySiteLatest);
router.get("/log/latest/:deviceId", sensors.getLogLatest);

// Select sensor(s)
router.get("/data/", sensors.findAllData);
router.get("/data/:id", sensors.findOneData);
router.get("/data/site/:siteId", sensors.getDataBySite);

router.post("/mqtt/", sensors.mqtt);

// router.put("/log/:id", sensors.updateLog);
// router.delete("/log/:id", sensors.deleteLog);
router.delete("/log/", sensors.deleteAllLogs);

// router.put("/data/:id", sensors.updateData);
// router.delete("/data/:id", sensors.deleteData);
router.delete("/data/", sensors.deleteAllData);

module.exports = router;
