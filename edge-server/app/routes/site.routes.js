
const site = require("../controllers/site.controller.js");

var router = require("express").Router();

// Create
router.post("/", site.create);

// Select
router.get("/", site.findAll);
router.get("/:siteId", site.findOne);

// router.put("/:id", site.update);
// router.delete("/:id", site.delete);
// router.delete("/", site.deleteAll);

module.exports = router;
