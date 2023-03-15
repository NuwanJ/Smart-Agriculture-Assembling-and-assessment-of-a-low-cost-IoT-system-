
const controller = require("../controllers/control.controller.js");
var router = require("express").Router();

// Create
router.post("/log/", controller.createLog);

// Select
router.get("/log/", controller.findAllLogs);
router.get("/log/:id", controller.findOneLog);

router.get("/log/device/:deviceId", controller.findById);

// Update via MQTT
router.post("/mqtt/", controller.mqtt);


// router.put("/:id", controller.update);
// router.delete("/:id", controller.delete);
// router.delete("/", controller.deleteAll);

module.exports = router;
