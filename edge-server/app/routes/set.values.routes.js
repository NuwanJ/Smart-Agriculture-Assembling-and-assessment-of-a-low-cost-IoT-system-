
const setValues = require("../controllers/set.values.controller.js");

var router = require("express").Router();

router.post("/", setValues.create);
router.get("/", setValues.findAll);

router.get("/:id", setValues.findOne);
router.put("/:id", setValues.update);
router.delete("/:id", setValues.delete);
router.delete("/", setValues.deleteAll);

module.exports = router;
